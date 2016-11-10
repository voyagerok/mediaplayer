/*
 * Window.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Window.h"
#include "../Dialogs/Gtk3FileDialog.h"
#include "../Application.h"

namespace Mediaplayer {

Window::Window() :
		openFileDialog(new Gtk3FileDialog) {

	set_default_size(800, 600);
	set_title("Mediaplayer");
	add_action("fileopen", sigc::mem_fun(*this, &Window::on_file_open));
	add(container);
}

void Window::on_file_open() {
	auto result = openFileDialog->ShowDialog(*this);
	if (result == DialogResult::Confirmed) {
		std::string filename = openFileDialog->GetFilename();
		auto currentApp = Glib::RefPtr<Application>::cast_dynamic(
				Gio::Application::get_default());
		if (currentApp) {
			currentApp->get_mpv_handler().load(filename);
		}
	}
}

int64_t Window::get_mpv_container_wid() {
	return container.get_wid();
}

} /* namespace Mediaplayer */
