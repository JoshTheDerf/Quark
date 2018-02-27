/*************************************************************************/
/*  basis.h                                                              */
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

#ifndef QUARK_BASIS_H
#define QUARK_BASIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_BASIS_SIZE 36

#ifndef QUARK_CORE_API_QUARK_BASIS_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_BASIS_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_BASIS_SIZE];
} quark_basis;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/quat.h>
#include <qnative/vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_basis_new_with_rows(quark_basis *r_dest, const quark_vector3 *p_x_axis, const quark_vector3 *p_y_axis, const quark_vector3 *p_z_axis);
void QAPI quark_basis_new_with_axis_and_angle(quark_basis *r_dest, const quark_vector3 *p_axis, const quark_real p_phi);
void QAPI quark_basis_new_with_euler(quark_basis *r_dest, const quark_vector3 *p_euler);

quark_string QAPI quark_basis_as_string(const quark_basis *p_self);

quark_basis QAPI quark_basis_inverse(const quark_basis *p_self);

quark_basis QAPI quark_basis_transposed(const quark_basis *p_self);

quark_basis QAPI quark_basis_orthonormalized(const quark_basis *p_self);

quark_real QAPI quark_basis_determinant(const quark_basis *p_self);

quark_basis QAPI quark_basis_rotated(const quark_basis *p_self, const quark_vector3 *p_axis, const quark_real p_phi);

quark_basis QAPI quark_basis_scaled(const quark_basis *p_self, const quark_vector3 *p_scale);

quark_vector3 QAPI quark_basis_get_scale(const quark_basis *p_self);

quark_vector3 QAPI quark_basis_get_euler(const quark_basis *p_self);

quark_real QAPI quark_basis_tdotx(const quark_basis *p_self, const quark_vector3 *p_with);

quark_real QAPI quark_basis_tdoty(const quark_basis *p_self, const quark_vector3 *p_with);

quark_real QAPI quark_basis_tdotz(const quark_basis *p_self, const quark_vector3 *p_with);

quark_vector3 QAPI quark_basis_xform(const quark_basis *p_self, const quark_vector3 *p_v);

quark_vector3 QAPI quark_basis_xform_inv(const quark_basis *p_self, const quark_vector3 *p_v);

quark_int QAPI quark_basis_get_orthogonal_index(const quark_basis *p_self);

void QAPI quark_basis_new(quark_basis *r_dest);

void QAPI quark_basis_new_with_euler_quat(quark_basis *r_dest, const quark_quat *p_euler);

// p_elements is a pointer to an array of 3 (!!) vector3
void QAPI quark_basis_get_elements(const quark_basis *p_self, quark_vector3 *p_elements);

quark_vector3 QAPI quark_basis_get_axis(const quark_basis *p_self, const quark_int p_axis);

void QAPI quark_basis_set_axis(quark_basis *p_self, const quark_int p_axis, const quark_vector3 *p_value);

quark_vector3 QAPI quark_basis_get_row(const quark_basis *p_self, const quark_int p_row);

void QAPI quark_basis_set_row(quark_basis *p_self, const quark_int p_row, const quark_vector3 *p_value);

quark_bool QAPI quark_basis_operator_equal(const quark_basis *p_self, const quark_basis *p_b);

quark_basis QAPI quark_basis_operator_add(const quark_basis *p_self, const quark_basis *p_b);

quark_basis QAPI quark_basis_operator_subtract(const quark_basis *p_self, const quark_basis *p_b);

quark_basis QAPI quark_basis_operator_multiply_vector(const quark_basis *p_self, const quark_basis *p_b);

quark_basis QAPI quark_basis_operator_multiply_scalar(const quark_basis *p_self, const quark_real p_b);

#ifdef __cplusplus
}
#endif

#endif // QUARK_BASIS_H
