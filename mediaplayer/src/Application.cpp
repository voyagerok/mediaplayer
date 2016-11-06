/*
 * Application.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "Application.h"
#include "Factories/MenuBarFactory.h"

namespace Mediaplayer {

Application::Application(int argc, char** argv) :
		Gtk::Application(argc, argv, "org.apps.mediaplayer"), menuBar(
				new MenuBarFactory) {
}

void Application::on_startup() {
	Gtk::Application::on_startup();
	set_menubar(menuBar->CreateMenuInstance());
}

void Application::on_activate() {
	Gtk::Application::on_activate();
	add_window(mainWindow);
	mainWindow.show_all();
}

Glib::RefPtr<Application> Application::create(int argc, char **argv) {
	return Glib::RefPtr<Application>(new Application(argc, argv));
}

} /* namespace Mediaplayer */
