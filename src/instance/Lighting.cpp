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

#include "instance/Lighting.h"

#include "OBEngine.h"

#if HAVE_IRRLICHT
#include <irrlicht/irrlicht.h>
#endif

namespace OB{
	namespace Instance{
		DEFINE_CLASS(Lighting, false, isDataModel, Instance){
			registerLuaClass(LuaClassName, register_lua_metamethods, register_lua_methods, register_lua_property_getters, register_lua_property_setters, register_lua_events);
		}

	    Lighting::Lighting(){
			Name = ClassName;
			
			FogEnabled = false;
		}

	    Lighting::~Lighting(){}

		shared_ptr<Instance> Lighting::cloneImpl(){
			return NULL;
		}

		shared_ptr<Type::Color3> Lighting::getSkyColor(){
			return SkyColor;
		}
		
		void Lighting::setSkyColor(shared_ptr<Type::Color3> skyColor){
			if(skyColor == NULL){
				shared_ptr<Type::Color3> col3 = make_shared<Type::Color3>();
				if(!col3->equals(SkyColor)){
					SkyColor = col3;
					
					propertyChanged("SkyColor");
				}
			}else{
				if(!skyColor->equals(SkyColor)){
					SkyColor = skyColor;

					propertyChanged("SkyColor");
				}
			}
		}

		void Lighting::updateFog(){
			#if HAVE_IRRLICHT
			
		    OBEngine* eng = OBEngine::getInstance();
		  	irr::IrrlichtDevice* irrDev = eng->getIrrlichtDevice();
			if(irrDev == NULL){
				return;
			}
			irr::video::IVideoDriver* driver = irrDev->getVideoDriver();
			if(driver == NULL){
				return;
			}

			if(FogEnabled){
				irr::video::SColor irrFogCol;
				if(FogColor != NULL){
					irrFogCol = FogColor->toIrrlichtSColor();
				}else{
					irrFogCol = irr::video::SColor(255, 0, 0, 0);
				}
				
				driver->setFog(irrFogCol, irr::video::EFT_FOG_LINEAR, FogStart, FogEnd, 0, true, false);
			}else{
				driver->setFog();
			}

			#endif
		}

		bool Lighting::isFogEnabled(){
			return FogEnabled;
		}
		
		void Lighting::setFogEnabled(bool fogEnabled){
			if(FogEnabled != fogEnabled){
				FogEnabled = fogEnabled;

				propertyChanged("FogEnabled");

				updateFog();
			}
		}
		
		shared_ptr<Type::Color3> Lighting::getFogColor(){
			return FogColor;
		}
		
		void Lighting::setFogColor(shared_ptr<Type::Color3> fogColor){
			if(fogColor == NULL){
				shared_ptr<Type::Color3> col3 = make_shared<Type::Color3>();
				if(!col3->equals(FogColor)){
					FogColor = col3;

					propertyChanged("FogColor");

					updateFog();
				}
			}else{
				if(!fogColor->equals(FogColor)){
					FogColor = fogColor;

					propertyChanged("FogColor");
					
					updateFog();
				}
			}
		}

	    float Lighting::getFogStart(){
			return FogStart;
		}

		void Lighting::setFogStart(float fogStart){
			if(fogStart != FogStart){
				FogStart = fogStart;

				propertyChanged("FogStart");
				
				updateFog();
			}
		}

		float Lighting::getFogEnd(){
			return FogEnd;
		}

		void Lighting::setFogEnd(float fogEnd){
			if(fogEnd != FogEnd){
				FogEnd = fogEnd;

				propertyChanged("FogEnd");
				
				updateFog();
			}
		}

		int Lighting::lua_getSkyColor(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
				    shared_ptr<Type::Color3> col3 = instL->getSkyColor();
					if(col3){
						return col3->wrap_lua(L);
					}else{
						lua_pushnil(L);
						return 1;
					}
				}
			}
			lua_pushnil(L);
			return 1;
		}

		int Lighting::lua_setSkyColor(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
				    shared_ptr<Type::Color3> col3 = Type::checkColor3(L, 2);
					if(col3){
						instL->setSkyColor(col3);
					}else{
						if(lua_isnil(L, 2)){
							instL->setSkyColor(NULL);
						}else{
							return luaL_error(L, "bad argument #1 to '?' (Color3 expected, got %s)", lua_typename(L, 2));
						}
					}
				}
			}
			return 0;
		}

		int Lighting::lua_getFogEnabled(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					lua_pushboolean(L, instL->isFogEnabled());
					return 1;
				}
			}
			lua_pushnil(L);
			return 1;
		}

		int Lighting::lua_setFogEnabled(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					bool newV = lua_toboolean(L, 2);
					instL->setFogEnabled(newV);
				}
			}
			return 0;
		}

		int Lighting::lua_getFogColor(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
				    shared_ptr<Type::Color3> col3 = instL->getFogColor();
					if(col3){
						return col3->wrap_lua(L);
					}else{
						lua_pushnil(L);
						return 1;
					}
				}
			}
			lua_pushnil(L);
			return 1;
		}

		int Lighting::lua_setFogColor(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
				    shared_ptr<Type::Color3> col3 = Type::checkColor3(L, 2);
					if(col3){
						instL->setFogColor(col3);
					}else{
						if(lua_isnil(L, 2)){
							instL->setFogColor(NULL);
						}else{
							return luaL_error(L, "bad argument #1 to '?' (Color3 expected, got %s)", lua_typename(L, 2));
						}
					}
				}
			}
			return 0;
		}

		int Lighting::lua_getFogStart(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					lua_pushnumber(L, instL->getFogStart());
					return 1;
				}
			}
			lua_pushnil(L);
			return 1;
		}

		int Lighting::lua_setFogStart(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					float newV = luaL_checknumber(L, 2);
					instL->setFogStart(newV);
				}
			}
			return 0;
		}

		int Lighting::lua_getFogEnd(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					lua_pushnumber(L, instL->getFogEnd());
					return 1;
				}
			}
			lua_pushnil(L);
			return 1;
		}

		int Lighting::lua_setFogEnd(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1);
			if(inst){
				shared_ptr<Lighting> instL = dynamic_pointer_cast<Lighting>(inst);
				if(instL){
					float newV = luaL_checknumber(L, 2);
					instL->setFogEnd(newV);
				}
			}
			return 0;
		}

		void Lighting::register_lua_property_setters(lua_State* L){
			Instance::register_lua_property_setters(L);
			
			luaL_Reg properties[] = {
				{"SkyColor", lua_setSkyColor},
				{"FogEnabled", lua_setFogEnabled},
				{"FogColor", lua_setFogColor},
				{"FogStart", lua_setFogStart},
				{"FogEnd", lua_setFogEnd},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}

		void Lighting::register_lua_property_getters(lua_State* L){
			Instance::register_lua_property_getters(L);
			
			luaL_Reg properties[] = {
				{"SkyColor", lua_getSkyColor},
				{"FogEnabled", lua_getFogEnabled},
				{"FogColor", lua_getFogColor},
				{"FogStart", lua_getFogStart},
				{"FogEnd", lua_getFogEnd},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}
	}
}
