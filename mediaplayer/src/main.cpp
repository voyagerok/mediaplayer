/*
 ============================================================================
 Name        : mediaplayer.cpp
 Author      : nikolay
 Version     :
 Copyright   : This file is part of Mediaplayer.  Mediaplayer is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. Mediaplayer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with Mediaplayer.  If not, see <http://www.gnu.org/licenses/>.
 Description : Hello World in C++,
 ============================================================================
 */

#include <gtkmm.h>
#include "Application.h"

using namespace std;

int main(int argc, char **argv) {
	auto app = Mediaplayer::Application::create(argc, argv);
	return app->run();
}
