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
		gm(GameMaster::GetInstance())
	{
		entities = new GameEntityVec();
	}

	ZSLogicGameState::~ZSLogicGameState() {
	}
	  
	void ZSLogicGameState::createScene01() {
		gm->log("Start in createScrene01");

	}

	void ZSLogicGameState::createScene02() {

	}

	void ZSLogicGameState::update(float timeSinceLast) {
		const size_t currIdx = mLogicSystem->getCurrentTransformIdx();
		const size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		for(auto itr = entities->begin(), end = entities->end(); itr != end; ++itr) {
			if((*itr)->behaviour)
				(*itr)->behaviour->update(timeSinceLast);
		}

		GameState::update(timeSinceLast);
	}
}
