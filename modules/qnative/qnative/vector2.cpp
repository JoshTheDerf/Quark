/*************************************************************************/
/*  vector2.cpp                                                          */
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

#include "qnative/vector2.h"

#include "core/math/math_2d.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_vector2_new(quark_vector2 *r_dest, const quark_real p_x, const quark_real p_y) {

	Vector2 *dest = (Vector2 *)r_dest;
	*dest = Vector2(p_x, p_y);
}

quark_string QAPI quark_vector2_as_string(const quark_vector2 *p_self) {
	quark_string ret;
	const Vector2 *self = (const Vector2 *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_vector2 QAPI quark_vector2_normalized(const quark_vector2 *p_self) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*((Vector2 *)&dest) = self->normalized();
	return dest;
}

quark_real QAPI quark_vector2_length(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->length();
}

quark_real QAPI quark_vector2_angle(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->angle();
}

quark_real QAPI quark_vector2_length_squared(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->length_squared();
}

quark_bool QAPI quark_vector2_is_normalized(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->is_normalized();
}

quark_real QAPI quark_vector2_distance_to(const quark_vector2 *p_self, const quark_vector2 *p_to) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *to = (const Vector2 *)p_to;
	return self->distance_to(*to);
}

quark_real QAPI quark_vector2_distance_squared_to(const quark_vector2 *p_self, const quark_vector2 *p_to) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *to = (const Vector2 *)p_to;
	return self->distance_squared_to(*to);
}

quark_real QAPI quark_vector2_angle_to(const quark_vector2 *p_self, const quark_vector2 *p_to) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *to = (const Vector2 *)p_to;
	return self->angle_to(*to);
}

quark_real QAPI quark_vector2_angle_to_point(const quark_vector2 *p_self, const quark_vector2 *p_to) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *to = (const Vector2 *)p_to;
	return self->angle_to_point(*to);
}

quark_vector2 QAPI quark_vector2_linear_interpolate(const quark_vector2 *p_self, const quark_vector2 *p_b, const quark_real p_t) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	*((Vector2 *)&dest) = self->linear_interpolate(*b, p_t);
	return dest;
}

quark_vector2 QAPI quark_vector2_cubic_interpolate(const quark_vector2 *p_self, const quark_vector2 *p_b, const quark_vector2 *p_pre_a, const quark_vector2 *p_post_b, const quark_real p_t) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	const Vector2 *pre_a = (const Vector2 *)p_pre_a;
	const Vector2 *post_b = (const Vector2 *)p_post_b;
	*((Vector2 *)&dest) = self->cubic_interpolate(*b, *pre_a, *post_b, p_t);
	return dest;
}

quark_vector2 QAPI quark_vector2_rotated(const quark_vector2 *p_self, const quark_real p_phi) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;

	*((Vector2 *)&dest) = self->rotated(p_phi);
	return dest;
}

quark_vector2 QAPI quark_vector2_tangent(const quark_vector2 *p_self) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*((Vector2 *)&dest) = self->tangent();
	return dest;
}

quark_vector2 QAPI quark_vector2_floor(const quark_vector2 *p_self) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*((Vector2 *)&dest) = self->floor();
	return dest;
}

quark_vector2 QAPI quark_vector2_snapped(const quark_vector2 *p_self, const quark_vector2 *p_by) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *by = (const Vector2 *)p_by;
	*((Vector2 *)&dest) = self->snapped(*by);
	return dest;
}

quark_real QAPI quark_vector2_aspect(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->aspect();
}

quark_real QAPI quark_vector2_dot(const quark_vector2 *p_self, const quark_vector2 *p_with) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *with = (const Vector2 *)p_with;
	return self->dot(*with);
}

quark_vector2 QAPI quark_vector2_slide(const quark_vector2 *p_self, const quark_vector2 *p_n) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *n = (const Vector2 *)p_n;
	*((Vector2 *)&dest) = self->slide(*n);
	return dest;
}

quark_vector2 QAPI quark_vector2_bounce(const quark_vector2 *p_self, const quark_vector2 *p_n) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *n = (const Vector2 *)p_n;
	*((Vector2 *)&dest) = self->bounce(*n);
	return dest;
}

quark_vector2 QAPI quark_vector2_reflect(const quark_vector2 *p_self, const quark_vector2 *p_n) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *n = (const Vector2 *)p_n;
	*((Vector2 *)&dest) = self->reflect(*n);
	return dest;
}

quark_vector2 QAPI quark_vector2_abs(const quark_vector2 *p_self) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*((Vector2 *)&dest) = self->abs();
	return dest;
}

quark_vector2 QAPI quark_vector2_clamped(const quark_vector2 *p_self, const quark_real p_length) {
	quark_vector2 dest;
	const Vector2 *self = (const Vector2 *)p_self;

	*((Vector2 *)&dest) = self->clamped(p_length);
	return dest;
}

quark_vector2 QAPI quark_vector2_operator_add(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	*dest = *self + *b;
	return raw_dest;
}

quark_vector2 QAPI quark_vector2_operator_subtract(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	*dest = *self - *b;
	return raw_dest;
}

quark_vector2 QAPI quark_vector2_operator_multiply_vector(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

quark_vector2 QAPI quark_vector2_operator_multiply_scalar(const quark_vector2 *p_self, const quark_real p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*dest = *self * p_b;
	return raw_dest;
}

quark_vector2 QAPI quark_vector2_operator_divide_vector(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	*dest = *self / *b;
	return raw_dest;
}

quark_vector2 QAPI quark_vector2_operator_divide_scalar(const quark_vector2 *p_self, const quark_real p_b) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*dest = *self / p_b;
	return raw_dest;
}

quark_bool QAPI quark_vector2_operator_equal(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	return *self == *b;
}

quark_bool QAPI quark_vector2_operator_less(const quark_vector2 *p_self, const quark_vector2 *p_b) {
	const Vector2 *self = (const Vector2 *)p_self;
	const Vector2 *b = (const Vector2 *)p_b;
	return *self < *b;
}

quark_vector2 QAPI quark_vector2_operator_neg(const quark_vector2 *p_self) {
	quark_vector2 raw_dest;
	Vector2 *dest = (Vector2 *)&raw_dest;
	const Vector2 *self = (const Vector2 *)p_self;
	*dest = -(*self);
	return raw_dest;
}

void QAPI quark_vector2_set_x(quark_vector2 *p_self, const quark_real p_x) {
	Vector2 *self = (Vector2 *)p_self;
	self->x = p_x;
}

void QAPI quark_vector2_set_y(quark_vector2 *p_self, const quark_real p_y) {
	Vector2 *self = (Vector2 *)p_self;
	self->y = p_y;
}

quark_real QAPI quark_vector2_get_x(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->x;
}

quark_real QAPI quark_vector2_get_y(const quark_vector2 *p_self) {
	const Vector2 *self = (const Vector2 *)p_self;
	return self->y;
}

#ifdef __cplusplus
}
#endif
