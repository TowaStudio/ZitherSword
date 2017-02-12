/**
 * Project ZS
 */

#ifndef _AUDIOSYSTEM_H
#define _AUDIOSYSTEM_H

#include "../JuceLibraryCode/JuceHeader.h"

namespace ZS {
	class AudioSystem : public Timer{
	private:
		static AudioSystem* instance;
		AudioSystem();
		AudioSystem(AudioSystem const&) {};
		AudioSystem& operator= (AudioSystem const&) {};

		void timerCallback() override;

	public:
		static AudioSystem* GetInstance() {
			return instance;
		}

		bool timerStarted; // read only

		enum UserInput
		{
			Idle = 0,
			Do = 1, 
			Re = 2, 
			Mi = 3,
			So = 5, 
			La = 6
		};

		//void timerStart() {
		//	startTimer(1000);
		//};

		void input(UserInput inputKey);

		int time;
	};
}

#endif //_AUDIOSYSTEM_H
