/*************************************************************************/
/*  string.cpp                                                           */
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

#include "qnative/string.h"

#include "core/string_db.h"
#include "core/ustring.h"
#include "core/variant.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

quark_int QAPI quark_char_string_length(const quark_char_string *p_cs) {
	const CharString *cs = (const CharString *)p_cs;

	return cs->length();
}

const char QAPI *quark_char_string_get_data(const quark_char_string *p_cs) {
	const CharString *cs = (const CharString *)p_cs;

	return cs->get_data();
}

void QAPI quark_char_string_destroy(quark_char_string *p_cs) {
	CharString *cs = (CharString *)p_cs;

	cs->~CharString();
}

void QAPI quark_string_new(quark_string *r_dest) {
	String *dest = (String *)r_dest;
	memnew_placement(dest, String);
}

void QAPI quark_string_new_copy(quark_string *r_dest, const quark_string *p_src) {
	String *dest = (String *)r_dest;
	const String *src = (const String *)p_src;
	memnew_placement(dest, String(*src));
}

void QAPI quark_string_new_with_wide_string(quark_string *r_dest, const wchar_t *p_contents, const int p_size) {
	String *dest = (String *)r_dest;
	memnew_placement(dest, String(p_contents, p_size));
}

wchar_t QAPI *quark_string_operator_index(quark_string *p_self, const quark_int p_idx) {
	String *self = (String *)p_self;
	return &(self->operator[](p_idx));
}

wchar_t QAPI quark_string_operator_index_const(const quark_string *p_self, const quark_int p_idx) {
	const String *self = (const String *)p_self;
	return self->operator[](p_idx);
}

const wchar_t QAPI *quark_string_wide_str(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	return self->c_str();
}

quark_bool QAPI quark_string_operator_equal(const quark_string *p_self, const quark_string *p_b) {
	const String *self = (const String *)p_self;
	const String *b = (const String *)p_b;
	return *self == *b;
}

quark_bool QAPI quark_string_operator_less(const quark_string *p_self, const quark_string *p_b) {
	const String *self = (const String *)p_self;
	const String *b = (const String *)p_b;
	return *self < *b;
}

quark_string QAPI quark_string_operator_plus(const quark_string *p_self, const quark_string *p_b) {
	quark_string ret;
	const String *self = (const String *)p_self;
	const String *b = (const String *)p_b;
	memnew_placement(&ret, String(*self + *b));
	return ret;
}

void QAPI quark_string_destroy(quark_string *p_self) {
	String *self = (String *)p_self;
	self->~String();
}

/* Standard size stuff */

quark_int QAPI quark_string_length(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->length();
}

/* Helpers */

signed char QAPI quark_string_casecmp_to(const quark_string *p_self, const quark_string *p_str) {
	const String *self = (const String *)p_self;
	const String *str = (const String *)p_str;

	return self->casecmp_to(*str);
}

signed char QAPI quark_string_nocasecmp_to(const quark_string *p_self, const quark_string *p_str) {
	const String *self = (const String *)p_self;
	const String *str = (const String *)p_str;

	return self->nocasecmp_to(*str);
}
signed char QAPI quark_string_naturalnocasecmp_to(const quark_string *p_self, const quark_string *p_str) {
	const String *self = (const String *)p_self;
	const String *str = (const String *)p_str;

	return self->naturalnocasecmp_to(*str);
}

quark_bool QAPI quark_string_begins_with(const quark_string *p_self, const quark_string *p_string) {
	const String *self = (const String *)p_self;
	const String *string = (const String *)p_string;

	return self->begins_with(*string);
}

quark_bool QAPI quark_string_begins_with_char_array(const quark_string *p_self, const char *p_char_array) {
	const String *self = (const String *)p_self;

	return self->begins_with(p_char_array);
}

quark_array QAPI quark_string_bigrams(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	Vector<String> return_value = self->bigrams();

	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
};

quark_string QAPI quark_string_chr(wchar_t p_character) {
	quark_string result;
	memnew_placement(&result, String(String::chr(p_character)));

	return result;
}

quark_bool QAPI quark_string_ends_with(const quark_string *p_self, const quark_string *p_string) {
	const String *self = (const String *)p_self;
	const String *string = (const String *)p_string;

	return self->ends_with(*string);
}

quark_int QAPI quark_string_find(const quark_string *p_self, quark_string p_what) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->find(*what);
}

