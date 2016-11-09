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
	// TODO Auto-generated constructor stub
	mpv = mpv_create();
	if (!mpv)
		throw std::runtime_error("mpv_create() failed");
}

MpvHandleWrapper::~MpvHandleWrapper() {
	// TODO Auto-generated destructor stub
	if (mpv)
		mpv_terminate_destroy(mpv);
}

} /* namespace Mediaplayer */
