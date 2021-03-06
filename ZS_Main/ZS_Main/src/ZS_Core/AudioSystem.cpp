/**
 * Project ZS
 */
#include "AudioSystem.h"
#include "GameMaster.h"
#include "EnemyAController.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();

	//int timeDiffTT = 0; // DEBUG
	//int clickNum = 0; // DEBUG

	// setup
	void AudioSystem::musicSetup(int _currentLevel, Patterns* _patterns, int _initBarNum, int _initTickNum, int _bpm, int _bpb) {
		// setting properties
		currentLevel = _currentLevel;
		patterns = _patterns;
		currentBarNum = -_initBarNum;
		bpm = _bpm;
		bpb = _bpb;

		// load bgm
		loadBGM();

		// hardcoding properties
		inputPart = MED;
		tolerance = 0.7;
		tpb = 4;
		playerInCharge = false;
		AIInCharge = false;
		isGameRunning = false;
		isGameClear = false;

		// calculating & initializing properties
		interval = 60 * 1000 / (tpb * bpm);
		thresTime = int(tolerance * interval + 0.5f); // round
		inputSequence = NoteSeq(tpb * bpb, REST);
		noteSequence = new NoteSeq(tpb * bpb, REST);
		partSequence = new PartSeq(tpb * bpb, MED);

		// AI composer setup
		AIComposer->setupComposer(currentLevel, tpb * bpb);

	}

	void AudioSystem::setChannel() {
		setAudioChannels(0, 2);
	}

	void AudioSystem::startMusic() {
		// init
		//setAudioChannels(0, 2);
		//currentBarNum = 0; // init in setup for prelude
		//currentTickNum = -1;
		currentTickTime = -1;
		//nextTickTime = -1;
		//comboNum = 0;

		// start timer
		//startTime = Time::currentTimeMillis();
		isGameRunning = true;
		startTimer(interval);

		// play background music
		mixer.addInputSource(SETransportSource, true);
		mixer.addInputSource(BGTransportSource, true);
		playBGM(0);
	}

	void AudioSystem::stopMusic(bool win) {
		//stopTimer();
		isGameRunning = false;
		isGameClear = win;
	}

	void AudioSystem::terminate() {
		stopTimer();
		isGameRunning = false;
		isGameClear = false;
		playerInCharge = false;
		AIInCharge = false;
	}

	// input 
	void AudioSystem::input(NoteName inputNote) {

		// judge input
		if(isTimerRunning()) {
			int64 currentTime = juce::Time::currentTimeMillis();
			inputJudge(currentTime, inputNote);
		}

		// play sound
		playSound(inputNote, inputPart);

	}

	void AudioSystem::inputJudge(int64 currentTime, NoteName noteName) {
		int timeDiff = static_cast<int>(currentTime - currentTickTime);
		timeDiff -= 20;
		//timeDiffTT += timeDiff; // DEBUG
		//clickNum += 1; // DEBUG
		if (tolerance <= 0.5f)
			if(timeDiff < thresTime) { // current tick
				recordNote(currentTickNum, noteName);
			} else if(timeDiff > interval - thresTime) { // next tick
				recordNote(currentTickNum + 1, noteName);
				//timeDiffTT -= interval; // DEBUG
			} else { // hit nothing

			}
		else
			if (currentTickNum % 2 == 0 && timeDiff < thresTime) // current tick
				recordNote(currentTickNum, noteName); 
			else if (timeDiff > interval - thresTime) { // next tick
					recordNote(currentTickNum + 1, noteName);
					//timeDiffTT -= interval; // DEBUG
			} else { // hit nothing

			}
	}

	void AudioSystem::recordNote(int tickNum, NoteName noteName) {
		if(tickNum == tpb * bpb) { // the last semi-part of a bar
			if(!playerInCharge && currentBarNum + 1 >= 0) {
				inputSequence[0] = noteName;
			}
		} else {
			if(playerInCharge) {
				inputSequence[tickNum] = noteName;
			}
		}
	}

	void AudioSystem::playSound(NoteName note, PartName part) {
		if(note == REST) {
			return; // nothing to play
		}
		int index = part * 7 + note;
		if(index < 0 || index >= sizeof(sampleReaders)) {
			// index error
			return;
		}
		if(sampleReaders[index] != nullptr) {
			AudioTransportSource* transportSource = new AudioTransportSource;
			sampleTransportSources.push(transportSource);
			//AudioTransportSource transportSource = sampleTransportSources.back();
			transportSource->setSource(new AudioFormatReaderSource(sampleReaders[index], true), 0, nullptr, sampleReaders[index]->sampleRate);
			//transportSource->setGain(0.25f);
			mixer.addInputSource(transportSource, true);
			transportSource->setPosition(0.0);
			transportSource->start();
		}
	}

	void AudioSystem::playBGM(int index) {
		if(index < 0 || index >= sizeof(BGReaders)) {
			// index error
			return;
		}
		if(BGReaders[index] != nullptr) {
			BGTransportSource->setSource(new AudioFormatReaderSource(BGReaders[index], true), 0, nullptr, BGReaders[index]->sampleRate);
			BGTransportSource->setPosition(0.0);
			BGTransportSource->start();
		}
	}

	void AudioSystem::playSoundEffect(int index) {
		if (index < 0 || index >= sizeof(SEReaders)) {
			// index error
			return;
		}
		if(SEReaders[index] != nullptr) {
			SETransportSource->setSource(new AudioFormatReaderSource(SEReaders[index], true), 0, nullptr, SEReaders[index]->sampleRate);
			SETransportSource->setPosition(0.0);
			SETransportSource->start();
		}
	}

	void AudioSystem::playEndingBGM() {
		int index = 0;
		if(isGameClear) index = 1;
		if(EndReaders[index] != nullptr) {
			BGTransportSource->setSource(new AudioFormatReaderSource(EndReaders[index], true), 0, nullptr, EndReaders[index]->sampleRate);
			BGTransportSource->setPosition(0.0);
			BGTransportSource->start();
		}
	}

	int AudioSystem::identifySequence() {
		
		if (!patterns) {
			//GameMaster::GetInstance()->log("Error");
			return 0;
		}
		for(int p = 0; p < patterns->size(); p++) {
			bool match = true;
			if(patterns->at(p).size() != tpb * bpb) {
				match = false;
				break;
			}
			for(int i = 0; i < inputSequence.size(); i++) {
				if(inputSequence[i] != patterns->at(p)[i]) {
					match = false;
					break;
				}
			}
			if (match) {
				//GameMaster::GetInstance()->log("Success");
				if (p <= 0) { // input nothing
					break;
				} else { // input correct
					//comboNum++;
					return p; // return the index of pattern
				}
			}
		}
		//comboNum = 0;
		playSoundEffect(2);
		return 0; // No match
	}

	// constructor
	AudioSystem::AudioSystem(){
		// init settings
		char buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buffer);
		Ogre::String cwd = buffer;
		replace(cwd.begin(), cwd.end(), '\\', '/');
		cwd += "/ZSResources/Audio/";
		directory = cwd;

		//setAudioChannels(0, 2);
		formatManager.registerBasicFormats();
		AIComposer = new AudioComposer();
		BGTransportSource = new AudioTransportSource;
		SETransportSource = new AudioTransportSource;

		musicSetup();

		// load files
		//loadBGM();
		loadFiles();

		// setup test
		/*NoteSeq  b0(16, REST);
		NoteSeq  b1(16, REST);
		NoteSeq  b2(16, REST);
		NoteSeq  b3(16, REST);
		NoteSeq  b4(16, REST);
		NoteSeq  b5(16, REST);
		b0[0] = DO; //b0[4] = DO; b0[8] = DO; b0[12] = DO;
		b1[0] = RE; //b1[4] = RE; b1[8] = RE; b1[12] = RE;
		b2[0] = MI; //b2[4] = MI; b2[8] = MI; b2[12] = MI;
		b3[0] = SO; //b3[4] = SO; b3[8] = SO; b3[12] = SO;
		b4[0] = LA; //b4[4] = LA; b4[8] = LA; b4[12] = LA;
		//b5[0] = REST; b5[4] = REST; b5[8] = REST; b5[12] = REST;
		Patterns* a = new Patterns();
		a->push_back(b0);
		a->push_back(b1);
		a->push_back(b2);
		a->push_back(b3);
		a->push_back(b4);
		//a->push_back(b5);
		musicSetup(0, a, 4, 0, 150);*/

	}

	void AudioSystem::loadFiles() {

		// samples
		String partsName[] = {"Low_", "Med_", "Hi_"};
		for(int p = 0; p < 3; p++) {
			for(int i = 1; i <= 7; i++) {
				String path = directory + partsName[p];
				path += i;
				path += ".wav";
				File file = File(path);
				sampleReaders[p * 7 + i] = formatManager.createReaderFor(file);
			}
		}

		// sound effects
		for (int i = 0; i < 8; i++) {
			String path = directory + "SE_";
			path += i;
			path += ".wav";
			File file = File(path);
			SEReaders[i] = formatManager.createReaderFor(file);
		}
	}

	void AudioSystem::loadBGM() {
		String prefix = "BG_" + to_string(currentLevel) + "_";

		// in game BGM
		for(int i = 0; i <= 4; i++) {
			String path = directory + prefix;
			path += i;
			path += ".wav";
			File file = File(path);
			BGReaders[i] = formatManager.createReaderFor(file);
		}

		// ending BGM
		String path = directory + prefix;
		String type[2] = {"FAL", "CLR"};
		for(int i = 0; i < 2; i++) {
			String fileDir = path + type[i] + ".wav";
			File file = File(fileDir);
			EndReaders[i] = formatManager.createReaderFor(file);
		}
	}

	// override 
	void AudioSystem::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
		mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
	}

	void AudioSystem::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
		mixer.getNextAudioBlock(bufferToFill);
	}

	void AudioSystem::releaseResources() {
		mixer.releaseResources();
	}

	/*void AudioSystem::changeListenerCallback(ChangeBroadcaster* source) {
		AudioTransportSource* transportSource = static_cast<AudioTransportSource*>(source);
		if (!transportSource->isPlaying()) {
			mixer.removeInputSource(transportSource);
		}
	}*/

	void AudioSystem::hiResTimerCallback() {
		currentTickNum++;
		currentTickTime = juce::Time::currentTimeMillis();

		// Bar end
		if(currentTickNum == tpb * bpb) {
			currentBarNum++;
			currentTickNum = 0;

			// main music start
			if(currentBarNum >= 0) {

				// start player input
				if(currentBarNum % 2 == 0) {
					playerInCharge = true;
					AIInCharge = false;

					// detect game ending
					if(!isGameRunning) {
						stopTimer();
						playerInCharge = false;
						AIInCharge = false;
						playEndingBGM();
						return;
					}

					// change BGM
					playBGM(AIComposer->getNextBGMIndex(currentBarNum));

				}
				// end player input
				else {
					playerInCharge = false;
					AIInCharge = true;

					// identify sequence
					int res = identifySequence();
					/*Ogre::String debugStr = "";
					for (int i = 0; i < 16; i += 4) {
						debugStr += to_string(inputSequence[i]);
						debugStr += to_string(inputSequence[i+1]);
						debugStr += to_string(inputSequence[i+2]);
						debugStr += to_string(inputSequence[i+3]);
						debugStr += " ";
					}
					debugStr += ": "; 
					int diffAvg = 0;
					if (clickNum > 0) {
						diffAvg = timeDiffTT / clickNum;
						timeDiffTT = 0; clickNum = 0;
					}
					debugStr += to_string(diffAvg);
					GameMaster::GetInstance()->log(debugStr);*/
					//GameMaster::GetInstance()->getInputManager()->setComboNum(comboNum);
					GameMaster::GetInstance()->getInputManager()->setInstruction(static_cast<ControlState>(res));
					//GameMaster::GetInstance()->getLevelManager()->showResult(static_cast<ControlState>(res));

					// get AI composing
					AIComposer->getNextSeq(noteSequence, partSequence, inputSequence, currentBarNum, res);

					// reset input buffer
					inputSequence = NoteSeq(tpb * bpb, REST);
				}
			}
		}

		// play AI composing
		if(AIInCharge) {
			playSound(noteSequence->at(currentTickNum), partSequence->at(currentTickNum));
		}

		// detect run-out
		while(sampleTransportSources.size() > 0) {
			if(sampleTransportSources.size() <= 10 && sampleTransportSources.front()->isPlaying()) {
				break;
			} else {
				mixer.removeInputSource(sampleTransportSources.front());
				sampleTransportSources.pop();
			}
		}
		//GameMaster::GetInstance()->log(to_string(sampleTransportSources.size()));


		/*for (int i = 0; i < sampleTransportSources.size(); i++) {
			if (!sampleTransportSources[i]->isPlaying()) {
				mixer.removeInputSource(sampleTransportSources[i]);
			}
		}*/

		// test
		//if (playerInCharge) {
		//	if (currentTickNum == 0) {
		//		//inputSequence[currentTickNum] = DO; 
		//		playSound(SO);
		//	}
		//	else if (currentTickNum % 4 == 0) {
		//		playSound(DO);
		//	}
		//}

	}
}
