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
		//notes->at(0) = MI; notes->at(4) = REST; notes->at(8) = MI; notes->at(12) = REST;

		int barLoop = currentBar % thisLevelData->numBarLoop;
		Cadence currentCadence = thisLevelData->cadenceLoop[barLoop];
		bool isFinalBar = (barLoop == thisLevelData->numBarLoop - 1);
		std::vector<int> thisRhythm(tNum, 0);
		NoteName lastPC = inputInfo[3 * tNum / 4];

		// Calculate rhythm
		for (int i = 0; i < tNum; i++) {
			switch (thisLevelData->rhythmIntensity[i]) {
			case 0: break;
			case 1: 
				thisRhythm[i] = 1;
				break;
			case 2:
				if (isFinalBar) break;
				thisRhythm[i] = 1;
				break;
			case 3: 
				if (isFinalBar) break;
				thisRhythm[i] = rand() % 2; // test
				break;
			default: 
				break;
			}
		}

		// calculate element
		for (int i = 0; i < tNum; i++) {
			int lastPrincipleNoteIndex = 0;
			
			if (i % 4 == 0) { // PC
				int tendency = rand() % 3 - 1;
				if (thisRhythm[i] == 1) {
					if (i == 0) {
						lastPrincipleNoteIndex = tendency + 1;
						notes->at(i) = _CadenceNoteMap_[currentCadence][lastPrincipleNoteIndex];
					} else {
						if (lastPrincipleNoteIndex == 0 && tendency == -1) {
							lastPrincipleNoteIndex += 3;
							parts->at(i) = getLowerPart(parts->at(i - 4));
						} else if (lastPrincipleNoteIndex == 2 && tendency == 1) {
							lastPrincipleNoteIndex -= 3;
							parts->at(i) = getHigherPart(parts->at(i - 4));
						}
						lastPrincipleNoteIndex = lastPrincipleNoteIndex + tendency;
						notes->at(i) = _CadenceNoteMap_[currentCadence][lastPrincipleNoteIndex];
					}
				}

			} else { // other
				parts->at(i) = parts->at(i - 1);

				if (thisRhythm[i] == 1) {
					// test random
					int a = rand() % 5 + 1;
					if (a == 4) a = 6;
					notes->at(i) = static_cast<NoteName>(a);
				}
			}
		}
		if (isFinalBar) {
			notes->at(tNum / 2) = static_cast<NoteName>(currentCadence);
		}

		

		// TODO
	}

	int AudioComposer::getNextBGMIndex(int currentBar) const {
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

	PartName AudioComposer::getHigherPart(PartName currentPart) {
		switch (currentPart) {
		case LOW: return MED;
		case MED: return HI;
		case HI: return HI;
		default: return HI;
		}
	}

	PartName AudioComposer::getLowerPart(PartName currentPart) {
		switch (currentPart) {
		case LOW: return LOW;
		case MED: return LOW;
		case HI: return MED;
		default: return LOW;
		}
	}

}