quark_int QAPI quark_string_find_from(const quark_string *p_self, quark_string p_what, quark_int p_from) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->find(*what, p_from);
}

quark_int QAPI quark_string_findmk(const quark_string *p_self, const quark_array *p_keys) {
	const String *self = (const String *)p_self;

	Vector<String> keys;
	Array *keys_proxy = (Array *)p_keys;
	keys.resize(keys_proxy->size());
	for (int i = 0; i < keys_proxy->size(); i++) {
		keys[i] = (*keys_proxy)[i];
	}

	return self->findmk(keys);
}

quark_int QAPI quark_string_findmk_from(const quark_string *p_self, const quark_array *p_keys, quark_int p_from) {
	const String *self = (const String *)p_self;

	Vector<String> keys;
	Array *keys_proxy = (Array *)p_keys;
	keys.resize(keys_proxy->size());
	for (int i = 0; i < keys_proxy->size(); i++) {
		keys[i] = (*keys_proxy)[i];
	}

	return self->findmk(keys, p_from);
}

quark_int QAPI quark_string_findmk_from_in_place(const quark_string *p_self, const quark_array *p_keys, quark_int p_from, quark_int *r_key) {
	const String *self = (const String *)p_self;

	Vector<String> keys;
	Array *keys_proxy = (Array *)p_keys;
	keys.resize(keys_proxy->size());
	for (int i = 0; i < keys_proxy->size(); i++) {
		keys[i] = (*keys_proxy)[i];
	}

	return self->findmk(keys, p_from, r_key);
}

quark_int QAPI quark_string_findn(const quark_string *p_self, quark_string p_what) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->findn(*what);
}

quark_int QAPI quark_string_findn_from(const quark_string *p_self, quark_string p_what, quark_int p_from) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->findn(*what, p_from);
}

quark_int QAPI quark_string_find_last(const quark_string *p_self, quark_string p_what) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->find_last(*what);
}

quark_string QAPI quark_string_format(const quark_string *p_self, const quark_variant *p_values) {
	const String *self = (const String *)p_self;
	const Variant *values = (const Variant *)p_values;
	quark_string result;
	memnew_placement(&result, String(self->format(*values)));

	return result;
}

quark_string QAPI quark_string_format_with_custom_placeholder(const quark_string *p_self, const quark_variant *p_values, const char *p_placeholder) {
	const String *self = (const String *)p_self;
	const Variant *values = (const Variant *)p_values;
	String placeholder = String(p_placeholder);
	quark_string result;
	memnew_placement(&result, String(self->format(*values, placeholder)));

	return result;
}

quark_string QAPI quark_string_hex_encode_buffer(const uint8_t *p_buffer, quark_int p_len) {
	quark_string result;
	memnew_placement(&result, String(String::hex_encode_buffer(p_buffer, p_len)));

	return result;
}

quark_int QAPI quark_string_hex_to_int(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hex_to_int();
}

quark_int QAPI quark_string_hex_to_int_without_prefix(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hex_to_int(true);
}

quark_string QAPI quark_string_insert(const quark_string *p_self, quark_int p_at_pos, quark_string p_string) {
	const String *self = (const String *)p_self;
	String *content = (String *)&p_string;
	quark_string result;
	memnew_placement(&result, String(self->insert(p_at_pos, *content)));

	return result;
}

quark_bool QAPI quark_string_is_numeric(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_numeric();
}

quark_bool QAPI quark_string_is_subsequence_of(const quark_string *p_self, const quark_string *p_string) {
	const String *self = (const String *)p_self;
	const String *string = (const String *)p_string;

	return self->is_subsequence_of(*string);
}

quark_bool QAPI quark_string_is_subsequence_ofi(const quark_string *p_self, const quark_string *p_string) {
	const String *self = (const String *)p_self;
	const String *string = (const String *)p_string;

	return self->is_subsequence_ofi(*string);
}

quark_string QAPI quark_string_lpad(const quark_string *p_self, quark_int p_min_length) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->lpad(p_min_length)));

	return result;
}

quark_string QAPI quark_string_lpad_with_custom_character(const quark_string *p_self, quark_int p_min_length, const quark_string *p_character) {
	const String *self = (const String *)p_self;
	const String *character = (const String *)p_character;
	quark_string result;
	memnew_placement(&result, String(self->lpad(p_min_length, *character)));

	return result;
}

