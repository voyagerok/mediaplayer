/*
 * MpvContainer.h
 *
 *  Created on: 10 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef WIDGETS_MPVCONTAINER_H_
#define WIDGETS_MPVCONTAINER_H_

#include <gtkmm.h>

namespace Mediaplayer {

class MpvContainer: public Gtk::DrawingArea {
public:
	MpvContainer();
	int64_t get_wid();
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
	void on_realize() override;
};

} /* namespace Mediaplayer */

#endif /* WIDGETS_MPVCONTAINER_H_ */
