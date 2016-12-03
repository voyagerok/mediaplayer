/*
 * MenuBarFactory.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include <iostream>
#include "MenuBarFactory.h"

namespace Mediaplayer {

Glib::RefPtr<Gio::Menu> MenuBarFactory::CreateMenuInstance() {

	Glib::RefPtr<Gtk::Builder> builder;

	try {
		builder = Gtk::Builder::create_from_resource(menubarResourcePath);
	} catch (const Glib::FileError &fileError) {
		std::cerr << "FileError: " << fileError.what() << std::endl;
	} catch (const Gtk::BuilderError &builderError) {
		std::cerr << "BuilderError: " << builderError.what() << std::endl;
	} catch (const Glib::MarkupError &markupError) {
		std::cerr << "MarkupError: " << markupError.what() << std::endl;
	}

	auto object = builder->get_object(menubarObjectId);
	auto menubar = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
	if (!menubar) throw std::runtime_error("Failed to instantiate menubar");

	return menubar;
}

} /* namespace Mediaplayer */
