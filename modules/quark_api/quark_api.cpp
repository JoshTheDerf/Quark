#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdexcept>

#include "include/quark_api.h"

typedef struct Atom Atom;

struct Atom {
	enum SexprType {
		TYPE_LIST,
		TYPE_SYMBOL,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT
	};
	SexprType type;
	char* start;
	uint64_t len;
	std::vector<Atom*> children;
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

std::vector<Atom> atomVec;

Atom* parse_string(std::vector<Atom>* atomVector, char** loc) {
	(*loc)++;

	atomVector->emplace_back();
	Atom* a = &atomVector->back();
	a->start = *loc;
	a->type = Atom::TYPE_STRING;

	bool escape;

	while(**loc != '\0' && (**loc != '"' || escape)) {
		if(escape) escape = false;
		// Allow backslash-escaping.
		// Currently doesn't remove the backslash from the actual string yet...
		if(**loc == '\\') escape = true;

		(*loc)++;
	}

	a->len = *loc - a->start;

	// Skip over the following " if needed.
	(*loc)++;

	return a;
}

Atom* parse_symbol(std::vector<Atom>* atomVector, char** loc) {
	atomVector->emplace_back();
	Atom* a = &atomVector->back();
	a->start = *loc;
	a->type = Atom::TYPE_SYMBOL;

	// -1 not set, 0 not number, 1 int, 2 float.
	char is_number_type = -1;

	while(**loc != '\0' && **loc != ' ' && **loc != ')') {
		// If we haven't set a type yet (first char, usually)
		// assume this is a int if the char is a digit.
		if (isdigit(**loc) && is_number_type == -1) {
			is_number_type = 1;
		// If the number type is unset or an int, and the character is a point (.)
		// assume this is a float.
		} else if (**loc == '.' && abs(is_number_type) == 1) {
			is_number_type = 2;
		// In any other case, if the char isn't a digit, this should be treated
		// as a normal symbol.
		} else if (!isdigit(**loc)) {
			is_number_type = 0;
		}

		(*loc)++;
	}

	if(is_number_type == 1) a->type = Atom::TYPE_INT;
	else if (is_number_type == 2) a->type = Atom::TYPE_FLOAT;

	a->len = *loc - a->start;

	return a;
}

Atom* parse_list(std::vector<Atom>* atomVector, char** loc) {
	(*loc)++;

	atomVector->emplace_back();
	Atom* a = &atomVector->back();
	a->type = Atom::TYPE_LIST;

	bool stop_iter = false;

	while(**loc != '\0' && !stop_iter) {
		switch(**loc) {
			case '(':
				a->children.push_back(parse_list(atomVector, loc));
				continue;
			case ')':
				(*loc)++;
				stop_iter = true;
				break;
			case '"':
				a->children.push_back(parse_string(atomVector, loc));
				continue;
			case ' ':
				(*loc)++;
				continue;
			default:
				a->children.push_back(parse_symbol(atomVector, loc));
				continue;
		}
	}

	return a;
}

Atom* parse_sexpr(std::vector<Atom>* atomVector, char** loc) {
	atomVector->emplace_back();
	Atom* a = &atomVector->back();

	// We have to check just in-case some of the root elements are not a list.
	// (Assuming the root element isn't denoted with parenthesis.)
	while(**loc != '\0') {
		switch(**loc) {
			case '(':
				a->children.push_back(parse_list(atomVector, loc));
				continue;
			case '"':
				a->children.push_back(parse_string(atomVector, loc));
				continue;
			case ' ':
				(*loc)++;
				continue;
			default:
				a->children.push_back(parse_symbol(atomVector, loc));
				continue;
		}
	}

	return a;
}

void print_sexpr(Atom* atom) {
	if (atom->type == Atom::TYPE_LIST) {
		printf("<");
		for (Atom* const child : atom->children) {
			print_sexpr(child);
			if(child != atom->children.back()) printf(" ");
		}
		printf(">");
	} else {
		switch(atom->type) {
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

		printf("%.*s", atom->len, atom->start);
	}
}

uint32_t QAPI quark_api_init(void(*notify_handler)(char*)) {
	notify_handler("Test Output");
	return 1;
}

char* QAPI quark_api_call(uint32_t user_id, char* message) {
	printf("User ID: %i\n", user_id);
	atomVec.reserve(500);

	if (message == NULL) return NULL;

	Atom* rootAtom = parse_sexpr(&atomVec, &message);

	print_sexpr(rootAtom);
	printf("\n");

	return "Output";
}
