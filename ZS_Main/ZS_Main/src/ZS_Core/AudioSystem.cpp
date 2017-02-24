/**
 * Project ZS
 */


#include "AudioSystem.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();

	void AudioSystem::musicSetup(NoteName *_patterns[] = nullptr, int _bpm = 92, int _bpb = 4) {
		// setting properties
		patterns = _patterns;
		bpm = _bpm;
		bpb = _bpb;
		//part = _part; // TODO 3 sound levels

		// hardcoding properties
		tolerance = 0.25;
		tpb = 4;

		// calculating properties
		interval = (60 * 1000) / (tpb * bpm);
		thresTime = tolerance * interval;
		inputSequence = new NoteName[tpb * bpb];

	}

	void AudioSystem::startMusic() {
		// init
		setAudioChannels(0, 2);
		currentBarNum = 0; // TODO prelude bars
		currentTickNum = -1;
		currentTickTime = -1;
		//nextTickTime = -1;

		// start timer
		//startTime = Time::currentTimeMillis();
		startTimer(interval);
	}

	void AudioSystem::stopMusic() {
		stopTimer();
	}

	void AudioSystem::input(NoteName inputNote) {

		// judge input
		if (isTimerRunning()) {
			int64 currentTime = Time::currentTimeMillis();
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
		if (tickNum == - tpb * bpb) {
			// TODO next[0] = noteName;
			inputSequence[0] = noteName;
		}
		else {
			inputSequence[tickNum] = noteName;
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
		for (int pat = 0; pat < sizeof(patterns); pat++) {
			bool match = true;
			for (int i = 0; i < sizeof(inputSequence); i++) {
				if (inputSequence[i] != patterns[i][pat]) {
					match = false;
					break;
				}
			}
			if (match) {
				return pat; // return the index of pattern
			}
		}
		return -1; // No match
	}

	// constructor
	AudioSystem::AudioSystem() {
		// init settings
		formatManager.registerBasicFormats();
		part = "Med_";

		// load files
		readFiles();

		//test sequense
		NoteName** a = new NoteName*[2];
		int b[] = { 1,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0 };
		int c[] = { 5,0,0,0,6,0,0,0,5,0,0,0,6,0,0,0 };
		a[0] = (NoteName*)b;
		a[1] = (NoteName*)c;
		musicSetup(a);
		//musicSetup();
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
	
	void AudioSystem::hiResTimerCallback() {
		if (currentTickNum + 1 - tpb * bpb >= 0) {
			currentBarNum += 1; 
			currentTickNum = 0;
			
			// 
			inputSequence = new NoteName[tpb * bpb];
			int res = identifySequence();
			// TODO return the action to core
		}
		else {
			currentTickNum++;
		}
		currentTickTime = Time::currentTimeMillis();
		//nextTickTime = currentTickTime + interval;

		// TODO: play solid music // test
		if (currentTickNum % 4 == 0) {
			playSound((NoteName)(currentTickNum / 4));
		}
	}
}
