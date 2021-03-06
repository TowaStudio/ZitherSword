﻿#ifndef _ZS_MUSICUIMANAGER_H
#define _ZS_MUSICUIMANAGER_H

#include "OgreOverlayContainer.h"
#include "OgreOverlay.h"
#include "Behaviour.h"
#include "OgreOverlayManager.h"
#include "AudioSystem.h"
#include "Instruction.h"
#include "CharacterController.h"

namespace ZS {
	class MusicUIManager : public Behaviour {
	private:
		bool isEnabled;
		bool isInBar;
		int bpm;

		Ogre::v1::OverlayManager& overlayManager;
		Ogre::v1::Overlay* uiMusic;
		Ogre::v1::OverlayContainer* uiBackground;
		Ogre::v1::OverlayContainer* uiSegmentLineGroup;
		Ogre::v1::OverlayContainer* uiInstructions;

		static float BAR_LENGTH;
		static float BAR_OFFSET;
		static float BAR_PRE_OFFSET;
		static float BAR_POST_OFFSET;
		Ogre::v1::OverlayElement* uiScanline;
		float currentScanlinePos;
		float scanlineSpeed;

		static float SEGMENT_OFFSET_X;
		static float SEGMENT_OFFSET_Y;
		static float SEGMENT_INTERVAL;

		static float VERTICAL_OFFSET_DO;
		static float VERTICAL_OFFSET_RE;
		static float VERTICAL_OFFSET_MI;
		static float VERTICAL_OFFSET_SO;
		static float VERTICAL_OFFSET_LA;
		Ogre::v1::Overlay* uiNotes;
		Ogre::v1::OverlayContainer* uiNotesGroup;
		std::vector<Ogre::v1::OverlayElement*> uiNotesVec;
		int currentNoteCount;
		int totalNoteCount;

		Ogre::v1::OverlayElement* uiResult;

	public:
		MusicUIManager();
		~MusicUIManager();

		void createMusicUI();
		void showMusicUI(bool _show);
		void run(int _bpm);
		void stop();
		void update(float timeSinceLast);

		void scanlineLoop(float timeSinceLast);
		void addNote(NoteName _noteName);
		void clearNotes();

		// Scene part
		void showResult(ControlState _cst);
		void clearResult();

	};
}

#endif
