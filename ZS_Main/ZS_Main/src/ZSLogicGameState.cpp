#include "ZSLogicGameState.h"
#include "Threading/MqMessages.h"

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
		gm->load();
		gm->loadLevel(0);
	}

	void ZSLogicGameState::update(float timeSinceLast) {

		GameState::update(timeSinceLast);
	}
}
