/*************************************************************************/
/*  transform.cpp                                                        */
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

#include "qnative/transform.h"

#include "core/math/transform.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_transform_new_with_axis_origin(quark_transform *r_dest, const quark_vector3 *p_x_axis, const quark_vector3 *p_y_axis, const quark_vector3 *p_z_axis, const quark_vector3 *p_origin) {
	const Vector3 *x_axis = (const Vector3 *)p_x_axis;
	const Vector3 *y_axis = (const Vector3 *)p_y_axis;
	const Vector3 *z_axis = (const Vector3 *)p_z_axis;
	const Vector3 *origin = (const Vector3 *)p_origin;
	Transform *dest = (Transform *)r_dest;
	dest->basis.set_axis(0, *x_axis);
	dest->basis.set_axis(1, *y_axis);
	dest->basis.set_axis(2, *z_axis);
	dest->origin = *origin;
}

void QAPI quark_transform_new(quark_transform *r_dest, const quark_basis *p_basis, const quark_vector3 *p_origin) {
	const Basis *basis = (const Basis *)p_basis;
	const Vector3 *origin = (const Vector3 *)p_origin;
	Transform *dest = (Transform *)r_dest;
	*dest = Transform(*basis, *origin);
}

quark_basis QAPI quark_transform_get_basis(const quark_transform *p_self) {
	quark_basis dest;
	const Transform *self = (const Transform *)p_self;
	*((Basis *)&dest) = self->basis;
	return dest;
}

void QAPI quark_transform_set_basis(quark_transform *p_self, const quark_basis *p_v) {
	Transform *self = (Transform *)p_self;
	const Basis *v = (const Basis *)p_v;
	self->basis = *v;
}

quark_vector3 QAPI quark_transform_get_origin(const quark_transform *p_self) {
	quark_vector3 dest;
	const Transform *self = (const Transform *)p_self;
	*((Vector3 *)&dest) = self->origin;
	return dest;
}

void QAPI quark_transform_set_origin(quark_transform *p_self, const quark_vector3 *p_v) {
	Transform *self = (Transform *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	self->origin = *v;
}

quark_string QAPI quark_transform_as_string(const quark_transform *p_self) {
	quark_string ret;
	const Transform *self = (const Transform *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_transform QAPI quark_transform_inverse(const quark_transform *p_self) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->inverse();
	return dest;
}

quark_transform QAPI quark_transform_affine_inverse(const quark_transform *p_self) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->affine_inverse();
	return dest;
}

quark_transform QAPI quark_transform_orthonormalized(const quark_transform *p_self) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->orthonormalized();
	return dest;
}

quark_transform QAPI quark_transform_rotated(const quark_transform *p_self, const quark_vector3 *p_axis, const quark_real p_phi) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *axis = (const Vector3 *)p_axis;
	*((Transform *)&dest) = self->rotated(*axis, p_phi);
	return dest;
}

quark_transform QAPI quark_transform_scaled(const quark_transform *p_self, const quark_vector3 *p_scale) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *scale = (const Vector3 *)p_scale;
	*((Transform *)&dest) = self->scaled(*scale);
	return dest;
}

quark_transform QAPI quark_transform_translated(const quark_transform *p_self, const quark_vector3 *p_ofs) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *ofs = (const Vector3 *)p_ofs;
	*((Transform *)&dest) = self->translated(*ofs);
	return dest;
}

quark_transform QAPI quark_transform_looking_at(const quark_transform *p_self, const quark_vector3 *p_target, const quark_vector3 *p_up) {
	quark_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *target = (const Vector3 *)p_target;
	const Vector3 *up = (const Vector3 *)p_up;
	*((Transform *)&dest) = self->looking_at(*target, *up);
	return dest;
}

quark_plane QAPI quark_transform_xform_plane(const quark_transform *p_self, const quark_plane *p_v) {
	quark_plane raw_dest;
	Plane *dest = (Plane *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Plane *v = (const Plane *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

quark_plane QAPI quark_transform_xform_inv_plane(const quark_transform *p_self, const quark_plane *p_v) {
	quark_plane raw_dest;
	Plane *dest = (Plane *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Plane *v = (const Plane *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

void QAPI quark_transform_new_identity(quark_transform *r_dest) {
	Transform *dest = (Transform *)r_dest;
	*dest = Transform();
}

quark_bool QAPI quark_transform_operator_equal(const quark_transform *p_self, const quark_transform *p_b) {
	const Transform *self = (const Transform *)p_self;
	const Transform *b = (const Transform *)p_b;
	return *self == *b;
}

quark_transform QAPI quark_transform_operator_multiply(const quark_transform *p_self, const quark_transform *p_b) {
	quark_transform raw_dest;
	Transform *dest = (Transform *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Transform *b = (const Transform *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

quark_vector3 QAPI quark_transform_xform_vector3(const quark_transform *p_self, const quark_vector3 *p_v) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

quark_vector3 QAPI quark_transform_xform_inv_vector3(const quark_transform *p_self, const quark_vector3 *p_v) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

quark_aabb QAPI quark_transform_xform_aabb(const quark_transform *p_self, const quark_aabb *p_v) {
	quark_aabb raw_dest;
	AABB *dest = (AABB *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const AABB *v = (const AABB *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

quark_aabb QAPI quark_transform_xform_inv_aabb(const quark_transform *p_self, const quark_aabb *p_v) {
	quark_aabb raw_dest;
	AABB *dest = (AABB *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const AABB *v = (const AABB *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

#ifdef __cplusplus
}
#endif
