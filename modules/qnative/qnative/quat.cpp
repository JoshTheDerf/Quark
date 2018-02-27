/*************************************************************************/
/*  quat.cpp                                                             */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
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

#include "qnative/quat.h"

#include "core/math/quat.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_quat_new(quark_quat *r_dest, const quark_real p_x, const quark_real p_y, const quark_real p_z, const quark_real p_w) {

	Quat *dest = (Quat *)r_dest;
	*dest = Quat(p_x, p_y, p_z, p_w);
}

void QAPI quark_quat_new_with_axis_angle(quark_quat *r_dest, const quark_vector3 *p_axis, const quark_real p_angle) {
	const Vector3 *axis = (const Vector3 *)p_axis;
	Quat *dest = (Quat *)r_dest;
	*dest = Quat(*axis, p_angle);
}

quark_real QAPI quark_quat_get_x(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->x;
}

void QAPI quark_quat_set_x(quark_quat *p_self, const quark_real val) {
	Quat *self = (Quat *)p_self;
	self->x = val;
}

quark_real QAPI quark_quat_get_y(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->y;
}

void QAPI quark_quat_set_y(quark_quat *p_self, const quark_real val) {
	Quat *self = (Quat *)p_self;
	self->y = val;
}

quark_real QAPI quark_quat_get_z(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->z;
}

void QAPI quark_quat_set_z(quark_quat *p_self, const quark_real val) {
	Quat *self = (Quat *)p_self;
	self->z = val;
}

quark_real QAPI quark_quat_get_w(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->w;
}

void QAPI quark_quat_set_w(quark_quat *p_self, const quark_real val) {
	Quat *self = (Quat *)p_self;
	self->w = val;
}

quark_string QAPI quark_quat_as_string(const quark_quat *p_self) {
	quark_string ret;
	const Quat *self = (const Quat *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_real QAPI quark_quat_length(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->length();
}

quark_real QAPI quark_quat_length_squared(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->length_squared();
}

quark_quat QAPI quark_quat_normalized(const quark_quat *p_self) {
	quark_quat dest;
	const Quat *self = (const Quat *)p_self;
	*((Quat *)&dest) = self->normalized();
	return dest;
}

quark_bool QAPI quark_quat_is_normalized(const quark_quat *p_self) {
	const Quat *self = (const Quat *)p_self;
	return self->is_normalized();
}

quark_quat QAPI quark_quat_inverse(const quark_quat *p_self) {
	quark_quat dest;
	const Quat *self = (const Quat *)p_self;
	*((Quat *)&dest) = self->inverse();
	return dest;
}

quark_real QAPI quark_quat_dot(const quark_quat *p_self, const quark_quat *p_b) {
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	return self->dot(*b);
}

quark_vector3 QAPI quark_quat_xform(const quark_quat *p_self, const quark_vector3 *p_v) {
	quark_vector3 dest;
	const Quat *self = (const Quat *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*((Vector3 *)&dest) = self->xform(*v);
	return dest;
}

quark_quat QAPI quark_quat_slerp(const quark_quat *p_self, const quark_quat *p_b, const quark_real p_t) {
	quark_quat dest;
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	*((Quat *)&dest) = self->slerp(*b, p_t);
	return dest;
}

quark_quat QAPI quark_quat_slerpni(const quark_quat *p_self, const quark_quat *p_b, const quark_real p_t) {
	quark_quat dest;
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	*((Quat *)&dest) = self->slerpni(*b, p_t);
	return dest;
}

quark_quat QAPI quark_quat_cubic_slerp(const quark_quat *p_self, const quark_quat *p_b, const quark_quat *p_pre_a, const quark_quat *p_post_b, const quark_real p_t) {
	quark_quat dest;
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	const Quat *pre_a = (const Quat *)p_pre_a;
	const Quat *post_b = (const Quat *)p_post_b;
	*((Quat *)&dest) = self->cubic_slerp(*b, *pre_a, *post_b, p_t);
	return dest;
}

quark_quat QAPI quark_quat_operator_multiply(const quark_quat *p_self, const quark_real p_b) {
	quark_quat raw_dest;
	Quat *dest = (Quat *)&raw_dest;
	const Quat *self = (const Quat *)p_self;
	*dest = *self * p_b;
	return raw_dest;
}

quark_quat QAPI quark_quat_operator_add(const quark_quat *p_self, const quark_quat *p_b) {
	quark_quat raw_dest;
	Quat *dest = (Quat *)&raw_dest;
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	*dest = *self + *b;
	return raw_dest;
}

quark_quat QAPI quark_quat_operator_subtract(const quark_quat *p_self, const quark_quat *p_b) {
	quark_quat raw_dest;
	Quat *dest = (Quat *)&raw_dest;
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	*dest = *self - *b;
	return raw_dest;
}

quark_quat QAPI quark_quat_operator_divide(const quark_quat *p_self, const quark_real p_b) {
	quark_quat raw_dest;
	Quat *dest = (Quat *)&raw_dest;
	const Quat *self = (const Quat *)p_self;
	*dest = *self / p_b;
	return raw_dest;
}

quark_bool QAPI quark_quat_operator_equal(const quark_quat *p_self, const quark_quat *p_b) {
	const Quat *self = (const Quat *)p_self;
	const Quat *b = (const Quat *)p_b;
	return *self == *b;
}

quark_quat QAPI quark_quat_operator_neg(const quark_quat *p_self) {
	quark_quat raw_dest;
	Quat *dest = (Quat *)&raw_dest;
	const Quat *self = (const Quat *)p_self;
	*dest = -(*self);
	return raw_dest;
}

#ifdef __cplusplus
}
#endif
