/*************************************************************************/
/*  quark_api.h                                                          */
/*************************************************************************/
/*                       This file is part of:                           */
/*                          QUARK TOOLKIT                                */
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

#ifndef QUARK_API_H
#define QUARK_API_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
	#define CALLINGCONV
	#define QAPI CALLINGCONV
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE
		#define CALLINGCONV __attribute__((visibility("default")))
		#define QAPI CALLINGCONV
	#elif TARGET_OS_MAC
		#define CALLINGCONV __attribute__((sysv_abi))
		#define QAPI CALLINGCONV
	#endif
#else
	#define CALLINGCONV __attribute__((sysv_abi))
	#define QAPI CALLINGCONV
#endif

// This is for libraries *using* the header.
#ifdef _WIN32
#define QAPI_EXPORT __declspec(dllexport)
#else
#define QAPI_EXPORT
#endif

#include <stdint.h>

#define QUARK_API_VERSION 1

uint32_t QAPI quark_api_init(void(*notify_handler)(char*));
char* QAPI quark_api_call(uint32_t user_id, char* message);

#ifdef __cplusplus
}
#endif

#endif // QUARK_API_H
