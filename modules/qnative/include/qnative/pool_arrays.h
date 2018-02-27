/*************************************************************************/
/*  pool_arrays.h                                                        */
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

#ifndef QUARK_POOL_ARRAYS_H
#define QUARK_POOL_ARRAYS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/////// Read Access

#define QUARK_POOL_ARRAY_READ_ACCESS_SIZE 1

typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_ARRAY_READ_ACCESS_SIZE];
} quark_pool_array_read_access;

typedef quark_pool_array_read_access quark_pool_byte_array_read_access;
typedef quark_pool_array_read_access quark_pool_int_array_read_access;
typedef quark_pool_array_read_access quark_pool_real_array_read_access;
typedef quark_pool_array_read_access quark_pool_string_array_read_access;
typedef quark_pool_array_read_access quark_pool_vector2_array_read_access;
typedef quark_pool_array_read_access quark_pool_vector3_array_read_access;
typedef quark_pool_array_read_access quark_pool_color_array_read_access;

/////// Write Access

#define QUARK_POOL_ARRAY_WRITE_ACCESS_SIZE 1

typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_ARRAY_WRITE_ACCESS_SIZE];
} quark_pool_array_write_access;

typedef quark_pool_array_write_access quark_pool_byte_array_write_access;
typedef quark_pool_array_write_access quark_pool_int_array_write_access;
typedef quark_pool_array_write_access quark_pool_real_array_write_access;
typedef quark_pool_array_write_access quark_pool_string_array_write_access;
typedef quark_pool_array_write_access quark_pool_vector2_array_write_access;
typedef quark_pool_array_write_access quark_pool_vector3_array_write_access;
typedef quark_pool_array_write_access quark_pool_color_array_write_access;

/////// PoolByteArray

#define QUARK_POOL_BYTE_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_BYTE_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_BYTE_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_BYTE_ARRAY_SIZE];
} quark_pool_byte_array;
#endif

/////// PoolIntArray

#define QUARK_POOL_INT_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_INT_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_INT_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_INT_ARRAY_SIZE];
} quark_pool_int_array;
#endif

/////// PoolRealArray

#define QUARK_POOL_REAL_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_REAL_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_REAL_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_REAL_ARRAY_SIZE];
} quark_pool_real_array;
#endif

/////// PoolStringArray

#define QUARK_POOL_STRING_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_STRING_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_STRING_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_STRING_ARRAY_SIZE];
} quark_pool_string_array;
#endif

/////// PoolVector2Array

#define QUARK_POOL_VECTOR2_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_VECTOR2_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_VECTOR2_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_VECTOR2_ARRAY_SIZE];
} quark_pool_vector2_array;
#endif

/////// PoolVector3Array

#define QUARK_POOL_VECTOR3_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_VECTOR3_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_VECTOR3_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_VECTOR3_ARRAY_SIZE];
} quark_pool_vector3_array;
#endif

/////// PoolColorArray

#define QUARK_POOL_COLOR_ARRAY_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_POOL_COLOR_ARRAY_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_POOL_COLOR_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_POOL_COLOR_ARRAY_SIZE];
} quark_pool_color_array;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/array.h>
#include <qnative/color.h>
#include <qnative/vector2.h>
#include <qnative/vector3.h>

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

// byte

