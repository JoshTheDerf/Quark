/*************************************************************************/
/*  string.h                                                             */
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

#ifndef QUARK_STRING_H
#define QUARK_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <wchar.h>

typedef wchar_t quark_char_type;

#define QUARK_STRING_SIZE sizeof(void *)
#define QUARK_CHAR_STRING_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_STRING_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_STRING_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_STRING_SIZE];
} quark_string;

#endif

#ifndef QUARK_CORE_API_QUARK_CHAR_STRING_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_CHAR_STRING_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_CHAR_STRING_SIZE];
} quark_char_string;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/array.h>
#include <qnative/qnative.h>
#include <qnative/variant.h>

#ifdef __cplusplus
extern "C" {
#endif

quark_int QAPI quark_char_string_length(const quark_char_string *p_cs);
const char QAPI *quark_char_string_get_data(const quark_char_string *p_cs);
void QAPI quark_char_string_destroy(quark_char_string *p_cs);

void QAPI quark_string_new(quark_string *r_dest);
void QAPI quark_string_new_copy(quark_string *r_dest, const quark_string *p_src);
void QAPI quark_string_new_with_wide_string(quark_string *r_dest, const wchar_t *p_contents, const int p_size);

wchar_t QAPI *quark_string_operator_index(quark_string *p_self, const quark_int p_idx);
wchar_t QAPI quark_string_operator_index_const(const quark_string *p_self, const quark_int p_idx);
const wchar_t QAPI *quark_string_wide_str(const quark_string *p_self);

quark_bool QAPI quark_string_operator_equal(const quark_string *p_self, const quark_string *p_b);
quark_bool QAPI quark_string_operator_less(const quark_string *p_self, const quark_string *p_b);
quark_string QAPI quark_string_operator_plus(const quark_string *p_self, const quark_string *p_b);

/* Standard size stuff */

quark_int QAPI quark_string_length(const quark_string *p_self);

/* Helpers */

signed char QAPI quark_string_casecmp_to(const quark_string *p_self, const quark_string *p_str);
signed char QAPI quark_string_nocasecmp_to(const quark_string *p_self, const quark_string *p_str);
signed char QAPI quark_string_naturalnocasecmp_to(const quark_string *p_self, const quark_string *p_str);

quark_bool QAPI quark_string_begins_with(const quark_string *p_self, const quark_string *p_string);
quark_bool QAPI quark_string_begins_with_char_array(const quark_string *p_self, const char *p_char_array);
quark_array QAPI quark_string_bigrams(const quark_string *p_self);
quark_string QAPI quark_string_chr(wchar_t p_character);
quark_bool QAPI quark_string_ends_with(const quark_string *p_self, const quark_string *p_string);
quark_int QAPI quark_string_find(const quark_string *p_self, quark_string p_what);
quark_int QAPI quark_string_find_from(const quark_string *p_self, quark_string p_what, quark_int p_from);
quark_int QAPI quark_string_findmk(const quark_string *p_self, const quark_array *p_keys);
quark_int QAPI quark_string_findmk_from(const quark_string *p_self, const quark_array *p_keys, quark_int p_from);
quark_int QAPI quark_string_findmk_from_in_place(const quark_string *p_self, const quark_array *p_keys, quark_int p_from, quark_int *r_key);
quark_int QAPI quark_string_findn(const quark_string *p_self, quark_string p_what);
quark_int QAPI quark_string_findn_from(const quark_string *p_self, quark_string p_what, quark_int p_from);
quark_int QAPI quark_string_find_last(const quark_string *p_self, quark_string p_what);
quark_string QAPI quark_string_format(const quark_string *p_self, const quark_variant *p_values);
quark_string QAPI quark_string_format_with_custom_placeholder(const quark_string *p_self, const quark_variant *p_values, const char *p_placeholder);
quark_string QAPI quark_string_hex_encode_buffer(const uint8_t *p_buffer, quark_int p_len);
quark_int QAPI quark_string_hex_to_int(const quark_string *p_self);
quark_int QAPI quark_string_hex_to_int_without_prefix(const quark_string *p_self);
quark_string QAPI quark_string_insert(const quark_string *p_self, quark_int p_at_pos, quark_string p_string);
quark_bool QAPI quark_string_is_numeric(const quark_string *p_self);
quark_bool QAPI quark_string_is_subsequence_of(const quark_string *p_self, const quark_string *p_string);
quark_bool QAPI quark_string_is_subsequence_ofi(const quark_string *p_self, const quark_string *p_string);
quark_string QAPI quark_string_lpad(const quark_string *p_self, quark_int p_min_length);
quark_string QAPI quark_string_lpad_with_custom_character(const quark_string *p_self, quark_int p_min_length, const quark_string *p_character);
quark_bool QAPI quark_string_match(const quark_string *p_self, const quark_string *p_wildcard);
quark_bool QAPI quark_string_matchn(const quark_string *p_self, const quark_string *p_wildcard);
quark_string QAPI quark_string_md5(const uint8_t *p_md5);
quark_string QAPI quark_string_num(double p_num);
quark_string QAPI quark_string_num_int64(int64_t p_num, quark_int p_base);
quark_string QAPI quark_string_num_int64_capitalized(int64_t p_num, quark_int p_base, quark_bool p_capitalize_hex);
quark_string QAPI quark_string_num_real(double p_num);
quark_string QAPI quark_string_num_scientific(double p_num);
quark_string QAPI quark_string_num_with_decimals(double p_num, quark_int p_decimals);
quark_string QAPI quark_string_pad_decimals(const quark_string *p_self, quark_int p_digits);
quark_string QAPI quark_string_pad_zeros(const quark_string *p_self, quark_int p_digits);
quark_string QAPI quark_string_replace_first(const quark_string *p_self, quark_string p_key, quark_string p_with);
quark_string QAPI quark_string_replace(const quark_string *p_self, quark_string p_key, quark_string p_with);
quark_string QAPI quark_string_replacen(const quark_string *p_self, quark_string p_key, quark_string p_with);
quark_int QAPI quark_string_rfind(const quark_string *p_self, quark_string p_what);
quark_int QAPI quark_string_rfindn(const quark_string *p_self, quark_string p_what);
quark_int QAPI quark_string_rfind_from(const quark_string *p_self, quark_string p_what, quark_int p_from);
quark_int QAPI quark_string_rfindn_from(const quark_string *p_self, quark_string p_what, quark_int p_from);
quark_string QAPI quark_string_rpad(const quark_string *p_self, quark_int p_min_length);
quark_string QAPI quark_string_rpad_with_custom_character(const quark_string *p_self, quark_int p_min_length, const quark_string *p_character);
quark_real QAPI quark_string_similarity(const quark_string *p_self, const quark_string *p_string);
quark_string QAPI quark_string_sprintf(const quark_string *p_self, const quark_array *p_values, quark_bool *p_error);
quark_string QAPI quark_string_substr(const quark_string *p_self, quark_int p_from, quark_int p_chars);
double QAPI quark_string_to_double(const quark_string *p_self);
quark_real QAPI quark_string_to_float(const quark_string *p_self);
quark_int QAPI quark_string_to_int(const quark_string *p_self);

quark_string QAPI quark_string_camelcase_to_underscore(const quark_string *p_self);
quark_string QAPI quark_string_camelcase_to_underscore_lowercased(const quark_string *p_self);
quark_string QAPI quark_string_capitalize(const quark_string *p_self);
double QAPI quark_string_char_to_double(const char *p_what);
quark_int QAPI quark_string_char_to_int(const char *p_what);
int64_t QAPI quark_string_wchar_to_int(const wchar_t *p_str);
quark_int QAPI quark_string_char_to_int_with_len(const char *p_what, quark_int p_len);
int64_t QAPI quark_string_char_to_int64_with_len(const wchar_t *p_str, int p_len);
int64_t QAPI quark_string_hex_to_int64(const quark_string *p_self);
int64_t QAPI quark_string_hex_to_int64_with_prefix(const quark_string *p_self);
int64_t QAPI quark_string_to_int64(const quark_string *p_self);
double QAPI quark_string_unicode_char_to_double(const wchar_t *p_str, const wchar_t **r_end);

quark_int QAPI quark_string_get_slice_count(const quark_string *p_self, quark_string p_splitter);
quark_string QAPI quark_string_get_slice(const quark_string *p_self, quark_string p_splitter, quark_int p_slice);
quark_string QAPI quark_string_get_slicec(const quark_string *p_self, wchar_t p_splitter, quark_int p_slice);

quark_array QAPI quark_string_split(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_allow_empty(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_floats(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_floats_allows_empty(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_floats_mk(const quark_string *p_self, const quark_array *p_splitters);
quark_array QAPI quark_string_split_floats_mk_allows_empty(const quark_string *p_self, const quark_array *p_splitters);
quark_array QAPI quark_string_split_ints(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_ints_allows_empty(const quark_string *p_self, const quark_string *p_splitter);
quark_array QAPI quark_string_split_ints_mk(const quark_string *p_self, const quark_array *p_splitters);
quark_array QAPI quark_string_split_ints_mk_allows_empty(const quark_string *p_self, const quark_array *p_splitters);
quark_array QAPI quark_string_split_spaces(const quark_string *p_self);

wchar_t QAPI quark_string_char_lowercase(wchar_t p_char);
wchar_t QAPI quark_string_char_uppercase(wchar_t p_char);
quark_string QAPI quark_string_to_lower(const quark_string *p_self);
quark_string QAPI quark_string_to_upper(const quark_string *p_self);

quark_string QAPI quark_string_get_basename(const quark_string *p_self);
quark_string QAPI quark_string_get_extension(const quark_string *p_self);
quark_string QAPI quark_string_left(const quark_string *p_self, quark_int p_pos);
wchar_t QAPI quark_string_ord_at(const quark_string *p_self, quark_int p_idx);
quark_string QAPI quark_string_plus_file(const quark_string *p_self, const quark_string *p_file);
quark_string QAPI quark_string_right(const quark_string *p_self, quark_int p_pos);
quark_string QAPI quark_string_strip_edges(const quark_string *p_self, quark_bool p_left, quark_bool p_right);
quark_string QAPI quark_string_strip_escapes(const quark_string *p_self);

void QAPI quark_string_erase(quark_string *p_self, quark_int p_pos, quark_int p_chars);

quark_char_string QAPI quark_string_ascii(const quark_string *p_self);
quark_char_string QAPI quark_string_ascii_extended(const quark_string *p_self);
quark_char_string QAPI quark_string_utf8(const quark_string *p_self);
quark_bool QAPI quark_string_parse_utf8(quark_string *p_self, const char *p_utf8);
quark_bool QAPI quark_string_parse_utf8_with_len(quark_string *p_self, const char *p_utf8, quark_int p_len);
quark_string QAPI quark_string_chars_to_utf8(const char *p_utf8);
quark_string QAPI quark_string_chars_to_utf8_with_len(const char *p_utf8, quark_int p_len);

uint32_t QAPI quark_string_hash(const quark_string *p_self);
uint64_t QAPI quark_string_hash64(const quark_string *p_self);
uint32_t QAPI quark_string_hash_chars(const char *p_cstr);
uint32_t QAPI quark_string_hash_chars_with_len(const char *p_cstr, quark_int p_len);
uint32_t QAPI quark_string_hash_utf8_chars(const wchar_t *p_str);
uint32_t QAPI quark_string_hash_utf8_chars_with_len(const wchar_t *p_str, quark_int p_len);
quark_pool_byte_array QAPI quark_string_md5_buffer(const quark_string *p_self);
quark_string QAPI quark_string_md5_text(const quark_string *p_self);
quark_pool_byte_array QAPI quark_string_sha256_buffer(const quark_string *p_self);
quark_string QAPI quark_string_sha256_text(const quark_string *p_self);

quark_bool quark_string_empty(const quark_string *p_self);

// path functions
quark_string QAPI quark_string_get_base_dir(const quark_string *p_self);
quark_string QAPI quark_string_get_file(const quark_string *p_self);
quark_string QAPI quark_string_humanize_size(size_t p_size);
quark_bool QAPI quark_string_is_abs_path(const quark_string *p_self);
quark_bool QAPI quark_string_is_rel_path(const quark_string *p_self);
quark_bool QAPI quark_string_is_resource_file(const quark_string *p_self);
quark_string QAPI quark_string_path_to(const quark_string *p_self, const quark_string *p_path);
quark_string QAPI quark_string_path_to_file(const quark_string *p_self, const quark_string *p_path);
quark_string QAPI quark_string_simplify_path(const quark_string *p_self);

quark_string QAPI quark_string_c_escape(const quark_string *p_self);
quark_string QAPI quark_string_c_escape_multiline(const quark_string *p_self);
quark_string QAPI quark_string_c_unescape(const quark_string *p_self);
quark_string QAPI quark_string_http_escape(const quark_string *p_self);
quark_string QAPI quark_string_http_unescape(const quark_string *p_self);
quark_string QAPI quark_string_json_escape(const quark_string *p_self);
quark_string QAPI quark_string_word_wrap(const quark_string *p_self, quark_int p_chars_per_line);
quark_string QAPI quark_string_xml_escape(const quark_string *p_self);
quark_string QAPI quark_string_xml_escape_with_quotes(const quark_string *p_self);
quark_string QAPI quark_string_xml_unescape(const quark_string *p_self);

quark_string QAPI quark_string_percent_decode(const quark_string *p_self);
quark_string QAPI quark_string_percent_encode(const quark_string *p_self);

quark_bool QAPI quark_string_is_valid_float(const quark_string *p_self);
quark_bool QAPI quark_string_is_valid_hex_number(const quark_string *p_self, quark_bool p_with_prefix);
quark_bool QAPI quark_string_is_valid_html_color(const quark_string *p_self);
quark_bool QAPI quark_string_is_valid_identifier(const quark_string *p_self);
quark_bool QAPI quark_string_is_valid_integer(const quark_string *p_self);
quark_bool QAPI quark_string_is_valid_ip_address(const quark_string *p_self);

void QAPI quark_string_destroy(quark_string *p_self);

#ifdef __cplusplus
}
#endif

#endif // QUARK_STRING_H
