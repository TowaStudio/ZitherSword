/**
 * Project ZS
 */
#include "AudioSystem.h"
#include "GameMaster.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();
	
	void AudioSystem::musicSetup(Patterns _patterns, int _initBarNum, int _initTickNum, int _bpm, int _bpb) {
		// setting properties
		patterns = _patterns;
		currentBarNum = -_initBarNum;
		bpm = _bpm;
		bpb = _bpb;
		//part = _part; // TODO 3 sound levels

		// hardcoding properties
		tolerance = 0.25;
		tpb = 4;
		playerInCharge = false;
		AIInCharge = false;

		// calculating properties
		interval = (60 * 1000) / (tpb * bpm);
		thresTime = tolerance * interval;
		inputSequence = std::vector<NoteName> (tpb * bpb, REST);

	}

	void AudioSystem::startMusic() {
		// init
		setAudioChannels(0, 2);
		//currentBarNum = 0; // init in setup for prelude
		//currentTickNum = -1;
		currentTickTime = -1;
		//nextTickTime = -1;

		// start timer
		//startTime = Time::currentTimeMillis();
		startTimer(interval);
		//TODO: play background music
	}

	void AudioSystem::stopMusic() {
		stopTimer();
	}

	void AudioSystem::input(NoteName inputNote) {

		// judge input
		if (isTimerRunning()) {
			int64 currentTime = juce::Time::currentTimeMillis();
			inputJudge(currentTime, inputNote);
		}

		// play sound
		playSound(inputNote);

	}

	void AudioSystem::inputJudge(int64 currentTime, NoteName noteName) {
		int timeDiff = currentTime - currentTickTime;
		if (timeDiff < thresTime) { // current tick
			recordNote(currentTickNum, noteName);
		}
		else if (timeDiff > interval - thresTime) { // next tick
			recordNote(currentTickNum + 1, noteName);
		}
		else { // hit nothing

		}
	}

	void AudioSystem::recordNote(int tickNum, NoteName noteName) {
		if (tickNum == tpb * bpb) { // the last semi-part of a bar
			if (!playerInCharge && currentBarNum + 1 >= 0) {
				inputSequence[0] = noteName;
			}
		}
		else {
			if (playerInCharge) {
				inputSequence[tickNum] = noteName;
			}
		}
	}

	void AudioSystem::playSound(NoteName note) {
		if (readers[note] != nullptr) {
			transportSource.setSource(new AudioFormatReaderSource(readers[note], true), 0, nullptr, readers[note]->sampleRate);
			mixer.addInputSource(&transportSource, true);
			transportSource.setPosition(0.0);
			transportSource.start();
		}
	}

	int AudioSystem::identifySequence() {
		/*for (std::vector<std::vector<NoteName>>::iterator p = patterns->begin(); p != patterns->end(); ++p)
		{
			bool match = true;
			if (p->size() != tpb * bpb) {
				match = false;
				break;
			}
			for (std::vector<NoteName>::iterator i = p->begin(); i != p->end(); ++i) {
				
			}
			if (match) {
				return p->; // return the index of pattern
			}
		}*/
		
		if (!patterns) {
			GameMaster::GetInstance()->log("Error");
			return -1;
		}
		for (int p = 0; p < patterns->size(); p++) {
			bool match = true; 
			if (patterns->at(p).size() != tpb * bpb) {
				match = false;
				break;
			}
			for (int i = 0; i < inputSequence.size(); i++) {
				if (inputSequence[i] != patterns->at(p)[i]) {
					match = false;
					break;
				}
			}
			if (match) {
				GameMaster::GetInstance()->log("Success");
				return p; // return the index of pattern
			}
		}
		GameMaster::GetInstance()->log("Fail");
		return -1; // No match
	}

	// constructor
	AudioSystem::AudioSystem() {
		// init settings
		formatManager.registerBasicFormats();
		part = "Med_";
		musicSetup();

		// load files
		readFiles();

		// setup test
		std::vector<NoteName>  b0(16, REST);
		std::vector<NoteName>  b1(16, REST);
		std::vector<NoteName>  b2(16, REST);
		std::vector<NoteName>  b3(16, REST);
		std::vector<NoteName>  b4(16, REST);
		std::vector<NoteName>  b5(16, REST);
		b0[0] = DO; b0[4] = DO; b0[8] = DO; b0[12] = DO;
		b1[0] = RE; b1[4] = RE; b1[8] = RE; b1[12] = RE;
		b2[0] = MI; b2[4] = MI; b2[8] = MI; b2[12] = MI;
		b3[0] = SO; b3[4] = SO; b3[8] = SO; b3[12] = SO;
		b4[0] = LA; b4[4] = LA; b4[8] = LA; b4[12] = LA;
		b5[0] = REST; b5[4] = REST; b5[8] = REST; b5[12] = REST;
		Patterns a = new std::vector<std::vector<NoteName>>();
		a->push_back(b0);
		a->push_back(b1);
		a->push_back(b2);
		a->push_back(b3);
		a->push_back(b4);
		a->push_back(b5);
		musicSetup(a);
		
		
	}

	void AudioSystem::readFiles() {
		String directory = "F:/ZitherSword/ZS_Main/Assets/Audio/";
		for (int i = 0; i < 5; i++) {
			String path = directory + part;
			path += noteGroup[i];
			path += ".wav";
			File file = File(path);
			readers[noteGroup[i]] = formatManager.createReaderFor(file);
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
	
	void AudioSystem::changeListenerCallback(ChangeBroadcaster* source) {
		AudioTransportSource* transportSource = (AudioTransportSource*)source;
		if (!transportSource->isPlaying()) {
			transportSource->releaseResources();
		}
	}

	void AudioSystem::hiResTimerCallback() {
		currentTickTime = juce::Time::currentTimeMillis();
		currentTickNum++;
		
		// Bar end
		if (currentTickNum == tpb * bpb) {
			currentBarNum++;
			currentTickNum = 0;

			// main music start
			if (currentBarNum >=0) { 

				// start player input
				if (currentBarNum % 2 == 0) { 
					playerInCharge = true;
					AIInCharge = false;
				}
				// end player input
				else { 
					playerInCharge = false;
					AIInCharge = true;

					// identify sequence
					int res = identifySequence();
					GameMaster::GetInstance()->log("Input sequence ID: " + to_string(res));
					// TODO return the action to core

					// reset input buffer
					inputSequence = std::vector<NoteName>(tpb * bpb, REST);
				}
			}
		}

		// TODO: AI composing
		// test
		if (currentTickNum == 0) {
			//inputSequence[currentTickNum] = DO; 
			playSound(SO); 
		}
		else if (currentTickNum % 4 == 0){
			playSound(DO);
		}


		/*if (currentTickNum + 1 - tpb * bpb >= 0) {
			currentBarNum += 1; 
			currentTickNum = 0;
			
			if (true) {// TODO: requiring identify
				int res = identifySequence();
				// TODO return the action to core
				GameMaster::GetInstance()->log("Input sequence ID: " + to_string(res));
			}
			//GameMaster::GetInstance()->log(to_string(currentBarNum));
 			

			inputSequence = std::vector<NoteName>(tpb * bpb, REST); 
		}
		else {
			currentTickNum++;
		}
		currentTickTime = juce::Time::currentTimeMillis();
		//nextTickTime = currentTickTime + interval;

		*/
	}
}
