/**
* Project ZS
*/

#ifndef _ZS_AUDIOCOMPOSER_H
#define _ZS_AUDIOCOMPOSER_H
#include <vector>

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
	enum PartName {
		LOW = 0,
		MED = 1,
		HI = 2
	};
	
	typedef std::vector<PartName> PartSeq;
	typedef std::vector<NoteName> NoteSeq;
	typedef std::vector<NoteSeq> Patterns;

	class AudioComposer {
	public: 
		enum Cadence {
			NIL_,
			DO_,
			RE_,
			MI_,
			FA_,
			SO_,
			LA_
		};

		struct LevelData {
			int level;
			int numBarLoop;
			std::vector<Cadence> cadenceLoop;
			std::vector<int> rhythmIntensity;

		};

		static const std::vector<LevelData> _LevelData_;
		
		AudioComposer();
		void setupComposer(int currentLevel = 0, int ticksPerBar = 16);

		void getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar);
		int getNextBGMIndex(int currentBar); 

	private: 
		int currentLevel;
		int tNum; // ticks per bar
		const LevelData* thisLevelData;

		void getRandomNearNote(NoteName* notePtr, PartName* partPtr, NoteName noteInput, PartName partInput, int distance = 1);

	};

	// AI CORE FILES! DO NOT MODIFY UNLESS YOU REALLY UNDERSTAND!
	const std::vector<AudioComposer::LevelData> AudioComposer::_LevelData_{
		{ 0, 0,{},{} }, // default null level

		// Lv. 1
		{
			1,
			32,
			{ 
				LA_, SO_, LA_, SO_, LA_, DO_, RE_, MI_, 
				LA_, SO_, LA_, SO_, LA_, DO_, RE_, MI_,
				RE_, MI_, LA_, SO_, RE_, FA_, LA_, MI_, 
				LA_, SO_, LA_, SO_, LA_, DO_, MI_, LA_
			},
			{ 1, 0, 0, 1, 1, 0, 1, 0, 1, 3, 2, 3, 2, 0, 0, 0 }
		}
	};
}

#endif //_AUDIOCOMPOSER_H
