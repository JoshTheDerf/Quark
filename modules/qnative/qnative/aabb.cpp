/*************************************************************************/
/*  aabb.cpp                                                             */
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

#include "qnative/aabb.h"

#include "core/math/aabb.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_aabb_new(quark_aabb *r_dest, const quark_vector3 *p_pos, const quark_vector3 *p_size) {
	const Vector3 *pos = (const Vector3 *)p_pos;
	const Vector3 *size = (const Vector3 *)p_size;
	AABB *dest = (AABB *)r_dest;
	*dest = AABB(*pos, *size);
}

quark_vector3 QAPI quark_aabb_get_position(const quark_aabb *p_self) {
	quark_vector3 raw_ret;
	const AABB *self = (const AABB *)p_self;
	Vector3 *ret = (Vector3 *)&raw_ret;
	*ret = self->position;
	return raw_ret;
}

void QAPI quark_aabb_set_position(const quark_aabb *p_self, const quark_vector3 *p_v) {
	AABB *self = (AABB *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	self->position = *v;
}

quark_vector3 QAPI quark_aabb_get_size(const quark_aabb *p_self) {
	quark_vector3 raw_ret;
	const AABB *self = (const AABB *)p_self;
	Vector3 *ret = (Vector3 *)&raw_ret;
	*ret = self->size;
	return raw_ret;
}

void QAPI quark_aabb_set_size(const quark_aabb *p_self, const quark_vector3 *p_v) {
	AABB *self = (AABB *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	self->size = *v;
}

quark_string QAPI quark_aabb_as_string(const quark_aabb *p_self) {
	quark_string ret;
	const AABB *self = (const AABB *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_real QAPI quark_aabb_get_area(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->get_area();
}

quark_bool QAPI quark_aabb_has_no_area(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->has_no_area();
}

quark_bool QAPI quark_aabb_has_no_surface(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->has_no_surface();
}

quark_bool QAPI quark_aabb_intersects(const quark_aabb *p_self, const quark_aabb *p_with) {
	const AABB *self = (const AABB *)p_self;
	const AABB *with = (const AABB *)p_with;
	return self->intersects(*with);
}

quark_bool QAPI quark_aabb_encloses(const quark_aabb *p_self, const quark_aabb *p_with) {
	const AABB *self = (const AABB *)p_self;
	const AABB *with = (const AABB *)p_with;
	return self->encloses(*with);
}

quark_aabb QAPI quark_aabb_merge(const quark_aabb *p_self, const quark_aabb *p_with) {
	quark_aabb dest;
	const AABB *self = (const AABB *)p_self;
	const AABB *with = (const AABB *)p_with;
	*((AABB *)&dest) = self->merge(*with);
	return dest;
}

quark_aabb QAPI quark_aabb_intersection(const quark_aabb *p_self, const quark_aabb *p_with) {
	quark_aabb dest;
	const AABB *self = (const AABB *)p_self;
	const AABB *with = (const AABB *)p_with;
	*((AABB *)&dest) = self->intersection(*with);
	return dest;
}

quark_bool QAPI quark_aabb_intersects_plane(const quark_aabb *p_self, const quark_plane *p_plane) {
	const AABB *self = (const AABB *)p_self;
	const Plane *plane = (const Plane *)p_plane;
	return self->intersects_plane(*plane);
}

quark_bool QAPI quark_aabb_intersects_segment(const quark_aabb *p_self, const quark_vector3 *p_from, const quark_vector3 *p_to) {
	const AABB *self = (const AABB *)p_self;
	const Vector3 *from = (const Vector3 *)p_from;
	const Vector3 *to = (const Vector3 *)p_to;
	return self->intersects_segment(*from, *to);
}

quark_bool QAPI quark_aabb_has_point(const quark_aabb *p_self, const quark_vector3 *p_point) {
	const AABB *self = (const AABB *)p_self;
	const Vector3 *point = (const Vector3 *)p_point;
	return self->has_point(*point);
}

quark_vector3 QAPI quark_aabb_get_support(const quark_aabb *p_self, const quark_vector3 *p_dir) {
	quark_vector3 dest;
	const AABB *self = (const AABB *)p_self;
	const Vector3 *dir = (const Vector3 *)p_dir;
	*((Vector3 *)&dest) = self->get_support(*dir);
	return dest;
}

quark_vector3 QAPI quark_aabb_get_longest_axis(const quark_aabb *p_self) {
	quark_vector3 dest;
	const AABB *self = (const AABB *)p_self;
	*((Vector3 *)&dest) = self->get_longest_axis();
	return dest;
}

quark_int QAPI quark_aabb_get_longest_axis_index(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->get_longest_axis_index();
}

quark_real QAPI quark_aabb_get_longest_axis_size(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->get_longest_axis_size();
}

quark_vector3 QAPI quark_aabb_get_shortest_axis(const quark_aabb *p_self) {
	quark_vector3 dest;
	const AABB *self = (const AABB *)p_self;
	*((Vector3 *)&dest) = self->get_shortest_axis();
	return dest;
}

quark_int QAPI quark_aabb_get_shortest_axis_index(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->get_shortest_axis_index();
}

quark_real QAPI quark_aabb_get_shortest_axis_size(const quark_aabb *p_self) {
	const AABB *self = (const AABB *)p_self;
	return self->get_shortest_axis_size();
}

quark_aabb QAPI quark_aabb_expand(const quark_aabb *p_self, const quark_vector3 *p_to_point) {
	quark_aabb dest;
	const AABB *self = (const AABB *)p_self;
	const Vector3 *to_point = (const Vector3 *)p_to_point;
	*((AABB *)&dest) = self->expand(*to_point);
	return dest;
}

quark_aabb QAPI quark_aabb_grow(const quark_aabb *p_self, const quark_real p_by) {
	quark_aabb dest;
	const AABB *self = (const AABB *)p_self;

	*((AABB *)&dest) = self->grow(p_by);
	return dest;
}

quark_vector3 QAPI quark_aabb_get_endpoint(const quark_aabb *p_self, const quark_int p_idx) {
	quark_vector3 dest;
	const AABB *self = (const AABB *)p_self;

	*((Vector3 *)&dest) = self->get_endpoint(p_idx);
	return dest;
}

quark_bool QAPI quark_aabb_operator_equal(const quark_aabb *p_self, const quark_aabb *p_b) {
	const AABB *self = (const AABB *)p_self;
	const AABB *b = (const AABB *)p_b;
	return *self == *b;
}

#ifdef __cplusplus
}
#endif
