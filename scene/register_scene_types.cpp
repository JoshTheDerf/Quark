/*************************************************************************/
/*  register_scene_types.cpp                                             */
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

#include "register_scene_types.h"

#include "core/class_db.h"
#include "core/os/os.h"
#include "core/project_settings.h"
#include "scene/2d/animated_sprite.h"
#include "scene/2d/back_buffer_copy.h"
#include "scene/2d/camera_2d.h"
#include "scene/2d/canvas_item.h"
#include "scene/2d/canvas_modulate.h"
#include "scene/2d/light_2d.h"
#include "scene/2d/light_occluder_2d.h"
#include "scene/2d/line_2d.h"
#include "scene/2d/parallax_background.h"
#include "scene/2d/parallax_layer.h"
#include "scene/2d/particles_2d.h"
#include "scene/2d/path_2d.h"
#include "scene/2d/polygon_2d.h"
#include "scene/2d/position_2d.h"
#include "scene/2d/remote_transform_2d.h"
#include "scene/2d/sprite.h"
#include "scene/2d/visibility_notifier_2d.h"
#include "scene/2d/y_sort.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree_player.h"
#include "scene/animation/tween.h"
#include "scene/audio/audio_player.h"
#include "scene/gui/box_container.h"
#include "scene/gui/button.h"
#include "scene/gui/center_container.h"
#include "scene/gui/check_box.h"
#include "scene/gui/check_button.h"
#include "scene/gui/color_picker.h"
#include "scene/gui/color_rect.h"
#include "scene/gui/control.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/file_dialog.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/graph_node.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/item_list.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/link_button.h"
#include "scene/gui/margin_container.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/nine_patch_rect.h"
#include "scene/gui/option_button.h"
#include "scene/gui/panel.h"
#include "scene/gui/panel_container.h"
#include "scene/gui/popup_menu.h"
#include "scene/gui/progress_bar.h"
#include "scene/gui/reference_rect.h"
#include "scene/gui/rich_text_label.h"
#include "scene/gui/scroll_bar.h"
#include "scene/gui/scroll_container.h"
#include "scene/gui/separator.h"
#include "scene/gui/slider.h"
#include "scene/gui/spin_box.h"
#include "scene/gui/split_container.h"
#include "scene/gui/tab_container.h"
#include "scene/gui/tabs.h"
#include "scene/gui/text_edit.h"
#include "scene/gui/texture_button.h"
#include "scene/gui/texture_progress.h"
#include "scene/gui/texture_rect.h"
#include "scene/gui/tool_button.h"
#include "scene/gui/tree.h"
#include "scene/gui/video_player.h"
#include "scene/gui/viewport_container.h"
#include "scene/main/canvas_layer.h"
#include "scene/main/instance_placeholder.h"
#include "scene/main/resource_preloader.h"
#include "scene/main/scene_tree.h"
#include "scene/main/timer.h"
#include "scene/main/viewport.h"
#include "scene/resources/audio_stream_sample.h"
#include "scene/resources/bit_mask.h"
#include "scene/resources/color_ramp.h"
#include "scene/resources/default_theme/default_theme.h"
#include "scene/resources/dynamic_font.h"
#include "scene/resources/dynamic_font_stb.h"
#include "scene/resources/material.h"
#include "scene/resources/mesh.h"
#include "scene/resources/mesh_data_tool.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/polygon_path_finder.h"
#include "scene/resources/primitive_meshes.h"
#include "scene/resources/scene_format_text.h"
#include "scene/resources/shader_graph.h"
#include "scene/resources/sky_box.h"
#include "scene/resources/surface_tool.h"
#include "scene/resources/texture.h"
#include "scene/resources/video_stream.h"
#include "scene/resources/world_2d.h"
#include "scene/scene_string_names.h"

static ResourceFormatLoaderTheme *resource_loader_theme = NULL;

static ResourceFormatSaverText *resource_saver_text = NULL;
static ResourceFormatLoaderText *resource_loader_text = NULL;

static ResourceFormatLoaderDynamicFont *resource_loader_dynamic_font = NULL;

