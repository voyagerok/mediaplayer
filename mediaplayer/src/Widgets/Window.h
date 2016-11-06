/*
 * Window.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_WINDOW_H_
#define WIDGETS_WINDOW_H_

#include <gtkmm-3.0/gtkmm/applicationwindow.h>

namespace Mediaplayer {

class Window: public Gtk::ApplicationWindow {
public:
	Window();
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_WINDOW_H_ */
