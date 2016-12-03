/*
 * KeyNameTranslator.h
 *
 *  Created on: 3 дек. 2016 г.
 *      Author: nikolay
 */

#ifndef UTILS_KEYNAMETRANSLATOR_H_
#define UTILS_KEYNAMETRANSLATOR_H_

#include <string>

namespace Mediaplayer{
namespace KeyNameTranslator {

std::string translate_from_gdk_to_mpv(unsigned gdk_key_value, unsigned gdk_mod_key_value);

}}


#endif /* UTILS_KEYNAMETRANSLATOR_H_ */
