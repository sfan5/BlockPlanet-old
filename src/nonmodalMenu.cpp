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

#include "nonmodalMenu.h"
#include "common_irrlicht.h"

GUIMenu::GUIMenu(gui::IGUIEnvironment* env,
			gui::IGUIElement* parent, s32 id,
		INonModalMenuManager *menumgr):
			IGUIElement(gui::EGUIET_ELEMENT, env, parent, id,
				core::rect<s32>(0,0,100,100))
{
	//m_force_regenerate_gui = false;

	m_menumgr = menumgr;
	m_allow_focus_removal = false;
	m_screensize_old = v2u32(0,0);

	setVisible(true);
	Environment->setFocus(this);
	m_menumgr->createdMenu(this);
}

GUIMenu::~GUIMenu()
{
	m_menumgr->deletingMenu(this);
}

void GUIMenu::allowFocusRemoval(bool allow)
{
	m_allow_focus_removal = allow;
}

bool GUIMenu::canTakeFocus(gui::IGUIElement *e)
{
	return true;
}

void GUIMenu::draw()
{
	if(!IsVisible)
	{
		return;
	}

	video::IVideoDriver* driver = Environment->getVideoDriver();
	v2u32 screensize = driver->getScreenSize();
	if(screensize != m_screensize_old /*|| m_force_regenerate_gui*/)
	{
		m_screensize_old = screensize;
		regenerateGui(screensize);
		//m_force_regenerate_gui = false;
	}

	drawMenu();
}

void GUIMenu::quitMenu()
{
	allowFocusRemoval(true);
	// This removes Environment's grab on us
	Environment->removeFocus(this);
	this->remove();
}

void GUIMenu::removeChildren()
{
	const core::list<gui::IGUIElement*> &children = getChildren();
	core::list<gui::IGUIElement*> children_copy;
	for(core::list<gui::IGUIElement*>::ConstIterator
			i = children.begin(); i != children.end(); i++)
	{
		children_copy.push_back(*i);
	}
	for(core::list<gui::IGUIElement*>::Iterator
			i = children_copy.begin();
			i != children_copy.end(); i++)
	{
		(*i)->remove();
	}
}
