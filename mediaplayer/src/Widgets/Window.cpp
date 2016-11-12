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

namespace Mediaplayer {

Window::Window() :
		openFileDialog(new Gtk3FileDialog), m_box { Gtk::ORIENTATION_VERTICAL }, m_slider {
				Gtk::ORIENTATION_HORIZONTAL } {

	set_default_size(800, 600);
	set_title("Mediaplayer");

	m_slider.signal_value_changed().connect(
			sigc::mem_fun(*this, &Window::on_slider_value_changed));

	m_box.pack_start(container, true, true, 0);
	m_box.pack_start(m_slider, false, true, 10);
	add(m_box);

	add_action("fileopen", sigc::mem_fun(*this, &Window::on_file_open));
	signal_key_release_event().connect(
			sigc::mem_fun(*this, &Window::on_key_release));

	mpvHandler.playback_progress_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_progress_signal));
	mpvHandler.duration_signal().connect(
			sigc::mem_fun(*this, &Window::on_mpv_duration_signal));
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
		mpvHandler.load(filename);
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
		set_show_menubar(!isFullscreen);
		break;
	default:
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
}

void Window::on_realize() {
	Gtk::Window::on_realize();
	mpvHandler.initialize(container.get_wid());
}

void Window::on_slider_value_changed() {
	if (m_slider.get_left_mouse_button_pressed()) {
		auto currentValue = m_slider.get_value();
		mpvHandler.seek(floor(currentValue));
	}
}

void Window::on_mpv_progress_signal(double value) {
	m_slider.set_value(floor(value));
}

void Window::on_mpv_duration_signal(int value) {
	m_slider.set_sensitive(true);
	m_slider.set_range(0, value);
	sigc::slot<bool> update_slider_slot = sigc::bind(
			sigc::mem_fun(*this, &Window::on_slider_update_timeout), 0);
	update_slider_connection = Glib::signal_timeout().connect(
			update_slider_slot, 1000);
}

bool Window::on_slider_update_timeout(int) {

	auto current = m_slider.get_value();
	if (current < m_slider.get_adjustment()->get_upper()) {
		m_slider.set_value(current + 1);
		return true;
	}
	return false;
}

} /* namespace Mediaplayer */
