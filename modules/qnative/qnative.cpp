/*************************************************************************/
/*  qnative.cpp                                                         */
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

#include "qnative.h"

#include "global_constants.h"
#include "os/file_access.h"
#include "os/os.h"
#include "project_settings.h"

#include "scene/main/scene_tree.h"

static const String init_symbol = "qnative_init";
static const String terminate_symbol = "qnative_terminate";
static const String default_symbol_prefix = "quark_";
static const bool default_singleton = false;
static const bool default_load_once = true;
static const bool default_reloadable = true;

// Defined in qnative_api_struct.gen.cpp
extern const quark__core_api_struct api_struct;

Map<String, Vector<Ref<QNative> > > *QNativeLibrary::loaded_libraries = NULL;

QNativeLibrary::QNativeLibrary() {
	config_file.instance();

	symbol_prefix = default_symbol_prefix;
	load_once = default_load_once;
	singleton = default_singleton;
	reloadable = default_reloadable;

	if (QNativeLibrary::loaded_libraries == NULL) {
		QNativeLibrary::loaded_libraries = memnew((Map<String, Vector<Ref<QNative> > >));
	}
}

QNativeLibrary::~QNativeLibrary() {
}

void QNativeLibrary::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_config_file"), &QNativeLibrary::get_config_file);

	ClassDB::bind_method(D_METHOD("get_current_library_path"), &QNativeLibrary::get_current_library_path);
	ClassDB::bind_method(D_METHOD("get_current_dependencies"), &QNativeLibrary::get_current_dependencies);

	ClassDB::bind_method(D_METHOD("should_load_once"), &QNativeLibrary::should_load_once);
	ClassDB::bind_method(D_METHOD("is_singleton"), &QNativeLibrary::is_singleton);
	ClassDB::bind_method(D_METHOD("get_symbol_prefix"), &QNativeLibrary::get_symbol_prefix);
	ClassDB::bind_method(D_METHOD("is_reloadable"), &QNativeLibrary::is_reloadable);

	ClassDB::bind_method(D_METHOD("set_load_once", "load_once"), &QNativeLibrary::set_load_once);
	ClassDB::bind_method(D_METHOD("set_singleton", "singleton"), &QNativeLibrary::set_singleton);
	ClassDB::bind_method(D_METHOD("set_symbol_prefix", "symbol_prefix"), &QNativeLibrary::set_symbol_prefix);
	ClassDB::bind_method(D_METHOD("set_reloadable", "reloadable"), &QNativeLibrary::set_reloadable);

	ADD_PROPERTYNZ(PropertyInfo(Variant::BOOL, "load_once"), "set_load_once", "should_load_once");
	ADD_PROPERTYNZ(PropertyInfo(Variant::BOOL, "singleton"), "set_singleton", "is_singleton");
	ADD_PROPERTYNZ(PropertyInfo(Variant::STRING, "symbol_prefix"), "set_symbol_prefix", "get_symbol_prefix");
	ADD_PROPERTYNZ(PropertyInfo(Variant::BOOL, "reloadable"), "set_reloadable", "is_reloadable");
}

QNative::QNative() {
	native_handle = NULL;
	initialized = false;
}

QNative::~QNative() {
}

void QNative::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_library", "library"), &QNative::set_library);
	ClassDB::bind_method(D_METHOD("get_library"), &QNative::get_library);

	ClassDB::bind_method(D_METHOD("initialize"), &QNative::initialize);
	ClassDB::bind_method(D_METHOD("terminate"), &QNative::terminate);

	ClassDB::bind_method(D_METHOD("call_native", "calling_type", "procedure_name", "arguments"), &QNative::call_native);

	ADD_PROPERTYNZ(PropertyInfo(Variant::OBJECT, "library", PROPERTY_HINT_RESOURCE_TYPE, "QNativeLibrary"), "set_library", "get_library");
}

void QNative::set_library(Ref<QNativeLibrary> p_library) {
	ERR_EXPLAIN("Tried to change library of QNative when it is already set");
	ERR_FAIL_COND(library.is_valid());
	library = p_library;
}

Ref<QNativeLibrary> QNative::get_library() {
	return library;
}

extern "C" void _qnative_report_version_mismatch(const quark_object *p_library, const char *p_ext, quark__api_version p_want, quark__api_version p_have);
extern "C" void _qnative_report_loading_error(const quark_object *p_library, const char *p_what);

