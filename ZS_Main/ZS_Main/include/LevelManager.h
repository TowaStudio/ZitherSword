/**
 * Project ZS
 */


#ifndef _ZS_LEVELMANAGER_H
#define _ZS_LEVELMANAGER_H

#include "tinyxml/tinyxml2.h"
#include "Swordsman.h"
#include "GameEntity.h"
#include "ZSLogicSystem.h"
#include "Path.h"
#include "SwordsmanController.h"
#include "CameraPathController.h"

namespace ZS {
	class GameMaster;
	class GraphicsSystem;

	enum LevelState {
		LST_NOT_IN_LEVEL = 0,
		LST_LOAD,
		LST_PLAY,
		LST_PASUE,
		LST_END,
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
		SwordsmanController* ccSwordsman;
		CameraPathController* mainCameraPathController;

		std::vector<CharacterController*> characterControllers;

	private:
		//Game Content
		GameMaster* gm;
		int level;
		int unitsCount;
		int jointCount;

		Path* levelPath;
		Path* cameraPath;
		Swordsman* swordsman;
		GameEntity* entSwordsman;

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

		GraphicsSystem* graphicsSystem;
		LogicSystem* logicSystem;

		Ogre::uint32 getScheduledForRemovalAvailableSlot(void);
		void destroyAllGameEntitiesIn(GameEntityVec &container);

		void aquireTransformSlot(size_t &outSlot, size_t &outBufferIdx);
		void releaseTransformSlot(size_t bufferIdx, GameEntityTransform *transform);

	public:
		LevelManager(GraphicsSystem* graphicsSystem, LogicSystem* logicSystem);
		~LevelManager();

		int getUnitID();
		int getJointID();

		Swordsman* GetSwordsman() const;
		Path* getLevelPath();
		Path* getCameraPath();
		void loadLevel(int level);
		void initLevel();
		void startLevel();

		void prepareResources();

		void update(const size_t currIdx, float timeSinceLast);
		CharacterController* createEnemy();

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
