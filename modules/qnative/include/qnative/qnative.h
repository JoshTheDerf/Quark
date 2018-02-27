/*************************************************************************/
/*  qnative.h                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           QUARK ENGINE                                */
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

#ifndef QUARK_QNATIVE_H
#define QUARK_QNATIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define GDCALLINGCONV
#define QAPI GDCALLINGCONV
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#define GDCALLINGCONV __attribute__((visibility("default")))
#define QAPI GDCALLINGCONV
#elif TARGET_OS_MAC
#define GDCALLINGCONV __attribute__((sysv_abi))
#define QAPI GDCALLINGCONV
#endif
#else
#define GDCALLINGCONV __attribute__((sysv_abi))
#define QAPI GDCALLINGCONV
#endif

// This is for libraries *using* the header, NOT QUARK EXPOSING STUFF!!
#ifdef _WIN32
#define GDN_EXPORT __declspec(dllexport)
#else
#define GDN_EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

#define QUARK_API_VERSION 1

////// Error

typedef enum {
	QUARK_OK,
	QUARK_FAILED, ///< Generic fail error
	QUARK_ERR_UNAVAILABLE, ///< What is requested is unsupported/unavailable
	QUARK_ERR_UNCONFIGURED, ///< The object being used hasn't been properly set up yet
	QUARK_ERR_UNAUTHORIZED, ///< Missing credentials for requested resource
	QUARK_ERR_PARAMETER_RANGE_ERROR, ///< Parameter given out of range (5)
	QUARK_ERR_OUT_OF_MEMORY, ///< Out of memory
	QUARK_ERR_FILE_NOT_FOUND,
	QUARK_ERR_FILE_BAD_DRIVE,
	QUARK_ERR_FILE_BAD_PATH,
	QUARK_ERR_FILE_NO_PERMISSION, // (10)
	QUARK_ERR_FILE_ALREADY_IN_USE,
	QUARK_ERR_FILE_CANT_OPEN,
	QUARK_ERR_FILE_CANT_WRITE,
	QUARK_ERR_FILE_CANT_READ,
	QUARK_ERR_FILE_UNRECOGNIZED, // (15)
	QUARK_ERR_FILE_CORRUPT,
	QUARK_ERR_FILE_MISSING_DEPENDENCIES,
	QUARK_ERR_FILE_EOF,
	QUARK_ERR_CANT_OPEN, ///< Can't open a resource/socket/file
	QUARK_ERR_CANT_CREATE, // (20)
	QUARK_ERR_QUERY_FAILED,
	QUARK_ERR_ALREADY_IN_USE,
	QUARK_ERR_LOCKED, ///< resource is locked
	QUARK_ERR_TIMEOUT,
	QUARK_ERR_CANT_CONNECT, // (25)
	QUARK_ERR_CANT_RESOLVE,
	QUARK_ERR_CONNECTION_ERROR,
	QUARK_ERR_CANT_ACQUIRE_RESOURCE,
	QUARK_ERR_CANT_FORK,
	QUARK_ERR_INVALID_DATA, ///< Data passed is invalid	(30)
	QUARK_ERR_INVALID_PARAMETER, ///< Parameter passed is invalid
	QUARK_ERR_ALREADY_EXISTS, ///< When adding, item already exists
	QUARK_ERR_DOES_NOT_EXIST, ///< When retrieving/erasing, it item does not exist
	QUARK_ERR_DATABASE_CANT_READ, ///< database is full
	QUARK_ERR_DATABASE_CANT_WRITE, ///< database is full	(35)
	QUARK_ERR_COMPILATION_FAILED,
	QUARK_ERR_METHOD_NOT_FOUND,
	QUARK_ERR_LINK_FAILED,
	QUARK_ERR_SCRIPT_FAILED,
	QUARK_ERR_CYCLIC_LINK, // (40)
	QUARK_ERR_INVALID_DECLARATION,
	QUARK_ERR_DUPLICATE_SYMBOL,
	QUARK_ERR_PARSE_ERROR,
	QUARK_ERR_BUSY,
	QUARK_ERR_SKIP, // (45)
	QUARK_ERR_HELP, ///< user requested help!!
	QUARK_ERR_BUG, ///< a bug in the software certainly happened, due to a double check failing or unexpected behavior.
	QUARK_ERR_PRINTER_ON_FIRE, /// the parallel port printer is engulfed in flames
} quark_error;

