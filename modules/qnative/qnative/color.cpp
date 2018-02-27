/*************************************************************************/
/*  color.cpp                                                            */
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

#include "qnative/color.h"

#include "core/color.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_color_new_rgba(quark_color *r_dest, const quark_real p_r, const quark_real p_g, const quark_real p_b, const quark_real p_a) {

	Color *dest = (Color *)r_dest;
	*dest = Color(p_r, p_g, p_b, p_a);
}

void QAPI quark_color_new_rgb(quark_color *r_dest, const quark_real p_r, const quark_real p_g, const quark_real p_b) {

	Color *dest = (Color *)r_dest;
	*dest = Color(p_r, p_g, p_b);
}

quark_real quark_color_get_r(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->r;
}

void quark_color_set_r(quark_color *p_self, const quark_real val) {
	Color *self = (Color *)p_self;
	self->r = val;
}

quark_real quark_color_get_g(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->g;
}

void quark_color_set_g(quark_color *p_self, const quark_real val) {
	Color *self = (Color *)p_self;
	self->g = val;
}

quark_real quark_color_get_b(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->b;
}

void quark_color_set_b(quark_color *p_self, const quark_real val) {
	Color *self = (Color *)p_self;
	self->b = val;
}

quark_real quark_color_get_a(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->a;
}

void quark_color_set_a(quark_color *p_self, const quark_real val) {
	Color *self = (Color *)p_self;
	self->a = val;
}

quark_real quark_color_get_h(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->get_h();
}

quark_real quark_color_get_s(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->get_s();
}

quark_real quark_color_get_v(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->get_v();
}

quark_string QAPI quark_color_as_string(const quark_color *p_self) {
	quark_string ret;
	const Color *self = (const Color *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

quark_int QAPI quark_color_to_rgba32(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->to_rgba32();
}

quark_int QAPI quark_color_to_argb32(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->to_argb32();
}

quark_real QAPI quark_color_gray(const quark_color *p_self) {
	const Color *self = (const Color *)p_self;
	return self->gray();
}

quark_color QAPI quark_color_inverted(const quark_color *p_self) {
	quark_color dest;
	const Color *self = (const Color *)p_self;
	*((Color *)&dest) = self->inverted();
	return dest;
}

quark_color QAPI quark_color_contrasted(const quark_color *p_self) {
	quark_color dest;
	const Color *self = (const Color *)p_self;
	*((Color *)&dest) = self->contrasted();
	return dest;
}

quark_color QAPI quark_color_linear_interpolate(const quark_color *p_self, const quark_color *p_b, const quark_real p_t) {
	quark_color dest;
	const Color *self = (const Color *)p_self;
	const Color *b = (const Color *)p_b;
	*((Color *)&dest) = self->linear_interpolate(*b, p_t);
	return dest;
}

quark_color QAPI quark_color_blend(const quark_color *p_self, const quark_color *p_over) {
	quark_color dest;
	const Color *self = (const Color *)p_self;
	const Color *over = (const Color *)p_over;
	*((Color *)&dest) = self->blend(*over);
	return dest;
}

quark_string QAPI quark_color_to_html(const quark_color *p_self, const quark_bool p_with_alpha) {
	quark_string dest;
	const Color *self = (const Color *)p_self;

	memnew_placement(&dest, String(self->to_html(p_with_alpha)));
	return dest;
}

quark_bool QAPI quark_color_operator_equal(const quark_color *p_self, const quark_color *p_b) {
	const Color *self = (const Color *)p_self;
	const Color *b = (const Color *)p_b;
	return *self == *b;
}

quark_bool QAPI quark_color_operator_less(const quark_color *p_self, const quark_color *p_b) {
	const Color *self = (const Color *)p_self;
	const Color *b = (const Color *)p_b;
	return *self < *b;
}

#ifdef __cplusplus
}
#endif
