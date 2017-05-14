
#ifndef _ZS_GameEntity_H_
#define _ZS_GameEntity_H_

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgreStringVector.h"
#include "Behaviour.h"
#include "Animation/OgreSkeletonInstance.h"
#include "AnimationController.h"

namespace ZS
{
    #define NUM_GAME_ENTITY_BUFFERS 16

    enum MovableObjectType
    {
        MoTypeItem,
		MoTypeItemInk,
		MoTypeItemSkeleton,
		MoTypeItemV1Mesh,
		MoTypeItemV1MeshTAMWrap,
        MoTypeEntity,
        NumMovableObjectType
    };

    struct MovableObjectDefinition
    {
        Ogre::String        meshName;
        Ogre::String        resourceGroup;
        Ogre::StringVector  submeshMaterials;
        MovableObjectType   moType;
    };

    struct GameEntityTransform
    {
        Ogre::Vector3       vPos;
        Ogre::Quaternion    qRot;
        Ogre::Vector3       vScale;
    };

    struct GameEntity
    {
    private:
        Ogre::uint32 mId;

    public:
        //----------------------------------------
        // Only used by Graphics thread
        //----------------------------------------
        Ogre::SceneNode         *mSceneNode;
        Ogre::MovableObject     *mMovableObject; //Could be Entity, InstancedEntity, Item.

		bool hasAnimation;
		AnimationController* animationController;

        //Your custom pointers go here, i.e. physics representation.
        //used only by Logic thread (hkpEntity, btRigidBody, etc)
		Behaviour* behaviour;

        //----------------------------------------
        // Used by both Logic and Graphics threads
        //----------------------------------------
        GameEntityTransform     *mTransform[NUM_GAME_ENTITY_BUFFERS];
        Ogre::SceneMemoryMgrTypes       mType;

        //----------------------------------------
        // Read-only
        //----------------------------------------
        MovableObjectDefinition const   *mMoDefinition;
        size_t                   mTransformBufferIdx;

        GameEntity( Ogre::uint32 id, const MovableObjectDefinition *moDefinition, Behaviour* _behaviour,
                    Ogre::SceneMemoryMgrTypes type) :
            mId( id ),
            mSceneNode( nullptr ),
            mMovableObject( nullptr ),
			hasAnimation(false),
			animationController(nullptr),
			behaviour(_behaviour),
            mType( type ),
            mMoDefinition( moDefinition ),
            mTransformBufferIdx( 0 )
        {
            for( int i=0; i<NUM_GAME_ENTITY_BUFFERS; ++i )
                mTransform[i] = nullptr;
        }

        Ogre::uint32 getId(void) const          { return mId; }

        bool operator < ( const GameEntity *_r ) const
        {
            return mId < _r->mId;
        }
    };

    typedef std::vector<GameEntity*> GameEntityVec;
}

#endif
