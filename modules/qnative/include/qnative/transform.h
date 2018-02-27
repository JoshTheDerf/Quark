/*************************************************************************/
/*  transform.h                                                          */
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

#ifndef QUARK_TRANSFORM_H
#define QUARK_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_TRANSFORM_SIZE 48

#ifndef QUARK_CORE_API_QUARK_TRANSFORM_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_TRANSFORM_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_TRANSFORM_SIZE];
} quark_transform;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/basis.h>
#include <qnative/qnative.h>
#include <qnative/variant.h>
#include <qnative/vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_transform_new_with_axis_origin(quark_transform *r_dest, const quark_vector3 *p_x_axis, const quark_vector3 *p_y_axis, const quark_vector3 *p_z_axis, const quark_vector3 *p_origin);
void QAPI quark_transform_new(quark_transform *r_dest, const quark_basis *p_basis, const quark_vector3 *p_origin);

quark_basis QAPI quark_transform_get_basis(const quark_transform *p_self);
void QAPI quark_transform_set_basis(quark_transform *p_self, const quark_basis *p_v);

quark_vector3 QAPI quark_transform_get_origin(const quark_transform *p_self);
void QAPI quark_transform_set_origin(quark_transform *p_self, const quark_vector3 *p_v);

quark_string QAPI quark_transform_as_string(const quark_transform *p_self);

quark_transform QAPI quark_transform_inverse(const quark_transform *p_self);

quark_transform QAPI quark_transform_affine_inverse(const quark_transform *p_self);

quark_transform QAPI quark_transform_orthonormalized(const quark_transform *p_self);

quark_transform QAPI quark_transform_rotated(const quark_transform *p_self, const quark_vector3 *p_axis, const quark_real p_phi);

quark_transform QAPI quark_transform_scaled(const quark_transform *p_self, const quark_vector3 *p_scale);

quark_transform QAPI quark_transform_translated(const quark_transform *p_self, const quark_vector3 *p_ofs);

quark_transform QAPI quark_transform_looking_at(const quark_transform *p_self, const quark_vector3 *p_target, const quark_vector3 *p_up);

quark_plane QAPI quark_transform_xform_plane(const quark_transform *p_self, const quark_plane *p_v);

quark_plane QAPI quark_transform_xform_inv_plane(const quark_transform *p_self, const quark_plane *p_v);

void QAPI quark_transform_new_identity(quark_transform *r_dest);

quark_bool QAPI quark_transform_operator_equal(const quark_transform *p_self, const quark_transform *p_b);

quark_transform QAPI quark_transform_operator_multiply(const quark_transform *p_self, const quark_transform *p_b);

quark_vector3 QAPI quark_transform_xform_vector3(const quark_transform *p_self, const quark_vector3 *p_v);

quark_vector3 QAPI quark_transform_xform_inv_vector3(const quark_transform *p_self, const quark_vector3 *p_v);

quark_aabb QAPI quark_transform_xform_aabb(const quark_transform *p_self, const quark_aabb *p_v);

quark_aabb QAPI quark_transform_xform_inv_aabb(const quark_transform *p_self, const quark_aabb *p_v);

#ifdef __cplusplus
}
#endif

#endif // QUARK_TRANSFORM_H
