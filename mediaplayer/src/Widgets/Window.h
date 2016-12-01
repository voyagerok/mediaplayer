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
#include "ControlPanel.h"

namespace Mediaplayer {

class Window: public Gtk::ApplicationWindow {
public:
	Window(Glib::RefPtr<Gio::Menu>);
	int64_t get_mpv_container_wid();
	void load_file(const std::string &filename);

protected:
	bool on_key_release_event(GdkEventKey*) override;
	bool on_key_press_event(GdkEventKey*) override;
	void on_realize() override;
	void on_slider_value_changed();
	void on_mpv_progress_signal(double);
	void on_mpv_duration_signal(int);
	void on_mpv_idle_signal();
	void on_mpv_media_title_signal(const std::string&);
	void on_mpv_fullscreen_signal();
	void on_pause_command() {mpvHandler.pause_playback();}
	void on_start_command() {mpvHandler.start_playback();}
	bool on_mpv_container_button_press(GdkEventButton*);
	bool on_mpv_container_motion_event(GdkEventMotion*);

private:
	void on_file_open();
	void toggle_fullscreen();
	uint64_t get_drawing_area_wid();
	bool on_hide_widgets_timeout(int);
	void set_cursor_visibility(bool);
	void show_control_widgets();
	void set_idle_state();

	using FileDialogPtr = std::unique_ptr<IFileDialog>;

	FileDialogPtr openFileDialog;
	MpvContainer container;
	bool isFullscreen = false;
	MpvHandleWrapper mpvHandler;
	ControlPanel controlPanel;
	Gtk::Overlay m_Overlay;
	Gtk::Revealer controlPanelRevealer;
	Gtk::Revealer menuBarRevealer;
	Gtk::MenuBar menuBar;
	Gtk::Stack videoArea;
	Gtk::Menu popupMenu;

	sigc::connection hideWidgetsConnection;

	const char *default_title = "Mediaplayer";
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_WINDOW_H_ */
