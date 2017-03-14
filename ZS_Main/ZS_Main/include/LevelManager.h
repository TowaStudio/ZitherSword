/**
 * Project ZS
 */


#ifndef _ZS_LEVELMANAGER_H
#define _ZS_LEVELMANAGER_H

#include "tinyxml/tinyxml2.h"
#include "Swordsman.h"
#include "GameEntity.h"
#include "Threading/MessageQueueSystem.h"
#include "ZSLogicSystem.h"

namespace ZS {
	class GameMaster;

	enum LevelState {
		LS_NOT_IN_LEVEL = 0,
		LS_LOAD,
		LS_PLAY,
		LS_PASUE,
		LS_END,
		NUM_LEVEL_STATE
	};

	class LevelManager {
	public:
		struct CreatedGameEntity {
			GameEntity          *gameEntity;
			GameEntityTransform initialTransform;
		};

		typedef std::vector<GameEntityVec> GameEntityVecVec;

		LevelState levelState;

		GameEntity* entSwordsman;

	private:
		//Game Content
		GameMaster* gm;
		int level;
		int unitsCount;
		int jointCount;
		Swordsman* swordsman;

		//Ogre environment, Thread synchronization
		struct Region {
			size_t slotOffset;
			size_t count;
			size_t bufferIdx;

			Region(size_t _slotOffset, size_t _count, size_t _bufferIdx) :
				slotOffset(_slotOffset),
				count(_count),
				bufferIdx(_bufferIdx) {
			}
		};

		//We assume mCurrentId never wraps
		Ogre::uint32    currentId;
		GameEntityVec   mGameEntities[Ogre::NUM_SCENE_MEMORY_MANAGER_TYPES];

		std::vector<GameEntityTransform*>   mTransformBuffers;
		std::vector<Region>                 mAvailableTransforms;

		GameEntityVecVec    mScheduledForRemoval;
		size_t              mScheduledForRemovalCurrentSlot;
		std::vector<size_t> mScheduledForRemovalAvailableSlots;

		Mq::MessageQueueSystem* graphicsSystem;
		LogicSystem* logicSystem;

		Ogre::uint32 getScheduledForRemovalAvailableSlot(void);
		void destroyAllGameEntitiesIn(GameEntityVec &container);

		void aquireTransformSlot(size_t &outSlot, size_t &outBufferIdx);
		void releaseTransformSlot(size_t bufferIdx, GameEntityTransform *transform);

	public:
		LevelManager(Mq::MessageQueueSystem* graphicsSystem, LogicSystem* logicSystem);
		~LevelManager();

		int getUnitID();
		int getJointID();

		Swordsman* GetSwordsman() const;

		void loadLevel(int level);
		void initLevel();
		void startLevel();

		void update(const size_t currIdx, float timeSinceLast);

		void trigger();

		GameEntity* addGameEntity(Ogre::SceneMemoryMgrTypes type,
								  const MovableObjectDefinition *moDefinition,
								  Behaviour* behaviour,
								  const Ogre::Vector3 &initialPos,
								  const Ogre::Quaternion &initialRot,
								  const Ogre::Vector3 &initialScale);

		/** Removes the GameEntity from the world. The pointer is not immediately destroyed,
		we first need to release data in other threads (i.e. Graphics).
		It will be destroyed after the Render thread confirms it is done with it
		(via a Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT message)
		*/
		void removeGameEntity(GameEntity *toRemove);

		/// Must be called by LogicSystem when Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT message arrives
		void _notifyGameEntitiesRemoved(size_t slot);

		/// Must be called every frame from the LOGIC THREAD.
		void finishFrameParallel(void);
	};

}

#endif //_LEVELMANAGER_H
