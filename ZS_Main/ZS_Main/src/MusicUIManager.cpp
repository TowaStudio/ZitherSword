﻿#include "MusicUIManager.h"
#include "GameMaster.h"
#include "OgreRenderQueue.h"

namespace ZS {
	//Initialize
	MusicUIManager::MusicUIManager() :
		Behaviour(Vec3::ZERO),
		isEnabled(false),
		overlayManager(Ogre::v1::OverlayManager::getSingleton()),
		uiMusic(nullptr),
		uiBackground(nullptr),
		uiScanline(nullptr),
		currentScanlinePos(0.0f), scanlineSpeed(1200.0f),
		uiNotes(nullptr),
		uiNotesVec(std::vector<Ogre::v1::OverlayElement*>()),
		currentNoteCount(0), totalNoteCount(0),
		uiResult(nullptr)
	{

	}

	MusicUIManager::~MusicUIManager() {
	}

	float MusicUIManager::SEGMENT_OFFSET_X = 2000;
	float MusicUIManager::SEGMENT_OFFSET_Y = 0;
	float MusicUIManager::SEGMENT_INTERVAL = 600;

	void MusicUIManager::createMusicUI() {
		uiMusic = overlayManager.create("MusicUI");
		uiNotes = overlayManager.create("MusicNotes");

		//Background
		{
			uiBackground = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIPanelBackground"));
			uiBackground->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiBackground->setPosition(0.0f, 7500.0f);
			uiBackground->setDimensions(10000.0f * 1280.0f / 720.0f, 10000.0f * 200.0f / 720.0f);
			uiBackground->setMaterialName("MusicUIBG");
			uiMusic->add2D(uiBackground);
		}

		//Scanline
		{
			uiScanline = static_cast<Ogre::v1::OverlayElement*>(
				overlayManager.createOverlayElement("Panel", "MusicUIScanline"));
			uiScanline->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiScanline->setPosition((BAR_OFFSET - 50.0f) * 1280.0f / 720.0f, 0.0f);
			uiScanline->setDimensions(100.0f * 1280.0f / 720.0f, 2500.0f);
			uiScanline->setMaterialName("MusicUIScanLine");
			uiBackground->addChild(uiScanline);
		}

		//Segments
		{
			uiSegmentLineGroup = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUISegmentLines"));
			uiSegmentLineGroup->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiSegmentLineGroup->setPosition(0.0f, SEGMENT_OFFSET_Y * 1280.0f / 720.0f);
			uiSegmentLineGroup->setDimensions(5000.0f * 1280.0f / 720.0f, 10000.0f * 100.0f / 720.0f);

			//Segment indicator
			for(int i = 0; i < 5; ++i) {
				Ogre::v1::OverlayElement* uiSegmentLine = static_cast<Ogre::v1::OverlayElement*>(
					overlayManager.createOverlayElement("Panel", "MusicUISegmentLine" + Ogre::StringConverter::toString(i)));
				uiSegmentLine->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
				uiSegmentLine->setPosition((SEGMENT_OFFSET_X + i * SEGMENT_INTERVAL - 40.0f) * 1280.0f / 720.0f, 0.0f);
				uiSegmentLine->setDimensions(80.0f * 1280.0f / 720.0f, 240.0f * 1280.0f / 720.0f);
				uiSegmentLine->setMaterialName("MusicUISegmentLine");
				uiSegmentLineGroup->addChild(uiSegmentLine);
			}
			uiBackground->addChild(uiSegmentLineGroup);
		}

		//Result
		{
			uiResult = static_cast<Ogre::v1::OverlayElement*>(
				overlayManager.createOverlayElement("Panel", "MusicUIResult"));
			uiResult->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiResult->setPosition(5000.0f * 1280.0f / 720.0f, 0.0f);
			uiResult->setDimensions(100.0f * 1280.0f / 720.0f, 2500.0f);
			uiBackground->addChild(uiResult);
		}

		//Notes group
		{
			uiNotesGroup = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicNotesGroup"));
			uiNotesGroup->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiNotesGroup->setPosition(0.0f, 7500.0f);
			uiNotesGroup->setDimensions(10000.0f * 1280.0f / 720.0f, 10000.0f * 200.0f / 720.0f);
			uiNotes->add2D(uiNotesGroup);
		}

		uiMusic->setRenderQueueGroup(254);
		uiNotes->setRenderQueueGroup(254);
	}

