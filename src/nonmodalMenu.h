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

#ifndef MENU_HEADER
#define MENU_HEADER

#include "common_irrlicht.h"

class GUIMenu;

class INonModalMenuManager
{
public:
	// A GUIMenu calls these when this class is passed as a parameter
	virtual void createdMenu(GUIMenu *menu) = 0;
	virtual void deletingMenu(GUIMenu *menu) = 0;
};

/*
	Remember to drop() the menu after creating, so that it can
	remove itself when it wants to.
*/

class GUIMenu : public gui::IGUIElement
{
public:
	GUIMenu(gui::IGUIEnvironment* env,
			gui::IGUIElement* parent, s32 id,
			INonModalMenuManager *menumgr);

	virtual ~GUIMenu();

	void allowFocusRemoval(bool allow);

	bool canTakeFocus(gui::IGUIElement *e);

	void draw();
	
	/*
		This should be called when the menu wants to quit.

		WARNING: THIS DEALLOCATES THE MENU FROM MEMORY. Return
		immediately if you call this from the menu itself.
	*/
	void quitMenu();

	void removeChildren();

	virtual void regenerateGui(v2u32 screensize) = 0;
	virtual void drawMenu() = 0;
	virtual bool OnEvent(const SEvent& event) { return false; };

protected:
	//bool m_force_regenerate_gui;
	v2u32 m_screensize_old;
private:
	INonModalMenuManager *m_menumgr;
	// This might be necessary to expose to the implementation if it
	// wants to launch other menus
	bool m_allow_focus_removal;
};


#endif

