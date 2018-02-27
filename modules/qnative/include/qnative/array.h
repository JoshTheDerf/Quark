/*************************************************************************/
/*  array.h                                                              */
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

#ifndef QUARK_ARRAY_H
#define QUARK_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_ARRAY_SIZE];
} quark_array;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/pool_arrays.h>
#include <qnative/variant.h>

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_array_new(quark_array *r_dest);
void QAPI quark_array_new_copy(quark_array *r_dest, const quark_array *p_src);
void QAPI quark_array_new_pool_color_array(quark_array *r_dest, const quark_pool_color_array *p_pca);
void QAPI quark_array_new_pool_vector3_array(quark_array *r_dest, const quark_pool_vector3_array *p_pv3a);
void QAPI quark_array_new_pool_vector2_array(quark_array *r_dest, const quark_pool_vector2_array *p_pv2a);
void QAPI quark_array_new_pool_string_array(quark_array *r_dest, const quark_pool_string_array *p_psa);
void QAPI quark_array_new_pool_real_array(quark_array *r_dest, const quark_pool_real_array *p_pra);
void QAPI quark_array_new_pool_int_array(quark_array *r_dest, const quark_pool_int_array *p_pia);
void QAPI quark_array_new_pool_byte_array(quark_array *r_dest, const quark_pool_byte_array *p_pba);

void QAPI quark_array_set(quark_array *p_self, const quark_int p_idx, const quark_variant *p_value);

quark_variant QAPI quark_array_get(const quark_array *p_self, const quark_int p_idx);

quark_variant QAPI *quark_array_operator_index(quark_array *p_self, const quark_int p_idx);

const quark_variant QAPI *quark_array_operator_index_const(const quark_array *p_self, const quark_int p_idx);

void QAPI quark_array_append(quark_array *p_self, const quark_variant *p_value);

void QAPI quark_array_clear(quark_array *p_self);

quark_int QAPI quark_array_count(const quark_array *p_self, const quark_variant *p_value);

quark_bool QAPI quark_array_empty(const quark_array *p_self);

void QAPI quark_array_erase(quark_array *p_self, const quark_variant *p_value);

quark_variant QAPI quark_array_front(const quark_array *p_self);

quark_variant QAPI quark_array_back(const quark_array *p_self);

quark_int QAPI quark_array_find(const quark_array *p_self, const quark_variant *p_what, const quark_int p_from);

quark_int QAPI quark_array_find_last(const quark_array *p_self, const quark_variant *p_what);

quark_bool QAPI quark_array_has(const quark_array *p_self, const quark_variant *p_value);

quark_int QAPI quark_array_hash(const quark_array *p_self);

void QAPI quark_array_insert(quark_array *p_self, const quark_int p_pos, const quark_variant *p_value);

void QAPI quark_array_invert(quark_array *p_self);

quark_variant QAPI quark_array_pop_back(quark_array *p_self);

quark_variant QAPI quark_array_pop_front(quark_array *p_self);

void QAPI quark_array_push_back(quark_array *p_self, const quark_variant *p_value);

void QAPI quark_array_push_front(quark_array *p_self, const quark_variant *p_value);

void QAPI quark_array_remove(quark_array *p_self, const quark_int p_idx);

void QAPI quark_array_resize(quark_array *p_self, const quark_int p_size);

quark_int QAPI quark_array_rfind(const quark_array *p_self, const quark_variant *p_what, const quark_int p_from);

quark_int QAPI quark_array_size(const quark_array *p_self);

void QAPI quark_array_sort(quark_array *p_self);

void QAPI quark_array_sort_custom(quark_array *p_self, quark_object *p_obj, const quark_string *p_func);

quark_int QAPI quark_array_bsearch(quark_array *p_self, const quark_variant *p_value, const quark_bool p_before);

quark_int QAPI quark_array_bsearch_custom(quark_array *p_self, const quark_variant *p_value, quark_object *p_obj, const quark_string *p_func, const quark_bool p_before);

void QAPI quark_array_destroy(quark_array *p_self);

#ifdef __cplusplus
}
#endif

#endif // QUARK_ARRAY_H
