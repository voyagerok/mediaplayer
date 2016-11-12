/*
 * MpvHandleWrapper.cpp
 *
 *  Created on: 9 нояб. 2016 г.
 *      Author: nikolay
 */

#include "MpvHandleWrapper.h"
#include <stdexcept>
#include <iostream>

namespace Mediaplayer {

MpvHandleWrapper::MpvHandleWrapper() {
	setlocale(LC_NUMERIC, "C");

	mpv = mpv_create();
	if (!mpv)
		throw std::runtime_error("mpv_create() failed");

	currentState = State::Allocated;
}

void MpvHandleWrapper::initialize(int64_t wid) {

	if (currentState == State::Initialized) {
		std::cerr << "Attempt to initialize mpv twice" << std::endl;
		return;
	}

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

	if (currentState != State::Initialized) {
		std::cerr << "load(): mpv handler not initialized" << std::endl;
		return;
	}

	const char *command[] = { "loadfile", filename.c_str(), nullptr };
	auto error = mpv_command(mpv, command);
	if (error < 0) {
		std::cerr << "load() failed: " << mpv_error_string(error) << std::endl;
		return;
	}

	currentState = State::Loaded;
}

void MpvHandleWrapper::seek(int percentage) {
	if (currentState != State::Loaded) {
		std::cerr << "seek(): you should load video before seek" << std::endl;
		return;
	}

	const char *command[] = {"seek", std::to_string(percentage).c_str(), "absolute-percent", nullptr};
	auto error = mpv_command_async(mpv, 0, command);
	if (error < 0) {
		std::cerr << "seek failed: " << mpv_error_string(error) << std::endl;
		return;
	}
}

MpvHandleWrapper::~MpvHandleWrapper() {
	if (mpv)
		mpv_terminate_destroy(mpv);
}

} /* namespace Mediaplayer */
