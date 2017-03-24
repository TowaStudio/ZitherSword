/**
 * Project ZS
 */

#include "LevelManager.h"
#include "GameMaster.h"
#include "Enemy.h"

namespace ZS {
	const size_t cNumTransforms = 512;

	LevelManager::LevelManager(Mq::MessageQueueSystem* _graphicsSystem, LogicSystem* _logicSystem) :
		gm(GameMaster::GetInstance()),
		level(-1), levelState(LST_NOT_IN_LEVEL),
		unitsCount(0), jointCount(0),
		swordsman(nullptr), entSwordsman(nullptr), ccSwordsman(nullptr),
		currentId(0), mScheduledForRemovalCurrentSlot( static_cast<size_t>(-1)),
		graphicsSystem(_graphicsSystem), logicSystem(_logicSystem)
	{
		logicSystem->_notifyLevelManager(this);

	}

	LevelManager::~LevelManager() {
		logicSystem->_notifyLevelManager(nullptr);

		{
			GameEntityVecVec::iterator itor = mScheduledForRemoval.begin();
			GameEntityVecVec::iterator end = mScheduledForRemoval.end();
			while(itor != end)
				destroyAllGameEntitiesIn(*itor++);
			mScheduledForRemoval.clear();
			mScheduledForRemovalAvailableSlots.clear();
		}

		destroyAllGameEntitiesIn(mGameEntities[Ogre::SCENE_DYNAMIC]);
		destroyAllGameEntitiesIn(mGameEntities[Ogre::SCENE_STATIC]);

		vector<GameEntityTransform*>::const_iterator itor = mTransformBuffers.begin();
		vector<GameEntityTransform*>::const_iterator end = mTransformBuffers.end();

		while(itor != end) {
			OGRE_FREE_SIMD(*itor, Ogre::MEMCATEGORY_SCENE_OBJECTS);
			++itor;
		}
		
		mTransformBuffers.clear();
		mAvailableTransforms.clear();
	}

	//----------------------------------Game content----------------------------------
	int LevelManager::getUnitID() {
		return unitsCount++;
	}

	int LevelManager::getJointID() {
		return jointCount++;
	}

	Swordsman* LevelManager::GetSwordsman() const {
		return swordsman;
	}

	Path* LevelManager::getLevelPath() {
		return levelPath;
	}

	/**
	* @return bool
	*/
	void LevelManager::loadLevel(int _level) {
		//TODO: Clean scene and all data.

		level = _level;

		//TODO: Load scene and enemy profile;
		loadLevelScene(); //LevelData
		//PathData

		// Define level path.
		levelPath = new Path();
		//TODO: Load path data from scene;

		//_DEBUG_
		levelPath->addPoint(Vec3(0.0f, 0.0f, 0.0f));
		levelPath->addPoint(Vec3(4.0f, 0.0f, 0.0f));
		levelPath->addPoint(Vec3(6.0f, 0.0f, 3.0f));
		levelPath->addPoint(Vec3(8.0f, 0.0f, 0.0f));
		levelPath->addPoint(Vec3(9.0f, 0.0f, -1.0f));
		//_DEBUG_

		initLevel();
	}

	void LevelManager::loadLevelScene() {
		using namespace tinyxml2;
		using namespace Ogre;
		XMLDocument doc;
		doc.LoadFile("F:/ZitherSword/ZS_Main/ZS_Main/resources/LevelScene1.xml"); // TODO find xml file
		XMLElement *rootNode = doc.FirstChildElement("scene")->FirstChildElement("nodes");
		/*bool flag = true;
		while (flag) {
			if (levelRoot->Attribute("id")) {
				if (level == atoi(levelRoot->Attribute("id"))) {
					break;
				}
			}
			if (levelRoot->NextSiblingElement()) {
				levelRoot = levelRoot->NextSiblingElement();
			} else {
				flag = false;
			}
		}
		if (!flag) { // level data not found
			return;
		}*/
		//XMLElement *buildings = levelRoot->FirstChildElement("buildings");
		//String aaa = buildings->FirstChildElement("building")->Attribute("x");
		XMLElement *node = rootNode->FirstChildElement("node");
		while (node != nullptr) {
			// get node info
			Ogre::String nodeName, entityName, meshFile;
			int nodeId, entityId;
			Vec3 pos, scale;
			Ogre::Quaternion rotation;
			std::vector<Ogre::String> subentities;

			nodeName = node->Attribute("name");
			entityName = node->FirstChildElement("entity")->Attribute("name");
			meshFile = node->FirstChildElement("entity")->Attribute("meshFile");
			nodeId = StringConverter::parseInt(node->Attribute("id"));
			entityId = StringConverter::parseInt(node->FirstChildElement("entity")->Attribute("id"));
			pos.x = StringConverter::parseReal(node->FirstChildElement("position")->Attribute("x"));
			pos.y = StringConverter::parseReal(node->FirstChildElement("position")->Attribute("y"));
			pos.z = StringConverter::parseReal(node->FirstChildElement("position")->Attribute("z"));
			scale.x = StringConverter::parseReal(node->FirstChildElement("scale")->Attribute("x"));
			scale.y = StringConverter::parseReal(node->FirstChildElement("scale")->Attribute("y"));
			scale.z = StringConverter::parseReal(node->FirstChildElement("scale")->Attribute("z"));
			rotation.x = StringConverter::parseReal(node->FirstChildElement("rotation")->Attribute("qx"));
			rotation.y = StringConverter::parseReal(node->FirstChildElement("rotation")->Attribute("qy"));
			rotation.z = StringConverter::parseReal(node->FirstChildElement("rotation")->Attribute("qz"));
			rotation.w = StringConverter::parseReal(node->FirstChildElement("rotation")->Attribute("qw"));
			XMLElement *subentity = node->FirstChildElement("entity")->FirstChildElement("subentities")->FirstChildElement("subentity");
			while (subentity != nullptr) {
				subentities.push_back(subentity->Attribute("materialName"));
				subentity = subentity->NextSiblingElement("subentity");				 
			}

			// TODO load node to scene

			// get next node
			node = node->NextSiblingElement("node");

		}
	}

