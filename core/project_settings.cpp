/*************************************************************************/
/*  project_settings.cpp                                                 */
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

#include "project_settings.h"

#include "bind/core_bind.h"
#include "core_string_names.h"
#include "io/marshalls.h"
#include "os/dir_access.h"
#include "os/keyboard.h"
#include "os/os.h"
#include "variant_parser.h"
#include <zlib.h>

#define FORMAT_VERSION 3

ProjectSettings *ProjectSettings::singleton = NULL;

ProjectSettings *ProjectSettings::get_singleton() {

	return singleton;
}

String ProjectSettings::get_resource_path() const {

	return resource_path;
};

String ProjectSettings::localize_path(const String &p_path) const {

	if (resource_path == "")
		return p_path; //not initialied yet

	if (p_path.begins_with("res://") || p_path.begins_with("user://") ||
			(p_path.is_abs_path() && !p_path.begins_with(resource_path)))
		return p_path.simplify_path();

	DirAccess *dir = DirAccess::create(DirAccess::ACCESS_FILESYSTEM);

	String path = p_path.replace("\\", "/").simplify_path();

	if (dir->change_dir(path) == OK) {

		String cwd = dir->get_current_dir();
		cwd = cwd.replace("\\", "/");

		memdelete(dir);

		if (!cwd.begins_with(resource_path)) {
			return p_path;
		};

		return cwd.replace_first(resource_path, "res:/");
	} else {

		memdelete(dir);

		int sep = path.find_last("/");
		if (sep == -1) {
			return "res://" + path;
		};

		String parent = path.substr(0, sep);

		String plocal = localize_path(parent);
		if (plocal == "") {
			return "";
		};
		return plocal + path.substr(sep, path.size() - sep);
	};
}

void ProjectSettings::set_initial_value(const String &p_name, const Variant &p_value) {

	ERR_FAIL_COND(!props.has(p_name));
	props[p_name].initial = p_value;
}

String ProjectSettings::globalize_path(const String &p_path) const {

	if (p_path.begins_with("res://")) {

		if (resource_path != "") {

			return p_path.replace("res:/", resource_path);
		};
		return p_path.replace("res://", "");
	} else if (p_path.begins_with("user://")) {

		String data_dir = OS::get_singleton()->get_user_data_dir();
		if (data_dir != "") {

			return p_path.replace("user:/", data_dir);
		};
		return p_path.replace("user://", "");
	}

	return p_path;
}

bool ProjectSettings::_set(const StringName &p_name, const Variant &p_value) {

	_THREAD_SAFE_METHOD_

	if (p_value.get_type() == Variant::NIL)
		props.erase(p_name);
	else {

		if (p_name == CoreStringNames::get_singleton()->_custom_features) {
			Vector<String> custom_feature_array = p_value;
			for (int i = 0; i < custom_feature_array.size(); i++) {

				custom_features.insert(custom_feature_array[i]);
			}
			return true;
		}

		if (!disable_feature_overrides) {
			int dot = p_name.operator String().find(".");
			if (dot != -1) {
				Vector<String> s = p_name.operator String().split(".");

				bool override_valid = false;
				for (int i = 1; i < s.size(); i++) {
					String feature = s[i].strip_edges();
					if (OS::get_singleton()->has_feature(feature) || custom_features.has(feature)) {
						override_valid = true;
						break;
					}
				}

				if (override_valid) {

					feature_overrides[s[0]] = p_name;
				}
			}
		}

		if (props.has(p_name)) {
			if (!props[p_name].overridden)
				props[p_name].variant = p_value;

		} else {
			props[p_name] = VariantContainer(p_value, last_order++);
		}
	}

	return true;
}
bool ProjectSettings::_get(const StringName &p_name, Variant &r_ret) const {

	_THREAD_SAFE_METHOD_

	StringName name = p_name;
	if (!disable_feature_overrides && feature_overrides.has(name)) {
		name = feature_overrides[name];
	}
	if (!props.has(name)) {
		print_line("WARNING: not found: " + String(name));
		return false;
	}
	r_ret = props[name].variant;
	return true;
}

