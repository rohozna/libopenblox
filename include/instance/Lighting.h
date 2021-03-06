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

#include "instance/Instance.h"

#include "type/Color3.h"

#ifndef OB_INST_LIGHTING
#define OB_INST_LIGHTING

namespace OB{
	namespace Instance{
		/**
		 * Lighting provides access to lighting related options as well as
		 * ambient colors and similar properties.
		 *
		 * @author John M. Harris, Jr.
		 */
		class Lighting: public Instance{
			public:
			    Lighting(OBEngine* eng);
				virtual ~Lighting();

				#if HAVE_PUGIXML
				virtual std::string serializedID();
				#endif

				shared_ptr<Type::Color3> getSkyColor();
				void setSkyColor(shared_ptr<Type::Color3> skyColor);

				bool isSkyTransparent();
				void setSkyTransparent(bool skyTransparent);

				bool isFogEnabled();
				void setFogEnabled(bool fogEnabled);

				shared_ptr<Type::Color3> getFogColor();
				void setFogColor(shared_ptr<Type::Color3> fogColor);

				float getFogStart();
				void setFogStart(float fogStart);

			    float getFogEnd();
				void setFogEnd(float fogEnd);

				#if HAVE_ENET
				/**
				 * Replicates properties of this Instance.
				 * 
				 * @param peer Peer
				 * @author John M. Harris, Jr.
				 */
				virtual void replicateProperties(shared_ptr<NetworkReplicator> peer);
				#endif

				virtual std::map<std::string, _PropertyInfo> getProperties();
				virtual shared_ptr<Type::VarWrapper> getProperty(std::string prop);
				virtual void setProperty(std::string prop, shared_ptr<Type::VarWrapper> val);

				DECLARE_LUA_METHOD(getSkyColor);
				DECLARE_LUA_METHOD(setSkyColor);
				DECLARE_LUA_METHOD(getSkyTransparent);
				DECLARE_LUA_METHOD(setSkyTransparent);
				DECLARE_LUA_METHOD(getFogEnabled);
				DECLARE_LUA_METHOD(setFogEnabled);
				DECLARE_LUA_METHOD(getFogColor);
				DECLARE_LUA_METHOD(setFogColor);
				DECLARE_LUA_METHOD(getFogStart);
				DECLARE_LUA_METHOD(setFogStart);
				DECLARE_LUA_METHOD(getFogEnd);
				DECLARE_LUA_METHOD(setFogEnd);

				static void register_lua_property_getters(lua_State* L);
				static void register_lua_property_setters(lua_State* L);

				DECLARE_CLASS(Lighting);

				void updateFog();

				shared_ptr<Type::Color3> SkyColor;
				bool SkyTransparent;
				
				bool FogEnabled;
				shared_ptr<Type::Color3> FogColor;
			    float FogStart;
			    float FogEnd;
		};
	}
}

#endif // OB_INST_LIGHTING


// Local Variables:
// mode: c++
// End:
