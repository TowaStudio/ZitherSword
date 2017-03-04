#include "ZSLogicGameState.h"
#include "Threading/MqMessages.h"
#include <SDL.h>

namespace ZS {

	ZSLogicGameState::ZSLogicGameState() :
		mLogicSystem(nullptr),
		gm(GameMaster::GetInstance())
	{

	}

	ZSLogicGameState::~ZSLogicGameState() {
	}
	  
	void ZSLogicGameState::createScene01() {
		gm->log("Start in createScrene01");
	}

	void ZSLogicGameState::update(float timeSinceLast) {

		GameState::update(timeSinceLast);
	}

	void ZSLogicGameState::keyReleased(const SDL_KeyboardEvent& arg) {
		//gm->log(Ogre::StringConverter::toString(arg.keysym.sym));
		if(arg.keysym.sym == SDLK_l) {
			gm->load();
			gm->loadLevel(0);
		} else {
			GameState::keyPressed(arg);
		}
	}
}
