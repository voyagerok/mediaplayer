/*
 * MpvHandleWrapper.cpp
 *
 *  Created on: 9 нояб. 2016 г.
 *      Author: nikolay
 */

#include "MpvHandleWrapper.h"
#include <stdexcept>

namespace Mediaplayer {

MpvHandleWrapper::MpvHandleWrapper() {
	setlocale(LC_NUMERIC, "C");

	mpv = mpv_create();
	if (!mpv)
		throw std::runtime_error("mpv_create() failed");

	currentState = State::Allocated;
}

void MpvHandleWrapper::initialize(int64_t wid) {


	this->wid = wid;
	mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

	// Enable default bindings, because we're lazy. Normally, a player using
	// mpv as backend would implement its own key bindings.
	mpv_set_option_string(mpv, "input-default-bindings", "yes");

	// Enable keyboard input on the X11 window. For the messy details, see
	// --input-vo-keyboard on the manpage.
	mpv_set_option_string(mpv, "input-vo-keyboard", "yes");

	auto error = mpv_initialize(mpv);
	if (error < 0)
		throw std::runtime_error(mpv_error_string(error));

	currentState = State::Initialized;
}

void MpvHandleWrapper::load(const std::string &filename) {

	const char *command[] = { "loadfile", filename.c_str(), nullptr, nullptr };
	auto error = mpv_command(mpv, command);
	if (error < 0)
		throw std::runtime_error(mpv_error_string(error));
}

MpvHandleWrapper::~MpvHandleWrapper() {
	if (mpv)
		mpv_terminate_destroy(mpv);
}

} /* namespace Mediaplayer */
