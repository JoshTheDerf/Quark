/*************************************************************************/
/*  quark_pluginscript.h                                                 */
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

#ifndef QUARK_PLUGINSCRIPT_H
#define QUARK_PLUGINSCRIPT_H

#include <qnative/qnative.h>
#include <nativescript/quark_nativescript.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void quark_pluginscript_instance_data;
typedef void quark_pluginscript_script_data;
typedef void quark_pluginscript_language_data;

// --- Instance ---

// TODO: use quark_string_name for faster lookup ?
typedef struct {
	quark_pluginscript_instance_data *(*init)(quark_pluginscript_script_data *p_data, quark_object *p_owner);
	void (*finish)(quark_pluginscript_instance_data *p_data);

	quark_bool (*set_prop)(quark_pluginscript_instance_data *p_data, const quark_string *p_name, const quark_variant *p_value);
	quark_bool (*get_prop)(quark_pluginscript_instance_data *p_data, const quark_string *p_name, quark_variant *r_ret);

	quark_variant (*call_method)(quark_pluginscript_instance_data *p_data,
			const quark_string_name *p_method, const quark_variant **p_args,
			int p_argcount, quark_variant_call_error *r_error);

	void (*notification)(quark_pluginscript_instance_data *p_data, int p_notification);
	// TODO: could this rpc mode stuff be moved to the quark_pluginscript_script_manifest ?
	quark_method_rpc_mode (*get_rpc_mode)(quark_pluginscript_instance_data *p_data, const quark_string *p_method);
	quark_method_rpc_mode (*get_rset_mode)(quark_pluginscript_instance_data *p_data, const quark_string *p_variable);

	//this is used by script languages that keep a reference counter of their own
	//you can make make Ref<> not die when it reaches zero, so deleting the reference
	//depends entirely from the script.
	// Note: You can set those function pointer to NULL if not needed.
	void (*refcount_incremented)(quark_pluginscript_instance_data *p_data);
	bool (*refcount_decremented)(quark_pluginscript_instance_data *p_data); // return true if it can die
} quark_pluginscript_instance_desc;

// --- Script ---

typedef struct {
	quark_pluginscript_script_data *data;
	quark_string_name name;
	quark_bool is_tool;
	quark_string_name base;

	// Member lines format: {<string>: <int>}
	quark_dictionary member_lines;
	// Method info dictionary format
	// {
	//  name: <string>
	//  args: [<dict:property>]
	//  default_args: [<variant>]
	//  return: <dict:property>
	//  flags: <int>
	//  rpc_mode: <int:quark_method_rpc_mode>
	// }
	quark_array methods;
	// Same format than for methods
	quark_array signals;
	// Property info dictionary format
	// {
	//  name: <string>
	//  type: <int:quark_variant_type>
	//  hint: <int:quark_property_hint>
	//  hint_string: <string>
	//  usage: <int:quark_property_usage_flags>
	//  default_value: <variant>
	//  rset_mode: <int:quark_method_rpc_mode>
	// }
	quark_array properties;
} quark_pluginscript_script_manifest;

typedef struct {
	quark_pluginscript_script_manifest (*init)(quark_pluginscript_language_data *p_data, const quark_string *p_path, const quark_string *p_source, quark_error *r_error);
	void (*finish)(quark_pluginscript_script_data *p_data);
	quark_pluginscript_instance_desc instance_desc;
} quark_pluginscript_script_desc;

// --- Language ---

typedef struct {
	quark_string_name signature;
	quark_int call_count;
	quark_int total_time; // In microseconds
	quark_int self_time; // In microseconds
} quark_pluginscript_profiling_data;

typedef struct {
	const char *name;
	const char *type;
	const char *extension;
	const char **recognized_extensions; // NULL terminated array
	quark_pluginscript_language_data *(*init)();
	void (*finish)(quark_pluginscript_language_data *p_data);
	const char **reserved_words; // NULL terminated array
	const char **comment_delimiters; // NULL terminated array
	const char **string_delimiters; // NULL terminated array
	quark_bool has_named_classes;
	quark_bool supports_builtin_mode;

	quark_string (*get_template_source_code)(quark_pluginscript_language_data *p_data, const quark_string *p_class_name, const quark_string *p_base_class_name);
	quark_bool (*validate)(quark_pluginscript_language_data *p_data, const quark_string *p_script, int *r_line_error, int *r_col_error, quark_string *r_test_error, const quark_string *p_path, quark_pool_string_array *r_functions);
	int (*find_function)(quark_pluginscript_language_data *p_data, const quark_string *p_function, const quark_string *p_code); // Can be NULL
	quark_string (*make_function)(quark_pluginscript_language_data *p_data, const quark_string *p_class, const quark_string *p_name, const quark_pool_string_array *p_args);
	quark_error (*complete_code)(quark_pluginscript_language_data *p_data, const quark_string *p_code, const quark_string *p_base_path, quark_object *p_owner, quark_array *r_options, quark_bool *r_force, quark_string *r_call_hint);
	void (*auto_indent_code)(quark_pluginscript_language_data *p_data, quark_string *p_code, int p_from_line, int p_to_line);

	void (*add_global_constant)(quark_pluginscript_language_data *p_data, const quark_string *p_variable, const quark_variant *p_value);
	quark_string (*debug_get_error)(quark_pluginscript_language_data *p_data);
	int (*debug_get_stack_level_count)(quark_pluginscript_language_data *p_data);
	int (*debug_get_stack_level_line)(quark_pluginscript_language_data *p_data, int p_level);
	quark_string (*debug_get_stack_level_function)(quark_pluginscript_language_data *p_data, int p_level);
	quark_string (*debug_get_stack_level_source)(quark_pluginscript_language_data *p_data, int p_level);
	void (*debug_get_stack_level_locals)(quark_pluginscript_language_data *p_data, int p_level, quark_pool_string_array *p_locals, quark_array *p_values, int p_max_subitems, int p_max_depth);
	void (*debug_get_stack_level_members)(quark_pluginscript_language_data *p_data, int p_level, quark_pool_string_array *p_members, quark_array *p_values, int p_max_subitems, int p_max_depth);
	void (*debug_get_globals)(quark_pluginscript_language_data *p_data, quark_pool_string_array *p_locals, quark_array *p_values, int p_max_subitems, int p_max_depth);
	quark_string (*debug_parse_stack_level_expression)(quark_pluginscript_language_data *p_data, int p_level, const quark_string *p_expression, int p_max_subitems, int p_max_depth);

	// TODO: could this stuff be moved to the quark_pluginscript_language_desc ?
	void (*get_public_functions)(quark_pluginscript_language_data *p_data, quark_array *r_functions);
	void (*get_public_constants)(quark_pluginscript_language_data *p_data, quark_dictionary *r_constants);

	void (*profiling_start)(quark_pluginscript_language_data *p_data);
	void (*profiling_stop)(quark_pluginscript_language_data *p_data);
	int (*profiling_get_accumulated_data)(quark_pluginscript_language_data *p_data, quark_pluginscript_profiling_data *r_info, int p_info_max);
	int (*profiling_get_frame_data)(quark_pluginscript_language_data *p_data, quark_pluginscript_profiling_data *r_info, int p_info_max);
	void (*profiling_frame)(quark_pluginscript_language_data *p_data);

	quark_pluginscript_script_desc script_desc;
} quark_pluginscript_language_desc;

void QAPI quark_pluginscript_register_language(const quark_pluginscript_language_desc *language_desc);

#ifdef __cplusplus
}
#endif

#endif // QUARK_PLUGINSCRIPT_H
