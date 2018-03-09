#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

#include "include/quark_api.h"
#include "parser/parser.h"
#include "core/ustring.h"
#include "core/variant.h"
#include "core/object.h"

typedef struct {
	enum CallTypes {
		CALL_TYPE_INSTANCE,
		CALL_TYPE_CALL,
		CALL_TYPE_GET_OBJECTID,
		CALL_TYPE_EVENT,
	};
	CallTypes type;
	char* head;
} CallType;

typedef struct {
	uint32_t id;
} UserData;

SexpParser parser;
std::vector<UserData> user_data_vec;

// This is copied to a char buffer for sending the response, then cleared & re-used on subsequent calls.
std::string response_string;

uint32_t QAPI quark_api_init(void(*notify_handler)(char*)) {
	notify_handler("Test Output");

	user_data_vec.emplace_back();
	UserData& udata = user_data_vec.back();
	udata.id = user_data_vec.size() - 1;

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

std::string handle_call(SexpParser::Atom& atom) {
	if (atom.next_sibling_index == -1) return "(error \"The first argument to 'call' must be an object id\")";;

	SexpParser::Atom& objectid_atom = parser.get_atom(atom.next_sibling_index);
	if (objectid_atom.type != SexpParser::Atom::TYPE_INT)
		return "(error \"The first argument to 'call' must be an object id\")";

	ObjectID object_id = ObjectID(atoi(objectid_atom.start));

	SexpParser::Atom& method_atom = parser.get_atom(objectid_atom.next_sibling_index);
	if (method_atom.type != SexpParser::Atom::TYPE_STRING)
		return "(error \"The second argument to 'call' must be a string\")";

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
		return "(error \"Unable to locate object with specified id\")";
	}

	obj->callv(method, args);

	return "(call successful)";
}

std::string handle_instance(SexpParser::Atom& atom) {
	if (atom.next_sibling_index == -1)
		return "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";

	SexpParser::Atom& classname_atom = parser.get_atom(atom.next_sibling_index);
	if (classname_atom.type != SexpParser::Atom::TYPE_STRING)
		return "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";

	String classname = (String) get_variant_from_atom(classname_atom);

	Object* instance = ClassDB::instance(classname);

	if(instance == NULL)
		return "(error \"The first argument to 'instance' must be a string indicating the object to instance.\")";

	return std::string("(ref ") + std::to_string((int) instance->get_instance_id()) + ")";
}

std::string handle_message(SexpParser::Atom& atom) {

	if(atom.type != SexpParser::Atom::TYPE_LIST || atom.first_child_index == -1)
		return "(error \"No valid command passed. Valid commands are: [call]\")";

	SexpParser::Atom& first_child = parser.get_atom(atom.first_child_index);
	if (first_child.type != SexpParser::Atom::TYPE_SYMBOL)
		return "(error \"Commands must be a symbols.\")";

	if (strncmp("call", first_child.start, first_child.len) == 0)
		return handle_call(first_child);
	else if (strncmp("inst", first_child.start, first_child.len) == 0)
		return handle_instance(first_child);

	return "(error \"No valid command passed. Valid commands are: [call]\")";
}

void build_response(char* res_buf, uint64_t res_buf_size, std::string response) {
	size_t copied = response.copy(res_buf, res_buf_size);
	res_buf[copied] = '\0';
}

char* QAPI quark_api_call(uint32_t user_id, char* message, char* response_buf, uint64_t response_buf_size) {
	response_string.clear();

	if (message == NULL) return NULL;

	UserData& udata = user_data_vec.at(user_id);
	printf("User ID: %u\n", udata.id);

	SexpParser::Atom& root_atom = parser.parse_sexpr(message);
	parser.print_sexpr(root_atom);
	printf("\n");

	std::ostringstream os;

	SexpParser::Atom* current_atom = &root_atom;

	while (current_atom != NULL) {
		response_string += handle_message(*current_atom);

		if(current_atom->next_sibling_index == -1) current_atom = NULL;
		else current_atom = &parser.get_atom(current_atom->next_sibling_index);
	}

	build_response(response_buf, response_buf_size, response_string);

	return response_buf;
}
