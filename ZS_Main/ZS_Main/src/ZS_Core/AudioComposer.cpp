/**
* Project ZS
*/
#include "AudioComposer.h"
#include <ctime>

namespace ZS {
	/**
	* AudioComposer implementation
	*/
	AudioComposer::AudioComposer(){
		srand(time(nullptr));

		// setup
		setupComposer();
	}

	void AudioComposer::setupComposer(int _currentLevel, int _tNum){
		currentLevel = _currentLevel;
		tNum = _tNum;
		thisLevelData = &(_LevelData_[currentLevel]);
	}

	void AudioComposer::getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar){
		*notes = NoteSeq(16, REST);
		*parts = PartSeq(16, MED);
		// test
		notes->at(0) = MI; notes->at(4) = REST; notes->at(8) = MI; notes->at(12) = REST;

		Cadence currentCadence = thisLevelData->cadenceLoop[currentBar % thisLevelData->numBarLoop];

		// TODO
	}

	int AudioComposer::getNextBGMIndex(int currentBar){
		if (currentBar < 0) {
			return -1; // not yet start main music
		}
		if (currentBar % 8 == 0) {
			int barInLoop = currentBar % thisLevelData->numBarLoop;
			return barInLoop / 8 + 1;
		} 
		return -1;
	}

	void AudioComposer::getRandomNearNote(NoteName *notePtr, PartName *partPtr, NoteName noteInput, PartName partInput, int d) {
		int num = rand() % d + 1;
		int sign = (rand() % 2) * 2 - 1;

	}

}
