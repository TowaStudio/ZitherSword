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
		*parts = PartSeq(16, HI);
		// test
		notes->at(0) = MI; notes->at(4) = MI; notes->at(8) = MI; notes->at(12) = MI;

		// TODO
	}

	int AudioComposer::getNextBGMIndex(){
		return 0;
		// TODO
	}
}
