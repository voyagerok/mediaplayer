/*
 * Application.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <gtkmm.h>
#include "Widgets/Window.h"
#include "Factories/IMenuFactory.h"

namespace Mediaplayer {

class Application: public Gtk::Application {
public:
	static Glib::RefPtr<Application> create(int, char**);
protected:
	Application(int, char**);
	void on_startup() override;
	void on_activate() override;
private:
	using MenuBarPtr = std::unique_ptr<IMenuFactory>;
	Window mainWindow;
	MenuBarPtr menuBar;
};

} /* namespace Mediaplayer */

#endif /* APPLICATION_H_ */
