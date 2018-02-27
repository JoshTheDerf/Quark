/*************************************************************************/
/*  pool_arrays.cpp                                                      */
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

#include "qnative/pool_arrays.h"

#include "array.h"
#include "core/variant.h"
#include "dvector.h"

#include "core/color.h"
#include "core/math/math_2d.h"
#include "core/math/vector3.h"

#ifdef __cplusplus
extern "C" {
#endif

#define memnew_placement_custom(m_placement, m_class, m_constr) _post_initialize(new (m_placement, sizeof(m_class), "") m_constr)

// byte

void QAPI quark_pool_byte_array_new(quark_pool_byte_array *r_dest) {
	PoolVector<uint8_t> *dest = (PoolVector<uint8_t> *)r_dest;
	memnew_placement(dest, PoolVector<uint8_t>);
}

void QAPI quark_pool_byte_array_new_copy(quark_pool_byte_array *r_dest, const quark_pool_byte_array *p_src) {
	PoolVector<uint8_t> *dest = (PoolVector<uint8_t> *)r_dest;
	const PoolVector<uint8_t> *src = (const PoolVector<uint8_t> *)p_src;
	memnew_placement(dest, PoolVector<uint8_t>(*src));
}

void QAPI quark_pool_byte_array_new_with_array(quark_pool_byte_array *r_dest, const quark_array *p_a) {
	PoolVector<uint8_t> *dest = (PoolVector<uint8_t> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<uint8_t>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_byte_array_append(quark_pool_byte_array *p_self, const uint8_t p_data) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->append(p_data);
}

void QAPI quark_pool_byte_array_append_array(quark_pool_byte_array *p_self, const quark_pool_byte_array *p_array) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	PoolVector<uint8_t> *array = (PoolVector<uint8_t> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_byte_array_insert(quark_pool_byte_array *p_self, const quark_int p_idx, const uint8_t p_data) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	return (quark_error)self->insert(p_idx, p_data);
}

void QAPI quark_pool_byte_array_invert(quark_pool_byte_array *p_self) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->invert();
}

void QAPI quark_pool_byte_array_push_back(quark_pool_byte_array *p_self, const uint8_t p_data) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->push_back(p_data);
}

void QAPI quark_pool_byte_array_remove(quark_pool_byte_array *p_self, const quark_int p_idx) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_byte_array_resize(quark_pool_byte_array *p_self, const quark_int p_size) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->resize(p_size);
}

quark_pool_byte_array_read_access QAPI *quark_pool_byte_array_read(const quark_pool_byte_array *p_self) {
	const PoolVector<uint8_t> *self = (const PoolVector<uint8_t> *)p_self;
	return (quark_pool_byte_array_read_access *)memnew(PoolVector<uint8_t>::Read(self->read()));
}

quark_pool_byte_array_write_access QAPI *quark_pool_byte_array_write(quark_pool_byte_array *p_self) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	return (quark_pool_byte_array_write_access *)memnew(PoolVector<uint8_t>::Write(self->write()));
}

void QAPI quark_pool_byte_array_set(quark_pool_byte_array *p_self, const quark_int p_idx, const uint8_t p_data) {
	PoolVector<uint8_t> *self = (PoolVector<uint8_t> *)p_self;
	self->set(p_idx, p_data);
}

uint8_t QAPI quark_pool_byte_array_get(const quark_pool_byte_array *p_self, const quark_int p_idx) {
	const PoolVector<uint8_t> *self = (const PoolVector<uint8_t> *)p_self;
	return self->get(p_idx);
}

quark_int QAPI quark_pool_byte_array_size(const quark_pool_byte_array *p_self) {
	const PoolVector<uint8_t> *self = (const PoolVector<uint8_t> *)p_self;
	return self->size();
}

void QAPI quark_pool_byte_array_destroy(quark_pool_byte_array *p_self) {
	((PoolVector<uint8_t> *)p_self)->~PoolVector();
}

// int

void QAPI quark_pool_int_array_new(quark_pool_int_array *r_dest) {
	PoolVector<quark_int> *dest = (PoolVector<quark_int> *)r_dest;
	memnew_placement(dest, PoolVector<quark_int>);
}

void QAPI quark_pool_int_array_new_copy(quark_pool_int_array *r_dest, const quark_pool_int_array *p_src) {
	PoolVector<quark_int> *dest = (PoolVector<quark_int> *)r_dest;
	const PoolVector<quark_int> *src = (const PoolVector<quark_int> *)p_src;
	memnew_placement(dest, PoolVector<quark_int>(*src));
}

void QAPI quark_pool_int_array_new_with_array(quark_pool_int_array *r_dest, const quark_array *p_a) {
	PoolVector<quark_int> *dest = (PoolVector<quark_int> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<quark_int>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_int_array_append(quark_pool_int_array *p_self, const quark_int p_data) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->append(p_data);
}

void QAPI quark_pool_int_array_append_array(quark_pool_int_array *p_self, const quark_pool_int_array *p_array) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	PoolVector<quark_int> *array = (PoolVector<quark_int> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_int_array_insert(quark_pool_int_array *p_self, const quark_int p_idx, const quark_int p_data) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	return (quark_error)self->insert(p_idx, p_data);
}

void QAPI quark_pool_int_array_invert(quark_pool_int_array *p_self) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->invert();
}

