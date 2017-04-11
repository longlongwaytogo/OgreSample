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
#include "Triangle.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
  
	// Create your scene here :)
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.31, 0.31, 0.31)); 
	Ogre::Light* light = mSceneMgr->createLight("sun");
	light->setPosition(200,200,200);
	light->setCastShadows(true);
	light->setDiffuseColour(1.0f,1.0f,1.0f);


	//Ogre::Light* light = mSceneMgr->createLight();
	//light->setType(Ogre::Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(Ogre::ColourValue::White);

	//light ->setCastShadows(true);
	//light ->setShadowFarDistance (100);

	////mSceneMgr->setShadowCameraSetup();
	//mSceneMgr->setShadowTextureCasterMaterial("Nombre material");
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE/*SHADOWTYPE_STENCIL_ADDITIVE*/);


	//mSceneMgr->setSkyDome(true,"ShaderLearn/SkyDome/CloudySky",5,8);
	mSceneMgr->setSkyBox(true,"ShaderLearn/Skybox/CloudySky");

	// plane
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	Ogre::MeshManager::getSingleton().createPlane("Myplane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,1500, 1500, 100, 100, true, 1, 200, 200, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity( "plane", "Myplane" );

	pPlaneEnt->setMaterialName("ShaderLearn/ground/grass");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* planeNode=mSceneMgr->getRootSceneNode()->createChildSceneNode();
	planeNode->attachObject(pPlaneEnt);
	planeNode->setPosition(Ogre::Vector3(0.0f,0.0f,-10.0f));

	//Ogre::String triangleName("triangle1");
	//CTriangle::Get()->createTriangle(triangleName,
	//		
	//		Ogre::Vector3(100,0,-50),
	//		Ogre::Vector3(0,50,-50),
	//		Ogre::Vector3(-100,0,-50),
	//		
	//		Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f)
	//		);


	// House
	Ogre::Entity* pEnt;
	pEnt = mSceneMgr->createEntity( "house1", "tudorhouse.mesh" );
	pEnt->setMaterialName("ShaderLearn/TudorHouse");

	pEnt->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	Ogre::SceneNode* n1 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 5.5, 5));
	n1->scale(0.01f,0.01f,0.01f);
	n1->attachObject( pEnt );

	pEnt = mSceneMgr->createEntity( "house2", "tudorhouse.mesh" );
	pEnt->setMaterialName("ShaderLearn/TudorHouse");
	pEnt->setQueryFlags(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	Ogre::SceneNode* n2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 5.5, -5));
	n2->scale(0.01f,0.01f,0.01f);
	n2->attachObject( pEnt );
	//ninja
	pEnt = mSceneMgr->createEntity( "ninja", "ninja.mesh" );
	pEnt->setMaterialName("ShaderLearn/Ninja");

	pEnt->setQueryFlags(Ogre::SceneManager::ENTITY_TYPE_MASK);
	Ogre::SceneNode* ninjaNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(6, 0, 5));
	ninjaNode->attachObject(pEnt);
	ninjaNode->setScale(0.01f,0.01f,0.01f);

	

	
	// Create your scene here :)
}

void TutorialApplication::createCamera(void)
{
	BaseApplication::createCamera();
	// Create the camera

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,70,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,1));
	mCamera->setNearClipDistance(1);

	

}

//---------------------------------------------------------------------------

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"
//#endif
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
//#else
//	int main(int argc, char *argv[])
//#endif
//	{
//		// Create application object
//		TutorialApplication app;
//
//		try {
//			app.go();
//		} catch(Ogre::Exception& e)  {
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//			MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//			std::cerr << "An exception has occurred: " <<
//				e.getFullDescription().c_str() << std::endl;
//#endif
//		}
//
//		return 0;
//	}
//
//#ifdef __cplusplus
//}
//#endif

//---------------------------------------------------------------------------
