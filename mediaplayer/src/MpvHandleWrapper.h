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

	sigc::signal1<void,double> playback_progress_signal() { return m_playback_progress; }
	sigc::signal<void,int> duration_signal() {return m_duration;}

	Glib::Dispatcher& mpv_events() {return m_mpv_events;}
private:
	sigc::signal1<void,double> m_playback_progress;
	sigc::signal<void,int> m_duration;
	Glib::Dispatcher m_mpv_events;

	mpv_handle *mpv;
	int64_t wid = -1;
	enum class State {Allocated, Initialized, Loaded};
	enum class PlaybackState {Started, Paused};
	State currentState;
	PlaybackState currentPlaybackState;

	const char *percent_pos_prop_name = "percent-pos";
	const char *duration_prop_name = "duration";

	void on_mpv_events();
};

} /* namespace Mediaplayer */

#endif /* MPVHANDLEWRAPPER_H_ */
