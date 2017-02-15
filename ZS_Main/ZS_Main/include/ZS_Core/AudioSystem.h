/**
 * Project ZS
 */

#ifndef _AUDIOSYSTEM_H
#define _AUDIOSYSTEM_H

#include "../JuceLibraryCode/JuceHeader.h"

namespace ZS {
	enum NoteName {
		REST = 0,
		DO = 1,
		RE = 2,
		MI = 3,
		FA = 4,
		SO = 5,
		LA = 6,
		SI = 7
	};
	struct Note {
		NoteName name = REST;
		float value = 1; // 1 = 1 meter
		float startMoment = 0; // 1 = 1 meter
		int barNum = 1;
	};


	class AudioSystem : public Timer{
	public:
		static AudioSystem* GetInstance() {
			return instance;
		}

		void musicSetup(int timePerBeat, int beatsPerBar);
		void startMusic(); 
		void stopMusic();
		void input(NoteName inputKey);

		// get
		float getBpm() {
			return bpm;
		}
		float getTolerance() {
			return tolerance;
		}


	private:
		int bpm; // beats per minute
		int bpb; // beats per bar

		float tolerance; // 0: no tolerance - 0.5: full tolerance 
		int tpb; // ticks per beat
		int interval;
		int thresTime;


		//int64 startTime;
		int currentBarNum; // the current number of bar
		int currentTickNum; // the current number of tick within a bar
		int64 currentTickTime; 
		//int64 nextTickTime;

		void inputJudge(int64 currentTime, NoteName noteName);
		void recordNote(int tickNum, NoteName noteName);

		static AudioSystem* instance;
		AudioSystem();
		AudioSystem(AudioSystem const&) {};
		AudioSystem& operator= (AudioSystem const&) {};

		void timerCallback() override;

	};
}

#endif //_AUDIOSYSTEM_H
