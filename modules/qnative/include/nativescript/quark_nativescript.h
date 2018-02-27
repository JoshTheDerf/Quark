/*************************************************************************/
/*  quark_nativescript.h                                                 */
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

#ifndef QUARK_NATIVESCRIPT_H
#define QUARK_NATIVESCRIPT_H

#include <qnative/qnative.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	QUARK_METHOD_RPC_MODE_DISABLED,
	QUARK_METHOD_RPC_MODE_REMOTE,
	QUARK_METHOD_RPC_MODE_SYNC,
	QUARK_METHOD_RPC_MODE_MASTER,
	QUARK_METHOD_RPC_MODE_SLAVE,
} quark_method_rpc_mode;

typedef enum {
	QUARK_PROPERTY_HINT_NONE, ///< no hint provided.
	QUARK_PROPERTY_HINT_RANGE, ///< hint_text = "min,max,step,slider; //slider is optional"
	QUARK_PROPERTY_HINT_EXP_RANGE, ///< hint_text = "min,max,step", exponential edit
	QUARK_PROPERTY_HINT_ENUM, ///< hint_text= "val1,val2,val3,etc"
	QUARK_PROPERTY_HINT_EXP_EASING, /// exponential easing function (Math::ease)
	QUARK_PROPERTY_HINT_LENGTH, ///< hint_text= "length" (as integer)
	QUARK_PROPERTY_HINT_SPRITE_FRAME,
	QUARK_PROPERTY_HINT_KEY_ACCEL, ///< hint_text= "length" (as integer)
	QUARK_PROPERTY_HINT_FLAGS, ///< hint_text= "flag1,flag2,etc" (as bit flags)
	QUARK_PROPERTY_HINT_LAYERS_2D_RENDER,
	QUARK_PROPERTY_HINT_LAYERS_2D_PHYSICS,
	QUARK_PROPERTY_HINT_LAYERS_3D_RENDER,
	QUARK_PROPERTY_HINT_LAYERS_3D_PHYSICS,
	QUARK_PROPERTY_HINT_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	QUARK_PROPERTY_HINT_DIR, ///< a directort path must be passed
	QUARK_PROPERTY_HINT_GLOBAL_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	QUARK_PROPERTY_HINT_GLOBAL_DIR, ///< a directort path must be passed
	QUARK_PROPERTY_HINT_RESOURCE_TYPE, ///< a resource object type
	QUARK_PROPERTY_HINT_MULTILINE_TEXT, ///< used for string properties that can contain multiple lines
	QUARK_PROPERTY_HINT_COLOR_NO_ALPHA, ///< used for ignoring alpha component when editing a color
	QUARK_PROPERTY_HINT_IMAGE_COMPRESS_LOSSY,
	QUARK_PROPERTY_HINT_IMAGE_COMPRESS_LOSSLESS,
	QUARK_PROPERTY_HINT_OBJECT_ID,
	QUARK_PROPERTY_HINT_TYPE_STRING, ///< a type string, the hint is the base type to choose
	QUARK_PROPERTY_HINT_NODE_PATH_TO_EDITED_NODE, ///< so something else can provide this (used in scripts)
	QUARK_PROPERTY_HINT_METHOD_OF_VARIANT_TYPE, ///< a method of a type
	QUARK_PROPERTY_HINT_METHOD_OF_BASE_TYPE, ///< a method of a base type
	QUARK_PROPERTY_HINT_METHOD_OF_INSTANCE, ///< a method of an instance
	QUARK_PROPERTY_HINT_METHOD_OF_SCRIPT, ///< a method of a script & base
	QUARK_PROPERTY_HINT_PROPERTY_OF_VARIANT_TYPE, ///< a property of a type
	QUARK_PROPERTY_HINT_PROPERTY_OF_BASE_TYPE, ///< a property of a base type
	QUARK_PROPERTY_HINT_PROPERTY_OF_INSTANCE, ///< a property of an instance
	QUARK_PROPERTY_HINT_PROPERTY_OF_SCRIPT, ///< a property of a script & base
	QUARK_PROPERTY_HINT_MAX,
} quark_property_hint;

typedef enum {

	QUARK_PROPERTY_USAGE_STORAGE = 1,
	QUARK_PROPERTY_USAGE_EDITOR = 2,
	QUARK_PROPERTY_USAGE_NETWORK = 4,
	QUARK_PROPERTY_USAGE_EDITOR_HELPER = 8,
	QUARK_PROPERTY_USAGE_CHECKABLE = 16, //used for editing global variables
	QUARK_PROPERTY_USAGE_CHECKED = 32, //used for editing global variables
	QUARK_PROPERTY_USAGE_INTERNATIONALIZED = 64, //hint for internationalized strings
	QUARK_PROPERTY_USAGE_GROUP = 128, //used for grouping props in the editor
	QUARK_PROPERTY_USAGE_CATEGORY = 256,
	QUARK_PROPERTY_USAGE_STORE_IF_NONZERO = 512, //only store if nonzero
	QUARK_PROPERTY_USAGE_STORE_IF_NONONE = 1024, //only store if false
	QUARK_PROPERTY_USAGE_NO_INSTANCE_STATE = 2048,
	QUARK_PROPERTY_USAGE_RESTART_IF_CHANGED = 4096,
	QUARK_PROPERTY_USAGE_SCRIPT_VARIABLE = 8192,
	QUARK_PROPERTY_USAGE_STORE_IF_NULL = 16384,
	QUARK_PROPERTY_USAGE_ANIMATE_AS_TRIGGER = 32768,
	QUARK_PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED = 65536,

	QUARK_PROPERTY_USAGE_DEFAULT = QUARK_PROPERTY_USAGE_STORAGE | QUARK_PROPERTY_USAGE_EDITOR | QUARK_PROPERTY_USAGE_NETWORK,
	QUARK_PROPERTY_USAGE_DEFAULT_INTL = QUARK_PROPERTY_USAGE_STORAGE | QUARK_PROPERTY_USAGE_EDITOR | QUARK_PROPERTY_USAGE_NETWORK | QUARK_PROPERTY_USAGE_INTERNATIONALIZED,
	QUARK_PROPERTY_USAGE_NOEDITOR = QUARK_PROPERTY_USAGE_STORAGE | QUARK_PROPERTY_USAGE_NETWORK,
} quark_property_usage_flags;