static ResourceFormatLoaderStreamTexture *resource_loader_stream_texture = NULL;

static ResourceFormatLoaderBMFont *resource_loader_bmfont = NULL;

static ResourceFormatSaverShader *resource_saver_shader = NULL;
static ResourceFormatLoaderShader *resource_loader_shader = NULL;

void register_scene_types() {

	SceneStringNames::create();

	OS::get_singleton()->yield(); //may take time to init

	Node::init_node_hrcr();

	resource_loader_dynamic_font = memnew(ResourceFormatLoaderDynamicFont);
	ResourceLoader::add_resource_format_loader(resource_loader_dynamic_font);

	resource_loader_stream_texture = memnew(ResourceFormatLoaderStreamTexture);
	ResourceLoader::add_resource_format_loader(resource_loader_stream_texture);

	resource_loader_theme = memnew(ResourceFormatLoaderTheme);
	ResourceLoader::add_resource_format_loader(resource_loader_theme);

	resource_saver_text = memnew(ResourceFormatSaverText);
	ResourceSaver::add_resource_format_saver(resource_saver_text, true);

	resource_loader_text = memnew(ResourceFormatLoaderText);
	ResourceLoader::add_resource_format_loader(resource_loader_text, true);

	resource_saver_shader = memnew(ResourceFormatSaverShader);
	ResourceSaver::add_resource_format_saver(resource_saver_shader, true);

	resource_loader_shader = memnew(ResourceFormatLoaderShader);
	ResourceLoader::add_resource_format_loader(resource_loader_shader, true);

	resource_loader_bmfont = memnew(ResourceFormatLoaderBMFont);
	ResourceLoader::add_resource_format_loader(resource_loader_bmfont, true);

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<Object>();

	ClassDB::register_class<Node>();
	ClassDB::register_virtual_class<InstancePlaceholder>();

	ClassDB::register_class<Viewport>();
	ClassDB::register_class<ViewportTexture>();
	ClassDB::register_class<Timer>();
	ClassDB::register_class<CanvasLayer>();
	ClassDB::register_class<CanvasModulate>();
	ClassDB::register_class<ResourcePreloader>();

	/* REGISTER GUI */
	ClassDB::register_class<ButtonGroup>();
	ClassDB::register_virtual_class<BaseButton>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<ShortCut>();
	ClassDB::register_class<Control>();
	ClassDB::register_class<Button>();
	ClassDB::register_class<Label>();
	ClassDB::register_virtual_class<ScrollBar>();
	ClassDB::register_class<HScrollBar>();
	ClassDB::register_class<VScrollBar>();
	ClassDB::register_class<ProgressBar>();
	ClassDB::register_virtual_class<Slider>();
	ClassDB::register_class<HSlider>();
	ClassDB::register_class<VSlider>();
	ClassDB::register_class<Popup>();
	ClassDB::register_class<PopupPanel>();
	ClassDB::register_class<MenuButton>();
	ClassDB::register_class<CheckBox>();
	ClassDB::register_class<CheckButton>();
	ClassDB::register_class<ToolButton>();
	ClassDB::register_class<LinkButton>();
	ClassDB::register_class<Panel>();
	ClassDB::register_virtual_class<Range>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<TextureRect>();
	ClassDB::register_class<ColorRect>();
	ClassDB::register_class<NinePatchRect>();
	ClassDB::register_class<TabContainer>();
	ClassDB::register_class<Tabs>();
	ClassDB::register_virtual_class<Separator>();
	ClassDB::register_class<HSeparator>();
	ClassDB::register_class<VSeparator>();
	ClassDB::register_class<TextureButton>();
	ClassDB::register_class<Container>();
	ClassDB::register_virtual_class<BoxContainer>();
	ClassDB::register_class<HBoxContainer>();
	ClassDB::register_class<VBoxContainer>();
	ClassDB::register_class<GridContainer>();
	ClassDB::register_class<CenterContainer>();
	ClassDB::register_class<ScrollContainer>();
	ClassDB::register_class<PanelContainer>();
	ClassDB::register_virtual_class<SplitContainer>();
	ClassDB::register_class<HSplitContainer>();
	ClassDB::register_class<VSplitContainer>();
	ClassDB::register_class<GraphNode>();
	ClassDB::register_class<GraphEdit>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<TextureProgress>();
	ClassDB::register_class<ItemList>();

#ifndef ADVANCED_GUI_DISABLED

	ClassDB::register_class<FileDialog>();
	ClassDB::register_class<LineEdit>();
	ClassDB::register_class<PopupMenu>();
	ClassDB::register_class<Tree>();

	ClassDB::register_class<TextEdit>();

	ClassDB::register_virtual_class<TreeItem>();
	ClassDB::register_class<OptionButton>();
	ClassDB::register_class<SpinBox>();
	ClassDB::register_class<ReferenceRect>();
	ClassDB::register_class<ColorPicker>();
	ClassDB::register_class<ColorPickerButton>();
	ClassDB::register_class<RichTextLabel>();
	ClassDB::register_class<PopupDialog>();
	ClassDB::register_class<WindowDialog>();
	ClassDB::register_class<AcceptDialog>();
	ClassDB::register_class<ConfirmationDialog>();
	ClassDB::register_class<VideoPlayer>();
	ClassDB::register_class<MarginContainer>();
	ClassDB::register_class<ViewportContainer>();

	OS::get_singleton()->yield(); //may take time to init

#endif

	ClassDB::register_class<AnimationPlayer>();
	ClassDB::register_class<Tween>();

	OS::get_singleton()->yield(); //may take time to init

	AcceptDialog::set_swap_ok_cancel(GLOBAL_DEF("gui/common/swap_ok_cancel", bool(OS::get_singleton()->get_swap_ok_cancel())));

	ClassDB::register_class<Shader>();
	ClassDB::register_class<ShaderMaterial>();
	ClassDB::register_virtual_class<CanvasItem>();
	ClassDB::register_class<CanvasItemMaterial>();
	SceneTree::add_idle_callback(CanvasItemMaterial::flush_changes);
	CanvasItemMaterial::init_shaders();
	ClassDB::register_class<Node2D>();
	ClassDB::register_class<Particles2D>();
	//ClassDB::register_class<ParticleAttractor2D>();
	ClassDB::register_class<Sprite>();
	//ClassDB::register_type<ViewportSprite>();
	ClassDB::register_class<SpriteFrames>();
	ClassDB::register_class<AnimatedSprite>();
	ClassDB::register_class<Position2D>();
	ClassDB::register_class<Line2D>();
	ClassDB::register_class<VisibilityNotifier2D>();
	ClassDB::register_class<VisibilityEnabler2D>();
	ClassDB::register_class<Polygon2D>();
	ClassDB::register_class<Light2D>();
	ClassDB::register_class<LightOccluder2D>();
	ClassDB::register_class<OccluderPolygon2D>();
	ClassDB::register_class<YSort>();
	ClassDB::register_class<BackBufferCopy>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<Camera2D>();
	ClassDB::register_class<ParallaxBackground>();
	ClassDB::register_class<ParallaxLayer>();
	ClassDB::register_class<RemoteTransform2D>();

	OS::get_singleton()->yield(); //may take time to init

	/* REGISTER RESOURCES */

	ClassDB::register_virtual_class<Shader>();

	ClassDB::register_class<World2D>();
	ClassDB::register_virtual_class<Texture>();
	ClassDB::register_virtual_class<Sky>();
	ClassDB::register_class<PanoramaSky>();
	ClassDB::register_class<ProceduralSky>();
	ClassDB::register_class<StreamTexture>();
	ClassDB::register_class<ImageTexture>();
	ClassDB::register_class<AtlasTexture>();
	ClassDB::register_class<LargeTexture>();
	ClassDB::register_class<CurveTexture>();
	ClassDB::register_class<GradientTexture>();
	ClassDB::register_class<ProxyTexture>();
	ClassDB::register_class<CubeMap>();
	ClassDB::register_class<Animation>();
	ClassDB::register_virtual_class<Font>();
	ClassDB::register_class<BitmapFont>();
	ClassDB::register_class<Curve>();

	ClassDB::register_class<DynamicFontData>();
	ClassDB::register_class<DynamicFont>();

	DynamicFont::initialize_dynamic_fonts();

	ClassDB::register_virtual_class<StyleBox>();
	ClassDB::register_class<StyleBoxEmpty>();
	ClassDB::register_class<StyleBoxTexture>();
	ClassDB::register_class<StyleBoxFlat>();
	ClassDB::register_class<StyleBoxLine>();
	ClassDB::register_class<Theme>();

	ClassDB::register_class<PolygonPathFinder>();
	ClassDB::register_class<BitMap>();
	ClassDB::register_class<Gradient>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<AudioStreamPlayer>();
	ClassDB::register_virtual_class<VideoStream>();
	ClassDB::register_class<AudioStreamSample>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_class<Curve2D>();
	ClassDB::register_class<Path2D>();
	ClassDB::register_class<PathFollow2D>();

	OS::get_singleton()->yield(); //may take time to init

	ClassDB::register_virtual_class<SceneState>();
	ClassDB::register_class<PackedScene>();

	ClassDB::register_class<SceneTree>();
	ClassDB::register_virtual_class<SceneTreeTimer>(); //sorry, you can't create it

	OS::get_singleton()->yield(); //may take time to init

	for (int i = 0; i < 20; i++) {
		GLOBAL_DEF("layer_names/2d_render/layer_" + itos(i + 1), "");
		GLOBAL_DEF("layer_names/2d_physics/layer_" + itos(i + 1), "");
	}

	bool default_theme_hidpi = GLOBAL_DEF("gui/theme/use_hidpi", false);
	ProjectSettings::get_singleton()->set_custom_property_info("gui/theme/use_hidpi", PropertyInfo(Variant::BOOL, "gui/theme/use_hidpi", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_RESTART_IF_CHANGED));
	String theme_path = GLOBAL_DEF("gui/theme/custom", "");
	ProjectSettings::get_singleton()->set_custom_property_info("gui/theme/custom", PropertyInfo(Variant::STRING, "gui/theme/custom", PROPERTY_HINT_FILE, "*.tres,*.res,*.theme", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_RESTART_IF_CHANGED));
	String font_path = GLOBAL_DEF("gui/theme/custom_font", "");
	ProjectSettings::get_singleton()->set_custom_property_info("gui/theme/custom_font", PropertyInfo(Variant::STRING, "gui/theme/custom_font", PROPERTY_HINT_FILE, "*.tres,*.res,*.font", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_RESTART_IF_CHANGED));

	Ref<Font> font;
	if (font_path != String()) {
		font = ResourceLoader::load(font_path);
		if (!font.is_valid()) {
			ERR_PRINTS("Error loading custom font '" + font_path + "'");
		}
	}

	// Always make the default theme to avoid invalid default font/icon/style in the given theme
	make_default_theme(default_theme_hidpi, font);

	if (theme_path != String()) {
		Ref<Theme> theme = ResourceLoader::load(theme_path);
		if (theme.is_valid()) {
			Theme::set_default(theme);
			if (font.is_valid()) {
				Theme::set_default_font(font);
			}
		} else {
			ERR_PRINTS("Error loading custom theme '" + theme_path + "'");
		}
	}
}

void unregister_scene_types() {

	clear_default_theme();

	memdelete(resource_loader_dynamic_font);
	memdelete(resource_loader_stream_texture);
	memdelete(resource_loader_theme);

	DynamicFont::finish_dynamic_fonts();

	if (resource_saver_text) {
		memdelete(resource_saver_text);
	}
	if (resource_loader_text) {
		memdelete(resource_loader_text);
	}

	if (resource_saver_shader) {
		memdelete(resource_saver_shader);
	}
	if (resource_loader_shader) {
		memdelete(resource_loader_shader);
	}
	if (resource_loader_bmfont) {
		memdelete(resource_loader_bmfont);
	}

	CanvasItemMaterial::finish_shaders();
	SceneStringNames::free();
}
