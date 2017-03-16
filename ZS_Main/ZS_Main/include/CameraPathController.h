#ifndef _ZS_CAMERAPATHCONTROLLER_H
#define _ZS_CAMERAPATHCONTROLLER_H
#include <OgreCamera.h>
#include "Path.h"

namespace ZS {
	class CameraPathController {
	protected:
		Ogre::Camera* camera;
		Path* path; //
		float progress;


	public:
		CameraPathController(Ogre::Camera* _camera, Path* _path, float _progress)
			: camera(_camera),
			  path(_path),
			  progress(_progress)
		{

		}
		~CameraPathController() {};

	};
}

#endif