////// bool

typedef bool quark_bool;

#define QUARK_TRUE 1
#define QUARK_FALSE 0

/////// int

typedef int quark_int;

/////// real

typedef float quark_real;

/////// Object (forward declared)
typedef void quark_object;

/////// String

#include <qnative/string.h>

/////// String name

#include <qnative/string_name.h>

////// Vector2

#include <qnative/vector2.h>

////// Rect2

#include <qnative/rect2.h>

////// Vector3

#include <qnative/vector3.h>

////// Transform2D

#include <qnative/transform2d.h>

/////// Plane

#include <qnative/plane.h>

/////// Quat

#include <qnative/quat.h>

/////// AABB

#include <qnative/aabb.h>

/////// Basis

#include <qnative/basis.h>

/////// Transform

#include <qnative/transform.h>

/////// Color

#include <qnative/color.h>

/////// NodePath

#include <qnative/node_path.h>

/////// RID

#include <qnative/rid.h>

/////// Dictionary

#include <qnative/dictionary.h>

/////// Array

#include <qnative/array.h>

// single API file for Pool*Array
#include <qnative/pool_arrays.h>

void QAPI quark_object_destroy(quark_object *p_o);

////// Variant

#include <qnative/variant.h>

////// Singleton API

quark_object QAPI *quark_global_get_singleton(char *p_name); // result shouldn't be freed

////// MethodBind API

typedef struct {
	uint8_t _dont_touch_that[1]; // TODO
} quark_method_bind;

quark_method_bind QAPI *quark_method_bind_get_method(const char *p_classname, const char *p_methodname);
void QAPI quark_method_bind_ptrcall(quark_method_bind *p_method_bind, quark_object *p_instance, const void **p_args, void *p_ret);
quark_variant QAPI quark_method_bind_call(quark_method_bind *p_method_bind, quark_object *p_instance, const quark_variant **p_args, const int p_arg_count, quark_variant_call_error *p_call_error);
////// Script API

typedef struct quark__api_version {
	unsigned int major;
	unsigned int minor;
} quark__api_version;

typedef struct quark__api_struct quark__api_struct;

struct quark__api_struct {
	unsigned int type;
	quark__api_version version;
	const quark__api_struct *next;
};

#define QNATIVE_VERSION_COMPATIBLE(want, have) (want.major == have.major && want.minor <= have.minor)

typedef struct {
	quark_bool in_editor;
	uint64_t core_api_hash;
	uint64_t editor_api_hash;
	uint64_t no_api_hash;
	void (*report_version_mismatch)(const quark_object *p_library, const char *p_what, quark__api_version p_want, quark__api_version p_have);
	void (*report_loading_error)(const quark_object *p_library, const char *p_what);
	quark_object *gd_native_library; // pointer to QNativeLibrary that is being initialized
	const struct quark__core_api_struct *api_struct;
	const quark_string *active_library_path;
} quark__init_options;

typedef struct {
	quark_bool in_editor;
} quark__terminate_options;

// Calling convention?
typedef quark_object *(*quark_class_constructor)();

quark_class_constructor QAPI quark_get_class_constructor(const char *p_classname);

quark_dictionary QAPI quark_get_global_constants();

////// QNative procedure types
typedef void (*quark__init_fn)(quark__init_options *);
typedef void (*quark__terminate_fn)(quark__terminate_options *);
typedef quark_variant (*quark__procedure_fn)(quark_array *);

////// System Functions

typedef quark_variant (*native_call_cb)(void *, quark_array *);
void QAPI quark_register_native_call_type(const char *p_call_type, native_call_cb p_callback);

//using these will help Godot track how much memory is in use in debug mode
void QAPI *quark_alloc(int p_bytes);
void QAPI *quark_realloc(void *p_ptr, int p_bytes);
void QAPI quark_free(void *p_ptr);

//print using Godot's error handler list
void QAPI quark_print_error(const char *p_description, const char *p_function, const char *p_file, int p_line);
void QAPI quark_print_warning(const char *p_description, const char *p_function, const char *p_file, int p_line);
void QAPI quark_print(const quark_string *p_message);

#ifdef __cplusplus
}
#endif

#endif // QUARK_C_H
