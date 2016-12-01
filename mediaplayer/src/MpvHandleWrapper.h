/*
 * MpvHandleWrapper.h
 *
 *  Created on: 9 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef MPVHANDLEWRAPPER_H_
#define MPVHANDLEWRAPPER_H_

#include <mpv/client.h>
#include <string>
#include <gtkmm.h>

namespace Mediaplayer {

class MpvHandleWrapper {
public:
	MpvHandleWrapper();
	virtual ~MpvHandleWrapper();
	void initialize(int64_t wid);
	void load(const std::string &filename);
	void seek(int time);
	void start_playback();
	void pause_playback();
	int press_key(const char *key_name);
	int key_up(const char *key_name);
	int key_down(const char *key_name);

	sigc::signal1<void,double> signal_playback_progress() { return m_playback_progress; }
	sigc::signal<void,int> signal_duration() {return m_duration;}
	sigc::signal<void> signal_state_idle() { return m_state_idle; };
	sigc::signal<void,std::string> media_title_changed_signal() { return m_media_title_changed; }
	sigc::signal<void> signal_fullscreen() { return m_fullscreen; }
	sigc::signal<void> signal_file_loaded() { return m_file_loaded; }

	Glib::Dispatcher& mpv_events() {return m_mpv_events;}
private:
	sigc::signal1<void,double> m_playback_progress;
	sigc::signal<void,int> m_duration;
	sigc::signal<void> m_state_idle;
	sigc::signal<void, std::string> m_media_title_changed;
	sigc::signal<void> m_fullscreen;
	sigc::signal<void> m_file_loaded;

	Glib::Dispatcher m_mpv_events;

	mpv_handle *mpv;
	int64_t wid = -1;
	enum class State {Allocated, Initialized, Loaded};
	enum class PlaybackState {Started, Paused, Undefined};
	State currentState;
	PlaybackState currentPlaybackState;

	const char *percent_pos_property_name = "percent-pos";
	const char *duration_property_name = "duration";
	const char *time_pos_property_name = "time-pos";
	const char *time_remaining_property_name = "time-remaining";
	const char *media_title_property_name = "media-title";
	const char *fullscreen_property_name = "fullscreen";

	void on_mpv_events();
};

} /* namespace Mediaplayer */

#endif /* MPVHANDLEWRAPPER_H_ */
