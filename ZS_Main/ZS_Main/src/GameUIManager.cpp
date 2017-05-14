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

		{
			uiCombo = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "GameUICombo"));
			uiCombo->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiCombo->setPosition(10000.0f * 50.0f / 720.0f, 10000.0f * 140.0f / 720.0f);
			uiCombo->setDimensions(10000.0f * 151.0f / 720.0f, 10000.0f * 57.0f / 720.0f);
			uiCombo->setMaterialName("GameUICombo0");
			uiGame->add2D(uiCombo);
		}

		{
			uiGameResult = static_cast<Ogre::v1::OverlayContainer*>(
				overlayManager.createOverlayElement("Panel", "GameUIGameEnd"));
			uiGameResult->setMetricsMode(Ogre::v1::GMM_RELATIVE_ASPECT_ADJUSTED);
			uiGameResult->setPosition(10000.0f * 263.0f / 720.0f, 10000.0f * 300.0f / 720.0f);
			uiGameResult->setDimensions(10000.0f * 755.0f / 720.0f, 10000.0f * 136.0f / 720.0f);
			uiGameResult->setMaterialName("GameUIEndBlank");
			uiGame->add2D(uiGameResult);
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
			uiHPFill->setWidth(hpFill * 950.0f * 1280 / 720.0f);
		}
	}

	void GameUIManager::updateHPFill(float _fill) {
		targetHPFill = _fill > 1.0f ? 1.0f : (_fill < 0.0f ? 0.0f : _fill);
	}

	void GameUIManager::setHPFill(float _fill) {
		uiHPFill->setWidth(_fill * 950.0f * 1280 / 720.0f);
	}

	void GameUIManager::updateCombo(int combo) {
		std::string materialName = "GameUICombo0";
		switch(combo) {
			case 3:
				materialName = "GameUICombo3";
				break;
			case 4:
				materialName = "GameUICombo4";
				break;
			case 5:
				materialName = "GameUICombo5";
				break;
			case 6:
				materialName = "GameUICombo6";
				break;
			case 7:
				materialName = "GameUICombo7";
				break;
			case 8:
				materialName = "GameUICombo8";
				break;
			case 9:
				materialName = "GameUICombo9";
				break;
			default:
				if(combo >= 10) {
					materialName = "GameUIComboSkill";
				}
				break;
		}
		uiCombo->setMaterialName(materialName);
	}

	void GameUIManager::updateEnd(bool win) {
		std::string materialName = "GameUIBlank";
		if(win)
			materialName = "GameUIEndWin";
		else
			materialName = "GameUIEndLose";
		uiGameResult->setMaterialName(materialName);
	}
}
