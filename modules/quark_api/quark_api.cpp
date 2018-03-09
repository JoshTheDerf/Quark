#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdexcept>
#include <cassert>

#include "include/quark_api.h"

typedef struct Atom Atom;

struct Atom {
	enum AtomType {
		TYPE_LIST,
		TYPE_SYMBOL,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT
	};
	AtomType type;
	char* start;
	uint64_t len;
	int first_child_index;
	int next_sibling_index;
};

typedef struct {
	enum CallTypes {
		CALL_TYPE_INSTANCE,
		CALL_TYPE_CALL,
		CALL_TYPE_EVENT,
	};
	CallTypes type;
	char* head;
} CallType;

std::vector<Atom> atom_vec;

int parse_string(std::vector<Atom>& atom_vector, int& vector_tail, char*& loc) {
	loc++;

	vector_tail++;
	unsigned int curr_atom_index = vector_tail;

	// The atom index should always be less than or equal to the size of the vector.
	// Otherwise we have a bug.
	assert(0 <= atom_vector.size() - curr_atom_index);
	// If the index is equal to the size, we need to allocate a new atom.
	if (atom_vector.size() == curr_atom_index) atom_vector.emplace_back();

	// We have to make sure everything gets initialized to the correct values in here.
	// because we are potentially reusing atoms from previous calls.
	Atom& a = atom_vector.at(curr_atom_index);
	a.start = loc;
	a.type = Atom::TYPE_STRING;
	a.first_child_index = -1;
	a.next_sibling_index = -1;

	bool escape;

	while(*loc != '\0' && (*loc != '"' || escape)) {
		if(escape) escape = false;
		// Allow backslash-escaping.
		// Currently doesn't remove the backslash from the actual string yet...
		if(*loc == '\\') escape = true;

		loc++;
	}

	a.len = loc - a.start;

	// Skip over the trailing doublquote ".
	loc++;

	return curr_atom_index;
}

int parse_symbol(std::vector<Atom>& atom_vector, int& vector_tail, char*& loc) {
	vector_tail++;
	unsigned int curr_atom_index = vector_tail;

	// The atom index should always be less than or equal to the size of the vector.
	// Otherwise we have a bug.
	assert(0 <= atom_vector.size() - curr_atom_index);
	// If the index is equal to the size, we need to allocate a new atom.
	if (atom_vector.size() == curr_atom_index) atom_vector.emplace_back();

	// We have to make sure everything gets initialized to the correct values in here.
	// because we are potentially reusing atoms from previous calls.
	Atom& a = atom_vector.at(curr_atom_index);
	a.start = loc;
	a.type = Atom::TYPE_SYMBOL;
	a.first_child_index = -1;
	a.next_sibling_index = -1;

	// -1 not set, 0 not number, 1 int, 2 float.
	char is_number_type = -1;

	while(*loc != '\0' && *loc != ' ' && *loc != ')') {
		// If we haven't set a type yet (first char, usually)
		// assume this is a int if the char is a digit.
		if (isdigit(*loc) && is_number_type == -1) {
			is_number_type = 1;
		// If the number type is unset or an int, and the character is a point (.)
		// assume this is a float.
		} else if (*loc == '.' && abs(is_number_type) == 1) {
			is_number_type = 2;
		// In any other case, if the char isn't a digit, this should be treated
		// as a normal symbol.
		} else if (!isdigit(*loc)) {
			is_number_type = 0;
		}

		loc++;
	}

	if(is_number_type == 1) a.type = Atom::TYPE_INT;
	else if (is_number_type == 2) a.type = Atom::TYPE_FLOAT;

	a.len = loc - a.start;

	return curr_atom_index;
}

