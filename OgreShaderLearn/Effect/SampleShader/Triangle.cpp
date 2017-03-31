

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
	manual->begin("ShaderLearn/Base_Color", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

	// define start and end point
	manual->position(v1);
	//manual->textureCoord(0,0);
	manual->colour(clr);

	manual->position(v2);
	//manual->textureCoord(0,0);
	manual->colour(clr);

	manual->position(v3);
	//manual->textureCoord(0,0);
	manual->colour(clr);


	manual->index(0);
	manual->index(1);
	manual->index(2);

	// tell Ogre, your definition has finished
	manual->end();

	// add ManualObject to the RootSceneNode (so it will be visible)
	mgr->getRootSceneNode()->attachObject(manual);


	return obj;

}