struct _VCSort {

	String name;
	Variant::Type type;
	int order;
	int flags;

	bool operator<(const _VCSort &p_vcs) const { return order == p_vcs.order ? name < p_vcs.name : order < p_vcs.order; }
};

void ProjectSettings::_get_property_list(List<PropertyInfo> *p_list) const {

	_THREAD_SAFE_METHOD_

	Set<_VCSort> vclist;

	for (Map<StringName, VariantContainer>::Element *E = props.front(); E; E = E->next()) {

		const VariantContainer *v = &E->get();

		if (v->hide_from_editor)
			continue;

		_VCSort vc;
		vc.name = E->key();
		vc.order = v->order;
		vc.type = v->variant.get_type();
		if (vc.name.begins_with("input/") || vc.name.begins_with("import/") || vc.name.begins_with("export/") || vc.name.begins_with("/remap") || vc.name.begins_with("/locale") || vc.name.begins_with("/autoload"))
			vc.flags = PROPERTY_USAGE_STORAGE;
		else
			vc.flags = PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_STORAGE;

		vclist.insert(vc);
	}

	for (Set<_VCSort>::Element *E = vclist.front(); E; E = E->next()) {

		String prop_info_name = E->get().name;
		int dot = prop_info_name.find(".");
		if (dot != -1)
			prop_info_name = prop_info_name.substr(0, dot);

		if (custom_prop_info.has(prop_info_name)) {
			PropertyInfo pi = custom_prop_info[prop_info_name];
			pi.name = E->get().name;
			pi.usage = E->get().flags;
			p_list->push_back(pi);
		} else
			p_list->push_back(PropertyInfo(E->get().type, E->get().name, PROPERTY_HINT_NONE, "", E->get().flags));
	}
}

Error ProjectSettings::setup() {
	// TODO: Reimplement with passable string.

	return OK;
}

bool ProjectSettings::has_setting(String p_var) const {

	_THREAD_SAFE_METHOD_

	return props.has(p_var);
}

void ProjectSettings::set_registering_order(bool p_enable) {

	registering_order = p_enable;
}

int ProjectSettings::get_order(const String &p_name) const {

	ERR_FAIL_COND_V(!props.has(p_name), -1);
	return props[p_name].order;
}

void ProjectSettings::set_order(const String &p_name, int p_order) {

	ERR_FAIL_COND(!props.has(p_name));
	props[p_name].order = p_order;
}

void ProjectSettings::set_builtin_order(const String &p_name) {

	ERR_FAIL_COND(!props.has(p_name));
	if (props[p_name].order >= NO_BUILTIN_ORDER_BASE) {
		props[p_name].order = last_builtin_order++;
	}
}

void ProjectSettings::clear(const String &p_name) {

	ERR_FAIL_COND(!props.has(p_name));
	props.erase(p_name);
}

Variant _GLOBAL_DEF(const String &p_var, const Variant &p_default) {

	Variant ret;
	if (ProjectSettings::get_singleton()->has_setting(p_var)) {
		ret = ProjectSettings::get_singleton()->get(p_var);
	} else {
		ProjectSettings::get_singleton()->set(p_var, p_default);
		ret = p_default;
	}
	ProjectSettings::get_singleton()->set_initial_value(p_var, p_default);
	ProjectSettings::get_singleton()->set_builtin_order(p_var);
	return ret;
}

Vector<String> ProjectSettings::get_optimizer_presets() const {

	List<PropertyInfo> pi;
	ProjectSettings::get_singleton()->get_property_list(&pi);
	Vector<String> names;

	for (List<PropertyInfo>::Element *E = pi.front(); E; E = E->next()) {

		if (!E->get().name.begins_with("optimizer_presets/"))
			continue;
		names.push_back(E->get().name.get_slicec('/', 1));
	}

	names.sort();

	return names;
}

