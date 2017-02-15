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

	void ScreenLogger::log(string str) {
		logList->push_back(str);
		zsGraphicsGameState->log(str);
	}

	void ScreenLogger::bindGraphicsGameState(ZSGraphicsGameState* _zsGraphicsGameState) {
		zsGraphicsGameState = _zsGraphicsGameState;
	}
}
