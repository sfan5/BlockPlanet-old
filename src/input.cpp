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

#include "input.h"
#include "utility.h"

bool MyEventReceiver::IsKeyDown(const KeyPress &keyCode) const
{
	return keyIsDown[keyCode];
}

// Checks whether a key was down and resets the state
bool MyEventReceiver::WasKeyDown(const KeyPress &keyCode)
{
	bool b = keyWasDown[keyCode];
	if (b)
	{
		keyWasDown.unset(keyCode);
	}
	return b;
}

s32 MyEventReceiver::getMouseWheel()
{
	s32 a = mouse_wheel;
	mouse_wheel = 0;
	return a;
}

void MyEventReceiver::clearInput()
{
	keyIsDown.clear();
	keyWasDown.clear();

	leftclicked = false;
	rightclicked = false;
	leftreleased = false;
	rightreleased = false;

	left_active = false;
	middle_active = false;
	right_active = false;

	mouse_wheel = 0;
}

MyEventReceiver::MyEventReceiver()
{
	clearInput();
}


bool RealInputHandler::isKeyDown(const KeyPress &keyCode)
{
	return m_receiver->IsKeyDown(keyCode);
}
bool RealInputHandler::wasKeyDown(const KeyPress &keyCode)
{
	return m_receiver->WasKeyDown(keyCode);
}
v2s32 RealInputHandler::getMousePos()
{
	return m_device->getCursorControl()->getPosition();
}
void RealInputHandler::setMousePos(s32 x, s32 y)
{
	m_device->getCursorControl()->setPosition(x, y);
}

bool RealInputHandler::getLeftState()
{
	return m_receiver->left_active;
}
bool RealInputHandler::getRightState()
{
	return m_receiver->right_active;
}

bool RealInputHandler::getLeftClicked()
{
	return m_receiver->leftclicked;
}
bool RealInputHandler::getRightClicked()
{
	return m_receiver->rightclicked;
}
void RealInputHandler::resetLeftClicked()
{
	m_receiver->leftclicked = false;
}
void RealInputHandler::resetRightClicked()
{
	m_receiver->rightclicked = false;
}

bool RealInputHandler::getLeftReleased()
{
	return m_receiver->leftreleased;
}
bool RealInputHandler::getRightReleased()
{
	return m_receiver->rightreleased;
}
void RealInputHandler::resetLeftReleased()
{
	m_receiver->leftreleased = false;
}
void RealInputHandler::resetRightReleased()
{
	m_receiver->rightreleased = false;
}

s32 RealInputHandler::getMouseWheel()
{
	return m_receiver->getMouseWheel();
}

void RealInputHandler::clear()
{
	m_receiver->clearInput();
}


RandomInputHandler::RandomInputHandler()
{
	leftdown = false;
	rightdown = false;
	leftclicked = false;
	rightclicked = false;
	leftreleased = false;
	rightreleased = false;
	keydown.clear();
}
bool RandomInputHandler::isKeyDown(const KeyPress &keyCode)
{
	return keydown[keyCode];
}
bool RandomInputHandler::wasKeyDown(const KeyPress &keyCode)
{
	return false;
}
v2s32 RandomInputHandler::getMousePos()
{
	return mousepos;
}
void RandomInputHandler::setMousePos(s32 x, s32 y)
{
	mousepos = v2s32(x,y);
}

bool RandomInputHandler::getLeftState()
{
	return leftdown;
}
bool RandomInputHandler::getRightState()
{
	return rightdown;
}

bool RandomInputHandler::getLeftClicked()
{
	return leftclicked;
}
bool RandomInputHandler::getRightClicked()
{
	return rightclicked;
}
void RandomInputHandler::resetLeftClicked()
{
	leftclicked = false;
}
void RandomInputHandler::resetRightClicked()
{
	rightclicked = false;
}

bool RandomInputHandler::getLeftReleased()
{
	return leftreleased;
}
bool RandomInputHandler::getRightReleased()
{
	return rightreleased;
}
void RandomInputHandler::resetLeftReleased()
{
	leftreleased = false;
}
void RandomInputHandler::resetRightReleased()
{
	rightreleased = false;
}

s32 RandomInputHandler::getMouseWheel()
{
	return 0;
}

void RandomInputHandler::step(float dtime)
{
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 40);
			keydown.toggle(getKeySetting("keymap_jump"));
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 40);
			keydown.toggle(getKeySetting("keymap_special1"));
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 40);
			keydown.toggle(getKeySetting("keymap_forward"));
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 40);
			keydown.toggle(getKeySetting("keymap_left"));
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 20);
			mousespeed = v2s32(Rand(-20,20), Rand(-15,20));
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 30);
			leftdown = !leftdown;
			if(leftdown)
			{
				leftclicked = true;
			}
			if(!leftdown)
			{
				leftreleased = true;
			}
		}
	}
	{
		static float counter1 = 0;
		counter1 -= dtime;
		if(counter1 < 0.0)
		{
			counter1 = 0.1*Rand(1, 15);
			rightdown = !rightdown;
			if(rightdown)
			{
				rightclicked = true;
			}
			if(!rightdown)
			{
				rightreleased = true;
			}
		}
	}
	mousepos += mousespeed;
}

s32 RandomInputHandler::Rand(s32 min, s32 max)
{
	return (myrand()%(max-min+1))+min;
}
