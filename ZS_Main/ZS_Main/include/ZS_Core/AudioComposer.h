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

	/*struct Note {
	NoteName name = REST;
	float value = 1; // 1 = 1 meter
	float startMoment = 0; // 1 = 1 meter
	int barNum = 1;
	};*/

	class AudioComposer {
	public: 
		AudioComposer();
		void SetupComposer(int currentLevel = 0, int ticksPerBar = 16);

		void getNextSeq(NoteSeq * notes, PartSeq * parts, NoteSeq inputInfo, int currentBar);
		void getNextBGMIndex(); // TODO

	private: 
		int currentLevel;
		int tNum;

	};
}

#endif //_AUDIOCOMPOSER_H
