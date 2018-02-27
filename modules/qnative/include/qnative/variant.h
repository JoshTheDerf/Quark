/*************************************************************************/
/*  variant.h                                                            */
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

#ifndef QUARK_VARIANT_H
#define QUARK_VARIANT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_VARIANT_SIZE (16 + sizeof(void *))

#ifndef QUARK_CORE_API_QUARK_VARIANT_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_VARIANT_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_VARIANT_SIZE];
} quark_variant;
#endif

typedef enum quark_variant_type {
	QUARK_VARIANT_TYPE_NIL,

	// atomic types
	QUARK_VARIANT_TYPE_BOOL,
	QUARK_VARIANT_TYPE_INT,
	QUARK_VARIANT_TYPE_REAL,
	QUARK_VARIANT_TYPE_STRING,

	// math types

	QUARK_VARIANT_TYPE_VECTOR2, // 5
	QUARK_VARIANT_TYPE_RECT2,
	QUARK_VARIANT_TYPE_VECTOR3,
	QUARK_VARIANT_TYPE_TRANSFORM2D,
	QUARK_VARIANT_TYPE_PLANE,
	QUARK_VARIANT_TYPE_QUAT, // 10
	QUARK_VARIANT_TYPE_AABB,
	QUARK_VARIANT_TYPE_BASIS,
	QUARK_VARIANT_TYPE_TRANSFORM,

	// misc types
	QUARK_VARIANT_TYPE_COLOR,
	QUARK_VARIANT_TYPE_NODE_PATH, // 15
	QUARK_VARIANT_TYPE_RID,
	QUARK_VARIANT_TYPE_OBJECT,
	QUARK_VARIANT_TYPE_DICTIONARY,
	QUARK_VARIANT_TYPE_ARRAY, // 20

	// arrays
	QUARK_VARIANT_TYPE_POOL_BYTE_ARRAY,
	QUARK_VARIANT_TYPE_POOL_INT_ARRAY,
	QUARK_VARIANT_TYPE_POOL_REAL_ARRAY,
	QUARK_VARIANT_TYPE_POOL_STRING_ARRAY,
	QUARK_VARIANT_TYPE_POOL_VECTOR2_ARRAY, // 25
	QUARK_VARIANT_TYPE_POOL_VECTOR3_ARRAY,
	QUARK_VARIANT_TYPE_POOL_COLOR_ARRAY,
} quark_variant_type;

typedef enum quark_variant_call_error_error {
	QUARK_CALL_ERROR_CALL_OK,
	QUARK_CALL_ERROR_CALL_ERROR_INVALID_METHOD,
	QUARK_CALL_ERROR_CALL_ERROR_INVALID_ARGUMENT,
	QUARK_CALL_ERROR_CALL_ERROR_TOO_MANY_ARGUMENTS,
	QUARK_CALL_ERROR_CALL_ERROR_TOO_FEW_ARGUMENTS,
	QUARK_CALL_ERROR_CALL_ERROR_INSTANCE_IS_NULL,
} quark_variant_call_error_error;

typedef struct quark_variant_call_error {
	quark_variant_call_error_error error;
	int argument;
	quark_variant_type expected;
} quark_variant_call_error;

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/aabb.h>
#include <qnative/array.h>
#include <qnative/basis.h>
#include <qnative/color.h>
#include <qnative/dictionary.h>
#include <qnative/node_path.h>
#include <qnative/plane.h>
#include <qnative/pool_arrays.h>
#include <qnative/quat.h>
#include <qnative/rect2.h>
#include <qnative/rid.h>
#include <qnative/string.h>
#include <qnative/transform.h>
#include <qnative/transform2d.h>
#include <qnative/variant.h>
#include <qnative/vector2.h>
#include <qnative/vector3.h>

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

quark_variant_type QAPI quark_variant_get_type(const quark_variant *p_v);

void QAPI quark_variant_new_copy(quark_variant *r_dest, const quark_variant *p_src);

void QAPI quark_variant_new_nil(quark_variant *r_dest);

