/**
* Project ZS
*/

#ifndef _ZS_AUDIOCOMPOSER_H
#define _ZS_AUDIOCOMPOSER_H
#include <vector>
#include <map>

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

		struct AudioLevelData {
			int level;
			int numBarLoop;
			std::vector<Cadence> cadenceLoop;
			std::vector<int> rhythmIntensity;

		};

		// AI CORE FILES! DO NOT MODIFY UNLESS YOU REALLY UNDERSTAND!
		static const std::map<Cadence, std::vector<NoteName>> _CadenceNoteMap_;
		static const std::vector<AudioLevelData> _AudioLevelData_;

		AudioComposer();
		void setupComposer(int currentLevel = 0, int ticksPerBar = 16);

		void getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar, int res);
		int getNextBGMIndex(int currentBar) const; 

	private: 
		int currentLevel;
		int tNum; // ticks per bar
		const AudioLevelData* thisLevelData;

		//static void getRandomNearNote(NoteName* notePtr, PartName* partPtr, NoteName noteInput, PartName partInput, int distance = 1);
		//static NoteName getNotLoop(Cadence currentCadence);

		static NoteName getHigherNote(NoteName currentNote, Cadence currentCadence = NIL_, PartName* currentPart = nullptr);
		static NoteName getLowerNote(NoteName currentNote, Cadence currentCadence = NIL_, PartName* currentPart = nullptr);
		static PartName getHigherPart(PartName currentPart);
		static PartName getLowerPart(PartName currentPart);
	};
}

#endif //_AUDIOCOMPOSER_H
