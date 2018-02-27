/*************************************************************************/
/*  dictionary.cpp                                                       */
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

#include "qnative/dictionary.h"

#include "core/variant.h"
// core/variant.h before to avoid compile errors with MSVC
#include "core/dictionary.h"

#ifdef __cplusplus
extern "C" {
#endif

void QAPI quark_dictionary_new(quark_dictionary *r_dest) {
	Dictionary *dest = (Dictionary *)r_dest;
	memnew_placement(dest, Dictionary);
}

void QAPI quark_dictionary_new_copy(quark_dictionary *r_dest, const quark_dictionary *p_src) {
	Dictionary *dest = (Dictionary *)r_dest;
	const Dictionary *src = (const Dictionary *)p_src;
	memnew_placement(dest, Dictionary(*src));
}

void QAPI quark_dictionary_destroy(quark_dictionary *p_self) {
	Dictionary *self = (Dictionary *)p_self;
	self->~Dictionary();
}

quark_int QAPI quark_dictionary_size(const quark_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->size();
}

quark_bool QAPI quark_dictionary_empty(const quark_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->empty();
}

void QAPI quark_dictionary_clear(quark_dictionary *p_self) {
	Dictionary *self = (Dictionary *)p_self;
	self->clear();
}

quark_bool QAPI quark_dictionary_has(const quark_dictionary *p_self, const quark_variant *p_key) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return self->has(*key);
}

quark_bool QAPI quark_dictionary_has_all(const quark_dictionary *p_self, const quark_array *p_keys) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Array *keys = (const Array *)p_keys;
	return self->has_all(*keys);
}

void QAPI quark_dictionary_erase(quark_dictionary *p_self, const quark_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	self->erase(*key);
}

quark_int QAPI quark_dictionary_hash(const quark_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->hash();
}

quark_array QAPI quark_dictionary_keys(const quark_dictionary *p_self) {
	quark_array dest;
	const Dictionary *self = (const Dictionary *)p_self;
	memnew_placement(&dest, Array(self->keys()));
	return dest;
}

quark_array QAPI quark_dictionary_values(const quark_dictionary *p_self) {
	quark_array dest;
	const Dictionary *self = (const Dictionary *)p_self;
	memnew_placement(&dest, Array(self->values()));
	return dest;
}

quark_variant QAPI quark_dictionary_get(const quark_dictionary *p_self, const quark_variant *p_key) {
	quark_variant raw_dest;
	Variant *dest = (Variant *)&raw_dest;
	const Dictionary *self = (const Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	memnew_placement(dest, Variant(self->operator[](*key)));
	return raw_dest;
}

void QAPI quark_dictionary_set(quark_dictionary *p_self, const quark_variant *p_key, const quark_variant *p_value) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	const Variant *value = (const Variant *)p_value;
	self->operator[](*key) = *value;
}

quark_variant QAPI *quark_dictionary_operator_index(quark_dictionary *p_self, const quark_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return (quark_variant *)&self->operator[](*key);
}

const quark_variant QAPI *quark_dictionary_operator_index_const(const quark_dictionary *p_self, const quark_variant *p_key) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return (const quark_variant *)&self->operator[](*key);
}

quark_variant QAPI *quark_dictionary_next(const quark_dictionary *p_self, const quark_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return (quark_variant *)self->next(key);
}

quark_bool QAPI quark_dictionary_operator_equal(const quark_dictionary *p_self, const quark_dictionary *p_b) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Dictionary *b = (const Dictionary *)p_b;
	return *self == *b;
}

#ifdef __cplusplus
}
#endif
