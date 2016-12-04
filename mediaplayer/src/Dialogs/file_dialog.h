/*
 * IFileDialog.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef DIALOGS_FILE_DIALOG_H_
#define DIALOGS_FILE_DIALOG_H_

#include <gtkmm.h>

namespace Mediaplayer {

enum class DialogResult {Confirmed, Canceled};

class FileDialog {
public:
	virtual DialogResult ShowDialog() = 0;
	virtual DialogResult ShowDialog(Gtk::Window&) = 0;
	virtual std::string GetFilename() = 0;
	virtual ~FileDialog() {}
};

} /* namespace Mediaplayer */

#endif /* DIALOGS_FILE_DIALOG_H_ */
