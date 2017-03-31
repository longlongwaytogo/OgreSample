/*!
 * \file Triangle.h
 *
 * \author ZZ-XA
 * \date ÈýÔÂ 2017
 *
 * 
 */
#ifndef __TRIANGLE_INC_H__
#define __TRIANGLE_INC_H__
#include <Ogre.h>
#include <OgreManualObject.h>
class CTriangle
{
public:
	~CTriangle() { instance = nullptr; }

	static CTriangle* Get() 
	{
		if (instance == nullptr)
			instance = new CTriangle;
		return instance;
	}

	Ogre::MovableObject* createTriangle(Ogre::String& name, Ogre::Vector3 v1,Ogre::Vector3 v2, Ogre::Vector3 v3,Ogre::ColourValue clr = Ogre::ColourValue::White);
private:
	static CTriangle* instance;
};


#endif