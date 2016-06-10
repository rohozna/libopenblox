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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "OBEngine.h"

#include "OBException.h"
#include "utility.h"

#include <irrlicht/irrlicht.h>

namespace OB{
    OBEngine* OBEngine::inst = NULL;

	OBEngine::OBEngine(){
		if(inst != NULL){
			throw new OBException("Only one instance of OBEngine can exist.");
		}
		inst = this;

		initialized = false;
		startTime = currentTimeMillis();
		_isRunning = true;

		doRendering = true;
		startWidth = 640;
		startHeight = 480;
		vsync = false;

		globalState = NULL;

		windowId = NULL;
		irrDev = NULL;
		irrDriv = NULL;
		irrSceneMgr = NULL;

		logger = new OBLogger();
	}

	OBEngine::~OBEngine(){}

	OBEngine* OBEngine::getInstance(){
		return inst;
	}

	void OBEngine::init(){
	    if(doRendering){
			irr::SIrrlichtCreationParameters p;
			p.DriverType = irr::video::EDT_OPENGL;

			p.WindowSize = irr::core::dimension2d<irr::u32>(startWidth,
															startHeight);
			p.Vsync = vsync;
			p.WindowId = windowId;

			p.LoggingLevel = irr::ELL_WARNING;

			irrDev = irr::createDeviceEx(p);

			if(!irrDev){
				throw new OBException("Failed to create Irrlicht Device");
			}

			irrDev->setWindowCaption(L"OpenBlox");

			irrDriv = irrDev->getVideoDriver();
			irrSceneMgr = irrDev->getSceneManager();
		}
	}

	bool OBEngine::isRunning(){
		return _isRunning;
	}

	void OBEngine::tick(){
	    if(doRendering){
			if(!irrDev->run()){
				_isRunning = false;
				return;//Early return, we're not running anymore!
			}
		}
		//TODO: stub
	}

	void OBEngine::render(){
		if(doRendering){
			irrDriv->beginScene(true, true, irr::video::SColor(255, 0, 255, 0));
			irrSceneMgr->drawAll();
			irrDriv->endScene();
		}
   	}

	lua_State* OBEngine::getGlobalLuaState(){
		return globalState;
	}

	ob_int64 OBEngine::getStartTime(){
		return startTime;
	}

    bool OBEngine::doesRendering(){
		return doRendering;
	}

	void OBEngine::setRendering(bool renders){
		if(initialized){
			throw new OBException("You can't setRendering after init is called.");
		}
		doRendering = renders;
	}

	int OBEngine::getInitWidth(){
		return startWidth;
	}

	void OBEngine::setInitWidth(int w){
		if(initialized){
			throw new OBException("You can't setRendering after init is called.");
		}
		startWidth = w;
	}

	int OBEngine::getInitHeight(){
		return startHeight;
	}

	void OBEngine::setInitHeight(int h){
		if(initialized){
			throw new OBException("You can't setRendering after init is called.");
		}
		startHeight = h;
	}

	bool OBEngine::getUseVsync(){
		return vsync;
	}

	void OBEngine::setUseVsync(bool useVsync){
		if(initialized){
			throw new OBException("You can't setRendering after init is called.");
		}
		vsync = useVsync;
	}

	void* OBEngine::getWindowId(){
		return windowId;
	}

	void OBEngine::setWindowId(void* wId){
		if(initialized){
			throw new OBException("You can't setRendering after init is called.");
		}
		windowId = wId;
	}
}