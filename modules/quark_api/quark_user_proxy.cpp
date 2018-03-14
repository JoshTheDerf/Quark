/*************************************************************************/
/*  quark_user_proxy.cpp                                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                          QUARK TOOLKIT                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include <sstream>
#include <string>
#include <iostream>

#include "quark_user_proxy.h"

void encode_type(std::ostringstream &os, Object* obj, Dictionary& prop_dict) {
	Variant data = obj->get(prop_dict["name"]);
	int type = prop_dict["type"];

	if (type == Variant::NIL || type == Variant::OBJECT) return;

	os << " (\"" << ((String) prop_dict["name"]).utf8().get_data() << "\"";

	switch(type) {
		// atomic types
		case Variant::BOOL: {
			bool b = (bool) data;
			os << (b ? " true" : " false");
		} break;

		case Variant::INT: {
			int i = (int) data;
			os << " " << i;
		} break;

		case Variant::REAL: {
			float r = (float) data;
			os << " " << r;
		} break;

		case Variant::STRING: {
			String s = (String) data;
			os << " \"" << s.utf8().get_data() << "\"";
		} break;

		case Variant::VECTOR2: {
			Vector2 v2 = (Vector2) data;
			os << " (v2 " << v2.x << " " << v2.y << ")";
		} break;

		case Variant::RECT2: {
			Rect2 r2 = (Rect2) data;
			const Vector2 pos = r2.get_position();
			const Vector2 size = r2.get_size();
			os << " (r2 " << pos.x << " " << pos.y << " " << size.width << " " << size.height << ")";
		} break;

		case Variant::VECTOR3: {
			Vector3 v3 = (Vector3) data;
			os << " (v3 " << v3.x << " " << v3.y << " " << v3.z << ")";
		} break;
		// math types

		// VECTOR2, // 5
		// RECT2,
		// VECTOR3,
		// TRANSFORM2D,
		// PLANE,
		// QUAT, // 10
		// AABB,
		// BASIS,
		// TRANSFORM,

		// // misc types
		// COLOR,
		// NODE_PATH, // 15
		// _RID,
		// OBJECT,
		// DICTIONARY,
		// ARRAY,

		// // arrays
		// POOL_BYTE_ARRAY, // 20
		// POOL_INT_ARRAY,
		// POOL_REAL_ARRAY,
		// POOL_STRING_ARRAY,
		// POOL_VECTOR2_ARRAY,
		// POOL_VECTOR3_ARRAY, // 25
		// POOL_COLOR_ARRAY,
	}

	os << ")";
}

void QuarkUserProxy::handle_signal(Variant var) {
	Array arr = (Array) var;

	printf("Num Args: %i\n", arr.size());

	std::ostringstream os;
	os << "(evt";

	Object* target = arr[0];
	os << " " << target->get_instance_id();

	for (int i = 1; i < arr.size(); i++) {
		Variant v = arr[i];

		if(v.get_type() ==  Variant::OBJECT) {
			Object* o = v;
			String class_name = (String) o->get_class_name();
			List<PropertyInfo> properties;
			o->get_property_list(&properties);
			os << " (obj \"" << class_name.utf8().get_data() << "\"";

			for (int j = 0; j < properties.size(); j++) {
				Dictionary prop_dict = (Dictionary) properties[j];
				encode_type(os, o, prop_dict);
			}

			os << ")";
		}
	}

	os << ")";

	user_data->notify_handler((char*) os.str().c_str());
};

void QuarkUserProxy::handle_notification() {
	printf("%s\n", "Notiication Recieved");
};
void QuarkUserProxy::set_userdata(QuarkUserData* data) {
	user_data = data;
};

QuarkUserData* QuarkUserProxy::get_userdata() {
	return user_data;
}

void QuarkUserProxy::_bind_methods() {
	ClassDB::bind_method(D_METHOD("handle_signal"), &QuarkUserProxy::handle_signal);
	ClassDB::bind_method(D_METHOD("handle_notification"), &QuarkUserProxy::handle_notification);
}

QuarkUserProxy::QuarkUserProxy() {}
QuarkUserProxy::~QuarkUserProxy() {}
