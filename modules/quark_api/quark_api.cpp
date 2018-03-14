/*************************************************************************/
/*  quark_api.cpp                                                        */
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

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

#include "core/ustring.h"
#include "core/variant.h"
#include "core/object.h"

#include "include/quark_api.h"
#include "parser/parser.h"
#include "quark_user_proxy.h"
#include "quark_user_data.h"

SexpParser parser;
std::vector<QuarkUserData> user_data_vec;

// This is copied to a char buffer for sending the response, then cleared & re-used on subsequent calls.
std::string response_string;

uint32_t QAPI quark_api_init(void(*notify_handler)(char*)) {
	user_data_vec.emplace_back();
	QuarkUserData& udata = user_data_vec.back();
	udata.id = user_data_vec.size() - 1;
	udata.notify_handler = notify_handler;
	udata.proxy_object = memnew(QuarkUserProxy);
	udata.proxy_object->set_userdata(&udata);

	return udata.id;
}

Variant get_variant_from_atom(SexpParser::Atom& atom) {
	switch (atom.type) {
		case SexpParser::Atom::TYPE_STRING:
			return String(atom.start, atom.len);
		default:
			printf("%s\n", "EMPTY VARIANT");
			return Variant();
	}
}

void handle_call(SexpParser::Atom& atom, QuarkUserData& udata, std::ostringstream& out) {
	if (atom.next_sibling_index == -1) {
		out << "(error \"The first argument to 'call' must be an object id\")";
		return;
	}

	SexpParser::Atom& objectid_atom = parser.get_atom(atom.next_sibling_index);
	if (objectid_atom.type != SexpParser::Atom::TYPE_INT) {
		out << "(error \"The first argument to 'call' must be an object id\")";
		return;
	}

	ObjectID object_id = ObjectID(atoi(objectid_atom.start));

	SexpParser::Atom& method_atom = parser.get_atom(objectid_atom.next_sibling_index);
	if (method_atom.type != SexpParser::Atom::TYPE_STRING) {
		out << "(error \"The second argument to 'call' must be a string\")";
		return;
	}

	String method = String(method_atom.start, method_atom.len);

	Array args;

	if (method_atom.next_sibling_index != -1) {
		SexpParser::Atom* arg_atom = &parser.get_atom(method_atom.next_sibling_index);

		while(arg_atom != NULL) {
			args.push_back(get_variant_from_atom(*arg_atom));

			if (arg_atom->next_sibling_index == -1) arg_atom = NULL;
			else arg_atom = &parser.get_atom(arg_atom->next_sibling_index);
		}
	};

	Object* obj = ObjectDB::get_instance(object_id);

	if(obj == NULL) {
		out << "(error \"Unable to locate object with id: "<< object_id << "\")";
		return;
	}

	obj->callv(method, args);

	out << "()"; // TODO: Implement casting responses.
}

void handle_instance(SexpParser::Atom& atom, QuarkUserData& udata, std::ostringstream& out) {
	if (atom.next_sibling_index == -1) {
		out << "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";
		return;
	}

	SexpParser::Atom& classname_atom = parser.get_atom(atom.next_sibling_index);
	if (classname_atom.type != SexpParser::Atom::TYPE_STRING) {
		out << "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";
		return;
	}

	String classname = (String) get_variant_from_atom(classname_atom);

	Object* instance = ClassDB::instance(classname);

	if(instance == NULL) {
		out << "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";
		return;
	}

	out << "(ref " << (int) instance->get_instance_id() << ")";
}

void handle_event(SexpParser::Atom& atom, QuarkUserData& udata, std::ostringstream& out) {
	if (atom.next_sibling_index == -1) {
		out << "(error \"The first argument to 'evt' must be an object id\")";
		return;
	}

	SexpParser::Atom& objectid_atom = parser.get_atom(atom.next_sibling_index);
	if (objectid_atom.type != SexpParser::Atom::TYPE_INT) {
		out << "(error \"The first argument to 'evt' must be an object id\")";
		return;
	}

	ObjectID object_id = ObjectID(atoi(objectid_atom.start));

	SexpParser::Atom& signal_atom = parser.get_atom(objectid_atom.next_sibling_index);
	if (signal_atom.type != SexpParser::Atom::TYPE_STRING) {
		out << "(error \"The second argument to 'evt' must be a string\")";
		return;
	}

	String signal = String(signal_atom.start, signal_atom.len);

	Object* obj = ObjectDB::get_instance(object_id);

	if(obj == NULL) {
		out << "(error \"Unable to locate object with id: "<< object_id << "\")";
		return;
	}

	obj->connect(signal, udata.proxy_object, "handle_signal", Vector<Variant>(), Object::CONNECT_COMBINED_ARGS);

	out << "()";
}

void handle_message(SexpParser::Atom& atom, QuarkUserData& udata, std::ostringstream& out) {

	if(atom.type != SexpParser::Atom::TYPE_LIST || atom.first_child_index == -1) {
		out << "(error \"No valid command passed. Valid commands are: [call]\")";
		return;
	}

	SexpParser::Atom& first_child = parser.get_atom(atom.first_child_index);
	if (first_child.type != SexpParser::Atom::TYPE_SYMBOL) {
		out << "(error \"Commands must be a symbols.\")";
		return;
	}

	if (strncmp("call", first_child.start, first_child.len) == 0)
		handle_call(first_child, udata, out);
	else if (strncmp("inst", first_child.start, first_child.len) == 0)
		handle_instance(first_child, udata, out);
	else if (strncmp("evt", first_child.start, first_child.len) == 0)
		handle_event(first_child, udata, out);
	else out << "(error \"No valid command passed. Valid commands are: [call]\")";

	return;
}

void build_response(char* res_buf, uint64_t res_buf_size, std::ostringstream& response) {
	size_t copied = response.str().copy(res_buf, res_buf_size);
	res_buf[copied] = '\0';
}

char* QAPI quark_api_call(uint32_t user_id, char* message, char* response_buf, uint64_t response_buf_size) {
	response_string.clear();

	if (message == NULL) return NULL;

	QuarkUserData& udata = user_data_vec.at(user_id);
	printf("User ID: %u\n", udata.id);

	SexpParser::Atom& root_atom = parser.parse_sexpr(message);
	parser.print_sexpr(root_atom);
	printf("\n");

	std::ostringstream out;
	SexpParser::Atom* current_atom = &root_atom;

	while (current_atom != NULL) {
		handle_message(*current_atom, udata, out);

		if(current_atom->next_sibling_index == -1) current_atom = NULL;
		else current_atom = &parser.get_atom(current_atom->next_sibling_index);
	}

	build_response(response_buf, response_buf_size, out);

	return response_buf;
}
