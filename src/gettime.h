/*
Minetest-c55
Copyright (C) 2010 celeron55, Perttu Ahola <celeron55@gmail.com>

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

#ifndef GETTIME_HEADER
#define GETTIME_HEADER

#include "common_irrlicht.h"

/*
	Get a millisecond counter value.
	Precision depends on implementation.
	Overflows at any value above 10000000.

	Implementation of this is done in:
		Normal build: main.cpp
		Server build: servermain.cpp
*/
extern u32 getTimeMs();

/*
	Timestamp stuff
*/

#include <time.h>
#include <string>

inline std::string getTimestamp()
{
	time_t t = time(NULL);
	// This is not really thread-safe but it won't break anything
	// except its own output, so just go with it.
	struct tm *tm = localtime(&t);
	char cs[20];
	strftime(cs, 20, "%H:%M:%S", tm);
	return cs;
}

#ifdef SERVER

u32 getTimeMs();

#else

// A small helper class
class TimeGetter
{
public:
	virtual u32 getTime() = 0;
};

// A precise irrlicht one
class IrrlichtTimeGetter: public TimeGetter
{
public:
	IrrlichtTimeGetter(IrrlichtDevice *device):
		m_device(device)
	{}
	u32 getTime();
private:
	IrrlichtDevice *m_device;
};
// Not so precise one which works without irrlicht
class SimpleTimeGetter: public TimeGetter
{
public:
	u32 getTime();
};

// A pointer to a global instance of the time getter
// TODO: why?
TimeGetter *g_timegetter = NULL;

u32 getTimeMs();

#endif


#endif
