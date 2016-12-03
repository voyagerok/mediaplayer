/*
 * MenuBarFactory.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef FACTORIES_MENUBARFACTORY_H_
#define FACTORIES_MENUBARFACTORY_H_

#include "IMenuFactory.h"

namespace Mediaplayer {

class MenuBarFactory: public IMenuFactory {
public:
	Glib::RefPtr<Gio::Menu> CreateMenuInstance() override;
private:
	const std::string menubarResourcePath = "/org/apps/mediaplayer/Menubar.xml";
	const std::string menubarObjectId = "MenuBar";
};

} /* namespace Mediaplayer */

#endif /* FACTORIES_MENUBARFACTORY_H_ */
