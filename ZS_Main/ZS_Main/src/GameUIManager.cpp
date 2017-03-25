#include "GameUIManager.h"
#include "ogre/hlms/Unlit/OgreHlmsUnlitDatablock.h"
#include <OgreHlmsSamplerblock.h>

namespace ZS {

	GameUIManager::GameUIManager() :
		isEnabled(false),
		overlayManager(Ogre::v1::OverlayManager::getSingleton()),
		uiGame(nullptr),
		uiCharacter(nullptr),
		uiHPBar(nullptr), uiHPFill(nullptr),
		targetHPFill(0.0f), hpFill(0.0f) {
	}

	GameUIManager::~GameUIManager() {
	}

	void GameUIManager::createGameUI() {
		uiGame = overlayManager.create("GameUI");

		//Avatar
		{
			uiCharacter = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "GameUICharacter"));
			uiCharacter->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiCharacter->setPosition(100.0f * 1280.0f / 720.0f, 100.0f * 1280.0f / 720.0f);
			uiCharacter->setDimensions(700.0f * 1280.0f / 720.0f, 700.0f * 1280.0f / 720.0f);
			uiCharacter->setMaterialName("SwordsmanAvatar");
			uiGame->add2D(uiCharacter);
		}

		//HPBar
		{
			uiHPBar = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "GameUIHPBar"));
			uiHPBar->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiHPBar->setPosition(900.0f * 1280.0f / 720.0f, 180.0f * 1280.0f / 720.0f);
			uiHPBar->setDimensions(1000.0f * 1280.0f / 720.0f, 179.0f * 1280 / 720.0f);
			uiHPBar->setMaterialName("SwordsmanHPBarBG");

			uiHPFill = static_cast<Ogre::v1::OverlayElement*>(
				overlayManager.createOverlayElement("Panel", "GameUIHPFill"));
			uiHPFill->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiHPFill->setPosition(25.0f * 1280.0f / 720.0f, 30.0f * 1280.0f / 720.0f);
			uiHPFill->setDimensions(950.0f * 1280.0f / 720.0f, 119.0f * 1280 / 720.0f);
			uiHPFill->setMaterialName("SwordsmanHPBarFill");

			// TODO: modify the texture address mode to change the fill of hp
			//Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(
			//	uiHPFill->getDatablock());
			////Make a hard copy of the sampler block
			//Ogre::HlmsSamplerblock samplerblock;
			//samplerblock.mU = Ogre::TAM_WRAP;
			//samplerblock.mV = Ogre::TAM_WRAP;
			//samplerblock.mW = Ogre::TAM_WRAP;
			//datablock->setSamplerblock(0, samplerblock);

			uiHPBar->addChild(uiHPFill);
			uiGame->add2D(uiHPBar);
		}

		uiGame->setRenderQueueGroup(254);

		targetHPFill = hpFill = 1.0f;
	}

	void GameUIManager::showGameUI(bool _show) {
		if(_show) {
			uiGame->show();
		} else {
			uiGame->hide();
		}
	}

	void GameUIManager::update(float timeSinceLast) {
		if(std::abs(hpFill - targetHPFill) > 0.001f) {
			float smoothingFactor = 4.0f * timeSinceLast + 0.02f;
			hpFill = smoothingFactor * targetHPFill + (1.0f - smoothingFactor) * hpFill;
		}
	}

	void GameUIManager::updateHPFill(float _fill) {
		targetHPFill = _fill > 1.0f ? 1.0f : (_fill < 0.0f ? 0.0f : _fill);
	}
	void GameUIManager::setHPFill(float _fill) {
		//
		uiHPFill->setWidth(hpFill * 950.0f * 1280 / 720.0f);
	}
}
