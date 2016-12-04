/*
 * Application.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include <application.h>
#include "Views/mediaplayer_views.h"
#include <iostream>

#include "Dialogs/gtk3_file_dialog.h"
#include "Factories/menu_bar_factory.h"

namespace Mediaplayer {

Application::Application(int argc, char** argv) :
		Gtk::Application(argc, argv, "org.apps.mediaplayer"), menuModel(
				new MenuBarFactory), fileDialog { new Gtk3FileDialog } {
	add_action("openinwindow",
			sigc::mem_fun(*this, &Application::on_open_in_new_window));
}

void Application::on_startup() {
	Gtk::Application::on_startup();
	//set_menubar(menuBar->CreateMenuInstance());

	Window *window { new Window(menuModel->CreateMenuInstance()) };
	store_window(window);
	window->show_all();
}

void Application::on_activate() {
	Gtk::Application::on_activate();
	g_resources_register(mediaplayer_views_get_resource());

	auto appSettings = Gtk::Settings::get_default();
	appSettings->property_gtk_application_prefer_dark_theme().set_value(true);
}

Glib::RefPtr<Application> Application::create(int argc, char **argv) {
	return Glib::RefPtr<Application>(new Application(argc, argv));
}

void Application::on_open_in_new_window() {

	if (auto window = get_active_window()) {
		auto result = fileDialog->ShowDialog(*window);
		if (result == DialogResult::Confirmed) {
			Window *window { new Window(menuModel->CreateMenuInstance()) };
			store_window(window);
			window->load_file(fileDialog->GetFilename());
			window->show_all();
		}
	}
}

void Application::store_window(Window *window) {
	window->signal_hide().connect(
			sigc::bind(sigc::mem_fun(*this, &Application::on_window_hidden),
					window));
	add_window(*window);
}

void Application::on_window_hidden(Gtk::Window *window) {
	delete window;
}

} /* namespace Mediaplayer */
