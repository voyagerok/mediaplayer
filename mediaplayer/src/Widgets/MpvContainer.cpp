/*
 * MpvContainer.cpp
 *
 *  Created on: 10 нояб. 2016 г.
 *      Author: nikolay
 */

#include "MpvContainer.h"
#include <gdk/gdkx.h>

namespace Mediaplayer {

int64_t MpvContainer::get_wid() {

	auto parent = this->get_parent_window();
	if (parent && !get_realized())
		realize();

	Glib::RefPtr<Gdk::Window> window = get_window();
	if (!window)
		throw std::runtime_error("get_wid(): Failed to get GDK Window object");

	int64_t wid = static_cast<int64_t>(gdk_x11_window_get_xid(window->gobj()));

	return wid;
}

} /* namespace Mediaplayer */
