/*
 * ControlPanel.cpp
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#include "ControlPanel.h"

namespace Mediaplayer {

ControlPanel::ControlPanel() :
		Gtk::Box { Gtk::ORIENTATION_HORIZONTAL }, buttonsPanel {
				Gtk::ORIENTATION_HORIZONTAL, 10 } {

	set_sensitive(false);

	startButton.set_image_from_icon_name("media-playback-start");
	pauseButton.set_image_from_icon_name("media-playback-pause");
	buttonsPanel.pack_start(startButton, false, true, 0);
	buttonsPanel.pack_start(pauseButton, false, true, 0);
	buttonsPanel.set_margin_bottom(10);
	buttonsPanel.set_margin_top(10);
	buttonsPanel.set_margin_right(10);
	buttonsPanel.set_margin_left(10);

	pack_start(buttonsPanel, false, true);
	pack_start(m_Slider, true, true);

	m_Slider.signal_value_changed().connect(
			sigc::mem_fun(*this, &ControlPanel::on_slider_value_changed));
	startButton.signal_clicked().connect(
			sigc::mem_fun(*this, &ControlPanel::on_start_button_clicked));
	pauseButton.signal_clicked().connect(
			sigc::mem_fun(*this, &ControlPanel::on_pause_button_clicked));
}

void ControlPanel::on_slider_value_changed() {
	signal_slider_value_changed().emit();
}

void ControlPanel::on_start_button_clicked() {
	signal_start_button_clicked().emit();
}

void ControlPanel::on_pause_button_clicked() {
	signal_pause_button_clicked().emit();
}

} /* namespace Mediaplayer */
