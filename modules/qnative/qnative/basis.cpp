/*************************************************************************/
/*  basis.cpp                                                            */
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

#include "qnative/basis.h"

#include "core/math/matrix3.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_basis_new_with_rows(quark_basis *r_dest, const quark_vector3 *p_x_axis, const quark_vector3 *p_y_axis, const quark_vector3 *p_z_axis) {
	const Vector3 *x_axis = (const Vector3 *)p_x_axis;
	const Vector3 *y_axis = (const Vector3 *)p_y_axis;
	const Vector3 *z_axis = (const Vector3 *)p_z_axis;
	Basis *dest = (Basis *)r_dest;
	*dest = Basis(*x_axis, *y_axis, *z_axis);
}

void QAPI quark_basis_new_with_axis_and_angle(quark_basis *r_dest, const quark_vector3 *p_axis, const quark_real p_phi) {
	const Vector3 *axis = (const Vector3 *)p_axis;
	Basis *dest = (Basis *)r_dest;
	*dest = Basis(*axis, p_phi);
}

void QAPI quark_basis_new_with_euler(quark_basis *r_dest, const quark_vector3 *p_euler) {
	const Vector3 *euler = (const Vector3 *)p_euler;
	Basis *dest = (Basis *)r_dest;
	*dest = Basis(*euler);
}

