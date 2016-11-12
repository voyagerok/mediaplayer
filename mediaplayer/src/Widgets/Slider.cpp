/*
 * Slider.cpp
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Slider.h"

namespace Mediaplayer {

Slider::Slider() : Slider {Gtk::ORIENTATION_HORIZONTAL} {
}

Slider::Slider(Gtk::Orientation orientation) : Gtk::Scale {orientation} {
	set_range(0,100);
	set_margin_left(10);
	set_margin_right(10);
	set_margin_bottom(10);
	set_margin_top(10);
	set_draw_value(false);
	set_increments(1,1);
}

} /* namespace Mediaplayer */
