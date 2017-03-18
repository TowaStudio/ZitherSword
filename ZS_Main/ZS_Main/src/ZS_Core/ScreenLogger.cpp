/**
* Project ZS
*/


#include "ScreenLogger.h"

namespace ZS {
	ScreenLogger* ScreenLogger::instance = new ScreenLogger();

	ScreenLogger::ScreenLogger() :
		zsGraphicsGameState(nullptr)
	{
		logList = new std::vector<string>();
	}

	ScreenLogger* ScreenLogger::GetInstance() {
		return instance;
	}

	void ScreenLogger::log(string content) {
		logList->push_back(content);
		zsGraphicsGameState->log(content);
	}

	void ScreenLogger::log(int content) {
		logList->push_back(Ogre::StringConverter::toString(content));
		zsGraphicsGameState->log(Ogre::StringConverter::toString(content));
	}

	void ScreenLogger::log(float content) {
		logList->push_back(Ogre::StringConverter::toString(content));
		zsGraphicsGameState->log(Ogre::StringConverter::toString(content));
	}

	void ScreenLogger::bindGraphicsGameState(ZSGraphicsGameState* _zsGraphicsGameState) {
		zsGraphicsGameState = _zsGraphicsGameState;
	}
}