void QAPI quark_pool_int_array_push_back(quark_pool_int_array *p_self, const quark_int p_data) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->push_back(p_data);
}

void QAPI quark_pool_int_array_remove(quark_pool_int_array *p_self, const quark_int p_idx) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_int_array_resize(quark_pool_int_array *p_self, const quark_int p_size) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->resize(p_size);
}

quark_pool_int_array_read_access QAPI *quark_pool_int_array_read(const quark_pool_int_array *p_self) {
	const PoolVector<quark_int> *self = (const PoolVector<quark_int> *)p_self;
	return (quark_pool_int_array_read_access *)memnew(PoolVector<quark_int>::Read(self->read()));
}

quark_pool_int_array_write_access QAPI *quark_pool_int_array_write(quark_pool_int_array *p_self) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	return (quark_pool_int_array_write_access *)memnew(PoolVector<quark_int>::Write(self->write()));
}

void QAPI quark_pool_int_array_set(quark_pool_int_array *p_self, const quark_int p_idx, const quark_int p_data) {
	PoolVector<quark_int> *self = (PoolVector<quark_int> *)p_self;
	self->set(p_idx, p_data);
}

quark_int QAPI quark_pool_int_array_get(const quark_pool_int_array *p_self, const quark_int p_idx) {
	const PoolVector<quark_int> *self = (const PoolVector<quark_int> *)p_self;
	return self->get(p_idx);
}

quark_int QAPI quark_pool_int_array_size(const quark_pool_int_array *p_self) {
	const PoolVector<quark_int> *self = (const PoolVector<quark_int> *)p_self;
	return self->size();
}

void QAPI quark_pool_int_array_destroy(quark_pool_int_array *p_self) {
	((PoolVector<quark_int> *)p_self)->~PoolVector();
}

// real

void QAPI quark_pool_real_array_new(quark_pool_real_array *r_dest) {
	PoolVector<quark_real> *dest = (PoolVector<quark_real> *)r_dest;
	memnew_placement(dest, PoolVector<quark_real>);
}

void QAPI quark_pool_real_array_new_copy(quark_pool_real_array *r_dest, const quark_pool_real_array *p_src) {
	PoolVector<quark_real> *dest = (PoolVector<quark_real> *)r_dest;
	const PoolVector<quark_real> *src = (const PoolVector<quark_real> *)p_src;
	memnew_placement(dest, PoolVector<quark_real>(*src));
}

void QAPI quark_pool_real_array_new_with_array(quark_pool_real_array *r_dest, const quark_array *p_a) {
	PoolVector<quark_real> *dest = (PoolVector<quark_real> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<quark_real>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_real_array_append(quark_pool_real_array *p_self, const quark_real p_data) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->append(p_data);
}

void QAPI quark_pool_real_array_append_array(quark_pool_real_array *p_self, const quark_pool_real_array *p_array) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	PoolVector<quark_real> *array = (PoolVector<quark_real> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_real_array_insert(quark_pool_real_array *p_self, const quark_int p_idx, const quark_real p_data) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	return (quark_error)self->insert(p_idx, p_data);
}

void QAPI quark_pool_real_array_invert(quark_pool_real_array *p_self) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->invert();
}

void QAPI quark_pool_real_array_push_back(quark_pool_real_array *p_self, const quark_real p_data) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->push_back(p_data);
}

void QAPI quark_pool_real_array_remove(quark_pool_real_array *p_self, const quark_int p_idx) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_real_array_resize(quark_pool_real_array *p_self, const quark_int p_size) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->resize(p_size);
}

quark_pool_real_array_read_access QAPI *quark_pool_real_array_read(const quark_pool_real_array *p_self) {
	const PoolVector<quark_real> *self = (const PoolVector<quark_real> *)p_self;
	return (quark_pool_real_array_read_access *)memnew(PoolVector<quark_real>::Read(self->read()));
}

quark_pool_int_array_write_access QAPI *quark_pool_real_array_write(quark_pool_real_array *p_self) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	return (quark_pool_real_array_write_access *)memnew(PoolVector<quark_real>::Write(self->write()));
}

void QAPI quark_pool_real_array_set(quark_pool_real_array *p_self, const quark_int p_idx, const quark_real p_data) {
	PoolVector<quark_real> *self = (PoolVector<quark_real> *)p_self;
	self->set(p_idx, p_data);
}

quark_real QAPI quark_pool_real_array_get(const quark_pool_real_array *p_self, const quark_int p_idx) {
	const PoolVector<quark_real> *self = (const PoolVector<quark_real> *)p_self;
	return self->get(p_idx);
}

quark_int QAPI quark_pool_real_array_size(const quark_pool_real_array *p_self) {
	const PoolVector<quark_real> *self = (const PoolVector<quark_real> *)p_self;
	return self->size();
}