void ProjectSettings::_add_property_info_bind(const Dictionary &p_info) {

	ERR_FAIL_COND(!p_info.has("name"));
	ERR_FAIL_COND(!p_info.has("type"));

	PropertyInfo pinfo;
	pinfo.name = p_info["name"];
	ERR_FAIL_COND(!props.has(pinfo.name));
	pinfo.type = Variant::Type(p_info["type"].operator int());
	ERR_FAIL_INDEX(pinfo.type, Variant::VARIANT_MAX);

	if (p_info.has("hint"))
		pinfo.hint = PropertyHint(p_info["hint"].operator int());
	if (p_info.has("hint_string"))
		pinfo.hint_string = p_info["hint_string"];

	set_custom_property_info(pinfo.name, pinfo);
}

void ProjectSettings::set_custom_property_info(const String &p_prop, const PropertyInfo &p_info) {

	ERR_FAIL_COND(!props.has(p_prop));
	custom_prop_info[p_prop] = p_info;
	custom_prop_info[p_prop].name = p_prop;
}

void ProjectSettings::set_disable_feature_overrides(bool p_disable) {

	disable_feature_overrides = p_disable;
}

bool ProjectSettings::is_using_datapack() const {

	return using_datapack;
}

bool ProjectSettings::property_can_revert(const String &p_name) {

	if (!props.has(p_name))
		return false;

	return props[p_name].initial != props[p_name].variant;
}

Variant ProjectSettings::property_get_revert(const String &p_name) {

	if (!props.has(p_name))
		return Variant();

	return props[p_name].initial;
}

void ProjectSettings::set_setting(const String &p_setting, const Variant &p_value) {
	set(p_setting, p_value);
}

Variant ProjectSettings::get_setting(const String &p_setting) const {
	return get(p_setting);
}

void ProjectSettings::_bind_methods() {

	ClassDB::bind_method(D_METHOD("has_setting", "name"), &ProjectSettings::has_setting);
	ClassDB::bind_method(D_METHOD("set_setting", "name", "value"), &ProjectSettings::set_setting);
	ClassDB::bind_method(D_METHOD("get_setting", "name"), &ProjectSettings::get_setting);
	ClassDB::bind_method(D_METHOD("set_order", "name", "position"), &ProjectSettings::set_order);
	ClassDB::bind_method(D_METHOD("get_order", "name"), &ProjectSettings::get_order);
	ClassDB::bind_method(D_METHOD("set_initial_value", "name", "value"), &ProjectSettings::set_initial_value);
	ClassDB::bind_method(D_METHOD("add_property_info", "hint"), &ProjectSettings::_add_property_info_bind);
	ClassDB::bind_method(D_METHOD("clear", "name"), &ProjectSettings::clear);
	ClassDB::bind_method(D_METHOD("localize_path", "path"), &ProjectSettings::localize_path);
	ClassDB::bind_method(D_METHOD("globalize_path", "path"), &ProjectSettings::globalize_path);
	ClassDB::bind_method(D_METHOD("property_can_revert", "name"), &ProjectSettings::property_can_revert);
	ClassDB::bind_method(D_METHOD("property_get_revert", "name"), &ProjectSettings::property_get_revert);
}

