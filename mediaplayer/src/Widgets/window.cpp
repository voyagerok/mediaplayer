/*
 * Window.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "window.h"

#include <cmath>
#include <iostream>
#include "../application.h"
#include "../Dialogs/gtk3_file_dialog.h"
#include "../Utils/key_name_translator.h"

namespace Mediaplayer {

Window::Window(Glib::RefPtr<Gio::Menu> menu) :
		Gtk::ApplicationWindow(), openFileDialog(new Gtk3FileDialog), menuBar {
				menu }, popupMenu {menu}, windowLayout{Gtk::ORIENTATION_VERTICAL}
{

	set_default_size(800, 600);
	set_title(default_title);

	controlPanelRevealer.add(controlPanel);
	controlPanelRevealer.set_reveal_child(false);
	controlPanelRevealer.set_valign(Gtk::ALIGN_END);

//	menuBarRevealer.add(menuBar);
//	menuBarRevealer.set_reveal_child(false);
//	menuBarRevealer.set_valign(Gtk::ALIGN_START);

	videoArea.add(container);
	videoArea.set_visible_child(container);

	m_Overlay.add(videoArea);
	m_Overlay.add_overlay(controlPanelRevealer);
	//m_Overlay.add_overlay(menuBarRevealer);

	windowLayout.pack_start(menuBar, false, true, 0);
	windowLayout.pack_start(m_Overlay, true, true, 0);
	add(windowLayout);
	//add(m_Overlay);

	add_action("fileopen", sigc::mem_fun(*this, &Window::on_file_open));

	mpvHandler.signal_playback_progress().connect(
			sigc::mem_fun(*this, &Window::on_mpv_progress_signal));
	mpvHandler.signal_duration().connect(
			sigc::mem_fun(*this, &Window::on_mpv_duration_signal));
	mpvHandler.signal_state_idle().connect(
			sigc::mem_fun(*this, &Window::on_mpv_idle_signal));
	mpvHandler.signal_media_title_changed().connect(
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

bool Window::on_key_release_event(GdkEventKey *key) {

	Gtk::ApplicationWindow::on_key_release_event(key);
	std::string mpv_keyname = KeyNameTranslator::translate_from_gdk_to_mpv(key->keyval, key->state);
	mpvHandler.key_up(mpv_keyname.c_str());
	show_control_widgets();
	return true;
}

bool Window::on_key_press_event(GdkEventKey *key) {
	Gtk::ApplicationWindow::on_key_press_event(key);
	std::string mpv_keyname = KeyNameTranslator::translate_from_gdk_to_mpv(key->keyval, key->state);
	mpvHandler.key_down(mpv_keyname.c_str());
	show_control_widgets();
	return true;
}

void Window::toggle_fullscreen() {
	if (!isFullscreen) {
		fullscreen();
	} else {
		unfullscreen();
	}
	isFullscreen = !isFullscreen;
	hideWidgetsTimer.disconnect();
	controlPanelRevealer.set_reveal_child(!isFullscreen);
	//menuBarRevealer.set_reveal_child(!isFullscreen);
	menuBar.set_visible(!isFullscreen);
	set_cursor_visibility(!isFullscreen);
}

void Window::set_idle_state() {
	set_default_size(800,600);
	set_title(default_title);
	controlPanel.set_slider_value(0);
	if (isFullscreen) toggle_fullscreen();
	controlPanel.set_time_default();
	controlPanel.set_sensitive(false);
}

void Window::on_realize() {
	Gtk::Window::on_realize();
	mpvHandler.initialize(container.get_wid());
}

void Window::on_slider_value_changed() {
	if (controlPanel.get_slider_left_mbutton_pressed()) {
		auto currentValue = controlPanel.get_slider_value();
		mpvHandler.seek(static_cast<int>(currentValue));
	}
}

void Window::on_mpv_progress_signal(double value) {
	auto seconds = static_cast<int>(value);
	controlPanel.set_slider_value(seconds);
	controlPanel.set_current_time(seconds);
}

void Window::on_mpv_duration_signal(int value) {
	controlPanel.set_sensitive(true);
	controlPanel.set_slider_range(0, value);
	controlPanel.set_overall_time(value);
}

void Window::on_mpv_fullscreen_signal() {
	toggle_fullscreen();
}

bool Window::on_hide_widgets_timeout(int) {
	controlPanelRevealer.set_reveal_child(false);
	//menuBarRevealer.set_reveal_child(false);
	set_cursor_visibility(false);
	return false;
}

bool Window::on_mpv_container_button_press(GdkEventButton *eventButton) {
	switch (eventButton->type) {
	case GDK_2BUTTON_PRESS:
		toggle_fullscreen();
		return true;
	case GDK_BUTTON_PRESS:
		if (eventButton->button == 3) {
			if (!popupMenu.get_attach_widget()) {
				popupMenu.attach_to_widget(*this);
			}
			popupMenu.popup(eventButton->button, eventButton->time);
			return true;
		}
		break;
	}

	return false;
}

void Window::show_control_widgets() {
	controlPanelRevealer.set_reveal_child();
	//menuBarRevealer.set_reveal_child();
	set_cursor_visibility(true);

	sigc::slot<bool> hide_widgets_slot = sigc::bind(sigc::mem_fun(*this, &Window::on_hide_widgets_timeout), 0);
	hideWidgetsTimer.disconnect();
	hideWidgetsTimer = Glib::signal_timeout().connect(hide_widgets_slot, 3000);
}

bool Window::on_mpv_container_motion_event(GdkEventMotion *event) {
	show_control_widgets();
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

void Window::on_mpv_idle_signal() {
	//controlPanel.set_slider_value(0);
	set_idle_state();
}

void Window::on_mpv_media_title_signal(const std::string &new_title) {
	set_title(new_title);
}

} /* namespace Mediaplayer */