void QAPI quark_pool_byte_array_new(quark_pool_byte_array *r_dest);
void QAPI quark_pool_byte_array_new_copy(quark_pool_byte_array *r_dest, const quark_pool_byte_array *p_src);
void QAPI quark_pool_byte_array_new_with_array(quark_pool_byte_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_byte_array_append(quark_pool_byte_array *p_self, const uint8_t p_data);

void QAPI quark_pool_byte_array_append_array(quark_pool_byte_array *p_self, const quark_pool_byte_array *p_array);

quark_error QAPI quark_pool_byte_array_insert(quark_pool_byte_array *p_self, const quark_int p_idx, const uint8_t p_data);

void QAPI quark_pool_byte_array_invert(quark_pool_byte_array *p_self);

void QAPI quark_pool_byte_array_push_back(quark_pool_byte_array *p_self, const uint8_t p_data);

void QAPI quark_pool_byte_array_remove(quark_pool_byte_array *p_self, const quark_int p_idx);

void QAPI quark_pool_byte_array_resize(quark_pool_byte_array *p_self, const quark_int p_size);

quark_pool_byte_array_read_access QAPI *quark_pool_byte_array_read(const quark_pool_byte_array *p_self);

quark_pool_byte_array_write_access QAPI *quark_pool_byte_array_write(quark_pool_byte_array *p_self);

void QAPI quark_pool_byte_array_set(quark_pool_byte_array *p_self, const quark_int p_idx, const uint8_t p_data);
uint8_t QAPI quark_pool_byte_array_get(const quark_pool_byte_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_byte_array_size(const quark_pool_byte_array *p_self);

void QAPI quark_pool_byte_array_destroy(quark_pool_byte_array *p_self);

// int

void QAPI quark_pool_int_array_new(quark_pool_int_array *r_dest);
void QAPI quark_pool_int_array_new_copy(quark_pool_int_array *r_dest, const quark_pool_int_array *p_src);
void QAPI quark_pool_int_array_new_with_array(quark_pool_int_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_int_array_append(quark_pool_int_array *p_self, const quark_int p_data);

void QAPI quark_pool_int_array_append_array(quark_pool_int_array *p_self, const quark_pool_int_array *p_array);

quark_error QAPI quark_pool_int_array_insert(quark_pool_int_array *p_self, const quark_int p_idx, const quark_int p_data);

void QAPI quark_pool_int_array_invert(quark_pool_int_array *p_self);

void QAPI quark_pool_int_array_push_back(quark_pool_int_array *p_self, const quark_int p_data);

void QAPI quark_pool_int_array_remove(quark_pool_int_array *p_self, const quark_int p_idx);

void QAPI quark_pool_int_array_resize(quark_pool_int_array *p_self, const quark_int p_size);

quark_pool_int_array_read_access QAPI *quark_pool_int_array_read(const quark_pool_int_array *p_self);

quark_pool_int_array_write_access QAPI *quark_pool_int_array_write(quark_pool_int_array *p_self);

void QAPI quark_pool_int_array_set(quark_pool_int_array *p_self, const quark_int p_idx, const quark_int p_data);
quark_int QAPI quark_pool_int_array_get(const quark_pool_int_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_int_array_size(const quark_pool_int_array *p_self);

void QAPI quark_pool_int_array_destroy(quark_pool_int_array *p_self);

// real

void QAPI quark_pool_real_array_new(quark_pool_real_array *r_dest);
void QAPI quark_pool_real_array_new_copy(quark_pool_real_array *r_dest, const quark_pool_real_array *p_src);
void QAPI quark_pool_real_array_new_with_array(quark_pool_real_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_real_array_append(quark_pool_real_array *p_self, const quark_real p_data);

void QAPI quark_pool_real_array_append_array(quark_pool_real_array *p_self, const quark_pool_real_array *p_array);

quark_error QAPI quark_pool_real_array_insert(quark_pool_real_array *p_self, const quark_int p_idx, const quark_real p_data);

void QAPI quark_pool_real_array_invert(quark_pool_real_array *p_self);

void QAPI quark_pool_real_array_push_back(quark_pool_real_array *p_self, const quark_real p_data);

void QAPI quark_pool_real_array_remove(quark_pool_real_array *p_self, const quark_int p_idx);

void QAPI quark_pool_real_array_resize(quark_pool_real_array *p_self, const quark_int p_size);

quark_pool_real_array_read_access QAPI *quark_pool_real_array_read(const quark_pool_real_array *p_self);

quark_pool_real_array_write_access QAPI *quark_pool_real_array_write(quark_pool_real_array *p_self);

void QAPI quark_pool_real_array_set(quark_pool_real_array *p_self, const quark_int p_idx, const quark_real p_data);
quark_real QAPI quark_pool_real_array_get(const quark_pool_real_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_real_array_size(const quark_pool_real_array *p_self);

void QAPI quark_pool_real_array_destroy(quark_pool_real_array *p_self);

// string

void QAPI quark_pool_string_array_new(quark_pool_string_array *r_dest);
void QAPI quark_pool_string_array_new_copy(quark_pool_string_array *r_dest, const quark_pool_string_array *p_src);
void QAPI quark_pool_string_array_new_with_array(quark_pool_string_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_string_array_append(quark_pool_string_array *p_self, const quark_string *p_data);

void QAPI quark_pool_string_array_append_array(quark_pool_string_array *p_self, const quark_pool_string_array *p_array);

quark_error QAPI quark_pool_string_array_insert(quark_pool_string_array *p_self, const quark_int p_idx, const quark_string *p_data);

void QAPI quark_pool_string_array_invert(quark_pool_string_array *p_self);

void QAPI quark_pool_string_array_push_back(quark_pool_string_array *p_self, const quark_string *p_data);

void QAPI quark_pool_string_array_remove(quark_pool_string_array *p_self, const quark_int p_idx);

void QAPI quark_pool_string_array_resize(quark_pool_string_array *p_self, const quark_int p_size);

quark_pool_string_array_read_access QAPI *quark_pool_string_array_read(const quark_pool_string_array *p_self);

quark_pool_string_array_write_access QAPI *quark_pool_string_array_write(quark_pool_string_array *p_self);

void QAPI quark_pool_string_array_set(quark_pool_string_array *p_self, const quark_int p_idx, const quark_string *p_data);
quark_string QAPI quark_pool_string_array_get(const quark_pool_string_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_string_array_size(const quark_pool_string_array *p_self);

void QAPI quark_pool_string_array_destroy(quark_pool_string_array *p_self);

// vector2

void QAPI quark_pool_vector2_array_new(quark_pool_vector2_array *r_dest);
void QAPI quark_pool_vector2_array_new_copy(quark_pool_vector2_array *r_dest, const quark_pool_vector2_array *p_src);
void QAPI quark_pool_vector2_array_new_with_array(quark_pool_vector2_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_vector2_array_append(quark_pool_vector2_array *p_self, const quark_vector2 *p_data);

void QAPI quark_pool_vector2_array_append_array(quark_pool_vector2_array *p_self, const quark_pool_vector2_array *p_array);

quark_error QAPI quark_pool_vector2_array_insert(quark_pool_vector2_array *p_self, const quark_int p_idx, const quark_vector2 *p_data);

void QAPI quark_pool_vector2_array_invert(quark_pool_vector2_array *p_self);

void QAPI quark_pool_vector2_array_push_back(quark_pool_vector2_array *p_self, const quark_vector2 *p_data);

void QAPI quark_pool_vector2_array_remove(quark_pool_vector2_array *p_self, const quark_int p_idx);

void QAPI quark_pool_vector2_array_resize(quark_pool_vector2_array *p_self, const quark_int p_size);

quark_pool_vector2_array_read_access QAPI *quark_pool_vector2_array_read(const quark_pool_vector2_array *p_self);

quark_pool_vector2_array_write_access QAPI *quark_pool_vector2_array_write(quark_pool_vector2_array *p_self);

void QAPI quark_pool_vector2_array_set(quark_pool_vector2_array *p_self, const quark_int p_idx, const quark_vector2 *p_data);
quark_vector2 QAPI quark_pool_vector2_array_get(const quark_pool_vector2_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_vector2_array_size(const quark_pool_vector2_array *p_self);

void QAPI quark_pool_vector2_array_destroy(quark_pool_vector2_array *p_self);

// vector3

void QAPI quark_pool_vector3_array_new(quark_pool_vector3_array *r_dest);
void QAPI quark_pool_vector3_array_new_copy(quark_pool_vector3_array *r_dest, const quark_pool_vector3_array *p_src);
void QAPI quark_pool_vector3_array_new_with_array(quark_pool_vector3_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_vector3_array_append(quark_pool_vector3_array *p_self, const quark_vector3 *p_data);

void QAPI quark_pool_vector3_array_append_array(quark_pool_vector3_array *p_self, const quark_pool_vector3_array *p_array);

quark_error QAPI quark_pool_vector3_array_insert(quark_pool_vector3_array *p_self, const quark_int p_idx, const quark_vector3 *p_data);

void QAPI quark_pool_vector3_array_invert(quark_pool_vector3_array *p_self);

void QAPI quark_pool_vector3_array_push_back(quark_pool_vector3_array *p_self, const quark_vector3 *p_data);

void QAPI quark_pool_vector3_array_remove(quark_pool_vector3_array *p_self, const quark_int p_idx);

void QAPI quark_pool_vector3_array_resize(quark_pool_vector3_array *p_self, const quark_int p_size);

quark_pool_vector3_array_read_access QAPI *quark_pool_vector3_array_read(const quark_pool_vector3_array *p_self);

quark_pool_vector3_array_write_access QAPI *quark_pool_vector3_array_write(quark_pool_vector3_array *p_self);

void QAPI quark_pool_vector3_array_set(quark_pool_vector3_array *p_self, const quark_int p_idx, const quark_vector3 *p_data);
quark_vector3 QAPI quark_pool_vector3_array_get(const quark_pool_vector3_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_vector3_array_size(const quark_pool_vector3_array *p_self);

void QAPI quark_pool_vector3_array_destroy(quark_pool_vector3_array *p_self);

// color

void QAPI quark_pool_color_array_new(quark_pool_color_array *r_dest);
void QAPI quark_pool_color_array_new_copy(quark_pool_color_array *r_dest, const quark_pool_color_array *p_src);
void QAPI quark_pool_color_array_new_with_array(quark_pool_color_array *r_dest, const quark_array *p_a);

void QAPI quark_pool_color_array_append(quark_pool_color_array *p_self, const quark_color *p_data);

void QAPI quark_pool_color_array_append_array(quark_pool_color_array *p_self, const quark_pool_color_array *p_array);

quark_error QAPI quark_pool_color_array_insert(quark_pool_color_array *p_self, const quark_int p_idx, const quark_color *p_data);

void QAPI quark_pool_color_array_invert(quark_pool_color_array *p_self);

void QAPI quark_pool_color_array_push_back(quark_pool_color_array *p_self, const quark_color *p_data);

void QAPI quark_pool_color_array_remove(quark_pool_color_array *p_self, const quark_int p_idx);

void QAPI quark_pool_color_array_resize(quark_pool_color_array *p_self, const quark_int p_size);

quark_pool_color_array_read_access QAPI *quark_pool_color_array_read(const quark_pool_color_array *p_self);

quark_pool_color_array_write_access QAPI *quark_pool_color_array_write(quark_pool_color_array *p_self);

void QAPI quark_pool_color_array_set(quark_pool_color_array *p_self, const quark_int p_idx, const quark_color *p_data);
quark_color QAPI quark_pool_color_array_get(const quark_pool_color_array *p_self, const quark_int p_idx);

quark_int QAPI quark_pool_color_array_size(const quark_pool_color_array *p_self);

void QAPI quark_pool_color_array_destroy(quark_pool_color_array *p_self);

//
// read accessor functions
//

quark_pool_byte_array_read_access QAPI *quark_pool_byte_array_read_access_copy(const quark_pool_byte_array_read_access *p_other);
const uint8_t QAPI *quark_pool_byte_array_read_access_ptr(const quark_pool_byte_array_read_access *p_read);
void QAPI quark_pool_byte_array_read_access_operator_assign(quark_pool_byte_array_read_access *p_read, quark_pool_byte_array_read_access *p_other);
void QAPI quark_pool_byte_array_read_access_destroy(quark_pool_byte_array_read_access *p_read);

quark_pool_int_array_read_access QAPI *quark_pool_int_array_read_access_copy(const quark_pool_int_array_read_access *p_other);
const quark_int QAPI *quark_pool_int_array_read_access_ptr(const quark_pool_int_array_read_access *p_read);
void QAPI quark_pool_int_array_read_access_operator_assign(quark_pool_int_array_read_access *p_read, quark_pool_int_array_read_access *p_other);
void QAPI quark_pool_int_array_read_access_destroy(quark_pool_int_array_read_access *p_read);

quark_pool_real_array_read_access QAPI *quark_pool_real_array_read_access_copy(const quark_pool_real_array_read_access *p_other);
const quark_real QAPI *quark_pool_real_array_read_access_ptr(const quark_pool_real_array_read_access *p_read);
void QAPI quark_pool_real_array_read_access_operator_assign(quark_pool_real_array_read_access *p_read, quark_pool_real_array_read_access *p_other);
void QAPI quark_pool_real_array_read_access_destroy(quark_pool_real_array_read_access *p_read);

quark_pool_string_array_read_access QAPI *quark_pool_string_array_read_access_copy(const quark_pool_string_array_read_access *p_other);
const quark_string QAPI *quark_pool_string_array_read_access_ptr(const quark_pool_string_array_read_access *p_read);
void QAPI quark_pool_string_array_read_access_operator_assign(quark_pool_string_array_read_access *p_read, quark_pool_string_array_read_access *p_other);
void QAPI quark_pool_string_array_read_access_destroy(quark_pool_string_array_read_access *p_read);

quark_pool_vector2_array_read_access QAPI *quark_pool_vector2_array_read_access_copy(const quark_pool_vector2_array_read_access *p_other);
const quark_vector2 QAPI *quark_pool_vector2_array_read_access_ptr(const quark_pool_vector2_array_read_access *p_read);
void QAPI quark_pool_vector2_array_read_access_operator_assign(quark_pool_vector2_array_read_access *p_read, quark_pool_vector2_array_read_access *p_other);
void QAPI quark_pool_vector2_array_read_access_destroy(quark_pool_vector2_array_read_access *p_read);

quark_pool_vector3_array_read_access QAPI *quark_pool_vector3_array_read_access_copy(const quark_pool_vector3_array_read_access *p_other);
const quark_vector3 QAPI *quark_pool_vector3_array_read_access_ptr(const quark_pool_vector3_array_read_access *p_read);
void QAPI quark_pool_vector3_array_read_access_operator_assign(quark_pool_vector3_array_read_access *p_read, quark_pool_vector3_array_read_access *p_other);
void QAPI quark_pool_vector3_array_read_access_destroy(quark_pool_vector3_array_read_access *p_read);

quark_pool_color_array_read_access QAPI *quark_pool_color_array_read_access_copy(const quark_pool_color_array_read_access *p_other);
const quark_color QAPI *quark_pool_color_array_read_access_ptr(const quark_pool_color_array_read_access *p_read);
void QAPI quark_pool_color_array_read_access_operator_assign(quark_pool_color_array_read_access *p_read, quark_pool_color_array_read_access *p_other);
void QAPI quark_pool_color_array_read_access_destroy(quark_pool_color_array_read_access *p_read);

//
// write accessor functions
//

quark_pool_byte_array_write_access QAPI *quark_pool_byte_array_write_access_copy(const quark_pool_byte_array_write_access *p_other);
uint8_t QAPI *quark_pool_byte_array_write_access_ptr(const quark_pool_byte_array_write_access *p_write);
void QAPI quark_pool_byte_array_write_access_operator_assign(quark_pool_byte_array_write_access *p_write, quark_pool_byte_array_write_access *p_other);
void QAPI quark_pool_byte_array_write_access_destroy(quark_pool_byte_array_write_access *p_write);

quark_pool_int_array_write_access QAPI *quark_pool_int_array_write_access_copy(const quark_pool_int_array_write_access *p_other);
quark_int QAPI *quark_pool_int_array_write_access_ptr(const quark_pool_int_array_write_access *p_write);
void QAPI quark_pool_int_array_write_access_operator_assign(quark_pool_int_array_write_access *p_write, quark_pool_int_array_write_access *p_other);
void QAPI quark_pool_int_array_write_access_destroy(quark_pool_int_array_write_access *p_write);

quark_pool_real_array_write_access QAPI *quark_pool_real_array_write_access_copy(const quark_pool_real_array_write_access *p_other);
quark_real QAPI *quark_pool_real_array_write_access_ptr(const quark_pool_real_array_write_access *p_write);
void QAPI quark_pool_real_array_write_access_operator_assign(quark_pool_real_array_write_access *p_write, quark_pool_real_array_write_access *p_other);
void QAPI quark_pool_real_array_write_access_destroy(quark_pool_real_array_write_access *p_write);

quark_pool_string_array_write_access QAPI *quark_pool_string_array_write_access_copy(const quark_pool_string_array_write_access *p_other);
quark_string QAPI *quark_pool_string_array_write_access_ptr(const quark_pool_string_array_write_access *p_write);
void QAPI quark_pool_string_array_write_access_operator_assign(quark_pool_string_array_write_access *p_write, quark_pool_string_array_write_access *p_other);
void QAPI quark_pool_string_array_write_access_destroy(quark_pool_string_array_write_access *p_write);

quark_pool_vector2_array_write_access QAPI *quark_pool_vector2_array_write_access_copy(const quark_pool_vector2_array_write_access *p_other);
quark_vector2 QAPI *quark_pool_vector2_array_write_access_ptr(const quark_pool_vector2_array_write_access *p_write);
void QAPI quark_pool_vector2_array_write_access_operator_assign(quark_pool_vector2_array_write_access *p_write, quark_pool_vector2_array_write_access *p_other);
void QAPI quark_pool_vector2_array_write_access_destroy(quark_pool_vector2_array_write_access *p_write);

quark_pool_vector3_array_write_access QAPI *quark_pool_vector3_array_write_access_copy(const quark_pool_vector3_array_write_access *p_other);
quark_vector3 QAPI *quark_pool_vector3_array_write_access_ptr(const quark_pool_vector3_array_write_access *p_write);
void QAPI quark_pool_vector3_array_write_access_operator_assign(quark_pool_vector3_array_write_access *p_write, quark_pool_vector3_array_write_access *p_other);
void QAPI quark_pool_vector3_array_write_access_destroy(quark_pool_vector3_array_write_access *p_write);

quark_pool_color_array_write_access QAPI *quark_pool_color_array_write_access_copy(const quark_pool_color_array_write_access *p_other);
quark_color QAPI *quark_pool_color_array_write_access_ptr(const quark_pool_color_array_write_access *p_write);
void QAPI quark_pool_color_array_write_access_operator_assign(quark_pool_color_array_write_access *p_write, quark_pool_color_array_write_access *p_other);
void QAPI quark_pool_color_array_write_access_destroy(quark_pool_color_array_write_access *p_write);

#ifdef __cplusplus
}
#endif

#endif // QUARK_POOL_ARRAYS_H
