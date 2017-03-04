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
	
	void AudioSystem::musicSetup(Patterns _patterns = nullptr, int _bpm = 92, int _bpb = 4) {
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
		inputSequence = std::vector<NoteName> (tpb * bpb, REST);

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
		if (tickNum == tpb * bpb) {
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
		std::vector<NoteName>  b (16, REST);
		b[0] = DO; b[4] = DO; b[8] = DO; b[12] = DO;
		Patterns a = new std::vector<std::vector<NoteName>>();
		a->push_back(b);
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
	
	void AudioSystem::hiResTimerCallback() {
		if (currentTickNum + 1 - tpb * bpb >= 0) {
			currentBarNum += 1; 
			currentTickNum = 0;
			
			GameMaster::GetInstance()->log(to_string(currentBarNum));
 			int res = identifySequence();
			// TODO return the action to core

			inputSequence = std::vector<NoteName>(tpb * bpb, REST); 
		}
		else {
			currentTickNum++;
		}
		currentTickTime = juce::Time::currentTimeMillis();
		//nextTickTime = currentTickTime + interval;

		// TODO: play solid music // test
		if (currentTickNum % 4 == 0) {
			inputSequence[currentTickNum] = DO; 
			//playSound((NoteName)(currentTickNum / 4)); 
		}
	}
}
