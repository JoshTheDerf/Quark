/*************************************************************************/
/*  color.h                                                              */
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

#ifndef QUARK_COLOR_H
#define QUARK_COLOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_COLOR_SIZE 16

#ifndef QUARK_CORE_API_QUARK_COLOR_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_COLOR_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_COLOR_SIZE];
} quark_color;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>
#include <qnative/string.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_color_new_rgba(quark_color *r_dest, const quark_real p_r, const quark_real p_g, const quark_real p_b, const quark_real p_a);
void QAPI quark_color_new_rgb(quark_color *r_dest, const quark_real p_r, const quark_real p_g, const quark_real p_b);

quark_real quark_color_get_r(const quark_color *p_self);
void quark_color_set_r(quark_color *p_self, const quark_real r);

quark_real quark_color_get_g(const quark_color *p_self);
void quark_color_set_g(quark_color *p_self, const quark_real g);

quark_real quark_color_get_b(const quark_color *p_self);
void quark_color_set_b(quark_color *p_self, const quark_real b);

quark_real quark_color_get_a(const quark_color *p_self);
void quark_color_set_a(quark_color *p_self, const quark_real a);

quark_real quark_color_get_h(const quark_color *p_self);
quark_real quark_color_get_s(const quark_color *p_self);
quark_real quark_color_get_v(const quark_color *p_self);

quark_string QAPI quark_color_as_string(const quark_color *p_self);

quark_int QAPI quark_color_to_rgba32(const quark_color *p_self);

quark_int QAPI quark_color_to_argb32(const quark_color *p_self);

quark_real QAPI quark_color_gray(const quark_color *p_self);

quark_color QAPI quark_color_inverted(const quark_color *p_self);

quark_color QAPI quark_color_contrasted(const quark_color *p_self);

quark_color QAPI quark_color_linear_interpolate(const quark_color *p_self, const quark_color *p_b, const quark_real p_t);

quark_color QAPI quark_color_blend(const quark_color *p_self, const quark_color *p_over);

quark_string QAPI quark_color_to_html(const quark_color *p_self, const quark_bool p_with_alpha);

quark_bool QAPI quark_color_operator_equal(const quark_color *p_self, const quark_color *p_b);

quark_bool QAPI quark_color_operator_less(const quark_color *p_self, const quark_color *p_b);

#ifdef __cplusplus
}
#endif

#endif // QUARK_COLOR_H
