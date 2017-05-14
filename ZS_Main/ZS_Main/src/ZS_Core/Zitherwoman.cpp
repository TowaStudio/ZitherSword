/**
 * Project ZS
 */


#include "ZitherWoman.h"
#include "GameMaster.h"
#include "LevelManager.h"


namespace ZS {

	/**
	* Swordsman implementation
	*/
	Zitherwoman::Zitherwoman(Vec3 startPos, Ogre::Quaternion startRotation, float startProgress) :
		Unit("Zitherwoman", Tag::PLAYER, startPos, startRotation, GameMaster::GetInstance()->getLevelManager()->getUnitID()
			 , 99999.0f, 99999.0f
			 , 20000.0f, 20000.0f
			 , 999.0f, 999.0f, 10.0f, Status::ST_NORMAL, startProgress)
	{

	}

	Zitherwoman::~Zitherwoman() {
	}
	
	Vec3 Zitherwoman::move(float _scale) {
		if(!isDead) {
			if(path) {
				float step = _scale * spd / path->totalLength;
				float nextProgress = std::min(std::max(progress + step, 0.0f), 1.0f);

				// Prevent from going outside
				progress = nextProgress;

				moveVec = path->getPosInPath(progress) - pos;
				Ogre::Quaternion q;
				q.FromAngleAxis(Ogre::Math::ATan2(-moveVec.z, moveVec.x) - Ogre::Radian(Ogre::Math::PI / 2.0f), Vec3::UNIT_Y);
				rot = q;
			}
			pos += moveVec;
		}
		return pos;
	}
	
	void Zitherwoman::heal(float amount) {
		//TODO: Add scene out
		Unit::heal(amount);
	}

	void Zitherwoman::update(float timeSinceLast) {
		if(isMoving) {
			move(timeSinceLast);
		}			
		//GameMaster::GetInstance()->log(Ogre::StringConverter::toString(this->pos.x));
	}
}
