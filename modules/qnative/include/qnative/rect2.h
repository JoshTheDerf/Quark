/*************************************************************************/
/*  rect2.h                                                              */
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

#ifndef QUARK_RECT2_H
#define QUARK_RECT2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef QUARK_CORE_API_QUARK_RECT2_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_RECT2_TYPE_DEFINED
typedef struct quark_rect2 {
	uint8_t _dont_touch_that[16];
} quark_rect2;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/vector2.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_rect2_new_with_position_and_size(quark_rect2 *r_dest, const quark_vector2 *p_pos, const quark_vector2 *p_size);
void QAPI quark_rect2_new(quark_rect2 *r_dest, const quark_real p_x, const quark_real p_y, const quark_real p_width, const quark_real p_height);

quark_string QAPI quark_rect2_as_string(const quark_rect2 *p_self);

quark_real QAPI quark_rect2_get_area(const quark_rect2 *p_self);

quark_bool QAPI quark_rect2_intersects(const quark_rect2 *p_self, const quark_rect2 *p_b);

quark_bool QAPI quark_rect2_encloses(const quark_rect2 *p_self, const quark_rect2 *p_b);

quark_bool QAPI quark_rect2_has_no_area(const quark_rect2 *p_self);

quark_rect2 QAPI quark_rect2_clip(const quark_rect2 *p_self, const quark_rect2 *p_b);

quark_rect2 QAPI quark_rect2_merge(const quark_rect2 *p_self, const quark_rect2 *p_b);

quark_bool QAPI quark_rect2_has_point(const quark_rect2 *p_self, const quark_vector2 *p_point);

quark_rect2 QAPI quark_rect2_grow(const quark_rect2 *p_self, const quark_real p_by);

quark_rect2 QAPI quark_rect2_expand(const quark_rect2 *p_self, const quark_vector2 *p_to);

quark_bool QAPI quark_rect2_operator_equal(const quark_rect2 *p_self, const quark_rect2 *p_b);

quark_vector2 QAPI quark_rect2_get_position(const quark_rect2 *p_self);

quark_vector2 QAPI quark_rect2_get_size(const quark_rect2 *p_self);

void QAPI quark_rect2_set_position(quark_rect2 *p_self, const quark_vector2 *p_pos);

void QAPI quark_rect2_set_size(quark_rect2 *p_self, const quark_vector2 *p_size);

#ifdef __cplusplus
}
#endif

#endif // QUARK_RECT2_H
