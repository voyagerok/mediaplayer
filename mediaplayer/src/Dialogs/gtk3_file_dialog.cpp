/*
 * Gtk3FileDialog.cpp
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#include "gtk3_file_dialog.h"

namespace Mediaplayer {

DialogResult Gtk3FileDialog::ShowDialog() {
	Gtk::FileChooserDialog dialog (dialogTitle, Gtk::FILE_CHOOSER_ACTION_OPEN);
	return ShowDialog(dialog);
}

DialogResult Gtk3FileDialog::ShowDialog(Gtk::Window &parent){
	Gtk::FileChooserDialog dialog (parent, dialogTitle, Gtk::FILE_CHOOSER_ACTION_OPEN);
	return ShowDialog(dialog);
}

DialogResult Gtk3FileDialog::ShowDialog(Gtk::FileChooserDialog &dialog) {

	filename = "";

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	auto result = dialog.run();

	switch(result) {
	case Gtk::RESPONSE_OK:
		filename = dialog.get_filename();
		return DialogResult::Confirmed;
	default:
		return DialogResult::Canceled;
	}
}

} /* namespace Mediaplayer */
