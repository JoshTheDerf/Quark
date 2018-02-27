/*************************************************************************/
/*  transform2d.h                                                        */
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

#ifndef QUARK_TRANSFORM2D_H
#define QUARK_TRANSFORM2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_TRANSFORM2D_SIZE 24

#ifndef QUARK_CORE_API_QUARK_TRANSFORM2D_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_TRANSFORM2D_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_TRANSFORM2D_SIZE];
} quark_transform2d;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/variant.h>
#include <qnative/vector2.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_transform2d_new(quark_transform2d *r_dest, const quark_real p_rot, const quark_vector2 *p_pos);
void QAPI quark_transform2d_new_axis_origin(quark_transform2d *r_dest, const quark_vector2 *p_x_axis, const quark_vector2 *p_y_axis, const quark_vector2 *p_origin);

quark_string QAPI quark_transform2d_as_string(const quark_transform2d *p_self);

quark_transform2d QAPI quark_transform2d_inverse(const quark_transform2d *p_self);

quark_transform2d QAPI quark_transform2d_affine_inverse(const quark_transform2d *p_self);

quark_real QAPI quark_transform2d_get_rotation(const quark_transform2d *p_self);

quark_vector2 QAPI quark_transform2d_get_origin(const quark_transform2d *p_self);

quark_vector2 QAPI quark_transform2d_get_scale(const quark_transform2d *p_self);

quark_transform2d QAPI quark_transform2d_orthonormalized(const quark_transform2d *p_self);

quark_transform2d QAPI quark_transform2d_rotated(const quark_transform2d *p_self, const quark_real p_phi);

quark_transform2d QAPI quark_transform2d_scaled(const quark_transform2d *p_self, const quark_vector2 *p_scale);

quark_transform2d QAPI quark_transform2d_translated(const quark_transform2d *p_self, const quark_vector2 *p_offset);

quark_vector2 QAPI quark_transform2d_xform_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v);

quark_vector2 QAPI quark_transform2d_xform_inv_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v);

quark_vector2 QAPI quark_transform2d_basis_xform_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v);

quark_vector2 QAPI quark_transform2d_basis_xform_inv_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v);

quark_transform2d QAPI quark_transform2d_interpolate_with(const quark_transform2d *p_self, const quark_transform2d *p_m, const quark_real p_c);

quark_bool QAPI quark_transform2d_operator_equal(const quark_transform2d *p_self, const quark_transform2d *p_b);

quark_transform2d QAPI quark_transform2d_operator_multiply(const quark_transform2d *p_self, const quark_transform2d *p_b);

void QAPI quark_transform2d_new_identity(quark_transform2d *r_dest);

quark_rect2 QAPI quark_transform2d_xform_rect2(const quark_transform2d *p_self, const quark_rect2 *p_v);

quark_rect2 QAPI quark_transform2d_xform_inv_rect2(const quark_transform2d *p_self, const quark_rect2 *p_v);

#ifdef __cplusplus
}
#endif

#endif // QUARK_TRANSFORM2D_H
