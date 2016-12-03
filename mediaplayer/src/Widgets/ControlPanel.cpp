/*
 * ControlPanel.cpp
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#include "ControlPanel.h"
#include <sstream>
#include <chrono>
#include <iomanip>

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

	timeLabel.set_text(time_default_string);
	timeLabel.set_margin_right(10);
	timeLabel.set_margin_left(10);

	pack_start(buttonsPanel, false, true);
	pack_start(m_Slider, true, true);
	pack_start(timeLabel, false, true);

	auto controlPanelStyleContext = get_style_context();
	controlPanelStyleContext->add_class(GTK_STYLE_CLASS_BACKGROUND);

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

void ControlPanel::set_overall_time(int overall_time) {
	m_overall_hours = overall_time / 3600;
	int remaining = overall_time % 3600;
	m_overall_minutes = remaining / 60;
	m_overall_seconds = remaining % 60;
}

void ControlPanel::set_current_time(int current_time) {
	int current_hours = current_time / 3600;
	int remaining = current_time % 3600;
	int current_minutes = remaining / 60;
	int current_seconds = remaining % 60;

	std::ostringstream stream;
	stream << std::setw(2) << std::setfill('0') << current_hours;
	stream << ":" << std::setw(2) << std::setfill('0') << current_minutes;
	stream << ":" << std::setw(2) << std::setfill('0') << current_seconds;
	stream << " / " << std::setw(2) << std::setfill('0') << m_overall_hours;
	stream << ":" << std::setw(2) << std::setfill('0') << m_overall_minutes;
	stream << ":" << std::setw(2) << std::setfill('0') << m_overall_seconds;

	timeLabel.set_text(stream.str());
}

void ControlPanel::set_time_default() {
	timeLabel.set_text(time_default_string);
}

} /* namespace Mediaplayer */
