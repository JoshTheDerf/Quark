/*************************************************************************/
/*  dictionary.h                                                         */
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

#ifndef QUARK_DICTIONARY_H
#define QUARK_DICTIONARY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_DICTIONARY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_DICTIONARY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_DICTIONARY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_DICTIONARY_SIZE];
} quark_dictionary;
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

void QAPI quark_dictionary_new(quark_dictionary *r_dest);
void QAPI quark_dictionary_new_copy(quark_dictionary *r_dest, const quark_dictionary *p_src);
void QAPI quark_dictionary_destroy(quark_dictionary *p_self);

quark_int QAPI quark_dictionary_size(const quark_dictionary *p_self);

quark_bool QAPI quark_dictionary_empty(const quark_dictionary *p_self);

void QAPI quark_dictionary_clear(quark_dictionary *p_self);

quark_bool QAPI quark_dictionary_has(const quark_dictionary *p_self, const quark_variant *p_key);

quark_bool QAPI quark_dictionary_has_all(const quark_dictionary *p_self, const quark_array *p_keys);

void QAPI quark_dictionary_erase(quark_dictionary *p_self, const quark_variant *p_key);

quark_int QAPI quark_dictionary_hash(const quark_dictionary *p_self);

quark_array QAPI quark_dictionary_keys(const quark_dictionary *p_self);

quark_array QAPI quark_dictionary_values(const quark_dictionary *p_self);

quark_variant QAPI quark_dictionary_get(const quark_dictionary *p_self, const quark_variant *p_key);
void QAPI quark_dictionary_set(quark_dictionary *p_self, const quark_variant *p_key, const quark_variant *p_value);

quark_variant QAPI *quark_dictionary_operator_index(quark_dictionary *p_self, const quark_variant *p_key);

const quark_variant QAPI *quark_dictionary_operator_index_const(const quark_dictionary *p_self, const quark_variant *p_key);

quark_variant QAPI *quark_dictionary_next(const quark_dictionary *p_self, const quark_variant *p_key);

quark_bool QAPI quark_dictionary_operator_equal(const quark_dictionary *p_self, const quark_dictionary *p_b);

quark_string QAPI quark_dictionary_to_json(const quark_dictionary *p_self);

#ifdef __cplusplus
}
#endif

#endif // QUARK_DICTIONARY_H