void QAPI quark_variant_new_bool(quark_variant *r_dest, const quark_bool p_b);
void QAPI quark_variant_new_uint(quark_variant *r_dest, const uint64_t p_i);
void QAPI quark_variant_new_int(quark_variant *r_dest, const int64_t p_i);
void QAPI quark_variant_new_real(quark_variant *r_dest, const double p_r);
void QAPI quark_variant_new_string(quark_variant *r_dest, const quark_string *p_s);
void QAPI quark_variant_new_vector2(quark_variant *r_dest, const quark_vector2 *p_v2);
void QAPI quark_variant_new_rect2(quark_variant *r_dest, const quark_rect2 *p_rect2);
void QAPI quark_variant_new_vector3(quark_variant *r_dest, const quark_vector3 *p_v3);
void QAPI quark_variant_new_transform2d(quark_variant *r_dest, const quark_transform2d *p_t2d);
void QAPI quark_variant_new_plane(quark_variant *r_dest, const quark_plane *p_plane);
void QAPI quark_variant_new_quat(quark_variant *r_dest, const quark_quat *p_quat);
void QAPI quark_variant_new_aabb(quark_variant *r_dest, const quark_aabb *p_aabb);
void QAPI quark_variant_new_basis(quark_variant *r_dest, const quark_basis *p_basis);
void QAPI quark_variant_new_transform(quark_variant *r_dest, const quark_transform *p_trans);
void QAPI quark_variant_new_color(quark_variant *r_dest, const quark_color *p_color);
void QAPI quark_variant_new_node_path(quark_variant *r_dest, const quark_node_path *p_np);
void QAPI quark_variant_new_rid(quark_variant *r_dest, const quark_rid *p_rid);
void QAPI quark_variant_new_object(quark_variant *r_dest, const quark_object *p_obj);
void QAPI quark_variant_new_dictionary(quark_variant *r_dest, const quark_dictionary *p_dict);
void QAPI quark_variant_new_array(quark_variant *r_dest, const quark_array *p_arr);
void QAPI quark_variant_new_pool_byte_array(quark_variant *r_dest, const quark_pool_byte_array *p_pba);
void QAPI quark_variant_new_pool_int_array(quark_variant *r_dest, const quark_pool_int_array *p_pia);
void QAPI quark_variant_new_pool_real_array(quark_variant *r_dest, const quark_pool_real_array *p_pra);
void QAPI quark_variant_new_pool_string_array(quark_variant *r_dest, const quark_pool_string_array *p_psa);
void QAPI quark_variant_new_pool_vector2_array(quark_variant *r_dest, const quark_pool_vector2_array *p_pv2a);
void QAPI quark_variant_new_pool_vector3_array(quark_variant *r_dest, const quark_pool_vector3_array *p_pv3a);
void QAPI quark_variant_new_pool_color_array(quark_variant *r_dest, const quark_pool_color_array *p_pca);

quark_bool QAPI quark_variant_as_bool(const quark_variant *p_self);
uint64_t QAPI quark_variant_as_uint(const quark_variant *p_self);
int64_t QAPI quark_variant_as_int(const quark_variant *p_self);
double QAPI quark_variant_as_real(const quark_variant *p_self);
quark_string QAPI quark_variant_as_string(const quark_variant *p_self);
quark_vector2 QAPI quark_variant_as_vector2(const quark_variant *p_self);
quark_rect2 QAPI quark_variant_as_rect2(const quark_variant *p_self);
quark_vector3 QAPI quark_variant_as_vector3(const quark_variant *p_self);
quark_transform2d QAPI quark_variant_as_transform2d(const quark_variant *p_self);
quark_plane QAPI quark_variant_as_plane(const quark_variant *p_self);
quark_quat QAPI quark_variant_as_quat(const quark_variant *p_self);
quark_aabb QAPI quark_variant_as_aabb(const quark_variant *p_self);
quark_basis QAPI quark_variant_as_basis(const quark_variant *p_self);
quark_transform QAPI quark_variant_as_transform(const quark_variant *p_self);
quark_color QAPI quark_variant_as_color(const quark_variant *p_self);
quark_node_path QAPI quark_variant_as_node_path(const quark_variant *p_self);
quark_rid QAPI quark_variant_as_rid(const quark_variant *p_self);
quark_object QAPI *quark_variant_as_object(const quark_variant *p_self);
quark_dictionary QAPI quark_variant_as_dictionary(const quark_variant *p_self);
quark_array QAPI quark_variant_as_array(const quark_variant *p_self);
quark_pool_byte_array QAPI quark_variant_as_pool_byte_array(const quark_variant *p_self);
quark_pool_int_array QAPI quark_variant_as_pool_int_array(const quark_variant *p_self);
quark_pool_real_array QAPI quark_variant_as_pool_real_array(const quark_variant *p_self);
quark_pool_string_array QAPI quark_variant_as_pool_string_array(const quark_variant *p_self);
quark_pool_vector2_array QAPI quark_variant_as_pool_vector2_array(const quark_variant *p_self);
quark_pool_vector3_array QAPI quark_variant_as_pool_vector3_array(const quark_variant *p_self);
quark_pool_color_array QAPI quark_variant_as_pool_color_array(const quark_variant *p_self);

quark_variant QAPI quark_variant_call(quark_variant *p_self, const quark_string *p_method, const quark_variant **p_args, const quark_int p_argcount, quark_variant_call_error *r_error);

quark_bool QAPI quark_variant_has_method(const quark_variant *p_self, const quark_string *p_method);

quark_bool QAPI quark_variant_operator_equal(const quark_variant *p_self, const quark_variant *p_other);
quark_bool QAPI quark_variant_operator_less(const quark_variant *p_self, const quark_variant *p_other);

quark_bool QAPI quark_variant_hash_compare(const quark_variant *p_self, const quark_variant *p_other);

quark_bool QAPI quark_variant_booleanize(const quark_variant *p_self);

void QAPI quark_variant_destroy(quark_variant *p_self);

#ifdef __cplusplus
}
#endif

#endif