typedef struct {
	quark_method_rpc_mode rset_type;

	quark_int type;
	quark_property_hint hint;
	quark_string hint_string;
	quark_property_usage_flags usage;
	quark_variant default_value;
} quark_property_attributes;

typedef struct {
	// instance pointer, method_data - return user data
	GDCALLINGCONV void *(*create_func)(quark_object *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} quark_instance_create_func;

typedef struct {
	// instance pointer, method data, user data
	GDCALLINGCONV void (*destroy_func)(quark_object *, void *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} quark_instance_destroy_func;

void QAPI quark_register_class(void *p_qnative_handle, const char *p_name, const char *p_base, quark_instance_create_func p_create_func, quark_instance_destroy_func p_destroy_func);

void QAPI quark_register_tool_class(void *p_qnative_handle, const char *p_name, const char *p_base, quark_instance_create_func p_create_func, quark_instance_destroy_func p_destroy_func);

typedef struct {
	quark_method_rpc_mode rpc_type;
} quark_method_attributes;

typedef struct {
	// instance pointer, method data, user data, num args, args - return result as varaint
	GDCALLINGCONV quark_variant (*method)(quark_object *, void *, void *, int, quark_variant **);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} quark_instance_method;

void QAPI quark_register_method(void *p_qnative_handle, const char *p_name, const char *p_function_name, quark_method_attributes p_attr, quark_instance_method p_method);

typedef struct {
	// instance pointer, method data, user data, value
	GDCALLINGCONV void (*set_func)(quark_object *, void *, void *, quark_variant *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} quark_property_set_func;

typedef struct {
	// instance pointer, method data, user data, value
	GDCALLINGCONV quark_variant (*get_func)(quark_object *, void *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} quark_property_get_func;

void QAPI quark_register_property(void *p_qnative_handle, const char *p_name, const char *p_path, quark_property_attributes *p_attr, quark_property_set_func p_set_func, quark_property_get_func p_get_func);

typedef struct {
	quark_string name;
	quark_int type;
	quark_property_hint hint;
	quark_string hint_string;
	quark_property_usage_flags usage;
	quark_variant default_value;
} quark_signal_argument;

typedef struct {
	quark_string name;
	int num_args;
	quark_signal_argument *args;
	int num_default_args;
	quark_variant *default_args;
} quark_signal;

void QAPI quark_register_signal(void *p_qnative_handle, const char *p_name, const quark_signal *p_signal);

void QAPI *quark_get_userdata(quark_object *p_instance);

/*
 *
 *
 * NativeScript 1.1
 *
 *
 */

// method registering with argument names

typedef struct {
	quark_string name;

	quark_variant_type type;
	quark_property_hint hint;
	quark_string hint_string;
} quark_method_arg;

void QAPI quark_set_method_argument_information(void *p_qnative_handle, const char *p_name, const char *p_function_name, int p_num_args, const quark_method_arg *p_args);

// documentation

void QAPI quark_set_class_documentation(void *p_qnative_handle, const char *p_name, quark_string p_documentation);
void QAPI quark_set_method_documentation(void *p_qnative_handle, const char *p_name, const char *p_function_name, quark_string p_documentation);
void QAPI quark_set_property_documentation(void *p_qnative_handle, const char *p_name, const char *p_path, quark_string p_documentation);
void QAPI quark_set_signal_documentation(void *p_qnative_handle, const char *p_name, const char *p_signal_name, quark_string p_documentation);

// type tag API

void QAPI quark_set_type_tag(void *p_qnative_handle, const char *p_name, const void *p_type_tag);
const void QAPI *quark_get_type_tag(const quark_object *p_object);

// instance binding API

typedef struct {
	void *(*alloc_instance_binding_data)(void *, quark_object *);
	void (*free_instance_binding_data)(void *, void *);
	void *data;
	void (*free_func)(void *);
} quark_instance_binding_functions;

int QAPI quark_register_instance_binding_data_functions(quark_instance_binding_functions p_binding_functions);
void QAPI quark_unregister_instance_binding_data_functions(int p_idx);

void QAPI *quark_get_instance_binding_data(int p_idx, quark_object *p_object);

#ifdef __cplusplus
}
#endif

#endif