void QAPI quark_pool_real_array_destroy(quark_pool_real_array *p_self) {
	((PoolVector<quark_real> *)p_self)->~PoolVector();
}

// string

void QAPI quark_pool_string_array_new(quark_pool_string_array *r_dest) {
	PoolVector<String> *dest = (PoolVector<String> *)r_dest;
	memnew_placement(dest, PoolVector<String>);
}

void QAPI quark_pool_string_array_new_copy(quark_pool_string_array *r_dest, const quark_pool_string_array *p_src) {
	PoolVector<String> *dest = (PoolVector<String> *)r_dest;
	const PoolVector<String> *src = (const PoolVector<String> *)p_src;
	memnew_placement(dest, PoolVector<String>(*src));
}

void QAPI quark_pool_string_array_new_with_array(quark_pool_string_array *r_dest, const quark_array *p_a) {
	PoolVector<String> *dest = (PoolVector<String> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<String>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_string_array_append(quark_pool_string_array *p_self, const quark_string *p_data) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	String &s = *(String *)p_data;
	self->append(s);
}

void QAPI quark_pool_string_array_append_array(quark_pool_string_array *p_self, const quark_pool_string_array *p_array) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	PoolVector<String> *array = (PoolVector<String> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_string_array_insert(quark_pool_string_array *p_self, const quark_int p_idx, const quark_string *p_data) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	String &s = *(String *)p_data;
	return (quark_error)self->insert(p_idx, s);
}

void QAPI quark_pool_string_array_invert(quark_pool_string_array *p_self) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	self->invert();
}

void QAPI quark_pool_string_array_push_back(quark_pool_string_array *p_self, const quark_string *p_data) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	String &s = *(String *)p_data;
	self->push_back(s);
}

void QAPI quark_pool_string_array_remove(quark_pool_string_array *p_self, const quark_int p_idx) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_string_array_resize(quark_pool_string_array *p_self, const quark_int p_size) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	self->resize(p_size);
}

quark_pool_string_array_read_access QAPI *quark_pool_string_array_read(const quark_pool_string_array *p_self) {
	const PoolVector<String> *self = (const PoolVector<String> *)p_self;
	return (quark_pool_string_array_read_access *)memnew(PoolVector<String>::Read(self->read()));
}

quark_pool_string_array_write_access QAPI *quark_pool_string_array_write(quark_pool_string_array *p_self) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	return (quark_pool_string_array_write_access *)memnew(PoolVector<String>::Write(self->write()));
}

void QAPI quark_pool_string_array_set(quark_pool_string_array *p_self, const quark_int p_idx, const quark_string *p_data) {
	PoolVector<String> *self = (PoolVector<String> *)p_self;
	String &s = *(String *)p_data;
	self->set(p_idx, s);
}

quark_string QAPI quark_pool_string_array_get(const quark_pool_string_array *p_self, const quark_int p_idx) {
	const PoolVector<String> *self = (const PoolVector<String> *)p_self;
	quark_string str;
	String *s = (String *)&str;
	memnew_placement(s, String);
	*s = self->get(p_idx);
	return str;
}

quark_int QAPI quark_pool_string_array_size(const quark_pool_string_array *p_self) {
	const PoolVector<String> *self = (const PoolVector<String> *)p_self;
	return self->size();
}

void QAPI quark_pool_string_array_destroy(quark_pool_string_array *p_self) {
	((PoolVector<String> *)p_self)->~PoolVector();
}

// vector2

void QAPI quark_pool_vector2_array_new(quark_pool_vector2_array *r_dest) {
	PoolVector<Vector2> *dest = (PoolVector<Vector2> *)r_dest;
	memnew_placement(dest, PoolVector<Vector2>);
}

void QAPI quark_pool_vector2_array_new_copy(quark_pool_vector2_array *r_dest, const quark_pool_vector2_array *p_src) {
	PoolVector<Vector2> *dest = (PoolVector<Vector2> *)r_dest;
	const PoolVector<Vector2> *src = (const PoolVector<Vector2> *)p_src;
	memnew_placement(dest, PoolVector<Vector2>(*src));
}

void QAPI quark_pool_vector2_array_new_with_array(quark_pool_vector2_array *r_dest, const quark_array *p_a) {
	PoolVector<Vector2> *dest = (PoolVector<Vector2> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<Vector2>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_vector2_array_append(quark_pool_vector2_array *p_self, const quark_vector2 *p_data) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	Vector2 &s = *(Vector2 *)p_data;
	self->append(s);
}

void QAPI quark_pool_vector2_array_append_array(quark_pool_vector2_array *p_self, const quark_pool_vector2_array *p_array) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	PoolVector<Vector2> *array = (PoolVector<Vector2> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_vector2_array_insert(quark_pool_vector2_array *p_self, const quark_int p_idx, const quark_vector2 *p_data) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	Vector2 &s = *(Vector2 *)p_data;
	return (quark_error)self->insert(p_idx, s);
}

void QAPI quark_pool_vector2_array_invert(quark_pool_vector2_array *p_self) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	self->invert();
}