int parse_list(std::vector<Atom>& atom_vector, int& vector_tail, char*& loc) {
	loc++;

	vector_tail++;
	unsigned int curr_atom_index = vector_tail;

	// The atom index should always be less than or equal to the size of the vector.
	// Otherwise we have a bug.
	assert(0 <= atom_vector.size() - curr_atom_index);
	// If the index is equal to the size, we need to allocate a new atom.
	if (atom_vector.size() == curr_atom_index) atom_vector.emplace_back();

	// We have to make sure everything gets initialized to the correct values in here.
	// because we are potentially reusing atoms from previous calls.
	Atom& a = atom_vector.at(curr_atom_index);
	a.start = loc;
	a.type = Atom::TYPE_LIST;
	a.first_child_index = -1;
	a.next_sibling_index = -1;

	bool stop_iter = false;

	int prev_sibling_index = -1;
	int active_atom_index = -1;

	while(*loc != '\0' && !stop_iter) {
		switch(*loc) {
			case '(':
				active_atom_index = parse_list(atom_vector, vector_tail, loc);
				break;
			case ')':
				loc++;
				active_atom_index = -1;
				prev_sibling_index = -1;
				stop_iter = true;
				break;
			case '"':
				active_atom_index = parse_string(atom_vector, vector_tail, loc);
				break;
			case ' ':
				loc++;
				break;
			default:
				active_atom_index = parse_symbol(atom_vector, vector_tail, loc);
		}

		if(active_atom_index == -1) continue;

		// This should always be called for the first child atom.
		if(a.first_child_index == -1) a.first_child_index = active_atom_index;
		// The prev sibling index should always be set by the second atom.
		else atom_vector.at(prev_sibling_index).next_sibling_index = active_atom_index;

		prev_sibling_index = active_atom_index;
	}

	return curr_atom_index;
}

Atom& parse_sexpr(std::vector<Atom>& atom_vector, char*& loc) {
	// We have to check just in-case some of the root elements are not a list.
	// (Assuming the root element isn't denoted with parenthesis.)

	int prev_sibling_index = -1;
	int active_atom_index = -1;
	int vector_tail = -1;

	while(*loc != '\0') {
		switch(*loc) {
			case '(':
				active_atom_index = parse_list(atom_vector, vector_tail, loc);
				break;
			case '"':
				active_atom_index = parse_string(atom_vector, vector_tail, loc);
				break;
			case ' ':
				loc++;
				break;
			default:
				active_atom_index = parse_symbol(atom_vector, vector_tail, loc);
		}

		if(active_atom_index == -1) continue;

		if(prev_sibling_index != -1)
			atom_vector.at(prev_sibling_index).next_sibling_index = active_atom_index;

		prev_sibling_index = active_atom_index;
	}

	// Currently we don't handle the case where an empty string is passed.
	assert(atom_vector.size() > 0);
	return atom_vector.at(0);
}

void print_sexpr(std::vector<Atom>& atom_vector, Atom& atom, int level = 0) {
	switch(atom.type) {
		case Atom::TYPE_LIST:
			printf("\n");
			for(int i = 0; i < level; ++i) printf("  "); 
			printf("<");
			if (atom.first_child_index != -1) {
				print_sexpr(atom_vector, atom_vector.at(atom.first_child_index), level + 1);
			}
			printf(">");
			// Sorry, it's just so convenient here.
			goto print_siblings;
		case Atom::TYPE_SYMBOL:
			printf("m:");
			break;
		case Atom::TYPE_STRING:
			printf("s:");
			break;
		case Atom::TYPE_INT:
			printf("i:");
			break;
		case Atom::TYPE_FLOAT:
			printf("f:");
			break;
		default:
			break;
	}

	printf("%.*s", atom.len, atom.start);

print_siblings:
	if (atom.next_sibling_index != -1) {
		printf(" ");
		print_sexpr(atom_vector, atom_vector.at(atom.next_sibling_index), level);
	}
}

uint32_t QAPI quark_api_init(void(*notify_handler)(char*)) {
	notify_handler("Test Output");
	return 1;
}

char* QAPI quark_api_call(uint32_t user_id, char* message) {
	printf("User ID: %i\n", user_id);
	atom_vec.reserve(500);

	if (message == NULL) return NULL;

	Atom& root_atom = parse_sexpr(atom_vec, message);
	print_sexpr(atom_vec, root_atom);
	printf("\n");

	return "Output";
}
