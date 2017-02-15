/**
 * Project ZS
 */


#include "AudioSystem.h"

namespace ZS {
	/**
	* AudioSystem implementation
	*/
	AudioSystem* AudioSystem::instance = new AudioSystem();

	void AudioSystem::musicSetup(int _bpm = 92, int _bpb = 4) {
		// setting properties
		bpm = _bpm;
		bpb = _bpb;

		// hardcoding properties
		tolerance = 0.25;
		tpb = 4;

		// calculating properties
		interval = (60 * 1000) / (tpb * bpm);
		thresTime = tolerance * interval;
	}

	void AudioSystem::startMusic() {
		// init
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

		// play sound : TODO

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

	AudioSystem::AudioSystem() {
		musicSetup();
	}
	
	void AudioSystem::timerCallback() {
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

		// TODO: play solid music
	}
}
