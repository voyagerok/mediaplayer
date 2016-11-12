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
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_SLIDER_H_ */
