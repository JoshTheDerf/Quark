/*************************************************************************/
/*  aabb.h                                                               */
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

#ifndef QUARK_AABB_H
#define QUARK_AABB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_AABB_SIZE 24

#ifndef QUARK_CORE_API_QUARK_AABB_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_AABB_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_AABB_SIZE];
} quark_aabb;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/plane.h>
#include <qnative/vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_aabb_new(quark_aabb *r_dest, const quark_vector3 *p_pos, const quark_vector3 *p_size);

quark_vector3 QAPI quark_aabb_get_position(const quark_aabb *p_self);
void QAPI quark_aabb_set_position(const quark_aabb *p_self, const quark_vector3 *p_v);

quark_vector3 QAPI quark_aabb_get_size(const quark_aabb *p_self);
void QAPI quark_aabb_set_size(const quark_aabb *p_self, const quark_vector3 *p_v);

quark_string QAPI quark_aabb_as_string(const quark_aabb *p_self);

quark_real QAPI quark_aabb_get_area(const quark_aabb *p_self);

quark_bool QAPI quark_aabb_has_no_area(const quark_aabb *p_self);

quark_bool QAPI quark_aabb_has_no_surface(const quark_aabb *p_self);

quark_bool QAPI quark_aabb_intersects(const quark_aabb *p_self, const quark_aabb *p_with);

quark_bool QAPI quark_aabb_encloses(const quark_aabb *p_self, const quark_aabb *p_with);

quark_aabb QAPI quark_aabb_merge(const quark_aabb *p_self, const quark_aabb *p_with);

quark_aabb QAPI quark_aabb_intersection(const quark_aabb *p_self, const quark_aabb *p_with);

quark_bool QAPI quark_aabb_intersects_plane(const quark_aabb *p_self, const quark_plane *p_plane);

quark_bool QAPI quark_aabb_intersects_segment(const quark_aabb *p_self, const quark_vector3 *p_from, const quark_vector3 *p_to);

quark_bool QAPI quark_aabb_has_point(const quark_aabb *p_self, const quark_vector3 *p_point);

quark_vector3 QAPI quark_aabb_get_support(const quark_aabb *p_self, const quark_vector3 *p_dir);

quark_vector3 QAPI quark_aabb_get_longest_axis(const quark_aabb *p_self);

quark_int QAPI quark_aabb_get_longest_axis_index(const quark_aabb *p_self);

quark_real QAPI quark_aabb_get_longest_axis_size(const quark_aabb *p_self);

quark_vector3 QAPI quark_aabb_get_shortest_axis(const quark_aabb *p_self);

quark_int QAPI quark_aabb_get_shortest_axis_index(const quark_aabb *p_self);

quark_real QAPI quark_aabb_get_shortest_axis_size(const quark_aabb *p_self);

quark_aabb QAPI quark_aabb_expand(const quark_aabb *p_self, const quark_vector3 *p_to_point);

quark_aabb QAPI quark_aabb_grow(const quark_aabb *p_self, const quark_real p_by);

quark_vector3 QAPI quark_aabb_get_endpoint(const quark_aabb *p_self, const quark_int p_idx);

quark_bool QAPI quark_aabb_operator_equal(const quark_aabb *p_self, const quark_aabb *p_b);

#ifdef __cplusplus
}
#endif

#endif // QUARK_AABB_H
