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
#include "../MpvHandleWrapper.h"
#include "Slider.h"

namespace Mediaplayer {

class Window: public Gtk::ApplicationWindow {
public:
	Window();
	int64_t get_mpv_container_wid();
	void load_file(const std::string &filename);

protected:
	bool on_key_release(GdkEventKey*);
	void on_realize() override;
	void on_slider_value_changed();
	void on_mpv_progress_signal(double);
	void on_mpv_duration_signal(int);

private:
	void on_file_open();
	void toggle_fullscreen();
	bool on_slider_update_timeout(int);

	using FileDialogPtr = std::unique_ptr<IFileDialog>;

	FileDialogPtr openFileDialog;
	MpvContainer container;
	bool isFullscreen = false;
	MpvHandleWrapper mpvHandler;
	Gtk::Box m_box;
	Slider m_slider;

	sigc::connection update_slider_connection;
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_WINDOW_H_ */
