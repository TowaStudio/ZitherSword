#include "ZSLogicGameState.h"
#include "Threading/MqMessages.h"

namespace ZS {

	ZSLogicGameState::ZSLogicGameState() :
		mLogicSystem(0)	
	{
	}

	ZSLogicGameState::~ZSLogicGameState() {
	}

	void ZSLogicGameState::createScene01() {
	}

	void ZSLogicGameState::update(float timeSinceLast) {

		GameState::update(timeSinceLast);
	}
}
