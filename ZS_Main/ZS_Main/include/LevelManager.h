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
#include "CharacterController.h"
#include "CameraPathController.h"
#include "AudioSystem.h"

namespace ZS {
	class GameMaster;
	class GraphicsSystem;
	class SwordsmanController;
	class ZitherWomanController;

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

		struct BindDefinition {
			GameEntity* source;
			GameEntity* target;
			std::string boneName;
		};

		typedef std::vector<GameEntityVec> GameEntityVecVec;

		LevelState levelState;
		SwordsmanController* ccSwordsman;
    ZitherWomanController* ccZitherwoman;
		std::vector<Unit*> unitVec;

		CameraPathController* mainCameraPathController;

		std::vector<CharacterController*> characterControllers;

	private:
		//Game Content
		GameMaster* gm;
		int level;
		Patterns * patterns;

		int unitsCount;
		int itemsCount;

		Path* levelPath;
		Path* cameraPath;
		Swordsman* swordsman;
		GameEntityVec entMainCharacters;
		std::vector<int> enemyTypes;
		std::vector<float> enemyLocs;

		GameEntityVec sceneEntities;
		GameEntityVec enemyEntities;

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
		int getItemID();

		Path* getLevelPath();
		Path* getCameraPath();
		void loadLevel(int level);
		void initLevel();
		void startLevel();

		void prepareResources();

		void update(const size_t currIdx, float timeSinceLast);
		void addHitInfo(const HitInfo& hit);
		void showResult(ControlState cst);
		void EndLevel(bool win);
		void NextLevel();
		void RetryLevel();
		CharacterController* createEnemy(int type, float progress);

		void changeAnimationOf(AnimationController* ac, Ogre::String state, bool loop);

		Swordsman* getSwordsman(); 
		Unit* getEnemy(int unitID);
		Unit* getClosestEnemy(float _pos, float threshold);
		void UnloadLevel();
		void ClearLevelData();

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

	private:
		void loadLevelScene();

		void loadLevelData();
	};

}

#endif //_LEVELMANAGER_H
