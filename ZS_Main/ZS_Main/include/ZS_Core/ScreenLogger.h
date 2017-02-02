/**
* Project ZS
*/


#ifndef _SCREENLOGGER_H
#define _SCREENLOGGER_H

#include "Logger.h"

namespace ZS {
	class ScreenLogger : public Logger {

	public:
		void Log(string str) override;
	};
}

#endif