quark_bool QAPI quark_string_match(const quark_string *p_self, const quark_string *p_wildcard) {
	const String *self = (const String *)p_self;
	const String *wildcard = (const String *)p_wildcard;

	return self->match(*wildcard);
}

quark_bool QAPI quark_string_matchn(const quark_string *p_self, const quark_string *p_wildcard) {
	const String *self = (const String *)p_self;
	const String *wildcard = (const String *)p_wildcard;

	return self->matchn(*wildcard);
}

quark_string QAPI quark_string_md5(const uint8_t *p_md5) {
	quark_string result;
	memnew_placement(&result, String(String::md5(p_md5)));

	return result;
}

quark_string QAPI quark_string_num(double p_num) {
	quark_string result;
	memnew_placement(&result, String(String::num(p_num)));

	return result;
}

quark_string QAPI quark_string_num_int64(int64_t p_num, quark_int p_base) {
	quark_string result;
	memnew_placement(&result, String(String::num_int64(p_num, p_base)));

	return result;
}

quark_string QAPI quark_string_num_int64_capitalized(int64_t p_num, quark_int p_base, quark_bool p_capitalize_hex) {
	quark_string result;
	memnew_placement(&result, String(String::num_int64(p_num, p_base, true)));

	return result;
}

quark_string QAPI quark_string_num_real(double p_num) {
	quark_string result;
	memnew_placement(&result, String(String::num_real(p_num)));

	return result;
}

quark_string QAPI quark_string_num_scientific(double p_num) {
	quark_string result;
	memnew_placement(&result, String(String::num_scientific(p_num)));

	return result;
}

quark_string QAPI quark_string_num_with_decimals(double p_num, quark_int p_decimals) {
	quark_string result;
	memnew_placement(&result, String(String::num(p_num, p_decimals)));

	return result;
}

quark_string QAPI quark_string_pad_decimals(const quark_string *p_self, quark_int p_digits) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->pad_decimals(p_digits)));

	return result;
}

quark_string QAPI quark_string_pad_zeros(const quark_string *p_self, quark_int p_digits) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->pad_zeros(p_digits)));

	return result;
}

quark_string QAPI quark_string_replace(const quark_string *p_self, quark_string p_key, quark_string p_with) {
	const String *self = (const String *)p_self;
	String *key = (String *)&p_key;
	String *with = (String *)&p_with;
	quark_string result;
	memnew_placement(&result, String(self->replace(*key, *with)));

	return result;
}

quark_string QAPI quark_string_replacen(const quark_string *p_self, quark_string p_key, quark_string p_with) {
	const String *self = (const String *)p_self;
	String *key = (String *)&p_key;
	String *with = (String *)&p_with;
	quark_string result;
	memnew_placement(&result, String(self->replacen(*key, *with)));

	return result;
}

quark_int QAPI quark_string_rfind(const quark_string *p_self, quark_string p_what) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->rfind(*what);
}

quark_int QAPI quark_string_rfindn(const quark_string *p_self, quark_string p_what) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->rfindn(*what);
}

quark_int QAPI quark_string_rfind_from(const quark_string *p_self, quark_string p_what, quark_int p_from) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->rfind(*what, p_from);
}

quark_int QAPI quark_string_rfindn_from(const quark_string *p_self, quark_string p_what, quark_int p_from) {
	const String *self = (const String *)p_self;
	String *what = (String *)&p_what;

	return self->rfindn(*what, p_from);
}

quark_string QAPI quark_string_replace_first(const quark_string *p_self, quark_string p_key, quark_string p_with) {
	const String *self = (const String *)p_self;
	String *key = (String *)&p_key;
	String *with = (String *)&p_with;
	quark_string result;
	memnew_placement(&result, String(self->replace_first(*key, *with)));

	return result;
}

quark_string QAPI quark_string_rpad(const quark_string *p_self, quark_int p_min_length) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->rpad(p_min_length)));

	return result;
}

quark_string QAPI quark_string_rpad_with_custom_character(const quark_string *p_self, quark_int p_min_length, const quark_string *p_character) {
	const String *self = (const String *)p_self;
	const String *character = (const String *)p_character;
	quark_string result;
	memnew_placement(&result, String(self->rpad(p_min_length, *character)));

	return result;
}

quark_real QAPI quark_string_similarity(const quark_string *p_self, const quark_string *p_string) {
	const String *self = (const String *)p_self;
	const String *string = (const String *)p_string;

	return self->similarity(*string);
}

