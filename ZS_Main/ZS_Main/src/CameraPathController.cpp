﻿#include "CameraPathController.h"
#include "GameMaster.h"

namespace ZS {
	class GameMaster;

	CameraPathController::CameraPathController(Ogre::Camera* _camera) :
		isEnabled(false),
		camera(_camera), path(nullptr),
		character(nullptr), characterPath(nullptr),
		cameraPos(Vec3::ZERO), lookingPos(Vec3::ZERO), currentLookingPos(Vec3::ZERO),
		progress(0.0f)
	{

	}

	CameraPathController::CameraPathController(Ogre::Camera* _camera, Path* _path, float _progress) :
		isEnabled(false),
		camera(_camera), path(_path),
		character(nullptr), characterPath(nullptr),
		lookingPos(Vec3::ZERO), currentLookingPos(Vec3::ZERO),
		progress(_progress)
	{
		cameraPos = _path->getPosInPath(_progress);
	}

	CameraPathController::~CameraPathController() {
	}

	void CameraPathController::bindPath(Path* _path) {
		path = _path;
		if(path != nullptr) {
			cameraPos = path->getPoint(0)->pos;
			camera->setPosition(path->getPoint(0)->pos);
		} else {
			camera->setPosition(0.0f, 0.0f, 0.0f);
		}
	}

	void CameraPathController::bindCharacter(Unit* _unit) {
		character = _unit;
		if(_unit != nullptr && _unit->path) {
			characterPath = _unit->path;
			currentLookingPos = character->pos;
			camera->setPosition(path->getPoint(0)->pos);
			camera->lookAt(character->pos);
		}
	}

	void CameraPathController::bindCharacter(Unit* _unit, Path* _path) {
		character = _unit;
		characterPath = _path;
		currentLookingPos = character->pos;
	}

	void CameraPathController::update(float timeSinceLast) {
		if(isEnabled && character) {
			if(character->progress > progress) {
				cameraPos = path->getPosInPath(characterPath->getSegmentPosFromPos(character->progress), true);
				lookingPos = character->pos;
				progress = character->progress;
				//GameMaster::GetInstance()->log(Ogre::StringConverter::toString(nextPos));
			}
			float smoothingFactor = 4.0f * timeSinceLast;
			camera->setPosition(smoothingFactor * cameraPos + (1.0f - smoothingFactor) * camera->getPosition());
			currentLookingPos = smoothingFactor * currentLookingPos + (1.0f - smoothingFactor) * lookingPos;
			camera->lookAt(currentLookingPos + Vec3(0.0f, 7.0f, 0.0f));
		}
	}

	void CameraPathController::reset() {
		if(path && character && character->path) {
			progress = 0.0f;
			cameraPos = path->getPoint(0)->pos;
			camera->setPosition(path->getPoint(0)->pos);
			currentLookingPos = character->path->getPoint(0)->pos;
			camera->lookAt(character->path->getPoint(0)->pos);
		}
	}
}
