/**
* Project ZS
*/


#ifndef _ZS_LOGGER_H
#define _ZS_LOGGER_H

#include "Ogre.h"
using namespace std;

namespace ZS {
	class Logger {
	protected:
		static Logger* instance;
		Logger() {}
		Logger(Logger const&) {}
		Logger& operator= (Logger const&) {}

	public:
		static Logger* GetInstance() {
			return instance;
		}

		virtual void log(string str) = 0;

	};
}

#endif //_GAMEMASTER_H