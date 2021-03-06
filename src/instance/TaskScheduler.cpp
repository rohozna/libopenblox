/*
 * Copyright (C) 2017 John M. Harris, Jr. <johnmh@openblox.org>
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

#include "instance/TaskScheduler.h"

#include "TaskScheduler.h"

namespace OB{
	namespace Instance{
		DEFINE_CLASS(TaskScheduler, false, isDataModel, Instance){
			registerLuaClass(eng, LuaClassName, register_lua_metamethods, register_lua_methods, register_lua_property_getters, register_lua_property_setters, register_lua_events);
		}

	    TaskScheduler::TaskScheduler(OBEngine* eng) : Instance(eng){
			Name = ClassName;
			netId = OB_NETID_NOT_REPLICATED;

			Archivable = false;
		}

	    TaskScheduler::~TaskScheduler(){}

		shared_ptr<Instance> TaskScheduler::cloneImpl(){
			return NULL;
		}

		int TaskScheduler::getNumSleepingJobs(){
			shared_ptr<OB::TaskScheduler> taskSched = eng->getTaskScheduler();
			if(taskSched){
				return taskSched->GetNumSleepingJobs();
			}
			return -1;
		}

		int TaskScheduler::getNumWaitingJobs(){
			shared_ptr<OB::TaskScheduler> taskSched = eng->getTaskScheduler();
			if(taskSched){
				return taskSched->GetNumWaitingJobs();
			}
			return -1;
		}

		#if HAVE_PUGIXML
	    std::string TaskScheduler::serializedID(){
			shared_ptr<OBSerializer> serializer = eng->getSerializer();
			serializer->SetID(shared_from_this(), getClassName());
			
			return Instance::serializedID();
		}
		#endif

		std::map<std::string, _PropertyInfo> TaskScheduler::getProperties(){
			std::map<std::string, _PropertyInfo> propMap = Instance::getProperties();
			propMap["NumSleepingJobs"] = {"int", true, true, false};
			propMap["NumWaitingJobs"] = {"int", true, true, false};

			return propMap;
		}

		shared_ptr<Type::VarWrapper> TaskScheduler::getProperty(std::string prop){
			if(prop == "NumSleepingJobs"){
				return make_shared<Type::VarWrapper>(getNumSleepingJobs());
			}
			if(prop == "NumWaitingJobs"){
				return make_shared<Type::VarWrapper>(getNumWaitingJobs());
			}
			
			return Instance::getProperty(prop);
		}

		int TaskScheduler::lua_getNumSleepingJobs(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1, false);
			
			if(inst){
				shared_ptr<TaskScheduler> instTS = dynamic_pointer_cast<TaskScheduler>(inst);
				if(instTS){
					lua_pushinteger(L, instTS->getNumSleepingJobs());
					return 1;
				}
			}
			
			lua_pushnil(L);
			return 1;
		}

		int TaskScheduler::lua_getNumWaitingJobs(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1, false);
			
			if(inst){
				shared_ptr<TaskScheduler> instTS = dynamic_pointer_cast<TaskScheduler>(inst);
				if(instTS){
					lua_pushinteger(L, instTS->getNumWaitingJobs());
					return 1;
				}
			}
			
			lua_pushnil(L);
			return 1;
		}

	    void TaskScheduler::register_lua_property_setters(lua_State* L){
			Instance::register_lua_property_setters(L);
			
			luaL_Reg properties[] = {
			    {"NumSleepingJobs", lua_readOnlyProperty},
				{"NumWaitingJobs", lua_readOnlyProperty},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}

		void TaskScheduler::register_lua_property_getters(lua_State* L){
			Instance::register_lua_property_getters(L);
			
			luaL_Reg properties[] = {
				{"NumSleepingJobs", lua_getNumSleepingJobs},
				{"NumWaitingJobs", lua_getNumWaitingJobs},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}
	}
}
