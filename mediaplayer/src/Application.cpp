/*
 * Application.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Application.h"

namespace Mediaplayer {

Application::Application(int argc, char** argv) :
		Gtk::Application(argc, argv, "org.apps.mediaplayer") {
}

void Application::on_startup() {
	Gtk::Application::on_startup();
}

void Application::on_activate() {
	Gtk::Application::on_activate();
	add_window(mainWindow);
	mainWindow.show_all();
}

Glib::RefPtr<Application> Application::create(int argc, char **argv) {
	return Glib::RefPtr<Application> (new Application(argc, argv));
}

} /* namespace Mediaplayer */
