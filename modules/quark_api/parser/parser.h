#ifndef QUARK_API_SEXP_PARSER
#define QUARK_API_SEXP_PARSER
#include <vector>
#include <cstdint>

class SexpParser {
public:
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

private:
	std::vector<Atom> atom_vector;

	int parse_string(int& vector_tail, char*& loc);
	int parse_symbol(int& vector_tail, char*& loc);
	int parse_list(int& vector_tail, char*& loc);
public:
	Atom& parse_sexpr(char*& message);
	Atom& get_atom(int atom_index);
	void print_sexpr(Atom& atom, int level = 0);

SexpParser();
~SexpParser();
};

#endif // QUARK_API_SEXP_PARSER
