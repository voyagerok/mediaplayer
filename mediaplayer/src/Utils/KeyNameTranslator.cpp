/*
 * KeyNameTranslator.cpp
 *
 *  Created on: 3 дек. 2016 г.
 *      Author: nikolay
 */


#include "KeyNameTranslator.h"
#include <gtkmm.h>
#include <map>

namespace Mediaplayer{
namespace KeyNameTranslator {

using keymap = std::map<std::string, std::string>;

static const keymap gdk_to_mpv_keymap = {
		{"less", "<"},
		{"greater", ">"},
		{"Page_Up", "PGUP"},
		{"Page_Down", "PGDWN"},
		{"BackSpace", "BS"},
		{"period", "."},
		{"comma", ","},
		{"grave", "`"},
		{"asciitilde", "~"},
		{"exclam", "!"},
		{"at", "@"},
		{"numbersign", "SHARP"},
		{"dollar","$"},
		{"percent", "%"},
		{"caret", "^"},
		{"ampersand", "&"},
		{"asterisk", "*"},
		{"minus", "-"},
		{"underscore", "_"},
		{"equal", "="},
		{"plus", "+"},
		{"semicolon", ";"},
		{"colon", ":"},
		{"apostrophe", "'"},
		{"quotedbl", "\""},
		{"slash", "/"},
		{"backslash", "\\"},
		{"parenleft", "("},
		{"parenright", ")"},
		{"bracketleft", "["},
		{"bracketright", "]"},
		{"question", "?"},
		{"Right", "RIGHT"},
		{"Left", "LEFT"},
		{"Up", "UP"},
		{"Down", "DOWN"},
		{"Escape", "ESC"},
		{"Delete", "DEL"},
		{"Return", "ENTER"},
		{"Insert", "INS"}
};

std::string translate_from_gdk_to_mpv(unsigned gdk_key_value, unsigned gdk_mod_key_value)
{
	std::string gdk_key_name = gdk_keyval_name(gdk_key_value);
	std::string mpv_mod_key_name{};

	if ((gdk_mod_key_value & GDK_SHIFT_MASK) != 0)
		mpv_mod_key_name = "Shift+";
	else if ((gdk_mod_key_value & GDK_CONTROL_MASK) != 0)
		mpv_mod_key_name = "Ctrl+";
	else if ((gdk_mod_key_value & GDK_MOD1_MASK) != 0)
		mpv_mod_key_name = "Alt+";
	else if ((gdk_mod_key_value & GDK_META_MASK) != 0 || (gdk_mod_key_value & GDK_SUPER_MASK) != 0)
		mpv_mod_key_name = "Meta+";

	auto mpv_keyname = gdk_to_mpv_keymap.find(gdk_key_name);
	if (mpv_keyname != gdk_to_mpv_keymap.end()) {
		return mpv_mod_key_name + mpv_keyname->second;
	}

	return mpv_mod_key_name + gdk_key_name;
}

}}
