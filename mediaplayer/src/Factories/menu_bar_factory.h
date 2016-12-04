/*
 * MenuBarFactory.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef FACTORIES_MENU_BAR_FACTORY_H_
#define FACTORIES_MENU_BAR_FACTORY_H_

#include "menu_factory.h"

namespace Mediaplayer {

class MenuBarFactory: public MenuFactory {
public:
	Glib::RefPtr<Gio::Menu> CreateMenuInstance() override;
private:
	const std::string menubarResourcePath = "/org/apps/mediaplayer/menubar.xml";
	const std::string menubarObjectId = "MenuBar";
};

} /* namespace Mediaplayer */

#endif /* FACTORIES_MENU_BAR_FACTORY_H_ */
