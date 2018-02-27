/*************************************************************************/
/*  quat.h                                                               */
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

#ifndef QUARK_QUAT_H
#define QUARK_QUAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_QUAT_SIZE 16

#ifndef QUARK_CORE_API_QUARK_QUAT_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_QUAT_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_QUAT_SIZE];
} quark_quat;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_quat_new(quark_quat *r_dest, const quark_real p_x, const quark_real p_y, const quark_real p_z, const quark_real p_w);
void QAPI quark_quat_new_with_axis_angle(quark_quat *r_dest, const quark_vector3 *p_axis, const quark_real p_angle);

quark_real QAPI quark_quat_get_x(const quark_quat *p_self);
void QAPI quark_quat_set_x(quark_quat *p_self, const quark_real val);

quark_real QAPI quark_quat_get_y(const quark_quat *p_self);
void QAPI quark_quat_set_y(quark_quat *p_self, const quark_real val);

quark_real QAPI quark_quat_get_z(const quark_quat *p_self);
void QAPI quark_quat_set_z(quark_quat *p_self, const quark_real val);

quark_real QAPI quark_quat_get_w(const quark_quat *p_self);
void QAPI quark_quat_set_w(quark_quat *p_self, const quark_real val);

quark_string QAPI quark_quat_as_string(const quark_quat *p_self);

quark_real QAPI quark_quat_length(const quark_quat *p_self);

quark_real QAPI quark_quat_length_squared(const quark_quat *p_self);

quark_quat QAPI quark_quat_normalized(const quark_quat *p_self);

quark_bool QAPI quark_quat_is_normalized(const quark_quat *p_self);

quark_quat QAPI quark_quat_inverse(const quark_quat *p_self);

quark_real QAPI quark_quat_dot(const quark_quat *p_self, const quark_quat *p_b);

quark_vector3 QAPI quark_quat_xform(const quark_quat *p_self, const quark_vector3 *p_v);

quark_quat QAPI quark_quat_slerp(const quark_quat *p_self, const quark_quat *p_b, const quark_real p_t);

quark_quat QAPI quark_quat_slerpni(const quark_quat *p_self, const quark_quat *p_b, const quark_real p_t);

quark_quat QAPI quark_quat_cubic_slerp(const quark_quat *p_self, const quark_quat *p_b, const quark_quat *p_pre_a, const quark_quat *p_post_b, const quark_real p_t);

quark_quat QAPI quark_quat_operator_multiply(const quark_quat *p_self, const quark_real p_b);

quark_quat QAPI quark_quat_operator_add(const quark_quat *p_self, const quark_quat *p_b);

quark_quat QAPI quark_quat_operator_subtract(const quark_quat *p_self, const quark_quat *p_b);

quark_quat QAPI quark_quat_operator_divide(const quark_quat *p_self, const quark_real p_b);

quark_bool QAPI quark_quat_operator_equal(const quark_quat *p_self, const quark_quat *p_b);

quark_quat QAPI quark_quat_operator_neg(const quark_quat *p_self);

#ifdef __cplusplus
}
#endif

#endif // QUARK_QUAT_H
