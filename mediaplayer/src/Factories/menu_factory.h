/*
 * IMenuFactory.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef FACTORIES_MENU_FACTORY_H_
#define FACTORIES_MENU_FACTORY_H_

#include <gtkmm.h>

namespace Mediaplayer {

class MenuFactory {
public:
	virtual Glib::RefPtr<Gio::Menu> CreateMenuInstance() = 0;
	virtual ~MenuFactory() {}
};

} /* namespace Mediaplayer */


#endif /* FACTORIES_MENU_FACTORY_H_ */
