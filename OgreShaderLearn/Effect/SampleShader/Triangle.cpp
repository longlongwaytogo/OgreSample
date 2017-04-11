

#include "Triangle.h"
#include <OgreRoot.h>
#include <OgreSceneManager.h>

CTriangle* CTriangle::instance = NULL;
Ogre::MovableObject* CTriangle::createTriangle(Ogre::String& name,Ogre::Vector3 v1,Ogre::Vector3 v2, Ogre::Vector3 v3,Ogre::ColourValue clr /*= Ogre::ColourValue::White*/)
{
	Ogre::Root& root = Ogre::Root::getSingleton();
	Ogre::SceneManager* mgr = root.getSceneManager("SceneManagerInstance1");
	Ogre::MovableObject* obj = NULL;
	
	Ogre::ManualObject* manual = mgr->createManualObject(name);
	manual->begin("ShaderLearn/Base_Color", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	// define start and end point
	manual->position(v1);
    //manual->textureCoord(0,0);
	manual->colour(clr);
	manual->normal(0,0,1);

	manual->position(v2);
	//manual->textureCoord(0.5,0.5);
	manual->colour(clr);
	manual->normal(0,0,1);

	manual->position(v3);
	//manual->textureCoord(1,0);
	manual->colour(clr);
	manual->normal(0,0,1);

	manual->index(0);
	manual->index(1);
	manual->index(2);

	 manual->triangle(0, 1, 2);
	// tell Ogre, your definition has finished
	manual->end();

	// add ManualObject to the RootSceneNode (so it will be visible)
	mgr->getRootSceneNode()->attachObject(manual);


	return obj;

}