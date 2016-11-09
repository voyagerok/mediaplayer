/*
 * Window.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Window.h"
#include "../Dialogs/Gtk3FileDialog.h"

namespace Mediaplayer {

Window::Window() :
		openFileDialog(new Gtk3FileDialog) {

	set_default_size(800, 600);
	set_title("Mediaplayer");
	add_action("fileopen", sigc::mem_fun(*this, &Window::on_file_open));
}

void Window::on_file_open() {
	openFileDialog->ShowDialog(*this);
}

} /* namespace Mediaplayer */
