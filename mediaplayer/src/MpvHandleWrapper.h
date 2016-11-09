/*
 * MpvHandleWrapper.h
 *
 *  Created on: 9 нояб. 2016 г.
 *      Author: nikolay
 */

#ifndef MPVHANDLEWRAPPER_H_
#define MPVHANDLEWRAPPER_H_

#include <mpv/client.h>

namespace Mediaplayer {

class MpvHandleWrapper {
public:
	MpvHandleWrapper();
	virtual ~MpvHandleWrapper();
private:
	mpv_handle *mpv;
};

} /* namespace Mediaplayer */

#endif /* MPVHANDLEWRAPPER_H_ */