quark_string QAPI quark_string_sprintf(const quark_string *p_self, const quark_array *p_values, quark_bool *p_error) {
	const String *self = (const String *)p_self;
	const Array *values = (const Array *)p_values;

	quark_string result;
	String return_value = self->sprintf(*values, p_error);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_substr(const quark_string *p_self, quark_int p_from, quark_int p_chars) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->substr(p_from, p_chars)));

	return result;
}

double QAPI quark_string_to_double(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->to_double();
}

quark_real QAPI quark_string_to_float(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->to_float();
}

quark_int QAPI quark_string_to_int(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->to_int();
}

quark_string QAPI quark_string_capitalize(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->capitalize()));

	return result;
}

quark_string QAPI quark_string_camelcase_to_underscore(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->camelcase_to_underscore(false)));

	return result;
}

quark_string QAPI quark_string_camelcase_to_underscore_lowercased(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->camelcase_to_underscore()));

	return result;
}

double QAPI quark_string_char_to_double(const char *p_what) {
	return String::to_double(p_what);
}

quark_int QAPI quark_string_char_to_int(const char *p_what) {
	return String::to_int(p_what);
}

int64_t QAPI quark_string_wchar_to_int(const wchar_t *p_str) {
	return String::to_int(p_str);
}

quark_int QAPI quark_string_char_to_int_with_len(const char *p_what, quark_int p_len) {
	return String::to_int(p_what, p_len);
}

int64_t QAPI quark_string_char_to_int64_with_len(const wchar_t *p_str, int p_len) {
	return String::to_int(p_str, p_len);
}

int64_t QAPI quark_string_hex_to_int64(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hex_to_int64(false);
}

int64_t QAPI quark_string_hex_to_int64_with_prefix(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hex_to_int64();
}

int64_t QAPI quark_string_to_int64(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->to_int64();
}

double QAPI quark_string_unicode_char_to_double(const wchar_t *p_str, const wchar_t **r_end) {
	return String::to_double(p_str, r_end);
}

quark_string QAPI quark_string_get_slice(const quark_string *p_self, quark_string p_splitter, quark_int p_slice) {
	const String *self = (const String *)p_self;
	String *splitter = (String *)&p_splitter;
	quark_string result;
	memnew_placement(&result, String(self->get_slice(*splitter, p_slice)));

	return result;
}

quark_string QAPI quark_string_get_slicec(const quark_string *p_self, wchar_t p_splitter, quark_int p_slice) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->get_slicec(p_splitter, p_slice)));

	return result;
}

