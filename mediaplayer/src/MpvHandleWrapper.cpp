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

static void wakeup_callback(void *param) {
	MpvHandleWrapper *handler = static_cast<MpvHandleWrapper*>(param);
	handler->mpv_events().emit();
}

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

	mpv_observe_property(mpv, 0, percent_pos_prop_name, MPV_FORMAT_DOUBLE);
	mpv_observe_property(mpv, 0, duration_prop_name, MPV_FORMAT_INT64);

	mpv_events().connect(sigc::mem_fun(*this, &MpvHandleWrapper::on_mpv_events));
	mpv_set_wakeup_callback(mpv, wakeup_callback, this);

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
	currentPlaybackState = PlaybackState::Started;
}

void MpvHandleWrapper::seek(int time) {
	if (currentState != State::Loaded) {
		std::cerr << "seek(): you should load video before seek" << std::endl;
		return;
	}

	const char *command[] = {"seek", std::to_string(time).c_str(), "absolute", nullptr};
	auto error = mpv_command_async(mpv, 0, command);
	if (error < 0) {
		std::cerr << "seek failed: " << mpv_error_string(error) << std::endl;
		return;
	}
}

void MpvHandleWrapper::on_mpv_events() {

	while (mpv) {
		mpv_event *event = mpv_wait_event(mpv, 0);
		if (event->event_id == MPV_EVENT_NONE)
			break;
		switch (event->event_id) {
		case MPV_EVENT_PROPERTY_CHANGE: {
			mpv_event_property *prop = static_cast<mpv_event_property*>(event->data);
			if (strcmp(prop->name, duration_prop_name) == 0) {
				duration_signal().emit(*static_cast<int*>(prop->data));
			}
			break;
		}
		default:
			break;
		}
	}
}

void MpvHandleWrapper::start_playback() {
	if (currentPlaybackState == PlaybackState::Paused) {
		const char *command[] = {"keypress", "p", nullptr};
		auto error = mpv_command_async(mpv, 0, command);
		if (error < 0) {
			std::cerr << "pause failed: " << mpv_error_string(error) << std::endl;
			return;
		}

		currentPlaybackState = PlaybackState::Started;
	}
}

void MpvHandleWrapper::pause_playback(){
	if (currentPlaybackState == PlaybackState::Started) {
		const char *command[] = {"keypress", "p", nullptr};
		auto error = mpv_command_async(mpv, 0, command);
		if (error < 0) {
			std::cerr << "pause failed: " << mpv_error_string(error) << std::endl;
			return;
		}
		currentPlaybackState = PlaybackState::Paused;
	}
}

MpvHandleWrapper::~MpvHandleWrapper() {
	if (mpv)
		mpv_terminate_destroy(mpv);
}

} /* namespace Mediaplayer */
