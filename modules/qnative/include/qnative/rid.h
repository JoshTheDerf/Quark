/*************************************************************************/
/*  rid.h                                                                */
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

#ifndef QUARK_RID_H
#define QUARK_RID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define QUARK_RID_SIZE sizeof(void *)

#ifndef QUARK_CORE_API_QUARK_RID_TYPE_DEFINED
#define QUARK_CORE_API_QUARK_RID_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[QUARK_RID_SIZE];
} quark_rid;
#endif

// reduce extern "C" nesting for VS2013
#ifdef __cplusplus
}
#endif

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_rid_new(quark_rid *r_dest);

quark_int QAPI quark_rid_get_id(const quark_rid *p_self);

void QAPI quark_rid_new_with_resource(quark_rid *r_dest, const quark_object *p_from);

quark_bool QAPI quark_rid_operator_equal(const quark_rid *p_self, const quark_rid *p_b);

quark_bool QAPI quark_rid_operator_less(const quark_rid *p_self, const quark_rid *p_b);

#ifdef __cplusplus
}
#endif

#endif // QUARK_RID_H