void QAPI quark_pool_vector2_array_push_back(quark_pool_vector2_array *p_self, const quark_vector2 *p_data) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	Vector2 &s = *(Vector2 *)p_data;
	self->push_back(s);
}

void QAPI quark_pool_vector2_array_remove(quark_pool_vector2_array *p_self, const quark_int p_idx) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_vector2_array_resize(quark_pool_vector2_array *p_self, const quark_int p_size) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	self->resize(p_size);
}

quark_pool_vector2_array_read_access QAPI *quark_pool_vector2_array_read(const quark_pool_vector2_array *p_self) {
	const PoolVector<Vector2> *self = (const PoolVector<Vector2> *)p_self;
	return (quark_pool_vector2_array_read_access *)memnew(PoolVector<Vector2>::Read(self->read()));
}

quark_pool_vector2_array_write_access QAPI *quark_pool_vector2_array_write(quark_pool_vector2_array *p_self) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	return (quark_pool_vector2_array_write_access *)memnew(PoolVector<Vector2>::Write(self->write()));
}

void QAPI quark_pool_vector2_array_set(quark_pool_vector2_array *p_self, const quark_int p_idx, const quark_vector2 *p_data) {
	PoolVector<Vector2> *self = (PoolVector<Vector2> *)p_self;
	Vector2 &s = *(Vector2 *)p_data;
	self->set(p_idx, s);
}

quark_vector2 QAPI quark_pool_vector2_array_get(const quark_pool_vector2_array *p_self, const quark_int p_idx) {
	const PoolVector<Vector2> *self = (const PoolVector<Vector2> *)p_self;
	quark_vector2 v;
	Vector2 *s = (Vector2 *)&v;
	*s = self->get(p_idx);
	return v;
}

quark_int QAPI quark_pool_vector2_array_size(const quark_pool_vector2_array *p_self) {
	const PoolVector<Vector2> *self = (const PoolVector<Vector2> *)p_self;
	return self->size();
}

void QAPI quark_pool_vector2_array_destroy(quark_pool_vector2_array *p_self) {
	((PoolVector<Vector2> *)p_self)->~PoolVector();
}

// vector3

void QAPI quark_pool_vector3_array_new(quark_pool_vector3_array *r_dest) {
	PoolVector<Vector3> *dest = (PoolVector<Vector3> *)r_dest;
	memnew_placement(dest, PoolVector<Vector3>);
}

void QAPI quark_pool_vector3_array_new_copy(quark_pool_vector3_array *r_dest, const quark_pool_vector3_array *p_src) {
	PoolVector<Vector3> *dest = (PoolVector<Vector3> *)r_dest;
	const PoolVector<Vector3> *src = (const PoolVector<Vector3> *)p_src;
	memnew_placement(dest, PoolVector<Vector3>(*src));
}

void QAPI quark_pool_vector3_array_new_with_array(quark_pool_vector3_array *r_dest, const quark_array *p_a) {
	PoolVector<Vector3> *dest = (PoolVector<Vector3> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<Vector3>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_vector3_array_append(quark_pool_vector3_array *p_self, const quark_vector3 *p_data) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	Vector3 &s = *(Vector3 *)p_data;
	self->append(s);
}

void QAPI quark_pool_vector3_array_append_array(quark_pool_vector3_array *p_self, const quark_pool_vector3_array *p_array) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	PoolVector<Vector3> *array = (PoolVector<Vector3> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_vector3_array_insert(quark_pool_vector3_array *p_self, const quark_int p_idx, const quark_vector3 *p_data) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	Vector3 &s = *(Vector3 *)p_data;
	return (quark_error)self->insert(p_idx, s);
}

void QAPI quark_pool_vector3_array_invert(quark_pool_vector3_array *p_self) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	self->invert();
}

void QAPI quark_pool_vector3_array_push_back(quark_pool_vector3_array *p_self, const quark_vector3 *p_data) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	Vector3 &s = *(Vector3 *)p_data;
	self->push_back(s);
}

void QAPI quark_pool_vector3_array_remove(quark_pool_vector3_array *p_self, const quark_int p_idx) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_vector3_array_resize(quark_pool_vector3_array *p_self, const quark_int p_size) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	self->resize(p_size);
}

quark_pool_vector3_array_read_access QAPI *quark_pool_vector3_array_read(const quark_pool_vector3_array *p_self) {
	const PoolVector<Vector3> *self = (const PoolVector<Vector3> *)p_self;
	return (quark_pool_vector3_array_read_access *)memnew(PoolVector<Vector3>::Read(self->read()));
}

quark_pool_vector3_array_write_access QAPI *quark_pool_vector3_array_write(quark_pool_vector3_array *p_self) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	return (quark_pool_vector3_array_write_access *)memnew(PoolVector<Vector3>::Write(self->write()));
}

void QAPI quark_pool_vector3_array_set(quark_pool_vector3_array *p_self, const quark_int p_idx, const quark_vector3 *p_data) {
	PoolVector<Vector3> *self = (PoolVector<Vector3> *)p_self;
	Vector3 &s = *(Vector3 *)p_data;
	self->set(p_idx, s);
}

