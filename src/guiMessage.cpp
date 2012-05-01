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

#include "guiMessage.h"
#include "debug.h"
#include "serialization.h"
#include <string>
#include <IGUICheckBox.h>
#include <IGUIEditBox.h>
#include <IGUIButton.h>
#include <IGUIStaticText.h>
#include <IGUIFont.h>
#include "gettext.h"

GUIMessage::GUIMessage(gui::IGUIEnvironment* env,
		gui::IGUIElement* parent, s32 id,
		IMenuManager *menumgr, std::string text
	):
	GUIModalMenu(env, parent, id, menumgr, false),
	m_screensize(1,1),
	m_text(text)
{
	allowFocusRemoval(true);
}

GUIMessage::~GUIMessage()
{
	removeChildren();
}

void GUIMessage::removeChildren()
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

void GUIMessage::regenerateGui(v2u32 screensize)
{
	m_screensize = screensize;

	/*
		Remove stuff
	*/
	removeChildren();
	
	/*
		Calculate new sizes and positions
	*/
	core::rect<s32> rect(
			screensize.X - screensize.X/4,
			0,
			screensize.X,
			screensize.Y/4
	);
	
	DesiredRect = rect;
	recalculateAbsolutePosition(false);

	v2s32 size = rect.getSize();
	const s32 btn_height = 30;
	const s32 btn_gap = 50;
	const s32 btn_gap_hor = 50;
	const s32 btn_num = 2;
	const s32 btn_width = 140;

	/*
		Add stuff
	*/
	changeCtype("");
	{
		core::rect<s32> rect(0, 0, size.X, size.Y);
		rect = rect + v2s32(size.X/2-400/2, size.Y/2-50/2-25);
		gui::IGUIStaticText *e = 
		Environment->addStaticText(wgettext(m_text.c_str()), rect, false,
				true, this, 256);
		e->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
	}
	changeCtype("C");
}

void GUIMessage::drawMenu()
{
	gui::IGUISkin* skin = Environment->getSkin();
	if (!skin)
	{
		return;
	}
	video::IVideoDriver* driver = Environment->getVideoDriver();
	{
		video::SColor bgcolor(50,0,0,0);
		driver->draw2DRectangle(bgcolor, AbsoluteRect, &AbsoluteClippingRect);
	}

	gui::IGUIElement::draw();
}

bool GUIMessage::OnEvent(const SEvent& event)
{
	/*if(event.EventType==EET_GUI_EVENT)
	{
		if(event.GUIEvent.EventType==gui::EGET_ELEMENT_FOCUS_LOST
				&& isVisible())
		{
			if(!canTakeFocus(event.GUIEvent.Element))
			{
				dstream<<"GUIDeathScreen: Not allowing focus change."
						<<std::endl;
				// Returning true disables focus change
				return true;
			}
		}
		if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED)
		{
			switch(event.GUIEvent.Caller->getID())
			{
			case 257: // respawn
				respawn();
				quitMenu();
				return true;
			case 258: // disconnect
				m_gamecallback->disconnect();
				quitMenu();
				return true;
			}
		}
	}

	return Parent ? Parent->OnEvent(event) : false;*/
	return false;
}

