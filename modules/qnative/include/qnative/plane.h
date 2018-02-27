/*************************************************************************/
/*  plane.h                                                              */
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

#ifndef QUARK_PLANE_H
#define QUARK_PLANE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_PLANE_SIZE 16

#ifndef QUARK_CORE_API_QUARK_PLANE_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_PLANE_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_PLANE_SIZE];
} quark_plane;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_plane_new_with_reals(quark_plane *r_dest, const quark_real p_a, const quark_real p_b, const quark_real p_c, const quark_real p_d);
void QAPI quark_plane_new_with_vectors(quark_plane *r_dest, const quark_vector3 *p_v1, const quark_vector3 *p_v2, const quark_vector3 *p_v3);
void QAPI quark_plane_new_with_normal(quark_plane *r_dest, const quark_vector3 *p_normal, const quark_real p_d);

quark_string QAPI quark_plane_as_string(const quark_plane *p_self);

quark_plane QAPI quark_plane_normalized(const quark_plane *p_self);

quark_vector3 QAPI quark_plane_center(const quark_plane *p_self);

quark_vector3 QAPI quark_plane_get_any_point(const quark_plane *p_self);

quark_bool QAPI quark_plane_is_point_over(const quark_plane *p_self, const quark_vector3 *p_point);

quark_real QAPI quark_plane_distance_to(const quark_plane *p_self, const quark_vector3 *p_point);

quark_bool QAPI quark_plane_has_point(const quark_plane *p_self, const quark_vector3 *p_point, const quark_real p_epsilon);

quark_vector3 QAPI quark_plane_project(const quark_plane *p_self, const quark_vector3 *p_point);

quark_bool QAPI quark_plane_intersect_3(const quark_plane *p_self, quark_vector3 *r_dest, const quark_plane *p_b, const quark_plane *p_c);

quark_bool QAPI quark_plane_intersects_ray(const quark_plane *p_self, quark_vector3 *r_dest, const quark_vector3 *p_from, const quark_vector3 *p_dir);

quark_bool QAPI quark_plane_intersects_segment(const quark_plane *p_self, quark_vector3 *r_dest, const quark_vector3 *p_begin, const quark_vector3 *p_end);

quark_plane QAPI quark_plane_operator_neg(const quark_plane *p_self);

quark_bool QAPI quark_plane_operator_equal(const quark_plane *p_self, const quark_plane *p_b);

void QAPI quark_plane_set_normal(quark_plane *p_self, const quark_vector3 *p_normal);

quark_vector3 QAPI quark_plane_get_normal(const quark_plane *p_self);

quark_real QAPI quark_plane_get_d(const quark_plane *p_self);

void QAPI quark_plane_set_d(quark_plane *p_self, const quark_real p_d);

#ifdef __cplusplus
}
#endif

#endif // QUARK_PLANE_H