quark_vector3 QAPI quark_pool_vector3_array_get(const quark_pool_vector3_array *p_self, const quark_int p_idx) {
	const PoolVector<Vector3> *self = (const PoolVector<Vector3> *)p_self;
	quark_vector3 v;
	Vector3 *s = (Vector3 *)&v;
	*s = self->get(p_idx);
	return v;
}

quark_int QAPI quark_pool_vector3_array_size(const quark_pool_vector3_array *p_self) {
	const PoolVector<Vector3> *self = (const PoolVector<Vector3> *)p_self;
	return self->size();
}

void QAPI quark_pool_vector3_array_destroy(quark_pool_vector3_array *p_self) {
	((PoolVector<Vector3> *)p_self)->~PoolVector();
}

// color

void QAPI quark_pool_color_array_new(quark_pool_color_array *r_dest) {
	PoolVector<Color> *dest = (PoolVector<Color> *)r_dest;
	memnew_placement(dest, PoolVector<Color>);
}

void QAPI quark_pool_color_array_new_copy(quark_pool_color_array *r_dest, const quark_pool_color_array *p_src) {
	PoolVector<Color> *dest = (PoolVector<Color> *)r_dest;
	const PoolVector<Color> *src = (const PoolVector<Color> *)p_src;
	memnew_placement(dest, PoolVector<Color>(*src));
}

void QAPI quark_pool_color_array_new_with_array(quark_pool_color_array *r_dest, const quark_array *p_a) {
	PoolVector<Color> *dest = (PoolVector<Color> *)r_dest;
	Array *a = (Array *)p_a;
	memnew_placement(dest, PoolVector<Color>);

	dest->resize(a->size());
	for (int i = 0; i < a->size(); i++) {
		dest->set(i, (*a)[i]);
	}
}

void QAPI quark_pool_color_array_append(quark_pool_color_array *p_self, const quark_color *p_data) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	Color &s = *(Color *)p_data;
	self->append(s);
}

void QAPI quark_pool_color_array_append_array(quark_pool_color_array *p_self, const quark_pool_color_array *p_array) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	PoolVector<Color> *array = (PoolVector<Color> *)p_array;
	self->append_array(*array);
}

quark_error QAPI quark_pool_color_array_insert(quark_pool_color_array *p_self, const quark_int p_idx, const quark_color *p_data) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	Color &s = *(Color *)p_data;
	return (quark_error)self->insert(p_idx, s);
}

void QAPI quark_pool_color_array_invert(quark_pool_color_array *p_self) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	self->invert();
}

void QAPI quark_pool_color_array_push_back(quark_pool_color_array *p_self, const quark_color *p_data) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	Color &s = *(Color *)p_data;
	self->push_back(s);
}

void QAPI quark_pool_color_array_remove(quark_pool_color_array *p_self, const quark_int p_idx) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	self->remove(p_idx);
}

void QAPI quark_pool_color_array_resize(quark_pool_color_array *p_self, const quark_int p_size) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	self->resize(p_size);
}

quark_pool_color_array_read_access QAPI *quark_pool_color_array_read(const quark_pool_color_array *p_self) {
	const PoolVector<Color> *self = (const PoolVector<Color> *)p_self;
	return (quark_pool_color_array_read_access *)memnew(PoolVector<Color>::Read(self->read()));
}

quark_pool_color_array_write_access QAPI *quark_pool_color_array_write(quark_pool_color_array *p_self) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	return (quark_pool_color_array_write_access *)memnew(PoolVector<Color>::Write(self->write()));
}

void QAPI quark_pool_color_array_set(quark_pool_color_array *p_self, const quark_int p_idx, const quark_color *p_data) {
	PoolVector<Color> *self = (PoolVector<Color> *)p_self;
	Color &s = *(Color *)p_data;
	self->set(p_idx, s);
}

quark_color QAPI quark_pool_color_array_get(const quark_pool_color_array *p_self, const quark_int p_idx) {
	const PoolVector<Color> *self = (const PoolVector<Color> *)p_self;
	quark_color v;
	Color *s = (Color *)&v;
	*s = self->get(p_idx);
	return v;
}

quark_int QAPI quark_pool_color_array_size(const quark_pool_color_array *p_self) {
	const PoolVector<Color> *self = (const PoolVector<Color> *)p_self;
	return self->size();
}

void QAPI quark_pool_color_array_destroy(quark_pool_color_array *p_self) {
	((PoolVector<Color> *)p_self)->~PoolVector();
}

//
// read accessor functions
//