	void LevelManager::initLevel() {
		levelState = LST_LOAD;
		//TODO: Create Objects and setup player, input;
		Vec3 pos = Vec3(0.5f, 0.0f, 0.0f);
		Vec3 enemyPos = Vec3(5.0f, 0.0f, 0.0f);

		
		// Count the mesh to load and start level asynchronously.
		// ------------------------------------------------------
		// ---------------------IMPORTANT------------------------
		//   The value of initObjectCount MUST be equal with the
		// number of function addGameEntity called, or the level 
		// will not start.
		// ------------------------------------------------------

		int initObjectCount = 1;
		logicSystem->queueSendMessage(graphicsSystem, Mq::INIT_LEVEL_START, initObjectCount);

		{ // 1
			// Create Swordsman
			MovableObjectDefinition* moSwordsman = new MovableObjectDefinition();
			moSwordsman->meshName = "swordsman.mesh";
			moSwordsman->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
			moSwordsman->submeshMaterials = Ogre::StringVector{"SwordsmanBody","SwordsmanShoe","SwordsmanFace","SwordsmanHead","SwordsmanBelt","SwordsmanArm"};
			moSwordsman->moType = MoTypeItemSkeleton;

			// Define behaviour and data model
			swordsman = new Swordsman(gm->getPlayerStats(), pos, 0.0f);
			swordsman->bindPath(levelPath);

			// Define the scene models.

			Ogre::Quaternion initialQuaternion = Ogre::Quaternion();
			initialQuaternion.FromAngleAxis(Ogre::Radian(-Ogre::Math::PI / 2.0f), Vec3::UNIT_Y);
			entSwordsman = addGameEntity(Ogre::SCENE_DYNAMIC, moSwordsman
										 , swordsman
										 , Vec3(0.0f, 0.0f, 0.0f) // Change to Level data start pos
										 , initialQuaternion
										 , Vec3::UNIT_SCALE);
			// Create controller
			ccSwordsman = new SwordsmanController(entSwordsman);
		}
		
	}
	
	void LevelManager::startLevel() {
		//TODO: Start audio system and input manager;
		InputManager* inputManager = gm->getInputManager();

		gm->getMusicUIManager()->run();
		AudioSystem::GetInstance()->startMusic();

		levelState = LST_PLAY;
	}

	void LevelManager::prepareResources() {
		//TODO: Preload enemies' mesh file to avoid the lag in game.
	}

	void LevelManager::update(const size_t currIdx, float timeSinceLast) {
		//Update Controllers
		//TODO: Camera controller
		//TODO: Character controllers

		//Update game entities
		if(mGameEntities[Ogre::SCENE_DYNAMIC].size() > 0) {
			for(auto itr = mGameEntities[Ogre::SCENE_DYNAMIC].begin(), end = mGameEntities[Ogre::SCENE_DYNAMIC].end(); itr != end; ++itr) {
				//Update the internal model
				if((*itr)->behaviour)
					(*itr)->behaviour->update(timeSinceLast);

				//Update scene model
				(*itr)->mTransform[currIdx]->vPos = (*itr)->behaviour->pos;
			}
		}
	}

	CharacterController* LevelManager::createEnemy() {
		
		return nullptr;
	}


