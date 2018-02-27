/*************************************************************************/
/*  vector3.cpp                                                          */
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

#include "qnative/vector3.h"

#include "core/variant.h"
#include "core/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_vector3_new(quark_vector3 *r_dest, const quark_real p_x, const quark_real p_y, const quark_real p_z) {

	Vector3 *dest = (Vector3 *)r_dest;
	*dest = Vector3(p_x, p_y, p_z);
}

quark_string QAPI quark_vector3_as_string(const quark_vector3 *p_self) {
	quark_string ret;
	const Vector3 *self = (const Vector3 *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_int QAPI quark_vector3_min_axis(const quark_vector3 *p_self) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->min_axis();
}

quark_int QAPI quark_vector3_max_axis(const quark_vector3 *p_self) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->max_axis();
}

quark_real QAPI quark_vector3_length(const quark_vector3 *p_self) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->length();
}

quark_real QAPI quark_vector3_length_squared(const quark_vector3 *p_self) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->length_squared();
}

quark_bool QAPI quark_vector3_is_normalized(const quark_vector3 *p_self) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->is_normalized();
}

quark_vector3 QAPI quark_vector3_normalized(const quark_vector3 *p_self) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Vector3 *)&dest) = self->normalized();
	return dest;
}

quark_vector3 QAPI quark_vector3_inverse(const quark_vector3 *p_self) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Vector3 *)&dest) = self->inverse();
	return dest;
}

quark_vector3 QAPI quark_vector3_snapped(const quark_vector3 *p_self, const quark_vector3 *p_by) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *snap_axis = (const Vector3 *)p_by;

	*((Vector3 *)&dest) = self->snapped(*snap_axis);
	return dest;
}

quark_vector3 QAPI quark_vector3_rotated(const quark_vector3 *p_self, const quark_vector3 *p_axis, const quark_real p_phi) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *axis = (const Vector3 *)p_axis;
	*((Vector3 *)&dest) = self->rotated(*axis, p_phi);
	return dest;
}

quark_vector3 QAPI quark_vector3_linear_interpolate(const quark_vector3 *p_self, const quark_vector3 *p_b, const quark_real p_t) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*((Vector3 *)&dest) = self->linear_interpolate(*b, p_t);
	return dest;
}

quark_vector3 QAPI quark_vector3_cubic_interpolate(const quark_vector3 *p_self, const quark_vector3 *p_b, const quark_vector3 *p_pre_a, const quark_vector3 *p_post_b, const quark_real p_t) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	const Vector3 *pre_a = (const Vector3 *)p_pre_a;
	const Vector3 *post_b = (const Vector3 *)p_post_b;
	*((Vector3 *)&dest) = self->cubic_interpolate(*b, *pre_a, *post_b, p_t);
	return dest;
}

quark_real QAPI quark_vector3_dot(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	return self->dot(*b);
}

quark_vector3 QAPI quark_vector3_cross(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*((Vector3 *)&dest) = self->cross(*b);
	return dest;
}

quark_basis QAPI quark_vector3_outer(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_basis dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*((Basis *)&dest) = self->outer(*b);
	return dest;
}

quark_basis QAPI quark_vector3_to_diagonal_matrix(const quark_vector3 *p_self) {
	quark_basis dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Basis *)&dest) = self->to_diagonal_matrix();
	return dest;
}

quark_vector3 QAPI quark_vector3_abs(const quark_vector3 *p_self) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Vector3 *)&dest) = self->abs();
	return dest;
}

quark_vector3 QAPI quark_vector3_floor(const quark_vector3 *p_self) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Vector3 *)&dest) = self->floor();
	return dest;
}

quark_vector3 QAPI quark_vector3_ceil(const quark_vector3 *p_self) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*((Vector3 *)&dest) = self->ceil();
	return dest;
}

quark_real QAPI quark_vector3_distance_to(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	return self->distance_to(*b);
}

quark_real QAPI quark_vector3_distance_squared_to(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	return self->distance_squared_to(*b);
}

quark_real QAPI quark_vector3_angle_to(const quark_vector3 *p_self, const quark_vector3 *p_to) {
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *to = (const Vector3 *)p_to;
	return self->angle_to(*to);
}

quark_vector3 QAPI quark_vector3_slide(const quark_vector3 *p_self, const quark_vector3 *p_n) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *n = (const Vector3 *)p_n;
	*((Vector3 *)&dest) = self->slide(*n);
	return dest;
}

quark_vector3 QAPI quark_vector3_bounce(const quark_vector3 *p_self, const quark_vector3 *p_n) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *n = (const Vector3 *)p_n;
	*((Vector3 *)&dest) = self->bounce(*n);
	return dest;
}

quark_vector3 QAPI quark_vector3_reflect(const quark_vector3 *p_self, const quark_vector3 *p_n) {
	quark_vector3 dest;
	const Vector3 *self = (const Vector3 *)p_self;
	const Vector3 *n = (const Vector3 *)p_n;
	*((Vector3 *)&dest) = self->reflect(*n);
	return dest;
}

quark_vector3 QAPI quark_vector3_operator_add(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*dest = *self + *b;
	return raw_dest;
}

quark_vector3 QAPI quark_vector3_operator_subtract(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*dest = *self - *b;
	return raw_dest;
}

quark_vector3 QAPI quark_vector3_operator_multiply_vector(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

quark_vector3 QAPI quark_vector3_operator_multiply_scalar(const quark_vector3 *p_self, const quark_real p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	*dest = *self * p_b;
	return raw_dest;
}

quark_vector3 QAPI quark_vector3_operator_divide_vector(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	*dest = *self / *b;
	return raw_dest;
}

quark_vector3 QAPI quark_vector3_operator_divide_scalar(const quark_vector3 *p_self, const quark_real p_b) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	Vector3 *self = (Vector3 *)p_self;
	*dest = *self / p_b;
	return raw_dest;
}

quark_bool QAPI quark_vector3_operator_equal(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	return *self == *b;
}

quark_bool QAPI quark_vector3_operator_less(const quark_vector3 *p_self, const quark_vector3 *p_b) {
	Vector3 *self = (Vector3 *)p_self;
	const Vector3 *b = (const Vector3 *)p_b;
	return *self < *b;
}

quark_vector3 QAPI quark_vector3_operator_neg(const quark_vector3 *p_self) {
	quark_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	const Vector3 *self = (const Vector3 *)p_self;
	*dest = -(*self);
	return raw_dest;
}

void QAPI quark_vector3_set_axis(quark_vector3 *p_self, const quark_vector3_axis p_axis, const quark_real p_val) {
	Vector3 *self = (Vector3 *)p_self;
	self->set_axis(p_axis, p_val);
}

quark_real QAPI quark_vector3_get_axis(const quark_vector3 *p_self, const quark_vector3_axis p_axis) {
	const Vector3 *self = (const Vector3 *)p_self;
	return self->get_axis(p_axis);
}

#ifdef __cplusplus
}
#endif
