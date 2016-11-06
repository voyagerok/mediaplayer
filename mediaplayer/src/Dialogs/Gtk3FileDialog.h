/*
 * Gtk3FileDialog.h
 *
 *  Created on: 6 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef DIALOGS_GTK3FILEDIALOG_H_
#define DIALOGS_GTK3FILEDIALOG_H_

#include "IFileDialog.h"

namespace Mediaplayer {

class Gtk3FileDialog: public IFileDialog {
public:
	DialogResult ShowDialog() override;
	DialogResult ShowDialog(Gtk::Window&) override;
	std::string GetFilename() override { return filename; }
private:
	std::string filename;
	DialogResult ShowDialog(Gtk::FileChooserDialog &dialog);
	const std::string dialogTitle = "Choose a video file";
};

} /* namespace Mediaplayer */

#endif /* DIALOGS_GTK3FILEDIALOG_H_ */
