/**
 * Project ZS
 */


#include "AudioSystem.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();

	void AudioSystem::musicSetup(NoteName *sequences[] = nullptr, int _bpm = 92, int _bpb = 4) {
		// setting properties
		bpm = _bpm;
		bpb = _bpb;
		//part = _part;

		// hardcoding properties
		tolerance = 0.25;
		tpb = 4;

		// calculating properties
		interval = (60 * 1000) / (tpb * bpm);
		thresTime = tolerance * interval;

	}

	void AudioSystem::startMusic() {
		// init
		setAudioChannels(0, 2);
		currentBarNum = 0;
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
		// TODO
	}

	void AudioSystem::playSound(NoteName note) {
		if (readers[note] != nullptr) {
			//AudioTransportSource transportSource;
			transportSource.setSource(new AudioFormatReaderSource(readers[note], true), 0, nullptr, readers[note]->sampleRate);
			mixer.addInputSource(&transportSource, true);
			transportSource.setPosition(0.0);
			transportSource.start();
		}
	}

	void AudioSystem::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
		mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
	}

	void AudioSystem::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
		mixer.getNextAudioBlock(bufferToFill);
	}

	void AudioSystem::releaseResources() {
		mixer.releaseResources();
	}

	AudioSystem::AudioSystem() {
		// load music file
		formatManager.registerBasicFormats();
		part = "Med_";
		readFiles();

		//test pointer
		//NoteName* a[4];
		//int b[] = { 1, 2, 3, 4 };
		//a[1] = (NoteName*)b;
		//musicSetup(a);
		musicSetup();
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
		//File file = File("F:/ZitherSword/ZS_Main/Assets/Audio/Med_1.wav");
		//reader = formatManager.createReaderFor(file); // test
	}
	
	void AudioSystem::hiResTimerCallback() {
		if (currentTickNum + 1 - tpb * bpb >= 0) {
			currentBarNum += 1; 
			currentTickNum = 0;
			// TODO: sequence identify
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
