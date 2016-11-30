/*
 * Window.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Window.h"
#include "../Dialogs/Gtk3FileDialog.h"
#include "../Application.h"
#include <cmath>
#include <iostream>

namespace Mediaplayer {

Window::Window(Glib::RefPtr<Gio::Menu> menu) :
		Gtk::ApplicationWindow(), openFileDialog(new Gtk3FileDialog), menuBar {
				menu } {

	set_default_size(800, 600);
	set_title("Mediaplayer");

	controlPanelRevealer.add(controlPanel);
	controlPanelRevealer.set_reveal_child(false);
	controlPanelRevealer.set_valign(Gtk::ALIGN_END);

	menuBarRevealer.add(menuBar);
	menuBarRevealer.set_reveal_child(false);
	menuBarRevealer.set_valign(Gtk::ALIGN_START);

	videoArea.add(container);
	videoArea.set_visible_child(container);

	m_Overlay.add(videoArea);
	m_Overlay.add_overlay(controlPanelRevealer);
	m_Overlay.add_overlay(menuBarRevealer);
	add(m_Overlay);

	add_action("fileopen", sigc::mem_fun(*this, &Window::on_file_open));
	signal_key_release_event().connect(
			sigc::mem_fun(*this, &Window::on_key_release));

	mpvHandler.playback_progress_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_progress_signal));
	mpvHandler.duration_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_duration_signal));
	mpvHandler.end_of_file_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_eof_signal));
	mpvHandler.media_title_changed_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_media_title_signal));

	controlPanel.signal_slider_value_changed().connect(
			sigc::mem_fun(*this, &Window::on_slider_value_changed));
	controlPanel.signal_pause_button_clicked().connect(
			sigc::mem_fun(*this, &Window::on_pause_command));
	controlPanel.signal_start_button_clicked().connect(
			sigc::mem_fun(*this, &Window::on_start_command));

	signal_button_press_event().connect(
			sigc::mem_fun(*this, &Window::on_mpv_container_button_press));
	signal_motion_notify_event().connect(
			sigc::mem_fun(*this, &Window::on_mpv_container_motion_event));
}

void Window::load_file(const std::string &filename) {
	if (!get_realized())
		realize();
	mpvHandler.load(filename);
	//set_title(mpvHandler.get_media_title());
}

void Window::on_file_open() {
	auto result = openFileDialog->ShowDialog(*this);
	if (result == DialogResult::Confirmed) {
		std::string filename = openFileDialog->GetFilename();
		load_file(filename);
	}
}

int64_t Window::get_mpv_container_wid() {
	return container.get_wid();
}

bool Window::on_key_release(GdkEventKey *key) {

	auto keyvalUpper = gdk_keyval_to_upper(key->keyval);

	switch (keyvalUpper) {
	case GDK_KEY_F:
		toggle_fullscreen();
		//set_show_menubar(!isFullscreen);
		//controlPanel.set_visible(!isFullscreen);
		break;
	default:
		mpvHandler.press_key(key->string);
		break;
	}

	return true;
}

void Window::toggle_fullscreen() {
	if (!isFullscreen) {
		fullscreen();
	} else {
		unfullscreen();
	}
	isFullscreen = !isFullscreen;
	controlPanelRevealer.set_reveal_child(!isFullscreen);
	menuBarRevealer.set_reveal_child(!isFullscreen);
	set_cursor_visibility(!isFullscreen);
}

void Window::on_realize() {
	Gtk::Window::on_realize();
	mpvHandler.initialize(container.get_wid());
}

void Window::on_slider_value_changed() {
	if (controlPanel.get_slider_left_mbutton_pressed()) {
		auto currentValue = controlPanel.get_slider_value();
		mpvHandler.seek(floor(currentValue));
	}
}

void Window::on_mpv_progress_signal(double value) {
	controlPanel.set_slider_value(static_cast<int>(value));
}

void Window::on_mpv_duration_signal(int value) {
	controlPanel.set_sensitive(true);
	controlPanel.set_slider_range(0, value);
//	sigc::slot<bool> update_slider_slot = sigc::bind(
//			sigc::mem_fun(*this, &Window::on_slider_update_timeout), 0);
//	update_slider_connection = Glib::signal_timeout().connect(
//			update_slider_slot, 1000);
}

bool Window::on_slider_update_timeout(int) {

	auto current = controlPanel.get_slider_value();
	if (current < controlPanel.get_slider_upper()) {
		controlPanel.set_slider_value(current + 1);
		return true;
	}
	return false;
}

bool Window::on_hide_widgets_timeout(int) {
	controlPanelRevealer.set_reveal_child(false);
	menuBarRevealer.set_reveal_child(false);
	set_cursor_visibility(false);
	return false;
}

bool Window::on_mpv_container_button_press(GdkEventButton *eventButton) {
	if (eventButton->type == GDK_2BUTTON_PRESS) {
		toggle_fullscreen();
	}

	return true;
}

bool Window::on_mpv_container_motion_event(GdkEventMotion *event) {
	controlPanelRevealer.set_reveal_child();
	menuBarRevealer.set_reveal_child();
	set_cursor_visibility(true);

	sigc::slot<bool> hide_widgets_slot = sigc::bind(sigc::mem_fun(*this, &Window::on_hide_widgets_timeout), 0);
	hideWidgetsConnection.disconnect();
	hideWidgetsConnection = Glib::signal_timeout().connect(hide_widgets_slot, 3000);

	return true;
}

void Window::set_cursor_visibility(bool visible) {
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window) {
		if (visible) {
			window->set_cursor();
		} else {
			window->set_cursor(Gdk::Cursor::create(Gdk::CursorType::BLANK_CURSOR));
		}
	}
}

void Window::on_mpv_eof_signal() {
	controlPanel.set_slider_value(0);
}

void Window::on_mpv_media_title_signal(const std::string &new_title) {
	set_title(new_title);
}

static gchar *get_full_keystr(guint keyval, guint state) {
//	/* strlen("Ctrl+Alt+Shift+Meta+")+1 == 21 */
//	const gsize max_modstr_len = 21;
//	gchar modstr[max_modstr_len];
//	gboolean found = FALSE;
//	const gchar *keystr = gdk_keyval_name(keyval);
//	const gchar *keystrmap[] = KEYSTRING_MAP;
//	modstr[0] = '\0';
//
//	if((state&GDK_SHIFT_MASK) != 0)
//	{
//		g_strlcat(modstr, "Shift+", max_modstr_len);
//	}
//
//	if((state&GDK_CONTROL_MASK) != 0)
//	{
//		g_strlcat(modstr, "Ctrl+", max_modstr_len);
//	}
//
//	if((state&GDK_MOD1_MASK) != 0)
//	{
//		g_strlcat(modstr, "Alt+", max_modstr_len);
//	}
//
//	if((state&GDK_META_MASK) != 0 || (state&GDK_SUPER_MASK) != 0)
//	{
//		g_strlcat(modstr, "Meta+", max_modstr_len);
//	}
//
//	/* Translate GDK key name to mpv key name */
//	for(gint i = 0; !found && keystrmap[i]; i += 2)
//	{
//		gint rc = g_ascii_strncasecmp(	keystr,
//						keystrmap[i+1],
//						KEYSTRING_MAX_LEN );
//
//		if(rc == 0)
//		{
//			keystr = keystrmap[i];
//			found = TRUE;
//		}
//	}
//
//	return (strlen(keystr) > 0)?g_strconcat(modstr, keystr, NULL):NULL;
}

} /* namespace Mediaplayer */
