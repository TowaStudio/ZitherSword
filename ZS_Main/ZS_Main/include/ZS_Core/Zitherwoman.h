/**
 * Project ZS
 */


#ifndef _ZS_ZITHERWOMAN_H
#define _ZS_ZITHERWOMAN_H

#include "Unit.h"
#include "SaveData.h"

namespace ZS {

	class Zitherwoman : public Unit {
	public:
		Zitherwoman(Vec3 startPos, Ogre::Quaternion startRot, float startProgress);
		~Zitherwoman();
		
		virtual Vec3 move(float _scale);
		void heal(float amount) override;
		void update(float timeSinceLast);
	};
}

#endif //_ZITHERWOMAN_H
