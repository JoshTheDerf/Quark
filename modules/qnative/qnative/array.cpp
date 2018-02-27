/*************************************************************************/
/*  array.cpp                                                            */
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

#include "qnative/array.h"

#include "core/array.h"
#include "core/os/memory.h"

#include "core/color.h"
#include "core/dvector.h"

#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_array_new(quark_array *r_dest) {
	Array *dest = (Array *)r_dest;
	memnew_placement(dest, Array);
}

void QAPI quark_array_new_copy(quark_array *r_dest, const quark_array *p_src) {
	Array *dest = (Array *)r_dest;
	const Array *src = (const Array *)p_src;
	memnew_placement(dest, Array(*src));
}

void QAPI quark_array_new_pool_color_array(quark_array *r_dest, const quark_pool_color_array *p_pca) {
	Array *dest = (Array *)r_dest;
	PoolVector<Color> *pca = (PoolVector<Color> *)p_pca;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_vector3_array(quark_array *r_dest, const quark_pool_vector3_array *p_pv3a) {
	Array *dest = (Array *)r_dest;
	PoolVector<Vector3> *pca = (PoolVector<Vector3> *)p_pv3a;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_vector2_array(quark_array *r_dest, const quark_pool_vector2_array *p_pv2a) {
	Array *dest = (Array *)r_dest;
	PoolVector<Vector2> *pca = (PoolVector<Vector2> *)p_pv2a;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_string_array(quark_array *r_dest, const quark_pool_string_array *p_psa) {
	Array *dest = (Array *)r_dest;
	PoolVector<String> *pca = (PoolVector<String> *)p_psa;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_real_array(quark_array *r_dest, const quark_pool_real_array *p_pra) {
	Array *dest = (Array *)r_dest;
	PoolVector<quark_real> *pca = (PoolVector<quark_real> *)p_pra;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_int_array(quark_array *r_dest, const quark_pool_int_array *p_pia) {
	Array *dest = (Array *)r_dest;
	PoolVector<quark_int> *pca = (PoolVector<quark_int> *)p_pia;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_new_pool_byte_array(quark_array *r_dest, const quark_pool_byte_array *p_pba) {
	Array *dest = (Array *)r_dest;
	PoolVector<uint8_t> *pca = (PoolVector<uint8_t> *)p_pba;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void QAPI quark_array_set(quark_array *p_self, const quark_int p_idx, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	Variant *val = (Variant *)p_value;
	self->operator[](p_idx) = *val;
}

quark_variant QAPI quark_array_get(const quark_array *p_self, const quark_int p_idx) {
	quark_variant raw_dest;
	Variant *dest = (Variant *)&raw_dest;
	const Array *self = (const Array *)p_self;
	memnew_placement(dest, Variant(self->operator[](p_idx)));
	return raw_dest;
}

quark_variant QAPI *quark_array_operator_index(quark_array *p_self, const quark_int p_idx) {
	Array *self = (Array *)p_self;
	return (quark_variant *)&self->operator[](p_idx);
}

const quark_variant QAPI *quark_array_operator_index_const(const quark_array *p_self, const quark_int p_idx) {
	const Array *self = (const Array *)p_self;
	return (const quark_variant *)&self->operator[](p_idx);
}

void QAPI quark_array_append(quark_array *p_self, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	Variant *val = (Variant *)p_value;
	self->append(*val);
}

void QAPI quark_array_clear(quark_array *p_self) {
	Array *self = (Array *)p_self;
	self->clear();
}

quark_int QAPI quark_array_count(const quark_array *p_self, const quark_variant *p_value) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	return self->count(*val);
}

quark_bool QAPI quark_array_empty(const quark_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->empty();
}

void QAPI quark_array_erase(quark_array *p_self, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->erase(*val);
}

quark_variant QAPI quark_array_front(const quark_array *p_self) {
	const Array *self = (const Array *)p_self;
	quark_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->front();
	return v;
}

quark_variant QAPI quark_array_back(const quark_array *p_self) {
	const Array *self = (const Array *)p_self;
	quark_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->back();
	return v;
}

quark_int QAPI quark_array_find(const quark_array *p_self, const quark_variant *p_what, const quark_int p_from) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->find(*val, p_from);
}

quark_int QAPI quark_array_find_last(const quark_array *p_self, const quark_variant *p_what) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->find_last(*val);
}

quark_bool QAPI quark_array_has(const quark_array *p_self, const quark_variant *p_value) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	return self->has(*val);
}

quark_int QAPI quark_array_hash(const quark_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->hash();
}

void QAPI quark_array_insert(quark_array *p_self, const quark_int p_pos, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->insert(p_pos, *val);
}

void QAPI quark_array_invert(quark_array *p_self) {
	Array *self = (Array *)p_self;
	self->invert();
}

quark_variant QAPI quark_array_pop_back(quark_array *p_self) {
	Array *self = (Array *)p_self;
	quark_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->pop_back();
	return v;
}

quark_variant QAPI quark_array_pop_front(quark_array *p_self) {
	Array *self = (Array *)p_self;
	quark_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->pop_front();
	return v;
}

void QAPI quark_array_push_back(quark_array *p_self, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->push_back(*val);
}

void QAPI quark_array_push_front(quark_array *p_self, const quark_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->push_front(*val);
}

void QAPI quark_array_remove(quark_array *p_self, const quark_int p_idx) {
	Array *self = (Array *)p_self;
	self->remove(p_idx);
}

void QAPI quark_array_resize(quark_array *p_self, const quark_int p_size) {
	Array *self = (Array *)p_self;
	self->resize(p_size);
}

quark_int QAPI quark_array_rfind(const quark_array *p_self, const quark_variant *p_what, const quark_int p_from) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->rfind(*val, p_from);
}

quark_int QAPI quark_array_size(const quark_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->size();
}

void QAPI quark_array_sort(quark_array *p_self) {
	Array *self = (Array *)p_self;
	self->sort();
}

void QAPI quark_array_sort_custom(quark_array *p_self, quark_object *p_obj, const quark_string *p_func) {
	Array *self = (Array *)p_self;
	const String *func = (const String *)p_func;
	self->sort_custom((Object *)p_obj, *func);
}

quark_int QAPI quark_array_bsearch(quark_array *p_self, const quark_variant *p_value, const quark_bool p_before) {
	Array *self = (Array *)p_self;
	return self->bsearch((const Variant *)p_value, p_before);
}

quark_int QAPI quark_array_bsearch_custom(quark_array *p_self, const quark_variant *p_value, quark_object *p_obj, const quark_string *p_func, const quark_bool p_before) {
	Array *self = (Array *)p_self;
	const String *func = (const String *)p_func;
	return self->bsearch_custom((const Variant *)p_value, (Object *)p_obj, *func, p_before);
}

void QAPI quark_array_destroy(quark_array *p_self) {
	((Array *)p_self)->~Array();
}

#ifdef __cplusplus
}
#endif
