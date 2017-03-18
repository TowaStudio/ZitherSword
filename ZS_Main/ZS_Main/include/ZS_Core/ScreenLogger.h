/**
* Project ZS
*/


#ifndef _ZS_SCREENLOGGER_H
#define _ZS_SCREENLOGGER_H

#include "ZSGraphicsGameState.h"
#include "Logger.h"
#include <string>

namespace ZS {
	class ScreenLogger : public Logger {
		
	private:
		static ScreenLogger* instance;
		std::vector<string>* logList;
		ZSGraphicsGameState* zsGraphicsGameState;
		ScreenLogger();
		ScreenLogger(Logger const&) {}
		ScreenLogger& operator= (ScreenLogger const&) {}
		
	public:
		static ScreenLogger* GetInstance();
		void log(string content) override;
		void log(int content) override;
		void log(float content) override;
		void bindGraphicsGameState(ZSGraphicsGameState* _zsGraphicsGameState);

	};
}

#endif
