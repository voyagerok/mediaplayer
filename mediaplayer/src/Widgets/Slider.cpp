/*
 * Slider.cpp
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Slider.h"

namespace Mediaplayer {

bool Slider::on_button_press_event(GdkEventButton *button) {
	left_mouse_button_pressed = button->button == 1;
	return Gtk::Scale::on_button_press_event(button);
}

bool Slider::on_button_release_event(GdkEventButton *button) {
	if (button->button == 1)
		if (left_mouse_button_pressed)
			left_mouse_button_pressed = false;
	return Gtk::Scale::on_button_release_event(button);
}

Slider::Slider() :
		Slider { Gtk::ORIENTATION_HORIZONTAL } {
}

Slider::Slider(Gtk::Orientation orientation) :
		Gtk::Scale { orientation } {
	set_range(0, 100);
	set_margin_left(10);
	set_margin_right(10);
	set_margin_bottom(10);
	set_margin_top(10);
	set_draw_value(false);
	set_increments(1, 1);
	set_sensitive(false);
}

} /* namespace Mediaplayer */
