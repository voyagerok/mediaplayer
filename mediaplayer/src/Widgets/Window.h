/*
 * Window.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_WINDOW_H_
#define WIDGETS_WINDOW_H_

#include <gtkmm.h>
#include "../Dialogs/IFileDialog.h"
#include "MpvContainer.h"

namespace Mediaplayer {

class Window: public Gtk::ApplicationWindow {
public:
	Window();
	int64_t get_mpv_container_wid();
private:
	bool on_key_release(GdkEventKey*);
	void on_file_open();
	void toggle_fullscreen();
	using FileDialogPtr = std::unique_ptr<IFileDialog>;
	FileDialogPtr openFileDialog;
	MpvContainer container;
	bool isFullscreen = false;
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_WINDOW_H_ */