bool QNative::initialize() {
	if (library.is_null()) {
		ERR_PRINT("No library set, can't initialize QNative object");
		return false;
	}

	String lib_path = library->get_current_library_path();
	if (lib_path.empty()) {
		ERR_PRINT("No library set for this platform");
		return false;
	}
#ifdef IPHONE_ENABLED
	// on iOS we use static linking
	String path = "";
#elif defined(ANDROID_ENABLED)
	// On Android dynamic libraries are located separately from resource assets,
	// we should pass library name to dlopen(). The library name is flattened
	// during export.
	String path = lib_path.get_file();
#elif defined(UWP_ENABLED)
	// On UWP we use a relative path from the app
	String path = lib_path.replace("res://", "");
#else
	String path = ProjectSettings::get_singleton()->globalize_path(lib_path);
#endif

	if (library->should_load_once()) {
		if (QNativeLibrary::loaded_libraries->has(lib_path)) {
			// already loaded. Don't load again.
			// copy some of the stuff instead
			this->native_handle = (*QNativeLibrary::loaded_libraries)[lib_path][0]->native_handle;
			initialized = true;
			return true;
		}
	}

	Error err = OS::get_singleton()->open_dynamic_library(path, native_handle, true);
	if (err != OK) {
		return false;
	}

	void *library_init;

	// we cheat here a little bit. you saw nothing
	initialized = true;

	err = get_symbol(library->get_symbol_prefix() + init_symbol, library_init, false);

	initialized = false;

	if (err || !library_init) {
		OS::get_singleton()->close_dynamic_library(native_handle);
		native_handle = NULL;
		ERR_PRINT("Failed to obtain quark__init symbol");
		return false;
	}

	quark__init_fn library_init_fpointer;
	library_init_fpointer = (quark__init_fn)library_init;

	static uint64_t core_api_hash = 0;
	static uint64_t editor_api_hash = 0;
	static uint64_t no_api_hash = 0;

	if (!(core_api_hash || editor_api_hash || no_api_hash)) {
		core_api_hash = ClassDB::get_api_hash(ClassDB::API_CORE);
		editor_api_hash = ClassDB::get_api_hash(ClassDB::API_EDITOR);
		no_api_hash = ClassDB::get_api_hash(ClassDB::API_NONE);
	}

	quark__init_options options;

	options.api_struct = &api_struct;
	options.in_editor = Engine::get_singleton()->is_editor_hint();
	options.core_api_hash = core_api_hash;
	options.editor_api_hash = editor_api_hash;
	options.no_api_hash = no_api_hash;
	options.report_version_mismatch = &_qnative_report_version_mismatch;
	options.report_loading_error = &_qnative_report_loading_error;
	options.gd_native_library = (quark_object *)(get_library().ptr());
	options.active_library_path = (quark_string *)&path;

	library_init_fpointer(&options);

	initialized = true;

	if (library->should_load_once() && !QNativeLibrary::loaded_libraries->has(lib_path)) {
		Vector<Ref<QNative> > qnatives;
		qnatives.resize(1);
		qnatives[0] = Ref<QNative>(this);
		QNativeLibrary::loaded_libraries->insert(lib_path, qnatives);
	}

	return true;
}

bool QNative::terminate() {

	if (!initialized) {
		ERR_PRINT("No valid library handle, can't terminate QNative object");
		return false;
	}

	if (library->should_load_once()) {
		Vector<Ref<QNative> > *qnatives = &(*QNativeLibrary::loaded_libraries)[library->get_current_library_path()];
		if (qnatives->size() > 1) {
			// there are other QNative's still using this library, so we actually don't terminte
			qnatives->erase(Ref<QNative>(this));
			initialized = false;
			return true;
		} else if (qnatives->size() == 1) {
			// we're the last one, terminate!
			qnatives->clear();
			// wew this looks scary, but all it does is remove the entry completely
			QNativeLibrary::loaded_libraries->erase(QNativeLibrary::loaded_libraries->find(library->get_current_library_path()));
		}
	}

	void *library_terminate;
	Error error = get_symbol(library->get_symbol_prefix() + terminate_symbol, library_terminate);
	if (error || !library_terminate) {
		OS::get_singleton()->close_dynamic_library(native_handle);
		native_handle = NULL;
		return true;
	}

	quark__terminate_fn library_terminate_pointer;
	library_terminate_pointer = (quark__terminate_fn)library_terminate;

	quark__terminate_options options;
	options.in_editor = Engine::get_singleton()->is_editor_hint();

	library_terminate_pointer(&options);

	initialized = false;

	// QNativeScriptLanguage::get_singleton()->initialized_libraries.erase(p_native_lib->path);

	OS::get_singleton()->close_dynamic_library(native_handle);
	native_handle = NULL;

	return true;
}

bool QNative::is_initialized() {
	return initialized;
}

void QNativeCallRegistry::register_native_call_type(StringName p_call_type, native_call_cb p_callback) {
	native_calls.insert(p_call_type, p_callback);
}

Vector<StringName> QNativeCallRegistry::get_native_call_types() {
	Vector<StringName> call_types;
	call_types.resize(native_calls.size());

	size_t idx = 0;
	for (Map<StringName, native_call_cb>::Element *E = native_calls.front(); E; E = E->next(), idx++) {
		call_types[idx] = E->key();
	}

	return call_types;
}

