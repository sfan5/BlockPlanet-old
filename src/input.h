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

#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "common_irrlicht.h"
#include "keycode.h"
#include "game.h"

#ifndef SERVER

/*
	Event handler for Irrlicht

	NOTE: Everything possible should be moved out from here,
	      probably to InputHandler and the_game
*/

class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);

	bool IsKeyDown(const KeyPress &keyCode) const;
	
	// Checks whether a key was down and resets the state
	bool WasKeyDown(const KeyPress &keyCode);

	s32 getMouseWheel();

	void clearInput();

	MyEventReceiver();

	bool leftclicked;
	bool rightclicked;
	bool leftreleased;
	bool rightreleased;

	bool left_active;
	bool middle_active;
	bool right_active;

	s32 mouse_wheel;

private:
	IrrlichtDevice *m_device;
	
	// The current state of keys
	KeyList keyIsDown;
	// Whether a key has been pressed or not
	KeyList keyWasDown;
};

/*
	Separated input handler
*/

class RealInputHandler : public InputHandler
{
public:
	RealInputHandler(IrrlichtDevice *device, MyEventReceiver *receiver):
		m_device(device),
		m_receiver(receiver)
	{
	}
	virtual bool isKeyDown(const KeyPress &keyCode);
	virtual bool wasKeyDown(const KeyPress &keyCode);
	virtual v2s32 getMousePos();
	virtual void setMousePos(s32 x, s32 y);

	virtual bool getLeftState();
	virtual bool getRightState();
	
	virtual bool getLeftClicked();
	virtual bool getRightClicked();
	virtual void resetLeftClicked();
	virtual void resetRightClicked();

	virtual bool getLeftReleased();
	virtual bool getRightReleased();
	virtual void resetLeftReleased();
	virtual void resetRightReleased();

	virtual s32 getMouseWheel();

	void clear();
private:
	IrrlichtDevice *m_device;
	MyEventReceiver *m_receiver;
};

class RandomInputHandler : public InputHandler
{
public:
	RandomInputHandler();
	virtual bool isKeyDown(const KeyPress &keyCode);
	virtual bool wasKeyDown(const KeyPress &keyCode);
	virtual v2s32 getMousePos();
	virtual void setMousePos(s32 x, s32 y);

	virtual bool getLeftState();
	virtual bool getRightState();

	virtual bool getLeftClicked();
	virtual bool getRightClicked();
	virtual void resetLeftClicked();
	virtual void resetRightClicked();

	virtual bool getLeftReleased();
	virtual bool getRightReleased();
	virtual void resetLeftReleased();
	virtual void resetRightReleased();

	virtual s32 getMouseWheel();

	virtual void step(float dtime);

	s32 Rand(s32 min, s32 max);
private:
	KeyList keydown;
	v2s32 mousepos;
	v2s32 mousespeed;
	bool leftdown;
	bool rightdown;
	bool leftclicked;
	bool rightclicked;
	bool leftreleased;
	bool rightreleased;
};

#endif

#endif
