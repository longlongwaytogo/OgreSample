/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::go(bool bUseRtss)
{
	mbUseRtss = bUseRtss;

#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
	mResourcesCfg = m_ResourcePath + "resources_all_d.cfg";
	mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
	mResourcesCfg = "resources_all_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
	mResourcesCfg = m_ResourcePath + "resources.cfg";
	mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
#endif

	if (!setup())
		return;

	mRoot->startRendering();

	// Clean up
	destroyScene();
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.31, 0.31, 0.31));
	mSceneMgr->setSkyDome(true,"Examples/CloudySky",5,8);

	// set shadow properties
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	mSceneMgr->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTextureSize(1024);
	mSceneMgr->setShadowTextureCount(1);

	// disable default camera control so the character can do its own
	//mCameraMan->setStyle(CS_MANUAL);

	// use a small amount of ambient lighting
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

	// add a bright light above the scene
	Ogre::Light* light = mSceneMgr->createLight();
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(Ogre::ColourValue::White);




	////mSceneMgr->setShadowCameraSetup();
	//mSceneMgr->setShadowTextureCasterMaterial("Nombre material");
	//sm->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
//	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// plane
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	Ogre::MeshManager::getSingleton().createPlane("Myplane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	 	plane,1500, 1500, 100, 100, true, 1, 200, 200, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity( "plane", "Myplane" );
	/*pPlaneEnt->setQueryFlags(CParabola::mQueryFlags);*/
	pPlaneEnt->setQueryFlags(0xF);
	pPlaneEnt->setMaterialName("Examples/Rockwall");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* planeNode=mSceneMgr->getRootSceneNode()->createChildSceneNode();
	planeNode->attachObject(pPlaneEnt);
	planeNode->setPosition(Ogre::Vector3::ZERO);
	 
	// House
	Ogre::Entity* pEnt;
	pEnt = mSceneMgr->createEntity( "house1", "tudorhouse.mesh" );
	pEnt->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	Ogre::SceneNode* n1 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 5.5, 5));
	n1->scale(0.01f,0.01f,0.01f);
	n1->attachObject( pEnt );
	 
	pEnt = mSceneMgr->createEntity( "house2", "tudorhouse.mesh" );
	pEnt->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	Ogre::SceneNode* n2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 5.5, -5));
	n2->scale(0.01f,0.01f,0.01f);
	n2->attachObject( pEnt );
	//ninja
	pEnt = mSceneMgr->createEntity( "ninja", "ninja.mesh" );
	pEnt->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	Ogre::SceneNode* ninjaNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(6, 0, 5));
	ninjaNode->attachObject(pEnt);
	ninjaNode->setScale(0.01f,0.01f,0.01f);
	 
	//razor
	pEnt = mSceneMgr->createEntity( "razor", "razor.mesh" );
	pEnt->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	Ogre::SceneNode* scenenodeRazor = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(5, 10, -3));
	scenenodeRazor->scale(0.02f,0.02f,0.02f);
	scenenodeRazor->attachObject( pEnt );
	//SinbadBody
	Ogre::Entity* mBodyEnt = mSceneMgr->createEntity( "SinbadBody", "Sinbad.mesh" );
	Ogre::SceneNode* SinbadScenenode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(6, 1, -5));
	mBodyEnt->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	SinbadScenenode->scale(0.2f,0.2f,0.2f);
	SinbadScenenode->attachObject( mBodyEnt );
	Ogre::Entity* mSword1 = mSceneMgr->createEntity("SinbadSword1", "Sword.mesh");
	mSword1->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	Ogre::Entity* mSword2 = mSceneMgr->createEntity("SinbadSword2", "Sword.mesh");
	mSword2->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	mBodyEnt->attachObjectToBone("Sheath.L", mSword1);
	mBodyEnt->attachObjectToBone("Sheath.R", mSword2);
	 


}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go(true);
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
