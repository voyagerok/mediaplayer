/*
 * MpvContainer.cpp
 *
 *  Created on: 10 нояб. 2016 г.
 *      Author: nikolay
 */

#include "MpvContainer.h"
#include <gdk/gdkx.h>
#include <iostream>

namespace Mediaplayer {

MpvContainer::MpvContainer() : Gtk::DrawingArea() {
	add_events(Gdk::EventMask::POINTER_MOTION_MASK);
}

int64_t MpvContainer::get_wid() {

	std::cerr << "mpv_container realized: " << get_realized() << std::endl;

//	auto parent = this->get_parent_window();
//	if (parent && !get_realized())
//		realize();
	if (!get_realized())
		realize();

	Glib::RefPtr<Gdk::Window> window = get_window();
	if (!window)
		throw std::runtime_error("get_wid(): Failed to get GDK Window object");

	int64_t wid = static_cast<int64_t>(gdk_x11_window_get_xid(window->gobj()));

	return wid;
}

bool MpvContainer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {

	//bool result = Gtk::DrawingArea::on_draw(cr);

	auto allocation = get_allocation();
	cr->rectangle(0, 0, allocation.get_width(), allocation.get_height());
	cr->set_source_rgb(0, 0, 0);
	cr->fill();

//	return Gtk::DrawingArea::on_draw(cr);

	return false;
}

void MpvContainer::on_realize() {
	Gtk::DrawingArea::on_realize();
}

} /* namespace Mediaplayer */