	void MusicUIManager::showMusicUI(bool _show) {
		if(_show) {
			uiMusic->show();
			uiNotes->show();
		}
		else {
			uiMusic->hide();
			uiNotes->hide();
			stop();
		}
	}

	void MusicUIManager::run() {
		isEnabled = true;
	}

	void MusicUIManager::stop() {
		isEnabled = false;
	}

	void MusicUIManager::update(float timeSinceLast) {
		if(isEnabled) {
			scanlineLoop(timeSinceLast);
		}
	}

	float MusicUIManager::BAR_LENGTH = 2400;
	float MusicUIManager::BAR_OFFSET = 2000;

	void MusicUIManager::scanlineLoop(float timesinceLast) {
		float nextScanlinePos = fmodf(currentScanlinePos + scanlineSpeed * timesinceLast, BAR_LENGTH);
		if(nextScanlinePos < currentScanlinePos)
			clearNotes();
		uiScanline->setLeft((nextScanlinePos + BAR_OFFSET) * 1280.0f / 720.0f);
		currentScanlinePos = nextScanlinePos;
	}

	float MusicUIManager::VERTICAL_OFFSET_DO = 1800.0f;
	float MusicUIManager::VERTICAL_OFFSET_RE = 1400.0f;
	float MusicUIManager::VERTICAL_OFFSET_MI = 1000.0f;
	float MusicUIManager::VERTICAL_OFFSET_SO = 600.0f;
	float MusicUIManager::VERTICAL_OFFSET_LA = 200.0f;

	void MusicUIManager::addNote(NoteName _noteName) {
		if(!isEnabled) return;

		Ogre::String noteDisplayMaterial;
		float verticalOffset;
		switch(_noteName) {
			case NoteName::DO:
				noteDisplayMaterial = "MusicNoteDO";
				verticalOffset = VERTICAL_OFFSET_DO;
				break;
			case NoteName::RE:
				noteDisplayMaterial = "MusicNoteRE";
				verticalOffset = VERTICAL_OFFSET_RE;
				break;
			case NoteName::MI:
				noteDisplayMaterial = "MusicNoteMI";
				verticalOffset = VERTICAL_OFFSET_MI;
				break;
			case NoteName::SO:
				noteDisplayMaterial = "MusicNoteSO";
				verticalOffset = VERTICAL_OFFSET_SO;
				break;
			case NoteName::LA:
				noteDisplayMaterial = "MusicNoteLA";
				verticalOffset = VERTICAL_OFFSET_LA;
				break;
			default:
				return;
		}

		Ogre::v1::OverlayElement* note = static_cast<Ogre::v1::OverlayElement*>(
			overlayManager.createOverlayElement("Panel", "MusicUINote" + Ogre::StringConverter::toString(++currentNoteCount, 3, '0')));
		GameMaster::GetInstance()->log("MusicUINote" + Ogre::StringConverter::toString(++totalNoteCount, 3, '0'));
		note->setMaterialName(noteDisplayMaterial);
		note->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
		note->setPosition((currentScanlinePos + BAR_OFFSET) * 1280.0f / 720.0f - 250.0f, verticalOffset);
		note->setDimensions(500.0f, 500.0f);
		uiNotesVec.push_back(note);
		uiNotesGroup->addChild(note);
	}

	void MusicUIManager::clearNotes() {
		//TODO: Release all notes
		for(auto itr = uiNotesVec.begin(); itr != uiNotesVec.end(); ++itr) {
			overlayManager.destroyOverlayElement((*itr)->getName());
		}
		uiNotesVec.clear();
		currentNoteCount = 0;
	}

	void MusicUIManager::showResult(INSTRUCTION _inst) {
		Ogre::String resultMaterial;
		switch(_inst) {
			default:
			case INST_IDLE:
				resultMaterial = "";
				break;
			case INST_ATTACK:
				resultMaterial = "";
				break;
			case INST_MOVE:
				resultMaterial = "";
				break;
		}
		uiResult->setMaterialName(resultMaterial);
	}

	void MusicUIManager::clearResult() {
		showResult(INST_IDLE);
	}
}
