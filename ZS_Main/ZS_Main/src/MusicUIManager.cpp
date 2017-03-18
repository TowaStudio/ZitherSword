#include "MusicUIManager.h"
#include "GameMaster.h"

namespace ZS {
	//Initialize
	MusicUIManager::MusicUIManager() :
		Behaviour(Vec3::ZERO),
		isEnabled(false),
		overlayManager(Ogre::v1::OverlayManager::getSingleton()),
		uiMusic(nullptr),
		uiBackground(nullptr),
		uiScanline(nullptr),
		currentScanlinePos(0.0f), scanlineSpeed(100.0f),
		uiNotes(nullptr),
		uiNotesVec(std::vector<Ogre::v1::OverlayContainer*>()),
		currentNoteCount(0), totalNoteCount(0),
		uiResult(nullptr)
	{

	}

	MusicUIManager::~MusicUIManager() {
	}

	void MusicUIManager::createMusicUI() {
		uiMusic = overlayManager.create("MusicUI");
		uiNotes = overlayManager.create("MusicNotes");

		//Background
		{
			uiBackground = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIPanelBackground"));
			uiBackground->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiBackground->setPosition(0.0f, 7500.0f);
			uiBackground->setDimensions(10000.0f * 1280.0f / 720.0f, 2500.0f);
			uiBackground->setMaterialName("MusicUIBG");
			uiMusic->add2D(uiBackground);
		}

		//Scanline
		{
			uiScanline = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIScanline"));
			uiScanline->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiScanline->setPosition(BAR_OFFSET * 1280.0f / 720.0f, 7500.0f);
			uiScanline->setDimensions(100.0f * 1280.0f / 720.0f, 2500.0f);
			uiScanline->setMaterialName("MusicUIScanLine");
			uiMusic->add2D(uiScanline);
		}

		//Result
		{
			uiResult = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIResult"));
			uiResult->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiResult->setPosition(5000.0f * 1280.0f / 720.0f, 7500.0f);
			uiResult->setDimensions(100.0f * 1280.0f / 720.0f, 2500.0f);
			uiMusic->add2D(uiResult);
		}
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

	float MusicUIManager::BAR_LENGTH = 2000;
	float MusicUIManager::BAR_OFFSET = 2000;

	void MusicUIManager::scanlineLoop(float timesinceLast) {
		float nextScanlinePos = fmodf(currentScanlinePos + scanlineSpeed * timesinceLast, BAR_LENGTH);
		if(nextScanlinePos < currentScanlinePos && currentNoteCount > 0)
			clearNotes();
		uiScanline->setLeft((nextScanlinePos + BAR_OFFSET) * 1280.0f / 720.0f);
		currentScanlinePos = nextScanlinePos;
	}

	float MusicUIManager::VERTICAL_OFFSET_DO = 7600.0f;
	float MusicUIManager::VERTICAL_OFFSET_RE = 8000.0f;
	float MusicUIManager::VERTICAL_OFFSET_MI = 8400.0f;
	float MusicUIManager::VERTICAL_OFFSET_SO = 8800.0f;
	float MusicUIManager::VERTICAL_OFFSET_LA = 9200.0f;

	void MusicUIManager::addNote(NoteName _noteName) {
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

		Ogre::v1::OverlayContainer* note = static_cast<Ogre::v1::OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "MusicUINote" + totalNoteCount++));
		++currentNoteCount;
		note->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
		note->setPosition((currentScanlinePos + BAR_OFFSET) * 1280.0f / 720.0f, verticalOffset);
		note->setDimensions(500.0f, 500.0f);
		note->setMaterialName(noteDisplayMaterial);
		uiNotesVec.push_back(note);
		GameMaster::GetInstance()->log(currentNoteCount);
		uiNotes->add2D(note);
	}

	void MusicUIManager::clearNotes() {
		uiNotes->clear();
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