ProjectSettings::ProjectSettings() {

	singleton = this;
	last_order = NO_BUILTIN_ORDER_BASE;
	last_builtin_order = 0;
	disable_feature_overrides = false;
	registering_order = true;

	Array va;
	Ref<InputEventKey> key;
	Ref<InputEventJoypadButton> joyb;

	GLOBAL_DEF("application/config/name", "");
	GLOBAL_DEF("application/run/main_scene", "");
	custom_prop_info["application/run/main_scene"] = PropertyInfo(Variant::STRING, "application/run/main_scene", PROPERTY_HINT_FILE, "tscn,scn,res");
	GLOBAL_DEF("application/run/disable_stdout", false);
	GLOBAL_DEF("application/run/disable_stderr", false);
	GLOBAL_DEF("application/config/use_custom_user_dir", false);
	GLOBAL_DEF("application/config/custom_user_dir_name", "");

	key.instance();
	key->set_scancode(KEY_ENTER);
	va.push_back(key);
	key.instance();
	key->set_scancode(KEY_KP_ENTER);
	va.push_back(key);
	key.instance();
	key->set_scancode(KEY_SPACE);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_BUTTON_0);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_accept", va);
	input_presets.push_back("input/ui_accept");

	va = Array();
	key.instance();
	key->set_scancode(KEY_SPACE);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_BUTTON_3);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_select", va);
	input_presets.push_back("input/ui_select");

	va = Array();
	key.instance();
	key->set_scancode(KEY_ESCAPE);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_BUTTON_1);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_cancel", va);
	input_presets.push_back("input/ui_cancel");

	va = Array();
	key.instance();
	key->set_scancode(KEY_TAB);
	va.push_back(key);
	GLOBAL_DEF("input/ui_focus_next", va);
	input_presets.push_back("input/ui_focus_next");

	va = Array();
	key.instance();
	key->set_scancode(KEY_TAB);
	key->set_shift(true);
	va.push_back(key);
	GLOBAL_DEF("input/ui_focus_prev", va);
	input_presets.push_back("input/ui_focus_prev");

	va = Array();
	key.instance();
	key->set_scancode(KEY_LEFT);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_DPAD_LEFT);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_left", va);
	input_presets.push_back("input/ui_left");

	va = Array();
	key.instance();
	key->set_scancode(KEY_RIGHT);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_DPAD_RIGHT);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_right", va);
	input_presets.push_back("input/ui_right");

	va = Array();
	key.instance();
	key->set_scancode(KEY_UP);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_DPAD_UP);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_up", va);
	input_presets.push_back("input/ui_up");

	va = Array();
	key.instance();
	key->set_scancode(KEY_DOWN);
	va.push_back(key);
	joyb.instance();
	joyb->set_button_index(JOY_DPAD_DOWN);
	va.push_back(joyb);
	GLOBAL_DEF("input/ui_down", va);
	input_presets.push_back("input/ui_down");

	va = Array();
	key.instance();
	key->set_scancode(KEY_PAGEUP);
	va.push_back(key);
	GLOBAL_DEF("input/ui_page_up", va);
	input_presets.push_back("input/ui_page_up");

	va = Array();
	key.instance();
	key->set_scancode(KEY_PAGEDOWN);
	va.push_back(key);
	GLOBAL_DEF("input/ui_page_down", va);
	input_presets.push_back("input/ui_page_down");

	//GLOBAL_DEF("display/window/handheld/orientation", "landscape");

	custom_prop_info["display/window/handheld/orientation"] = PropertyInfo(Variant::STRING, "display/window/handheld/orientation", PROPERTY_HINT_ENUM, "landscape,portrait,reverse_landscape,reverse_portrait,sensor_landscape,sensor_portrait,sensor");
	custom_prop_info["rendering/threads/thread_model"] = PropertyInfo(Variant::INT, "rendering/threads/thread_model", PROPERTY_HINT_ENUM, "Single-Unsafe,Single-Safe,Multi-Threaded");
	custom_prop_info["physics/2d/thread_model"] = PropertyInfo(Variant::INT, "physics/2d/thread_model", PROPERTY_HINT_ENUM, "Single-Unsafe,Single-Safe,Multi-Threaded");
	custom_prop_info["rendering/quality/intended_usage/framebuffer_allocation"] = PropertyInfo(Variant::INT, "rendering/quality/intended_usage/framebuffer_allocation", PROPERTY_HINT_ENUM, "2D,2D Without Sampling,3D,3D Without Effects");
	GLOBAL_DEF("rendering/quality/intended_usage/framebuffer_mode", 2);

	GLOBAL_DEF("debug/settings/profiler/max_functions", 16384);

	using_datapack = false;
}

ProjectSettings::~ProjectSettings() {

	singleton = NULL;
}
