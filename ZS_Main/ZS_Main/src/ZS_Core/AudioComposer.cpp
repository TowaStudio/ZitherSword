/**
* Project ZS
*/
#include "AudioComposer.h"

namespace ZS {
	/**
	* AudioComposer implementation
	*/
	AudioComposer::AudioComposer(){
		// setup
		SetupComposer();
	}

	void AudioComposer::SetupComposer(int _currentLevel, int _tNum){
		currentLevel = _currentLevel;
		tNum = _tNum;
	}

	void AudioComposer::getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar){
		*notes = NoteSeq(16, REST);
		*parts = PartSeq(16, MED);
		// test
		notes->at(0) = MI; notes->at(4) = REST; notes->at(8) = MI; notes->at(12) = REST;

		// TODO
	}

	int AudioComposer::getNextBGMIndex(int currentBar){
		if (currentBar < 0) {
			return -1; // not yet start main music
		}
		if (currentBar % 8 == 0) {
			return currentBar / 8 + 1;
		} else {
			return -1;
		}
		return -1;
		// TODO
	}
}
