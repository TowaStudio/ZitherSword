/**
 * Project ZS
 */

#ifndef _ZS_AUDIOSYSTEM_H
#define _ZS_AUDIOSYSTEM_H

#include "../JuceLibraryCode/JuceHeader.h"

namespace ZS {
	enum NoteName {
		REST = 0,
		DO = 1,
		RE = 2,
		MI = 3,
		FA = 4,
		SO = 5,
		LA = 6,
		SI = 7
	};
	/*struct Note {
		NoteName name = REST;
		float value = 1; // 1 = 1 meter
		float startMoment = 0; // 1 = 1 meter
		int barNum = 1;
	};*/

	class AudioSystem : public juce::AudioAppComponent, public juce::HighResolutionTimer{
	public:
		static AudioSystem* GetInstance() {
			return instance;
		}

		void musicSetup(NoteName *sequences[], int timePerBeat, int beatsPerBar);
		void startMusic(); 
		void stopMusic();
		void input(NoteName inputKey);

		// get
		float getBpm() {
			return bpm;
		}
		float getTolerance() {
			return tolerance;
		}


	private:
		int bpm; // beats per minute
		int bpb; // beats per bar
		String part; // Hi_, Low, Med_

		float tolerance; // 0: no tolerance - 0.5: full tolerance 
		int tpb; // ticks per beat
		int interval;
		int thresTime;
		const int noteGroup[5] = { 1, 2, 3, 5, 6 }; // INTERNAL USE

		//int64 startTime;
		int currentBarNum; // the current number of bar
		int currentTickNum; // the current number of tick within a bar
		int64 currentTickTime; 
		//int64 nextTickTime;

		MixerAudioSource mixer;
		AudioFormatManager formatManager;
		AudioFormatReader* readers[7];
		AudioTransportSource transportSource;

		void readFiles();
		void inputJudge(int64 currentTime, NoteName noteName);
		void recordNote(int tickNum, NoteName noteName);
		void playSound(NoteName note);

		static AudioSystem* instance;
		AudioSystem();
		AudioSystem(AudioSystem const&) {};
		AudioSystem& operator= (AudioSystem const&) {};

		// override AudioAppComponent
		void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
		void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
		void releaseResources() override;

		// override Timer
		void hiResTimerCallback() override;

	};
}

#endif //_AUDIOSYSTEM_H
