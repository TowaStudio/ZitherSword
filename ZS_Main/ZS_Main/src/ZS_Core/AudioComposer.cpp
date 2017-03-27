/**
* Project ZS
*/
#include "AudioComposer.h"
#include <time.h>

namespace ZS {
	/**
	* AudioComposer implementation
	*/
	AudioComposer::AudioComposer() {
		// setup
		setupComposer();
	}

	void AudioComposer::setupComposer(int _currentLevel, int _tNum) {
		currentLevel = _currentLevel;
		tNum = _tNum;
		thisLevelData = &(_AudioLevelData_[currentLevel]);
	}

	void AudioComposer::getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar) {

		srand(time(nullptr));

		*notes = NoteSeq(16, REST);
		*parts = PartSeq(16, MED);
		// test
		//notes->at(0) = MI; notes->at(4) = REST; notes->at(8) = MI; notes->at(12) = REST;

		int barLoop = currentBar % thisLevelData->numBarLoop;
		Cadence currentCadence = thisLevelData->cadenceLoop[barLoop];
		bool isFinalBar = (barLoop == thisLevelData->numBarLoop - 1);
		std::vector<int> thisRhythm(tNum, 0);
		//NoteName lastPC = inputInfo[3 * tNum / 4];

		// Calculate rhythm
		for(int i = 0; i < tNum; i++) {
			switch(thisLevelData->rhythmIntensity[i]) {
				case 0: break;
				case 1:
					thisRhythm[i] = 1;
					break;
				case 2:
					if(isFinalBar) break;
					thisRhythm[i] = 1;
					break;
				case 3:
					if(isFinalBar) break;
					if (rand()%3 == 0)
						thisRhythm[i] = 1; // 1/3
					break;
				default:
					break;
			}
		}

		// calculate element
		//int tendency = rand() % 3 - 1;
		NoteName lastNote = MI;
		for (int i = 0; i < tNum; i++) {
			if (inputInfo[tNum - 1 - i] != REST) {
				lastNote = inputInfo[tNum - 1 - i];
				break;
			}
		}
		for(int i = 0; i < tNum; i++) {
			/*int lastPrincipleNoteIndex = 0;
			
			if(i % 4 == 0) { // PC
				//int tendency = rand()%3 - 1;
				if(thisRhythm[i] == 1) {
					if(i == 0) {
						lastPrincipleNoteIndex = tendency + 1;
						notes->at(i) = _CadenceNoteMap_[currentCadence][lastPrincipleNoteIndex];
					} else {
						if(lastPrincipleNoteIndex == 0 && tendency == -1) {
							lastPrincipleNoteIndex += 3;
							parts->at(i) = getLowerPart(parts->at(i - 4));
						} else if(lastPrincipleNoteIndex == 2 && tendency == 1) {
							lastPrincipleNoteIndex -= 3;
							parts->at(i) = getHigherPart(parts->at(i - 4));
						}
						lastPrincipleNoteIndex = lastPrincipleNoteIndex + tendency;
						notes->at(i) = _CadenceNoteMap_[currentCadence][lastPrincipleNoteIndex];
					}
				}
				tendency = rand() % 3 - 1;

			} else { // other
				parts->at(i) = parts->at(i - 1);

				if(thisRhythm[i] == 1) {
					// test random
					//int a = rand()%5 + 1;
					//if(a == 4) a = 6;
					//notes->at(i) = static_cast<NoteName>(a);
					NoteName lastPCNote = notes->at(i / 4 * 4);
					if (lastPCNote != REST) {
						
					} else {
						// TODO no last PC
					}
				}
			}*/
			
			if (i != 0) {
				parts->at(i) = parts->at(i - 1);
			}
			if (thisRhythm[i] == 1) {
				int tendency = rand() % 2;
				PartName newPart = parts->at(i);
				if (tendency == 0) {
					notes->at(i) = getLowerNote(lastNote, true, &newPart);
				} else {
					notes->at(i) = getHigherNote(lastNote, true, &newPart);
				}
				parts->at(i) = newPart;
				lastNote = notes->at(i);
			}
		}
		if(isFinalBar) {
			notes->at(tNum / 2) = static_cast<NoteName>(currentCadence);
		}



		// TODO
	}

	int AudioComposer::getNextBGMIndex(int currentBar) const {
		if(currentBar < 0) {
			return -1; // not yet start main music
		}
		if(currentBar % 8 == 0) {
			int barInLoop = currentBar % thisLevelData->numBarLoop;
			return barInLoop / 8 + 1;
		}
		return -1;
	}

	void AudioComposer::getRandomNearNote(NoteName *notePtr, PartName *partPtr, NoteName noteInput, PartName partInput, int d) {
		int num = rand()%d + 1;
		int sign = rand()%2 * 2 - 1;

	}

	NoteName AudioComposer::getNoteWithTendency(NoteName lastPCNote, Cadence currentCadence, int tendency) {
		std::vector<NoteName> noteloop;
		switch (currentCadence) {

			case NIL_: break;
			case DO_: 
				noteloop = { DO, RE, MI, FA, SO, LA };
				break;
			case RE_: 
				noteloop = { DO, RE, MI, FA, SO, LA };
				break;
			case MI_: 
				noteloop = { RE, MI, FA, SO, LA, SI }; 
				break;
			case FA_: 
				noteloop = { DO, RE, FA, SO, LA, SI }; 
				break;
			case SO_: 
				noteloop = { DO, RE, MI, SO, LA, SI }; 
				break;
			case LA_: 
				noteloop = { DO, RE, MI, SO, LA, SI }; 
				break;
			default: ;
		}
		return REST;
	}

	NoteName AudioComposer::getHigherNote(NoteName currentNote, bool isPentatonic, PartName* currentPart) {

		bool switchPart = false;
		NoteName res = REST;
		switch (currentNote) {

			case REST: 
				res = REST; break;
			case DO: 
				res = RE; break;
			case RE: 
				res = MI; break;
			case MI: 
				if (isPentatonic)
					res = SO;
				else
					res = FA; 
				break;
			case FA: 
				res = SO; break;
			case SO: 
				res = LA; break;
			case LA: 
				if (isPentatonic) {
					res = DO;
					switchPart = true;
				} else
					res = SI;
				break;
			case SI: 
				res = DO;
				switchPart = true;
			default: ;
		}
		if (currentPart != nullptr) {
			if (switchPart)
				*currentPart = getHigherPart(*currentPart);
		}
		return res;
	}

	NoteName AudioComposer::getLowerNote(NoteName currentNote, bool isPentatonic, PartName* currentPart) {

		bool switchPart = false;
		NoteName res = REST;
		switch (currentNote) {

		case REST:
			res = REST; break;
		case DO:
			if (isPentatonic)
				res = LA;
			else
				res = SI;
			switchPart = true;
			break;
		case RE:
			res = DO; break;
		case MI:
			res = RE; break;
		case FA:
			res = MI; break;
		case SO:
			if (isPentatonic)
				res = MI;
			else
				res = FA;
			break;
		case LA:
			res = SO; break;
		case SI:
			res = LA;
		default:;
		}
		if (currentPart != nullptr) {
			if (switchPart)
				*currentPart = getLowerPart(*currentPart);
		}
		return res;
	}

	PartName AudioComposer::getHigherPart(PartName currentPart) {
		switch(currentPart) {
			case LOW: return MED;
			case MED: return HI;
			case HI: return HI;
			default: return HI;
		}
	}

	PartName AudioComposer::getLowerPart(PartName currentPart) {
		switch(currentPart) {
			case LOW: return LOW;
			case MED: return LOW;
			case HI: return MED;
			default: return LOW;
		}
	}

}
