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
#include "Dialogs/IFileDialog.h"
#include <vector>

namespace Mediaplayer {

class Application: public Gtk::Application {
public:
	static Glib::RefPtr<Application> create(int, char**);
protected:
	Application(int, char**);
	void on_startup() override;
	void on_activate() override;
	void on_open_in_new_window();
	void on_window_hidden(Gtk::Window*);
private:
	using MenuBarPtr = std::unique_ptr<IMenuFactory>;
	using FileDialogPtr = std::unique_ptr<IFileDialog>;
	MenuBarPtr menuBar;
	FileDialogPtr fileDialog;

	void store_window(Window *window);
};

} /* namespace Mediaplayer */

#endif /* APPLICATION_H_ */
