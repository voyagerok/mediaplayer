/*
 * MpvHandleWrapper.cpp
 *
 *  Created on: 9 нояб. 2016 г.
 *      Author: nikolay
 */

#include "mpv_handle_wrapper.h"

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
	currentPlaybackState = PlaybackState::Undefined;
}

void MpvHandleWrapper::initialize(int64_t wid) {

	if (currentState == State::Initialized) {
		std::cerr << "Attempt to initialize mpv twice" << std::endl;
		return;
	}

	this->wid = wid;
	mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

	std::map<std::string,std::string> default_options = {
			{"osd-level", "1"},
			{"idle", "yes"},
			{"input-default-bindings", "yes"},
			{"input-cursor", "no"},
			{"cursor-autohide", "no"}
	};

	for (auto &option : default_options) {
		mpv_set_option_string(mpv, option.first.c_str(), option.second.c_str());
	}

	mpv_observe_property(mpv, 0, percent_pos_property_name, MPV_FORMAT_DOUBLE);
	mpv_observe_property(mpv, 0, duration_property_name, MPV_FORMAT_INT64);
	mpv_observe_property(mpv, 0, time_pos_property_name, MPV_FORMAT_DOUBLE);
	mpv_observe_property(mpv, 0, media_title_property_name, MPV_FORMAT_STRING);
	mpv_observe_property(mpv, 0, fullscreen_property_name, MPV_FORMAT_FLAG);

	mpv_events().connect(sigc::mem_fun(*this, &MpvHandleWrapper::on_mpv_events));
	mpv_set_wakeup_callback(mpv, wakeup_callback, this);

	auto error = mpv_initialize(mpv);
	if (error < 0)
		throw std::runtime_error(mpv_error_string(error));

	currentState = State::Initialized;
}

void MpvHandleWrapper::load(const std::string &filename) {

	if (currentState == State::Allocated) {
		std::cerr << "load(): mpv handler not initialized" << std::endl;
		return;
	}
	currentState = State::Initialized;

	const char *command[] = { "loadfile", filename.c_str(), nullptr };
	auto error = mpv_command(mpv, command);
	if (error < 0) {
		std::cerr << "load() failed: " << mpv_error_string(error) << std::endl;
		return;
	}
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
		case MPV_EVENT_PROPERTY_CHANGE:
		{
			mpv_event_property *prop = static_cast<mpv_event_property*>(event->data);
			if (strcmp(prop->name, duration_property_name) == 0)
			{
				auto duration = static_cast<int*>(prop->data);
				if (duration) {
					signal_duration().emit(*duration);
				}
			}
			else if (strcmp(prop->name, time_pos_property_name) == 0)
			{
				if (currentState == State::Loaded) {
					auto time_pos = static_cast<double*>(prop->data);
					if (time_pos) {
						signal_playback_progress().emit(*time_pos);
					}
				}
			}
			else if (strcmp(prop->name, media_title_property_name) == 0)
			{
				char **media_title = static_cast<char**>(prop->data);
				if (media_title) {
					signal_media_title_changed().emit(*media_title);
				}
			}
			else if (strcmp(prop->name, fullscreen_property_name) == 0)
			{
				if (currentState == State::Loaded) {
					signal_fullscreen().emit();
				}
			}
			break;
		}
		case MPV_EVENT_IDLE:
		{
			signal_state_idle().emit();
			currentPlaybackState = PlaybackState::Undefined;
			currentState = State::Initialized;
			break;
		}
		case MPV_EVENT_FILE_LOADED:
		{
			signal_file_loaded().emit();
			currentState = State::Loaded;
			currentPlaybackState = PlaybackState::Started;
			break;
		}
		case MPV_EVENT_END_FILE:
		{
			break;
		}
		default:
			break;
		}
	}
}

void MpvHandleWrapper::start_playback() {
	if (currentPlaybackState == PlaybackState::Paused) {
		auto error = press_key("p");
		if (error < 0) {
			std::cerr << "pause failed: " << mpv_error_string(error) << std::endl;
			return;
		}
		currentPlaybackState = PlaybackState::Started;
	}
}

void MpvHandleWrapper::pause_playback(){
	if (currentPlaybackState == PlaybackState::Started) {
		auto error = press_key("p");
		if (error < 0) {
			std::cerr << "pause failed: " << mpv_error_string(error) << std::endl;
			return;
		}
		currentPlaybackState = PlaybackState::Paused;
	}
}

int MpvHandleWrapper::press_key(const char *key_name) {
	const char *command[] = {"keypress", key_name, nullptr};
	return mpv_command_async(mpv, 0, command);
}

int MpvHandleWrapper::key_down(const char *key_name) {
	const char *command[] = {"keydown", key_name, nullptr};
	return mpv_command_async(mpv, 0, command);
}

int MpvHandleWrapper::key_up(const char *key_name) {
	const char *command[] = {"keyup", key_name, nullptr};
	return mpv_command_async(mpv, 0, command);
}

MpvHandleWrapper::~MpvHandleWrapper() {
	if (mpv)
		mpv_terminate_destroy(mpv);
}

} /* namespace Mediaplayer */
