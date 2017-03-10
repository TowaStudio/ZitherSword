/**
 * Project ZS
 */

#ifndef _ZS_AUDIOSYSTEM_H
#define _ZS_AUDIOSYSTEM_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioComposer.h"

using namespace juce;

namespace ZS {
	class AudioSystem : 
		private juce::AudioAppComponent, 
		private juce::HighResolutionTimer, 
		private juce::ChangeListener
	{
	public:
		static AudioSystem* GetInstance() {
			return instance;
		}

		void musicSetup(Patterns* patterns = nullptr, int preBarNum = 0, int preTickNum = 0, int timePerBeat = 120, int beatsPerBar = 4);
		void startMusic(); 
		void stopMusic();
		void input(NoteName inputKey);

		bool playerInCharge;
		bool AIInCharge;

		// get
		float getBpm() {
			return bpm;
		}
		float getTolerance() {
			return tolerance;
		}


	private:
		// editing variables
		const String directory = "F:/ZitherSword/ZS_Main/Assets/Audio/";
		const int noteGroup[5] = { 1, 2, 3, 5, 6 }; // INTERNAL USE: for loading the music files

		// setting variables
		Patterns* patterns;
		PartName inputPart; // the part that user can input
		int bpm; // beats per minute
		int bpb; // beats per bar

		// computing variables
		float tolerance; // 0: no tolerance - 0.5: full tolerance 
		int tpb; // ticks per beat
		int interval;
		int thresTime;

		// run time variables
		//int64 startTime;
		int currentBarNum; // the current number of bar
		int currentTickNum; // the current number of tick within a bar
		int64 currentTickTime; 
		//int64 nextTickTime;
		NoteSeq inputSequence;
		NoteSeq* noteSequence; // used for AI composing
		PartSeq* partSequence; // used for AI composing

		AudioComposer* AIComposer;

		MixerAudioSource mixer;
		AudioFormatManager formatManager;
		AudioFormatReader* readers[22];
		AudioTransportSource transportSource;

		void loadFiles();
		void inputJudge(int64 currentTime, NoteName noteName);
		void recordNote(int tickNum, NoteName noteName);
		void playSound(NoteName note, PartName part = MED);
		int identifySequence();

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

		// override ChangeListener
		void changeListenerCallback(ChangeBroadcaster* source) override;

	};
}

#endif //_AUDIOSYSTEM_H
