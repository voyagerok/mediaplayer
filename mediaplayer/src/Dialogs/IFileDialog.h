/*
 * IFileDialog.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef DIALOGS_IFILEDIALOG_H_
#define DIALOGS_IFILEDIALOG_H_

#include <gtkmm.h>

namespace Mediaplayer {

enum class DialogResult {Confirmed, Canceled};

class IFileDialog {
public:
	virtual DialogResult ShowDialog() = 0;
	virtual DialogResult ShowDialog(Gtk::Window&) = 0;
	virtual std::string GetFilename() = 0;
	virtual ~IFileDialog() {}
};

} /* namespace Mediaplayer */

#endif /* DIALOGS_IFILEDIALOG_H_ */