quark_pool_byte_array_read_access QAPI *quark_pool_byte_array_read_access_copy(const quark_pool_byte_array_read_access *p_other) {
	PoolVector<uint8_t>::Read *other = (PoolVector<uint8_t>::Read *)p_other;
	return (quark_pool_byte_array_read_access *)memnew(PoolVector<uint8_t>::Read(*other));
}
const uint8_t QAPI *quark_pool_byte_array_read_access_ptr(const quark_pool_byte_array_read_access *p_read) {
	const PoolVector<uint8_t>::Read *read = (const PoolVector<uint8_t>::Read *)p_read;
	return read->ptr();
}
void QAPI quark_pool_byte_array_read_access_operator_assign(quark_pool_byte_array_read_access *p_read, quark_pool_byte_array_read_access *p_other) {
	PoolVector<uint8_t>::Read *read = (PoolVector<uint8_t>::Read *)p_read;
	PoolVector<uint8_t>::Read *other = (PoolVector<uint8_t>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_byte_array_read_access_destroy(quark_pool_byte_array_read_access *p_read) {
	memdelete((PoolVector<uint8_t>::Read *)p_read);
}

quark_pool_int_array_read_access QAPI *quark_pool_int_array_read_access_copy(const quark_pool_int_array_read_access *p_other) {
	PoolVector<quark_int>::Read *other = (PoolVector<quark_int>::Read *)p_other;
	return (quark_pool_int_array_read_access *)memnew(PoolVector<quark_int>::Read(*other));
}
const quark_int QAPI *quark_pool_int_array_read_access_ptr(const quark_pool_int_array_read_access *p_read) {
	const PoolVector<quark_int>::Read *read = (const PoolVector<quark_int>::Read *)p_read;
	return read->ptr();
}
void QAPI quark_pool_int_array_read_access_operator_assign(quark_pool_int_array_read_access *p_read, quark_pool_int_array_read_access *p_other) {
	PoolVector<quark_int>::Read *read = (PoolVector<quark_int>::Read *)p_read;
	PoolVector<quark_int>::Read *other = (PoolVector<quark_int>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_int_array_read_access_destroy(quark_pool_int_array_read_access *p_read) {
	memdelete((PoolVector<quark_int>::Read *)p_read);
}

quark_pool_real_array_read_access QAPI *quark_pool_real_array_read_access_copy(const quark_pool_real_array_read_access *p_other) {
	PoolVector<quark_real>::Read *other = (PoolVector<quark_real>::Read *)p_other;
	return (quark_pool_real_array_read_access *)memnew(PoolVector<quark_real>::Read(*other));
}
const quark_real QAPI *quark_pool_real_array_read_access_ptr(const quark_pool_real_array_read_access *p_read) {
	const PoolVector<quark_real>::Read *read = (const PoolVector<quark_real>::Read *)p_read;
	return read->ptr();
}
void QAPI quark_pool_real_array_read_access_operator_assign(quark_pool_real_array_read_access *p_read, quark_pool_real_array_read_access *p_other) {
	PoolVector<quark_real>::Read *read = (PoolVector<quark_real>::Read *)p_read;
	PoolVector<quark_real>::Read *other = (PoolVector<quark_real>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_real_array_read_access_destroy(quark_pool_real_array_read_access *p_read) {
	memdelete((PoolVector<quark_real>::Read *)p_read);
}

quark_pool_string_array_read_access QAPI *quark_pool_string_array_read_access_copy(const quark_pool_string_array_read_access *p_other) {
	PoolVector<String>::Read *other = (PoolVector<String>::Read *)p_other;
	return (quark_pool_string_array_read_access *)memnew(PoolVector<String>::Read(*other));
}
const quark_string QAPI *quark_pool_string_array_read_access_ptr(const quark_pool_string_array_read_access *p_read) {
	const PoolVector<String>::Read *read = (const PoolVector<String>::Read *)p_read;
	return (const quark_string *)read->ptr();
}
void QAPI quark_pool_string_array_read_access_operator_assign(quark_pool_string_array_read_access *p_read, quark_pool_string_array_read_access *p_other) {
	PoolVector<String>::Read *read = (PoolVector<String>::Read *)p_read;
	PoolVector<String>::Read *other = (PoolVector<String>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_string_array_read_access_destroy(quark_pool_string_array_read_access *p_read) {
	memdelete((PoolVector<String>::Read *)p_read);
}

quark_pool_vector2_array_read_access QAPI *quark_pool_vector2_array_read_access_copy(const quark_pool_vector2_array_read_access *p_other) {
	PoolVector<Vector2>::Read *other = (PoolVector<Vector2>::Read *)p_other;
	return (quark_pool_vector2_array_read_access *)memnew(PoolVector<Vector2>::Read(*other));
}
const quark_vector2 QAPI *quark_pool_vector2_array_read_access_ptr(const quark_pool_vector2_array_read_access *p_read) {
	const PoolVector<Vector2>::Read *read = (const PoolVector<Vector2>::Read *)p_read;
	return (const quark_vector2 *)read->ptr();
}
void QAPI quark_pool_vector2_array_read_access_operator_assign(quark_pool_vector2_array_read_access *p_read, quark_pool_vector2_array_read_access *p_other) {
	PoolVector<Vector2>::Read *read = (PoolVector<Vector2>::Read *)p_read;
	PoolVector<Vector2>::Read *other = (PoolVector<Vector2>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_vector2_array_read_access_destroy(quark_pool_vector2_array_read_access *p_read) {
	memdelete((PoolVector<Vector2>::Read *)p_read);
}

quark_pool_vector3_array_read_access QAPI *quark_pool_vector3_array_read_access_copy(const quark_pool_vector3_array_read_access *p_other) {
	PoolVector<Vector3>::Read *other = (PoolVector<Vector3>::Read *)p_other;
	return (quark_pool_vector3_array_read_access *)memnew(PoolVector<Vector3>::Read(*other));
}
const quark_vector3 QAPI *quark_pool_vector3_array_read_access_ptr(const quark_pool_vector3_array_read_access *p_read) {
	const PoolVector<Vector3>::Read *read = (const PoolVector<Vector3>::Read *)p_read;
	return (const quark_vector3 *)read->ptr();
}
void QAPI quark_pool_vector3_array_read_access_operator_assign(quark_pool_vector3_array_read_access *p_read, quark_pool_vector3_array_read_access *p_other) {
	PoolVector<Vector3>::Read *read = (PoolVector<Vector3>::Read *)p_read;
	PoolVector<Vector3>::Read *other = (PoolVector<Vector3>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_vector3_array_read_access_destroy(quark_pool_vector3_array_read_access *p_read) {
	memdelete((PoolVector<Vector2>::Read *)p_read);
}

quark_pool_color_array_read_access QAPI *quark_pool_color_array_read_access_copy(const quark_pool_color_array_read_access *p_other) {
	PoolVector<Color>::Read *other = (PoolVector<Color>::Read *)p_other;
	return (quark_pool_color_array_read_access *)memnew(PoolVector<Color>::Read(*other));
}
const quark_color QAPI *quark_pool_color_array_read_access_ptr(const quark_pool_color_array_read_access *p_read) {
	const PoolVector<Color>::Read *read = (const PoolVector<Color>::Read *)p_read;
	return (const quark_color *)read->ptr();
}
void QAPI quark_pool_color_array_read_access_operator_assign(quark_pool_color_array_read_access *p_read, quark_pool_color_array_read_access *p_other) {
	PoolVector<Color>::Read *read = (PoolVector<Color>::Read *)p_read;
	PoolVector<Color>::Read *other = (PoolVector<Color>::Read *)p_other;
	read->operator=(*other);
}
void QAPI quark_pool_color_array_read_access_destroy(quark_pool_color_array_read_access *p_read) {
	memdelete((PoolVector<Color>::Read *)p_read);
}

//
// write accessor functions
//

quark_pool_byte_array_write_access QAPI *quark_pool_byte_array_write_access_copy(const quark_pool_byte_array_write_access *p_other) {
	PoolVector<uint8_t>::Write *other = (PoolVector<uint8_t>::Write *)p_other;
	return (quark_pool_byte_array_write_access *)memnew(PoolVector<uint8_t>::Write(*other));
}
uint8_t QAPI *quark_pool_byte_array_write_access_ptr(const quark_pool_byte_array_write_access *p_write) {
	PoolVector<uint8_t>::Write *write = (PoolVector<uint8_t>::Write *)p_write;
	return write->ptr();
}
void QAPI quark_pool_byte_array_write_access_operator_assign(quark_pool_byte_array_write_access *p_write, quark_pool_byte_array_write_access *p_other) {
	PoolVector<uint8_t>::Write *write = (PoolVector<uint8_t>::Write *)p_write;
	PoolVector<uint8_t>::Write *other = (PoolVector<uint8_t>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_byte_array_write_access_destroy(quark_pool_byte_array_write_access *p_write) {
	memdelete((PoolVector<uint8_t>::Write *)p_write);
}

quark_pool_int_array_write_access QAPI *quark_pool_int_array_write_access_copy(const quark_pool_int_array_write_access *p_other) {
	PoolVector<quark_int>::Write *other = (PoolVector<quark_int>::Write *)p_other;
	return (quark_pool_int_array_write_access *)memnew(PoolVector<quark_int>::Write(*other));
}
quark_int QAPI *quark_pool_int_array_write_access_ptr(const quark_pool_int_array_write_access *p_write) {
	PoolVector<quark_int>::Write *write = (PoolVector<quark_int>::Write *)p_write;
	return write->ptr();
}
void QAPI quark_pool_int_array_write_access_operator_assign(quark_pool_int_array_write_access *p_write, quark_pool_int_array_write_access *p_other) {
	PoolVector<quark_int>::Write *write = (PoolVector<quark_int>::Write *)p_write;
	PoolVector<quark_int>::Write *other = (PoolVector<quark_int>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_int_array_write_access_destroy(quark_pool_int_array_write_access *p_write) {
	memdelete((PoolVector<quark_int>::Write *)p_write);
}

quark_pool_real_array_write_access QAPI *quark_pool_real_array_write_access_copy(const quark_pool_real_array_write_access *p_other) {
	PoolVector<quark_real>::Write *other = (PoolVector<quark_real>::Write *)p_other;
	return (quark_pool_real_array_write_access *)memnew(PoolVector<quark_real>::Write(*other));
}
quark_real QAPI *quark_pool_real_array_write_access_ptr(const quark_pool_real_array_write_access *p_write) {
	PoolVector<quark_real>::Write *write = (PoolVector<quark_real>::Write *)p_write;
	return write->ptr();
}
void QAPI quark_pool_real_array_write_access_operator_assign(quark_pool_real_array_write_access *p_write, quark_pool_real_array_write_access *p_other) {
	PoolVector<quark_real>::Write *write = (PoolVector<quark_real>::Write *)p_write;
	PoolVector<quark_real>::Write *other = (PoolVector<quark_real>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_real_array_write_access_destroy(quark_pool_real_array_write_access *p_write) {
	memdelete((PoolVector<quark_real>::Write *)p_write);
}

quark_pool_string_array_write_access QAPI *quark_pool_string_array_write_access_copy(const quark_pool_string_array_write_access *p_other) {
	PoolVector<String>::Write *other = (PoolVector<String>::Write *)p_other;
	return (quark_pool_string_array_write_access *)memnew(PoolVector<String>::Write(*other));
}
quark_string QAPI *quark_pool_string_array_write_access_ptr(const quark_pool_string_array_write_access *p_write) {
	PoolVector<String>::Write *write = (PoolVector<String>::Write *)p_write;
	return (quark_string *)write->ptr();
}
void QAPI quark_pool_string_array_write_access_operator_assign(quark_pool_string_array_write_access *p_write, quark_pool_string_array_write_access *p_other) {
	PoolVector<String>::Write *write = (PoolVector<String>::Write *)p_write;
	PoolVector<String>::Write *other = (PoolVector<String>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_string_array_write_access_destroy(quark_pool_string_array_write_access *p_write) {
	memdelete((PoolVector<String>::Write *)p_write);
}

quark_pool_vector2_array_write_access QAPI *quark_pool_vector2_array_write_access_copy(const quark_pool_vector2_array_write_access *p_other) {
	PoolVector<Vector2>::Write *other = (PoolVector<Vector2>::Write *)p_other;
	return (quark_pool_vector2_array_write_access *)memnew(PoolVector<Vector2>::Write(*other));
}
quark_vector2 QAPI *quark_pool_vector2_array_write_access_ptr(const quark_pool_vector2_array_write_access *p_write) {
	PoolVector<Vector2>::Write *write = (PoolVector<Vector2>::Write *)p_write;
	return (quark_vector2 *)write->ptr();
}
void QAPI quark_pool_vector2_array_write_access_operator_assign(quark_pool_vector2_array_write_access *p_write, quark_pool_vector2_array_write_access *p_other) {
	PoolVector<Vector2>::Write *write = (PoolVector<Vector2>::Write *)p_write;
	PoolVector<Vector2>::Write *other = (PoolVector<Vector2>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_vector2_array_write_access_destroy(quark_pool_vector2_array_write_access *p_write) {
	memdelete((PoolVector<Vector2>::Write *)p_write);
}

quark_pool_vector3_array_write_access QAPI *quark_pool_vector3_array_write_access_copy(const quark_pool_vector3_array_write_access *p_other) {
	PoolVector<Vector3>::Write *other = (PoolVector<Vector3>::Write *)p_other;
	return (quark_pool_vector3_array_write_access *)memnew(PoolVector<Vector3>::Write(*other));
}
quark_vector3 QAPI *quark_pool_vector3_array_write_access_ptr(const quark_pool_vector3_array_write_access *p_write) {
	PoolVector<Vector3>::Write *write = (PoolVector<Vector3>::Write *)p_write;
	return (quark_vector3 *)write->ptr();
}
void QAPI quark_pool_vector3_array_write_access_operator_assign(quark_pool_vector3_array_write_access *p_write, quark_pool_vector3_array_write_access *p_other) {
	PoolVector<Vector3>::Write *write = (PoolVector<Vector3>::Write *)p_write;
	PoolVector<Vector3>::Write *other = (PoolVector<Vector3>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_vector3_array_write_access_destroy(quark_pool_vector3_array_write_access *p_write) {
	memdelete((PoolVector<Vector3>::Write *)p_write);
}

quark_pool_color_array_write_access QAPI *quark_pool_color_array_write_access_copy(const quark_pool_color_array_write_access *p_other) {
	PoolVector<Color>::Write *other = (PoolVector<Color>::Write *)p_other;
	return (quark_pool_color_array_write_access *)memnew(PoolVector<Color>::Write(*other));
}
quark_color QAPI *quark_pool_color_array_write_access_ptr(const quark_pool_color_array_write_access *p_write) {
	PoolVector<Color>::Write *write = (PoolVector<Color>::Write *)p_write;
	return (quark_color *)write->ptr();
}
void QAPI quark_pool_color_array_write_access_operator_assign(quark_pool_color_array_write_access *p_write, quark_pool_color_array_write_access *p_other) {
	PoolVector<Color>::Write *write = (PoolVector<Color>::Write *)p_write;
	PoolVector<Color>::Write *other = (PoolVector<Color>::Write *)p_other;
	write->operator=(*other);
}
void QAPI quark_pool_color_array_write_access_destroy(quark_pool_color_array_write_access *p_write) {
	memdelete((PoolVector<Color>::Write *)p_write);
}

#ifdef __cplusplus
}
#endif
