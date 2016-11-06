/*
 * IMenuFactory.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef FACTORIES_IMENUFACTORY_H_
#define FACTORIES_IMENUFACTORY_H_

#include <gtkmm.h>

namespace Mediaplayer {

class IMenuFactory {
public:
	virtual Glib::RefPtr<Gio::Menu> CreateMenuInstance() = 0;
	virtual ~IMenuFactory() {}
};

} /* namespace Mediaplayer */


#endif /* FACTORIES_IMENUFACTORY_H_ */
