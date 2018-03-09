#include "parser.h"
#include <cassert>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int SexpParser::parse_string(int& vector_tail, char*& loc) {
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

	// Skip over the trailing doublequote ".
	loc++;

	return curr_atom_index;
}

int SexpParser::parse_symbol(int& vector_tail, char*& loc) {
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

int SexpParser::parse_list(int& vector_tail, char*& loc) {
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
				active_atom_index = parse_list(vector_tail, loc);
				break;
			case ')':
				loc++;
				active_atom_index = -1;
				prev_sibling_index = -1;
				stop_iter = true;
				break;
			case '"':
				active_atom_index = parse_string(vector_tail, loc);
				break;
			case ' ':
				loc++;
				break;
			default:
				active_atom_index = parse_symbol(vector_tail, loc);
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

SexpParser::Atom& SexpParser::parse_sexpr(char*& message) {
	int prev_sibling_index = -1;
	int active_atom_index = -1;
	int vector_tail = -1;
	char* loc = message;

	while(*loc != '\0') {
		switch(*loc) {
			case '(':
				active_atom_index = parse_list(vector_tail, loc);
				break;
			case '"':
				active_atom_index = parse_string(vector_tail, loc);
				break;
			case ' ':
				loc++;
				break;
			default:
				active_atom_index = parse_symbol(vector_tail, loc);
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

SexpParser::Atom& SexpParser::get_atom(int atom_index) {
	return atom_vector.at(atom_index);
}

void SexpParser::print_sexpr(SexpParser::Atom& atom, int level) {
	switch(atom.type) {
		case Atom::TYPE_LIST:
			printf("\n");
			for(int i = 0; i < level; ++i) printf("  "); 
			printf("<");
			if (atom.first_child_index != -1) {
				print_sexpr(atom_vector.at(atom.first_child_index), level + 1);
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
	}

	printf("%.*s", atom.len, atom.start);

print_siblings:
	if (atom.next_sibling_index != -1) {
		printf(" ");
		print_sexpr(atom_vector.at(atom.next_sibling_index), level);
	}
}

SexpParser::SexpParser() {
	atom_vector.reserve(500);
}

SexpParser::~SexpParser() {
	atom_vector.clear();
}
