#include "ZSLogicGameState.h"
#include "Threading/MqMessages.h"
#include "AudioSystem.h"
#include "LevelManager.h"
#include <SDL.h>
#include "Enemy.h"
#include "Path.h"
#include "OgreStringVector.h"

namespace ZS {

	ZSLogicGameState::ZSLogicGameState() :
		mLogicSystem(nullptr),
		gm(GameMaster::GetInstance()),
		levelManager(nullptr)
	{
		
	}

	ZSLogicGameState::~ZSLogicGameState() {
	}
	  
	void ZSLogicGameState::createScene01() {
		levelManager = gm->getLevelManager();
	}

	void ZSLogicGameState::createScene02() {

	}

	void ZSLogicGameState::update(float timeSinceLast) {
		const size_t currIdx = mLogicSystem->getCurrentTransformIdx();
		const size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		if(levelManager->levelState == LST_PLAY) {
			levelManager->update(currIdx, timeSinceLast);
		}

		GameState::update(timeSinceLast);
	}
}
