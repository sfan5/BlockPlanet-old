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

#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#include "common_irrlicht.h"
#include <string>
#include <jthread.h>
#include <jmutex.h>
#include <jmutexautolock.h>
#include "strfnd.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "debug.h"
#include "utility.h"
#include "log.h"

enum ValueType
{
	VALUETYPE_STRING,
	VALUETYPE_FLAG // Doesn't take any arguments
};

struct ValueSpec
{
	ValueSpec(ValueType a_type, const char *a_help=NULL)
	{
		type = a_type;
		help = a_help;
	}
	ValueType type;
	const char *help;
};

class Settings
{
public:
	Settings()
	{
		m_mutex.Init();
	}

	void writeLines(std::ostream &os);

	bool parseConfigLine(const std::string &line);

	void parseConfigLines(std::istream &is, const std::string &endstring);

	bool parseConfigObject(std::istream &is);

	/*
		Description: Reads a configuration file
		Returns: True on success
	*/
	bool readConfigFile(const char *filename);

	/*
		Description: Reads a configuration object from stream (usually a single line)
			and adds it to dst.

		Notes: Preserves comments and empty lines.
			Settings that were added to dst are also added to updated.
			key of updated is setting name, value of updated is dummy.

		Returns: False on EOF
	*/
	bool getUpdatedConfigObject(std::istream &is,
			core::list<std::string> &dst,
			core::map<std::string, bool> &updated,
			bool &value_changed);

	/*
		Updates configuration file

		Returns true on success
	*/
	bool updateConfigFile(const char *filename);

	/*
		NOTE: Types of allowed_options are ignored

		returns true on success
	*/
	bool parseCommandLine(int argc, char *argv[],
			core::map<std::string, ValueSpec> &allowed_options);

	void set(std::string name, std::string value);

	void set(std::string name, const char *value);


	void setDefault(std::string name, std::string value);

	bool exists(std::string name);

	std::string get(std::string name);

	bool getBool(std::string name);
	
	bool getFlag(std::string name);

	bool getBoolAsk(std::string name, std::string question, bool def);

	float getFloat(std::string name);
	
	u16 getU16(std::string name);

	u16 getU16Ask(std::string name, std::string question, u16 def);

	s16 getS16(std::string name);

	s32 getS32(std::string name);

	v3f getV3F(std::string name);

	v2f getV2F(std::string name);

	u64 getU64(std::string name);


	void setBool(std::string name, bool value);
	
	void setS32(std::string name, s32 value);

	void setFloat(std::string name, float value);

	void setV3F(std::string name, v3f value);

	void setV2F(std::string name, v2f value);

	void setU64(std::string name, u64 value);

	void clear();

	void updateValue(Settings &other, const std::string &name);

	void update(Settings &other);

	Settings & operator+=(Settings &other);

	Settings & operator=(Settings &other);

private:
	core::map<std::string, std::string> m_settings;
	core::map<std::string, std::string> m_defaults;
	// All methods that access m_settings/m_defaults directly should lock this.
	JMutex m_mutex;
};

#endif

