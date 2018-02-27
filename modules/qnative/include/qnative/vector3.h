/*************************************************************************/
/*  vector3.h                                                            */
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

#ifndef QUARK_VECTOR3_H
#define QUARK_VECTOR3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_VECTOR3_SIZE 12

#ifndef QUARK_CORE_API_QUARK_VECTOR3_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_VECTOR3_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_VECTOR3_SIZE];
} quark_vector3;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/basis.h>
#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	QUARK_VECTOR3_AXIS_X,
	QUARK_VECTOR3_AXIS_Y,
	QUARK_VECTOR3_AXIS_Z,
} quark_vector3_axis;

void QAPI quark_vector3_new(quark_vector3 *r_dest, const quark_real p_x, const quark_real p_y, const quark_real p_z);

quark_string QAPI quark_vector3_as_string(const quark_vector3 *p_self);

quark_int QAPI quark_vector3_min_axis(const quark_vector3 *p_self);

quark_int QAPI quark_vector3_max_axis(const quark_vector3 *p_self);

quark_real QAPI quark_vector3_length(const quark_vector3 *p_self);

quark_real QAPI quark_vector3_length_squared(const quark_vector3 *p_self);

quark_bool QAPI quark_vector3_is_normalized(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_normalized(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_inverse(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_snapped(const quark_vector3 *p_self, const quark_vector3 *p_by);

quark_vector3 QAPI quark_vector3_rotated(const quark_vector3 *p_self, const quark_vector3 *p_axis, const quark_real p_phi);

quark_vector3 QAPI quark_vector3_linear_interpolate(const quark_vector3 *p_self, const quark_vector3 *p_b, const quark_real p_t);

quark_vector3 QAPI quark_vector3_cubic_interpolate(const quark_vector3 *p_self, const quark_vector3 *p_b, const quark_vector3 *p_pre_a, const quark_vector3 *p_post_b, const quark_real p_t);

quark_real QAPI quark_vector3_dot(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_cross(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_basis QAPI quark_vector3_outer(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_basis QAPI quark_vector3_to_diagonal_matrix(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_abs(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_floor(const quark_vector3 *p_self);

quark_vector3 QAPI quark_vector3_ceil(const quark_vector3 *p_self);

quark_real QAPI quark_vector3_distance_to(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_real QAPI quark_vector3_distance_squared_to(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_real QAPI quark_vector3_angle_to(const quark_vector3 *p_self, const quark_vector3 *p_to);

quark_vector3 QAPI quark_vector3_slide(const quark_vector3 *p_self, const quark_vector3 *p_n);

quark_vector3 QAPI quark_vector3_bounce(const quark_vector3 *p_self, const quark_vector3 *p_n);

quark_vector3 QAPI quark_vector3_reflect(const quark_vector3 *p_self, const quark_vector3 *p_n);

quark_vector3 QAPI quark_vector3_operator_add(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_operator_subtract(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_operator_multiply_vector(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_operator_multiply_scalar(const quark_vector3 *p_self, const quark_real p_b);

quark_vector3 QAPI quark_vector3_operator_divide_vector(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_operator_divide_scalar(const quark_vector3 *p_self, const quark_real p_b);

quark_bool QAPI quark_vector3_operator_equal(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_bool QAPI quark_vector3_operator_less(const quark_vector3 *p_self, const quark_vector3 *p_b);

quark_vector3 QAPI quark_vector3_operator_neg(const quark_vector3 *p_self);

void QAPI quark_vector3_set_axis(quark_vector3 *p_self, const quark_vector3_axis p_axis, const quark_real p_val);

quark_real QAPI quark_vector3_get_axis(const quark_vector3 *p_self, const quark_vector3_axis p_axis);

#ifdef __cplusplus
}
#endif

#endif // QUARK_VECTOR3_H