Variant QNative::call_native(StringName p_native_call_type, StringName p_procedure_name, Array p_arguments) {

	Map<StringName, native_call_cb>::Element *E = QNativeCallRegistry::singleton->native_calls.find(p_native_call_type);
	if (!E) {
		ERR_PRINT((String("No handler for native call type \"" + p_native_call_type) + "\" found").utf8().get_data());
		return Variant();
	}

	void *procedure_handle;

	Error err = OS::get_singleton()->get_dynamic_library_symbol_handle(
			native_handle,
			p_procedure_name,
			procedure_handle);

	if (err != OK || procedure_handle == NULL) {
		return Variant();
	}

	quark_variant result = E->get()(procedure_handle, (quark_array *)&p_arguments);

	return *(Variant *)&result;
}

Error QNative::get_symbol(StringName p_procedure_name, void *&r_handle, bool p_optional) {

	if (!initialized) {
		ERR_PRINT("No valid library handle, can't get symbol from QNative object");
		return ERR_CANT_OPEN;
	}

	Error result = OS::get_singleton()->get_dynamic_library_symbol_handle(
			native_handle,
			p_procedure_name,
			r_handle,
			p_optional);

	return result;
}

RES QNativeLibraryResourceLoader::load(const String &p_path, const String &p_original_path, Error *r_error) {
	Ref<QNativeLibrary> lib;
	lib.instance();

	Ref<ConfigFile> config = lib->get_config_file();

	Error err = config->load(p_path);

	if (r_error) {
		*r_error = err;
	}

	lib->set_singleton(config->get_value("general", "singleton", default_singleton));
	lib->set_load_once(config->get_value("general", "load_once", default_load_once));
	lib->set_symbol_prefix(config->get_value("general", "symbol_prefix", default_symbol_prefix));
	lib->set_reloadable(config->get_value("general", "reloadable", default_reloadable));

	String entry_lib_path;
	{

		List<String> entry_keys;
		config->get_section_keys("entry", &entry_keys);

		for (List<String>::Element *E = entry_keys.front(); E; E = E->next()) {
			String key = E->get();

			Vector<String> tags = key.split(".");

			bool skip = false;
			for (int i = 0; i < tags.size(); i++) {
				bool has_feature = OS::get_singleton()->has_feature(tags[i]);

				if (!has_feature) {
					skip = true;
					break;
				}
			}

			if (skip) {
				continue;
			}

			entry_lib_path = config->get_value("entry", key);
			break;
		}
	}

	Vector<String> dependency_paths;
	{

		List<String> dependency_keys;
		config->get_section_keys("dependencies", &dependency_keys);

		for (List<String>::Element *E = dependency_keys.front(); E; E = E->next()) {
			String key = E->get();

			Vector<String> tags = key.split(".");

			bool skip = false;
			for (int i = 0; i < tags.size(); i++) {
				bool has_feature = OS::get_singleton()->has_feature(tags[i]);

				if (!has_feature) {
					skip = true;
					break;
				}
			}

			if (skip) {
				continue;
			}

			dependency_paths = config->get_value("dependencies", key);
			break;
		}
	}

	lib->current_library_path = entry_lib_path;
	lib->current_dependencies = dependency_paths;

	return lib;
}

void QNativeLibraryResourceLoader::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("qnslib");
}

bool QNativeLibraryResourceLoader::handles_type(const String &p_type) const {
	return p_type == "QNativeLibrary";
}

String QNativeLibraryResourceLoader::get_resource_type(const String &p_path) const {
	String el = p_path.get_extension().to_lower();
	if (el == "qnslib")
		return "QNativeLibrary";
	return "";
}

Error QNativeLibraryResourceSaver::save(const String &p_path, const RES &p_resource, uint32_t p_flags) {

	Ref<QNativeLibrary> lib = p_resource;

	if (lib.is_null()) {
		return ERR_INVALID_DATA;
	}

	Ref<ConfigFile> config = lib->get_config_file();

	config->set_value("general", "singleton", lib->is_singleton());
	config->set_value("general", "load_once", lib->should_load_once());
	config->set_value("general", "symbol_prefix", lib->get_symbol_prefix());
	config->set_value("general", "reloadable", lib->is_reloadable());

	return config->save(p_path);
}

bool QNativeLibraryResourceSaver::recognize(const RES &p_resource) const {
	return Object::cast_to<QNativeLibrary>(*p_resource) != NULL;
}

void QNativeLibraryResourceSaver::get_recognized_extensions(const RES &p_resource, List<String> *p_extensions) const {
	if (Object::cast_to<QNativeLibrary>(*p_resource) != NULL) {
		p_extensions->push_back("qnslib");
	}
}