quark_array QAPI quark_string_split(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<String> return_value = self->split(*splitter, false);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_allow_empty(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<String> return_value = self->split(*splitter);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_floats(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<float> return_value = self->split_floats(*splitter, false);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_floats_allows_empty(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<float> return_value = self->split_floats(*splitter);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_floats_mk(const quark_string *p_self, const quark_array *p_splitters) {
	const String *self = (const String *)p_self;

	Vector<String> splitters;
	Array *splitter_proxy = (Array *)p_splitters;
	splitters.resize(splitter_proxy->size());
	for (int i = 0; i < splitter_proxy->size(); i++) {
		splitters[i] = (*splitter_proxy)[i];
	}

	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<float> return_value = self->split_floats_mk(splitters, false);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_floats_mk_allows_empty(const quark_string *p_self, const quark_array *p_splitters) {
	const String *self = (const String *)p_self;

	Vector<String> splitters;
	Array *splitter_proxy = (Array *)p_splitters;
	splitters.resize(splitter_proxy->size());
	for (int i = 0; i < splitter_proxy->size(); i++) {
		splitters[i] = (*splitter_proxy)[i];
	}

	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<float> return_value = self->split_floats_mk(splitters);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_ints(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<int> return_value = self->split_ints(*splitter, false);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_ints_allows_empty(const quark_string *p_self, const quark_string *p_splitter) {
	const String *self = (const String *)p_self;
	const String *splitter = (const String *)p_splitter;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<int> return_value = self->split_ints(*splitter);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_ints_mk(const quark_string *p_self, const quark_array *p_splitters) {
	const String *self = (const String *)p_self;

	Vector<String> splitters;
	Array *splitter_proxy = (Array *)p_splitters;
	splitters.resize(splitter_proxy->size());
	for (int i = 0; i < splitter_proxy->size(); i++) {
		splitters[i] = (*splitter_proxy)[i];
	}

	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<int> return_value = self->split_ints_mk(splitters, false);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_ints_mk_allows_empty(const quark_string *p_self, const quark_array *p_splitters) {
	const String *self = (const String *)p_self;

	Vector<String> splitters;
	Array *splitter_proxy = (Array *)p_splitters;
	splitters.resize(splitter_proxy->size());
	for (int i = 0; i < splitter_proxy->size(); i++) {
		splitters[i] = (*splitter_proxy)[i];
	}

	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<int> return_value = self->split_ints_mk(splitters);

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_array QAPI quark_string_split_spaces(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_array result;
	memnew_placement(&result, Array);
	Array *proxy = (Array *)&result;
	Vector<String> return_value = self->split_spaces();

	proxy->resize(return_value.size());
	for (int i = 0; i < return_value.size(); i++) {
		(*proxy)[i] = return_value[i];
	}

	return result;
}

quark_int QAPI quark_string_get_slice_count(const quark_string *p_self, quark_string p_splitter) {
	const String *self = (const String *)p_self;
	String *splitter = (String *)&p_splitter;

	return self->get_slice_count(*splitter);
}

wchar_t QAPI quark_string_char_lowercase(wchar_t p_char) {
	return String::char_lowercase(p_char);
}

wchar_t QAPI quark_string_char_uppercase(wchar_t p_char) {
	return String::char_uppercase(p_char);
}

quark_string QAPI quark_string_to_lower(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->to_lower()));

	return result;
}

quark_string QAPI quark_string_to_upper(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->to_upper()));

	return result;
}

quark_string QAPI quark_string_get_basename(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->get_basename()));

	return result;
}

quark_string QAPI quark_string_get_extension(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->get_extension()));

	return result;
}

quark_string QAPI quark_string_left(const quark_string *p_self, quark_int p_pos) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->left(p_pos)));

	return result;
}

wchar_t QAPI quark_string_ord_at(const quark_string *p_self, quark_int p_idx) {
	const String *self = (const String *)p_self;

	return self->ord_at(p_idx);
}

quark_string QAPI quark_string_plus_file(const quark_string *p_self, const quark_string *p_file) {
	const String *self = (const String *)p_self;
	const String *file = (const String *)p_file;
	quark_string result;
	memnew_placement(&result, String(self->plus_file(*file)));

	return result;
}

quark_string QAPI quark_string_right(const quark_string *p_self, quark_int p_pos) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->right(p_pos)));

	return result;
}

quark_string QAPI quark_string_strip_edges(const quark_string *p_self, quark_bool p_left, quark_bool p_right) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->strip_edges(p_left, p_right)));

	return result;
}

quark_string QAPI quark_string_strip_escapes(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->strip_escapes()));

	return result;
}

void QAPI quark_string_erase(quark_string *p_self, quark_int p_pos, quark_int p_chars) {
	String *self = (String *)p_self;

	return self->erase(p_pos, p_chars);
}

quark_char_string QAPI quark_string_ascii(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_char_string result;

	memnew_placement(&result, CharString(self->ascii()));

	return result;
}

quark_char_string QAPI quark_string_ascii_extended(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	quark_char_string result;

	memnew_placement(&result, CharString(self->ascii(true)));

	return result;
}

quark_char_string QAPI quark_string_utf8(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	quark_char_string result;

	memnew_placement(&result, CharString(self->utf8()));

	return result;
}

quark_bool QAPI quark_string_parse_utf8(quark_string *p_self, const char *p_utf8) {
	String *self = (String *)p_self;

	return self->parse_utf8(p_utf8);
}

quark_bool QAPI quark_string_parse_utf8_with_len(quark_string *p_self, const char *p_utf8, quark_int p_len) {
	String *self = (String *)p_self;

	return self->parse_utf8(p_utf8, p_len);
}

quark_string QAPI quark_string_chars_to_utf8(const char *p_utf8) {
	quark_string result;
	memnew_placement(&result, String(String::utf8(p_utf8)));

	return result;
}

quark_string QAPI quark_string_chars_to_utf8_with_len(const char *p_utf8, quark_int p_len) {
	quark_string result;
	memnew_placement(&result, String(String::utf8(p_utf8, p_len)));

	return result;
}

uint32_t QAPI quark_string_hash(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hash();
}

uint64_t QAPI quark_string_hash64(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->hash64();
}

