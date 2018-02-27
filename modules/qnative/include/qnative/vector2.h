/*************************************************************************/
/*  vector2.h                                                            */
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

#ifndef QUARK_VECTOR2_H
#define QUARK_VECTOR2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_VECTOR2_SIZE 8

#ifndef QUARK_CORE_API_QUARK_VECTOR2_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_VECTOR2_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_VECTOR2_SIZE];
} quark_vector2;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_vector2_new(quark_vector2 *r_dest, const quark_real p_x, const quark_real p_y);

quark_string QAPI quark_vector2_as_string(const quark_vector2 *p_self);

quark_vector2 QAPI quark_vector2_normalized(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_length(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_angle(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_length_squared(const quark_vector2 *p_self);

quark_bool QAPI quark_vector2_is_normalized(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_distance_to(const quark_vector2 *p_self, const quark_vector2 *p_to);

quark_real QAPI quark_vector2_distance_squared_to(const quark_vector2 *p_self, const quark_vector2 *p_to);

quark_real QAPI quark_vector2_angle_to(const quark_vector2 *p_self, const quark_vector2 *p_to);

quark_real QAPI quark_vector2_angle_to_point(const quark_vector2 *p_self, const quark_vector2 *p_to);

quark_vector2 QAPI quark_vector2_linear_interpolate(const quark_vector2 *p_self, const quark_vector2 *p_b, const quark_real p_t);

quark_vector2 QAPI quark_vector2_cubic_interpolate(const quark_vector2 *p_self, const quark_vector2 *p_b, const quark_vector2 *p_pre_a, const quark_vector2 *p_post_b, const quark_real p_t);

quark_vector2 QAPI quark_vector2_rotated(const quark_vector2 *p_self, const quark_real p_phi);

quark_vector2 QAPI quark_vector2_tangent(const quark_vector2 *p_self);

quark_vector2 QAPI quark_vector2_floor(const quark_vector2 *p_self);

quark_vector2 QAPI quark_vector2_snapped(const quark_vector2 *p_self, const quark_vector2 *p_by);

quark_real QAPI quark_vector2_aspect(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_dot(const quark_vector2 *p_self, const quark_vector2 *p_with);

quark_vector2 QAPI quark_vector2_slide(const quark_vector2 *p_self, const quark_vector2 *p_n);

quark_vector2 QAPI quark_vector2_bounce(const quark_vector2 *p_self, const quark_vector2 *p_n);

quark_vector2 QAPI quark_vector2_reflect(const quark_vector2 *p_self, const quark_vector2 *p_n);

quark_vector2 QAPI quark_vector2_abs(const quark_vector2 *p_self);

quark_vector2 QAPI quark_vector2_clamped(const quark_vector2 *p_self, const quark_real p_length);

quark_vector2 QAPI quark_vector2_operator_add(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_vector2 QAPI quark_vector2_operator_subtract(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_vector2 QAPI quark_vector2_operator_multiply_vector(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_vector2 QAPI quark_vector2_operator_multiply_scalar(const quark_vector2 *p_self, const quark_real p_b);

quark_vector2 QAPI quark_vector2_operator_divide_vector(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_vector2 QAPI quark_vector2_operator_divide_scalar(const quark_vector2 *p_self, const quark_real p_b);

quark_bool QAPI quark_vector2_operator_equal(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_bool QAPI quark_vector2_operator_less(const quark_vector2 *p_self, const quark_vector2 *p_b);

quark_vector2 QAPI quark_vector2_operator_neg(const quark_vector2 *p_self);

void QAPI quark_vector2_set_x(quark_vector2 *p_self, const quark_real p_x);

void QAPI quark_vector2_set_y(quark_vector2 *p_self, const quark_real p_y);

quark_real QAPI quark_vector2_get_x(const quark_vector2 *p_self);

quark_real QAPI quark_vector2_get_y(const quark_vector2 *p_self);

#ifdef __cplusplus
}
#endif

#endif // QUARK_VECTOR2_H
