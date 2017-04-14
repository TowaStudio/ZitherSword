#ifndef _ZS_ANIMATIONCONTROLLER_H
#define _ZS_ANIMATIONCONTROLLER_H

#include "Animation/OgreSkeletonInstance.h"

namespace ZS {
	class AnimationController {
	public:
		struct AnimationInstruction {
			AnimationController* ac;
			std::string state;
			bool loop;
		};

	private:
		Ogre::SkeletonInstance* skeleton;

	public:
		Ogre::String currentState;
		Ogre::SkeletonAnimation* currentAnim;
		bool isEnabled;

		AnimationController(Ogre::SkeletonInstance* _character);
		~AnimationController();

		void startAnimation(Ogre::String _state = "_CURRENT", bool _loop = true, float _playbackSpeed = 1.0f);
		void changeAnimation(Ogre::String _state);
		void stopAnimation();
		void update(float timeSinceLast);

	};
}

#endif