uint32_t QAPI quark_string_hash_chars(const char *p_cstr) {
	return String::hash(p_cstr);
}

uint32_t QAPI quark_string_hash_chars_with_len(const char *p_cstr, quark_int p_len) {
	return String::hash(p_cstr, p_len);
}

uint32_t QAPI quark_string_hash_utf8_chars(const wchar_t *p_str) {
	return String::hash(p_str);
}

uint32_t QAPI quark_string_hash_utf8_chars_with_len(const wchar_t *p_str, quark_int p_len) {
	return String::hash(p_str, p_len);
}

quark_pool_byte_array QAPI quark_string_md5_buffer(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	Vector<uint8_t> tmp_result = self->md5_buffer();

	quark_pool_byte_array result;
	memnew_placement(&result, PoolByteArray);
	PoolByteArray *proxy = (PoolByteArray *)&result;
	PoolByteArray::Write proxy_writer = proxy->write();
	proxy->resize(tmp_result.size());

	for (int i = 0; i < tmp_result.size(); i++) {
		proxy_writer[i] = tmp_result[i];
	}

	return result;
}

quark_string QAPI quark_string_md5_text(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->md5_text()));

	return result;
}

quark_pool_byte_array QAPI quark_string_sha256_buffer(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	Vector<uint8_t> tmp_result = self->sha256_buffer();

	quark_pool_byte_array result;
	memnew_placement(&result, PoolByteArray);
	PoolByteArray *proxy = (PoolByteArray *)&result;
	PoolByteArray::Write proxy_writer = proxy->write();
	proxy->resize(tmp_result.size());

	for (int i = 0; i < tmp_result.size(); i++) {
		proxy_writer[i] = tmp_result[i];
	}

	return result;
}

quark_string QAPI quark_string_sha256_text(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	memnew_placement(&result, String(self->sha256_text()));

	return result;
}

quark_bool quark_string_empty(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->empty();
}

// path functions
quark_string QAPI quark_string_get_base_dir(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->get_base_dir();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_get_file(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->get_file();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_humanize_size(size_t p_size) {
	quark_string result;
	String return_value = String::humanize_size(p_size);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_bool QAPI quark_string_is_abs_path(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_abs_path();
}

quark_bool QAPI quark_string_is_rel_path(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_rel_path();
}

quark_bool QAPI quark_string_is_resource_file(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_resource_file();
}

quark_string QAPI quark_string_path_to(const quark_string *p_self, const quark_string *p_path) {
	const String *self = (const String *)p_self;
	String *path = (String *)p_path;
	quark_string result;
	String return_value = self->path_to(*path);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_path_to_file(const quark_string *p_self, const quark_string *p_path) {
	const String *self = (const String *)p_self;
	String *path = (String *)p_path;
	quark_string result;
	String return_value = self->path_to_file(*path);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_simplify_path(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->simplify_path();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_c_escape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->c_escape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_c_escape_multiline(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->c_escape_multiline();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_c_unescape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->c_unescape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_http_escape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->http_escape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_http_unescape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->http_unescape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_json_escape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->json_escape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_word_wrap(const quark_string *p_self, quark_int p_chars_per_line) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->word_wrap(p_chars_per_line);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_xml_escape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->xml_escape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_xml_escape_with_quotes(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->xml_escape(true);
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_xml_unescape(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->xml_unescape();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_percent_decode(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->percent_decode();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_string QAPI quark_string_percent_encode(const quark_string *p_self) {
	const String *self = (const String *)p_self;
	quark_string result;
	String return_value = self->percent_encode();
	memnew_placement(&result, String(return_value));

	return result;
}

quark_bool QAPI quark_string_is_valid_float(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_valid_float();
}

quark_bool QAPI quark_string_is_valid_hex_number(const quark_string *p_self, quark_bool p_with_prefix) {
	const String *self = (const String *)p_self;

	return self->is_valid_hex_number(p_with_prefix);
}

quark_bool QAPI quark_string_is_valid_html_color(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_valid_html_color();
}

quark_bool QAPI quark_string_is_valid_identifier(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_valid_identifier();
}

quark_bool QAPI quark_string_is_valid_integer(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_valid_integer();
}

quark_bool QAPI quark_string_is_valid_ip_address(const quark_string *p_self) {
	const String *self = (const String *)p_self;

	return self->is_valid_ip_address();
}

#ifdef __cplusplus
}
#endif
