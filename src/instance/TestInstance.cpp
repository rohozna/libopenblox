/*
 * Copyright (C) 2016 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox.	 If not, see <https://www.gnu.org/licenses/>.
 */

#include "instance/TestInstance.h"

namespace OB{
	namespace Instance{
		DEFINE_CLASS(TestInstance, true, false, Instance){
			registerLuaClass(LuaClassName, register_lua_metamethods, register_lua_methods, register_lua_property_getters, register_lua_property_setters, register_lua_events);
		}

		TestInstance::TestInstance(){
			Name = ClassName;
		}

		TestInstance::~TestInstance(){}

		Instance* TestInstance::cloneImpl(){
			TestInstance* ti = new TestInstance;
			ti->Archivable = Archivable;
			ti->Name = Name;
			ti->ParentLocked = ParentLocked;//Hah, that'd be amusing
			return ti;
		}
	}
}
