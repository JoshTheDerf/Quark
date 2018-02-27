/*************************************************************************/
/*  transform2d.cpp                                                      */
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

#include "qnative/transform2d.h"

#include "core/math/math_2d.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_transform2d_new(quark_transform2d *r_dest, const quark_real p_rot, const quark_vector2 *p_pos) {
	const Vector2 *pos = (const Vector2 *)p_pos;
	Transform2D *dest = (Transform2D *)r_dest;
	*dest = Transform2D(p_rot, *pos);
}

void QAPI quark_transform2d_new_axis_origin(quark_transform2d *r_dest, const quark_vector2 *p_x_axis, const quark_vector2 *p_y_axis, const quark_vector2 *p_origin) {
	const Vector2 *x_axis = (const Vector2 *)p_x_axis;
	const Vector2 *y_axis = (const Vector2 *)p_y_axis;
	const Vector2 *origin = (const Vector2 *)p_origin;
	Transform2D *dest = (Transform2D *)r_dest;
	*dest = Transform2D(x_axis->x, x_axis->y, y_axis->x, y_axis->y, origin->x, origin->y);
}

quark_string QAPI quark_transform2d_as_string(const quark_transform2d *p_self) {
	quark_string ret;
	const Transform2D *self = (const Transform2D *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_transform2d QAPI quark_transform2d_inverse(const quark_transform2d *p_self) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	*((Transform2D *)&dest) = self->inverse();
	return dest;
}

quark_transform2d QAPI quark_transform2d_affine_inverse(const quark_transform2d *p_self) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	*((Transform2D *)&dest) = self->affine_inverse();
	return dest;
}

quark_real QAPI quark_transform2d_get_rotation(const quark_transform2d *p_self) {
	const Transform2D *self = (const Transform2D *)p_self;
	return self->get_rotation();
}

quark_vector2 QAPI quark_transform2d_get_origin(const quark_transform2d *p_self) {
	quark_vector2 dest;
	const Transform2D *self = (const Transform2D *)p_self;
	*((Vector2 *)&dest) = self->get_origin();
	return dest;
}

quark_vector2 QAPI quark_transform2d_get_scale(const quark_transform2d *p_self) {
	quark_vector2 dest;
	const Transform2D *self = (const Transform2D *)p_self;
	*((Vector2 *)&dest) = self->get_scale();
	return dest;
}

quark_transform2d QAPI quark_transform2d_orthonormalized(const quark_transform2d *p_self) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	*((Transform2D *)&dest) = self->orthonormalized();
	return dest;
}

quark_transform2d QAPI quark_transform2d_rotated(const quark_transform2d *p_self, const quark_real p_phi) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;

	*((Transform2D *)&dest) = self->rotated(p_phi);
	return dest;
}

quark_transform2d QAPI quark_transform2d_scaled(const quark_transform2d *p_self, const quark_vector2 *p_scale) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *scale = (const Vector2 *)p_scale;
	*((Transform2D *)&dest) = self->scaled(*scale);
	return dest;
}

quark_transform2d QAPI quark_transform2d_translated(const quark_transform2d *p_self, const quark_vector2 *p_offset) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *offset = (const Vector2 *)p_offset;
	*((Transform2D *)&dest) = self->translated(*offset);
	return dest;
}

quark_vector2 QAPI quark_transform2d_xform_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *v = (const Vector2 *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

quark_vector2 QAPI quark_transform2d_xform_inv_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *v = (const Vector2 *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

quark_vector2 QAPI quark_transform2d_basis_xform_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *v = (const Vector2 *)p_v;
	*dest = self->basis_xform(*v);
	return raw_dest;
}

quark_vector2 QAPI quark_transform2d_basis_xform_inv_vector2(const quark_transform2d *p_self, const quark_vector2 *p_v) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Vector2 *v = (const Vector2 *)p_v;
	*dest = self->basis_xform_inv(*v);
	return raw_dest;
}

quark_transform2d QAPI quark_transform2d_interpolate_with(const quark_transform2d *p_self, const quark_transform2d *p_m, const quark_real p_c) {
	quark_transform2d dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Transform2D *m = (const Transform2D *)p_m;
	*((Transform2D *)&dest) = self->interpolate_with(*m, p_c);
	return dest;
}

quark_bool QAPI quark_transform2d_operator_equal(const quark_transform2d *p_self, const quark_transform2d *p_b) {
	const Transform2D *self = (const Transform2D *)p_self;
	const Transform2D *b = (const Transform2D *)p_b;
	return *self == *b;
}

quark_transform2d QAPI quark_transform2d_operator_multiply(const quark_transform2d *p_self, const quark_transform2d *p_b) {
	quark_transform2d raw_dest;
	Transform2D *dest = (Transform2D *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Transform2D *b = (const Transform2D *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

void QAPI quark_transform2d_new_identity(quark_transform2d *r_dest) {
	Transform2D *dest = (Transform2D *)r_dest;
	*dest = Transform2D();
}

quark_rect2 QAPI quark_transform2d_xform_rect2(const quark_transform2d *p_self, const quark_rect2 *p_v) {
	quark_rect2 raw_dest;
	Rect2 *dest = (Rect2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Rect2 *v = (const Rect2 *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

quark_rect2 QAPI quark_transform2d_xform_inv_rect2(const quark_transform2d *p_self, const quark_rect2 *p_v) {
	quark_rect2 raw_dest;
	Rect2 *dest = (Rect2 *)&raw_dest;
	const Transform2D *self = (const Transform2D *)p_self;
	const Rect2 *v = (const Rect2 *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

#ifdef __cplusplus
}
#endif
