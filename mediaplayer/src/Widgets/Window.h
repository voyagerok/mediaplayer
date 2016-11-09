/*
 * Window.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_WINDOW_H_
#define WIDGETS_WINDOW_H_

#include <gtkmm.h>
#include "../Dialogs/IFileDialog.h"

namespace Mediaplayer {

class Window: public Gtk::ApplicationWindow {
public:
	Window();
private:
	void on_file_open();
	using FileDialogPtr = std::unique_ptr<IFileDialog>;
	FileDialogPtr openFileDialog;
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_WINDOW_H_ */