	//------------------------------------Game Environments------------------------------------
	//-----------------------------------------------------------------------------------
	GameEntity* LevelManager::addGameEntity(Ogre::SceneMemoryMgrTypes type,
											const MovableObjectDefinition *moDefinition,
											Behaviour* behaviour,
											const Ogre::Vector3 &initialPos,
											const Ogre::Quaternion &initialRot,
											const Ogre::Vector3 &initialScale) {
		GameEntity *gameEntity = new GameEntity(currentId++, moDefinition, behaviour, type);

		CreatedGameEntity cge;
		cge.gameEntity = gameEntity;
		cge.initialTransform.vPos = initialPos;
		cge.initialTransform.qRot = initialRot;
		cge.initialTransform.vScale = initialScale;

		size_t slot, bufferIdx;
		aquireTransformSlot(slot, bufferIdx);

		gameEntity->mTransformBufferIdx = bufferIdx;
		for(int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i) {
			gameEntity->mTransform[i] = mTransformBuffers[bufferIdx] + slot + cNumTransforms * i;
			memcpy(gameEntity->mTransform[i], &cge.initialTransform, sizeof(GameEntityTransform));
		}

		mGameEntities[type].push_back(gameEntity);

		logicSystem->queueSendMessage(graphicsSystem, Mq::GAME_ENTITY_ADDED, cge);

		return gameEntity;
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::removeGameEntity(GameEntity *toRemove) {
		Ogre::uint32 slot = getScheduledForRemovalAvailableSlot();
		mScheduledForRemoval[slot].push_back(toRemove);
		GameEntityVec::iterator itor = lower_bound(mGameEntities[toRemove->mType].begin(),
														mGameEntities[toRemove->mType].end(),
														toRemove);
		assert(itor != mGameEntities[toRemove->mType].end() && *itor == toRemove);
		mGameEntities[toRemove->mType].erase(itor);
		logicSystem->queueSendMessage(graphicsSystem, Mq::GAME_ENTITY_REMOVED, toRemove);
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::_notifyGameEntitiesRemoved(size_t slot) {
		destroyAllGameEntitiesIn(mScheduledForRemoval[slot]);

		mScheduledForRemoval[slot].clear();
		mScheduledForRemovalAvailableSlots.push_back(slot);
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::destroyAllGameEntitiesIn(GameEntityVec &container) {
		GameEntityVec::const_iterator itor = container.begin();
		GameEntityVec::const_iterator end = container.end();

		while(itor != end) {
			releaseTransformSlot((*itor)->mTransformBufferIdx, (*itor)->mTransform[0]);
			delete *itor;
			++itor;
		}
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::aquireTransformSlot(size_t &outSlot, size_t &outBufferIdx) {
		if(mAvailableTransforms.empty()) {
			GameEntityTransform *buffer = reinterpret_cast<GameEntityTransform*>(OGRE_MALLOC_SIMD(
				sizeof(GameEntityTransform) * cNumTransforms * NUM_GAME_ENTITY_BUFFERS,
				Ogre::MEMCATEGORY_SCENE_OBJECTS));
			mTransformBuffers.push_back(buffer);
			mAvailableTransforms.push_back(Region(0, cNumTransforms, mTransformBuffers.size() - 1));
		}

		Region &region = mAvailableTransforms.back();
		outSlot = region.slotOffset++;
		--region.count;
		outBufferIdx = region.bufferIdx;

		if(region.count == 0)
			mAvailableTransforms.pop_back();
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::releaseTransformSlot(size_t bufferIdx, GameEntityTransform *transform) {
		//Try to prevent a lot of fragmentation by adding the slot to an existing region.
		//It won't fully avoid it, but this is good/simple enough. If you want to fully
		//prevent fragmentation, see StagingBuffer::mergeContiguousBlocks implementation.
		const size_t slot = transform - mTransformBuffers[bufferIdx];

		vector<Region>::iterator itor = mAvailableTransforms.begin();
		vector<Region>::iterator end = mAvailableTransforms.end();

		while(itor != end) {
			if(itor->bufferIdx == bufferIdx &&
				(itor->slotOffset == slot + 1 || slot == itor->slotOffset + itor->count)) {
				break;
			}

			++itor;
		}

		if(itor != end) {
			if(itor->slotOffset == slot + 1)
				--itor->slotOffset;
			else //if( slot == itor->slot + itor->count )
				++itor->count;
		} else {
			mAvailableTransforms.push_back(Region(slot, 1, bufferIdx));
		}
	}
	//-----------------------------------------------------------------------------------
	Ogre::uint32 LevelManager::getScheduledForRemovalAvailableSlot(void) {
		if(mScheduledForRemovalCurrentSlot >= mScheduledForRemoval.size()) {
			if(mScheduledForRemovalAvailableSlots.empty()) {
				mScheduledForRemovalAvailableSlots.push_back(mScheduledForRemoval.size());
				mScheduledForRemoval.push_back(GameEntityVec());
			}

			mScheduledForRemovalCurrentSlot = mScheduledForRemovalAvailableSlots.back();
			mScheduledForRemovalAvailableSlots.pop_back();
		}

		return mScheduledForRemovalCurrentSlot;
	}
	//-----------------------------------------------------------------------------------
	void LevelManager::finishFrameParallel(void) {
		if(mScheduledForRemovalCurrentSlot < mScheduledForRemoval.size()) {
			logicSystem->queueSendMessage(graphicsSystem, Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
										   mScheduledForRemovalCurrentSlot);

			mScheduledForRemovalCurrentSlot = static_cast<size_t>(-1);
		}
	}
}
