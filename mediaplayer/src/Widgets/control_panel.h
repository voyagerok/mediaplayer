/*
 * ControlPanel.h
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_CONTROL_PANEL_H_
#define WIDGETS_CONTROL_PANEL_H_

#include <gtkmm.h>

#include "slider.h"

namespace Mediaplayer {

class ControlPanel: public Gtk::Box {
public:
	ControlPanel();
	void set_slider_value(double value) {m_Slider.set_value(value);}
	double get_slider_value() {return m_Slider.get_value();}
	double get_slider_upper() {return m_Slider.get_adjustment()->get_upper();}
	bool get_slider_left_mbutton_pressed() {return m_Slider.get_left_mouse_button_pressed();}
	void set_slider_range(double lower, double upper) {m_Slider.set_range(lower, upper);}
	void set_overall_time(int);
	void set_current_time(int);
	void set_time_default();

	sigc::signal<void> signal_slider_value_changed() {return m_signal_slider_value_changed;}
	sigc::signal<void> signal_start_button_clicked() {return m_signal_on_start_button_clicked;}
	sigc::signal<void> signal_pause_button_clicked() {return m_signal_on_pause_button_clicked;}
private:
	int m_overall_hours;
	int m_overall_minutes;
	int m_overall_seconds;

	Slider m_Slider;
	Gtk::Button startButton;
	Gtk::Button pauseButton;
	Gtk::Box buttonsPanel;
	Gtk::Label timeLabel;

	sigc::signal<void> m_signal_slider_value_changed;
	sigc::signal<void> m_signal_on_start_button_clicked;
	sigc::signal<void> m_signal_on_pause_button_clicked;

	void on_slider_value_changed();
	void on_start_button_clicked();
	void on_pause_button_clicked();

	const char *time_default_string = "00:00:00 / 00:00:00";
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_CONTROL_PANEL_H_ */
