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

namespace Mediaplayer {

class MpvHandleWrapper {
public:
	MpvHandleWrapper();
	virtual ~MpvHandleWrapper();
	void initialize(int64_t wid);
	void load(const std::string &filename);
	void seek(int percentage);
private:
	mpv_handle *mpv;
	int64_t wid = -1;
	enum class State {Allocated, Initialized, Loaded};
	State currentState;
};

} /* namespace Mediaplayer */

#endif /* MPVHANDLEWRAPPER_H_ */
