/*************************************************************************/
/*  register_types.cpp                                                   */
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

#include "register_types.h"
#include "qnative/qnative.h"

#include "qnative.h"

#include "io/resource_loader.h"
#include "io/resource_saver.h"

#include "nativescript/register_types.h"
#include "pluginscript/register_types.h"

#include "core/engine.h"
#include "core/os/os.h"
#include "core/project_settings.h"

static quark_variant cb_standard_varcall(void *p_procedure_handle, quark_array *p_args) {

	quark__procedure_fn proc;
	proc = (quark__procedure_fn)p_procedure_handle;

	return proc(p_args);
}

QNativeCallRegistry *QNativeCallRegistry::singleton;

Vector<Ref<QNative> > singleton_qnatives;

QNativeLibraryResourceLoader *resource_loader_qnslib = NULL;
QNativeLibraryResourceSaver *resource_saver_qnslib = NULL;

void register_qnative_types() {

	ClassDB::register_class<QNativeLibrary>();
	ClassDB::register_class<QNative>();

	resource_loader_qnslib = memnew(QNativeLibraryResourceLoader);
	resource_saver_qnslib = memnew(QNativeLibraryResourceSaver);

	ResourceLoader::add_resource_format_loader(resource_loader_qnslib);
	ResourceSaver::add_resource_format_saver(resource_saver_qnslib);

	QNativeCallRegistry::singleton = memnew(QNativeCallRegistry);

	QNativeCallRegistry::singleton->register_native_call_type("standard_varcall", cb_standard_varcall);

	register_nativescript_types();
	register_pluginscript_types();

	// run singletons

	Array singletons = Array();
	if (ProjectSettings::get_singleton()->has_setting("qnative/singletons")) {
		singletons = ProjectSettings::get_singleton()->get("qnative/singletons");
	}

	singleton_qnatives.resize(singletons.size());

	for (int i = 0; i < singletons.size(); i++) {
		String path = singletons[i];

		Ref<QNativeLibrary> lib = ResourceLoader::load(path);

		singleton_qnatives[i].instance();
		singleton_qnatives[i]->set_library(lib);

		if (!singleton_qnatives[i]->initialize()) {
			// Can't initialize. Don't make a native_call then
			continue;
		}

		void *proc_ptr;
		Error err = singleton_qnatives[i]->get_symbol(
				lib->get_symbol_prefix() + "qnative_singleton",
				proc_ptr);

		if (err != OK) {
			ERR_PRINT((String("No quark__singleton in \"" + singleton_qnatives[i]->get_library()->get_current_library_path()) + "\" found").utf8().get_data());
		} else {
			((void (*)())proc_ptr)();
		}
	}
}

void unregister_qnative_types() {

	for (int i = 0; i < singleton_qnatives.size(); i++) {

		if (singleton_qnatives[i].is_null()) {
			continue;
		}

		if (!singleton_qnatives[i]->is_initialized()) {
			continue;
		}

		singleton_qnatives[i]->terminate();
	}
	singleton_qnatives.clear();

	unregister_pluginscript_types();
	unregister_nativescript_types();

	memdelete(QNativeCallRegistry::singleton);

	memdelete(resource_loader_qnslib);
	memdelete(resource_saver_qnslib);

	// This is for printing out the sizes of the core types

	/*
	print_line(String("array:\t")     + itos(sizeof(Array)));
	print_line(String("basis:\t")     + itos(sizeof(Basis)));
	print_line(String("color:\t")     + itos(sizeof(Color)));
	print_line(String("dict:\t" )     + itos(sizeof(Dictionary)));
	print_line(String("node_path:\t") + itos(sizeof(NodePath)));
	print_line(String("plane:\t")     + itos(sizeof(Plane)));
	print_line(String("poolarray:\t") + itos(sizeof(PoolByteArray)));
	print_line(String("quat:\t")      + itos(sizeof(Quat)));
	print_line(String("rect2:\t")     + itos(sizeof(Rect2)));
	print_line(String("aabb:\t")     + itos(sizeof(AABB)));
	print_line(String("rid:\t")       + itos(sizeof(RID)));
	print_line(String("string:\t")    + itos(sizeof(String)));
	print_line(String("transform:\t") + itos(sizeof(Transform)));
	print_line(String("transfo2D:\t") + itos(sizeof(Transform2D)));
	print_line(String("variant:\t")   + itos(sizeof(Variant)));
	print_line(String("vector2:\t")   + itos(sizeof(Vector2)));
	print_line(String("vector3:\t")   + itos(sizeof(Vector3)));
	*/
}
