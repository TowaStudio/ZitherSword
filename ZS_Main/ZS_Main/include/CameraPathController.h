#ifndef _ZS_CAMERAPATHCONTROLLER_H
#define _ZS_CAMERAPATHCONTROLLER_H
#include "OgreCamera.h"
#include "Path.h"
#include "Unit.h"
#include "GameEntity.h"

namespace ZS {
	class CameraPathController {
	public:
		bool isEnabled;
	protected:
		Ogre::Camera* camera;
		Path* path;

		Unit* character;
		Path* characterPath;

		Vec3 cameraPos;
		Vec3 lookingPos;
		Vec3 currentLookingPos;

		float progress;

	public:
		CameraPathController(Ogre::Camera* _camera);
		CameraPathController(Ogre::Camera* _camera, Path* _path, float _progress);

		~CameraPathController();

		void bindPath(Path* _path);
		void bindCharacter(Unit* _unit);
		void bindCharacter(Unit* _unit, Path* _path);

		void update(float timeSinceLast);
		void reset();

	};
}

#endif
