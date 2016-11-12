/*
 * Slider.h
 *
 *  Created on: 12 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_SLIDER_H_
#define WIDGETS_SLIDER_H_

#include <gtkmm.h>

namespace Mediaplayer {

class Slider: public Gtk::Scale {
public:
	Slider();
	explicit Slider(Gtk::Orientation);
	bool get_left_mouse_button_pressed() {return left_mouse_button_pressed;}
protected:
	bool on_button_press_event(GdkEventButton*) override;
	bool on_button_release_event(GdkEventButton*) override;
private:
	bool left_mouse_button_pressed = false;
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_SLIDER_H_ */
