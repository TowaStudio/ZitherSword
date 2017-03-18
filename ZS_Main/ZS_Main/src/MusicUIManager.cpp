#include "MusicUIManager.h"
#include <OgreOverlayManager.h>

namespace ZS {
	//Initialize
	MusicUIManager::MusicUIManager() : 
		Behaviour(Vec3::ZERO),
		uiMusic(nullptr),
		uiScanline(nullptr),
		uiNotesVec(std::vector<Ogre::v1::OverlayContainer*>()),
		isEnabled(false)
	{

	}

	MusicUIManager::~MusicUIManager() {
	}

	void MusicUIManager::createMusicUI() {
		Ogre::v1::OverlayManager &overlayManager = Ogre::v1::OverlayManager::getSingleton();
		uiMusic = overlayManager.create("MusicUI");

		//Background
		{
			uiBackground = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIPanelBackground"));
			uiBackground->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiBackground->setPosition(0, 7500);
			uiBackground->setDimensions(10000 * 1280 / 720, 2500);
			uiBackground->setMaterialName("MusicUIBG");
			uiMusic->add2D(uiBackground);
		}

		//Scanline
		{
			uiScanline = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "MusicUIPanelScanline"));
			uiScanline->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiScanline->setPosition(2000 * 1280 / 720, 7500);
			uiScanline->setDimensions(100 * 1280 / 720, 2500);
			uiScanline->setMaterialName("MusicUIScanLine");
			uiMusic->add2D(uiScanline);
		}

	}

	void MusicUIManager::showMusicUI(bool _show) {
		if(_show)
			uiMusic->show();
		else
			uiMusic->hide();

		isEnabled = _show;
	}

	void MusicUIManager::update(float tineSinceLast) {
	}

	void MusicUIManager::scanlineLoop() {
	}

	void MusicUIManager::addNote() {
	}

	void MusicUIManager::clearNotes() {
	}

	void MusicUIManager::updateNotes() {
	}

	void MusicUIManager::showResult() {
	}

	void MusicUIManager::clearResult() {
	}
}
