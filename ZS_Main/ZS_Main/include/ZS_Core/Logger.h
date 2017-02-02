/**
* Project ZS
*/


#ifndef _LOGGER_H
#define _LOGGER_H

#include "Ogre.h"
using namespace std;

namespace ZS {
	class Logger {

	private:
		static Logger* instance;
		Logger();
		Logger(Logger const&) {};
		Logger& operator= (Logger const&) {};


	public:
		static Logger* GetInstance() {
			return instance;
		}

		virtual void Log(string str) = 0;

	};
}

#endif //_GAMEMASTER_H