quark_string QAPI quark_basis_as_string(const quark_basis *p_self) {
	quark_string ret;
	const Basis *self = (const Basis *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_basis QAPI quark_basis_inverse(const quark_basis *p_self) {
	quark_basis dest;
	const Basis *self = (const Basis *)p_self;
	*((Basis *)&dest) = self->inverse();
	return dest;
}

quark_basis QAPI quark_basis_transposed(const quark_basis *p_self) {
	quark_basis dest;
	const Basis *self = (const Basis *)p_self;
	*((Basis *)&dest) = self->transposed();
	return dest;
}

quark_basis QAPI quark_basis_orthonormalized(const quark_basis *p_self) {
	quark_basis dest;
	const Basis *self = (const Basis *)p_self;
	*((Basis *)&dest) = self->orthonormalized();
	return dest;
}

quark_real QAPI quark_basis_determinant(const quark_basis *p_self) {
	const Basis *self = (const Basis *)p_self;
	return self->determinant();
}

quark_basis QAPI quark_basis_rotated(const quark_basis *p_self, const quark_vector3 *p_axis, const quark_real p_phi) {
	quark_basis dest;
	const Basis *self = (const Basis *)p_self;
	const Vector3 *axis = (const Vector3 *)p_axis;
	*((Basis *)&dest) = self->rotated(*axis, p_phi);
	return dest;
}

quark_basis QAPI quark_basis_scaled(const quark_basis *p_self, const quark_vector3 *p_scale) {
	quark_basis dest;
	const Basis *self = (const Basis *)p_self;
	const Vector3 *scale = (const Vector3 *)p_scale;
	*((Basis *)&dest) = self->scaled(*scale);
	return dest;
}

quark_vector3 QAPI quark_basis_get_scale(const quark_basis *p_self) {
	quark_vector3 dest;
	const Basis *self = (const Basis *)p_self;
	*((Vector3 *)&dest) = self->get_scale();
	return dest;
}

quark_vector3 QAPI quark_basis_get_euler(const quark_basis *p_self) {
	quark_vector3 dest;
	const Basis *self = (const Basis *)p_self;
	*((Vector3 *)&dest) = self->get_euler();
	return dest;
}

quark_real QAPI quark_basis_tdotx(const quark_basis *p_self, const quark_vector3 *p_with) {
	const Basis *self = (const Basis *)p_self;
	const Vector3 *with = (const Vector3 *)p_with;
	return self->tdotx(*with);
}

quark_real QAPI quark_basis_tdoty(const quark_basis *p_self, const quark_vector3 *p_with) {
	const Basis *self = (const Basis *)p_self;
	const Vector3 *with = (const Vector3 *)p_with;
	return self->tdoty(*with);
}

quark_real QAPI quark_basis_tdotz(const quark_basis *p_self, const quark_vector3 *p_with) {
	const Basis *self = (const Basis *)p_self;
	const Vector3 *with = (const Vector3 *)p_with;
	return self->tdotz(*with);
}

quark_vector3 QAPI quark_basis_xform(const quark_basis *p_self, const quark_vector3 *p_v) {
	quark_vector3 dest;
	const Basis *self = (const Basis *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*((Vector3 *)&dest) = self->xform(*v);
	return dest;
}

quark_vector3 QAPI quark_basis_xform_inv(const quark_basis *p_self, const quark_vector3 *p_v) {
	quark_vector3 dest;
	const Basis *self = (const Basis *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*((Vector3 *)&dest) = self->xform_inv(*v);
	return dest;
}

quark_int QAPI quark_basis_get_orthogonal_index(const quark_basis *p_self) {
	const Basis *self = (const Basis *)p_self;
	return self->get_orthogonal_index();
}

void QAPI quark_basis_new(quark_basis *r_dest) {
	Basis *dest = (Basis *)r_dest;
	*dest = Basis();
}

void QAPI quark_basis_new_with_euler_quat(quark_basis *r_dest, const quark_quat *p_euler) {
	Basis *dest = (Basis *)r_dest;
	const Quat *euler = (const Quat *)p_euler;
	*dest = Basis(*euler);
}

// p_elements is a pointer to an array of 3 (!!) vector3
void QAPI quark_basis_get_elements(const quark_basis *p_self, quark_vector3 *p_elements) {
	const Basis *self = (const Basis *)p_self;
	Vector3 *elements = (Vector3 *)p_elements;
	elements[0] = self->elements[0];
	elements[1] = self->elements[1];
	elements[2] = self->elements[2];
}

quark_vector3 QAPI quark_basis_get_axis(const quark_basis *p_self, const quark_int p_axis) {
	quark_vector3 dest;
	Vector3 *d = (Vector3 *)&dest;
	const Basis *self = (const Basis *)p_self;
	*d = self->get_axis(p_axis);
	return dest;
}

void QAPI quark_basis_set_axis(quark_basis *p_self, const quark_int p_axis, const quark_vector3 *p_value) {
	Basis *self = (Basis *)p_self;
	const Vector3 *value = (const Vector3 *)p_value;
	self->set_axis(p_axis, *value);
}

quark_vector3 QAPI quark_basis_get_row(const quark_basis *p_self, const quark_int p_row) {
	quark_vector3 dest;
	Vector3 *d = (Vector3 *)&dest;
	const Basis *self = (const Basis *)p_self;
	*d = self->get_row(p_row);
	return dest;
}

void QAPI quark_basis_set_row(quark_basis *p_self, const quark_int p_row, const quark_vector3 *p_value) {
	Basis *self = (Basis *)p_self;
	const Vector3 *value = (const Vector3 *)p_value;
	self->set_row(p_row, *value);
}

quark_bool QAPI quark_basis_operator_equal(const quark_basis *p_self, const quark_basis *p_b) {
	const Basis *self = (const Basis *)p_self;
	const Basis *b = (const Basis *)p_b;
	return *self == *b;
}

quark_basis QAPI quark_basis_operator_add(const quark_basis *p_self, const quark_basis *p_b) {
	quark_basis raw_dest;
	Basis *dest = (Basis *)&raw_dest;
	const Basis *self = (const Basis *)p_self;
	const Basis *b = (const Basis *)p_b;
	*dest = *self + *b;
	return raw_dest;
}

quark_basis QAPI quark_basis_operator_subtract(const quark_basis *p_self, const quark_basis *p_b) {
	quark_basis raw_dest;
	Basis *dest = (Basis *)&raw_dest;
	const Basis *self = (const Basis *)p_self;
	const Basis *b = (const Basis *)p_b;
	*dest = *self - *b;
	return raw_dest;
}

quark_basis QAPI quark_basis_operator_multiply_vector(const quark_basis *p_self, const quark_basis *p_b) {
	quark_basis raw_dest;
	Basis *dest = (Basis *)&raw_dest;
	const Basis *self = (const Basis *)p_self;
	const Basis *b = (const Basis *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

quark_basis QAPI quark_basis_operator_multiply_scalar(const quark_basis *p_self, const quark_real p_b) {
	quark_basis raw_dest;
	Basis *dest = (Basis *)&raw_dest;
	const Basis *self = (const Basis *)p_self;
	*dest = *self * p_b;
	return raw_dest;
}

#ifdef __cplusplus
}
#endif
