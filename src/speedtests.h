/*
BlockPlanet
Copyright (C) 2012 MiJyn, Joel Leclerc <mijyn@mail.com>
Licensed under GPLv3


Based on:
Minetest-c55
Copyright (C) 2010-2011 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef SPEEDTESTS_HEADER
#define SPEEDTESTS_HEADER

#include <string>
#include "common_irrlicht.h"

class SpeedTest
{
	private:
	// These are defined global so that they're not optimized too much.
	// Can't change them to volatile.
	s16 temp16;
	f32 tempf;
	v3f tempv3f1;
	v3f tempv3f2;
	std::string tempstring;
	std::string tempstring2;

	public:
	void SpeedTests();
};

#endif
