/**
Copyright 2016 zzsoft
Author:   2016/11/23
Description: 开启Ogre对固定管线的支持，使用Ogre的RTSS机制
*/

#ifndef VRAPPENGINE_RTSSHELPER_H
#define VRAPPENGINE_RTSSHELPER_H

#include <Ogre.h>
#include <OgreRTShaderSystem.h>

namespace Rtss
{
	/**
	*	材质监听类
	* 
	*   监听材质不支持可编程管线的材质，动态创建RTSS材质， 模拟固定管线
	*/
	class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
	{
	public:

		ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
		{
			mShaderGenerator = pShaderGenerator;			
		}

		/** This is the hook point where shader based technique will be created.
		It will be called whenever the material manager won't find appropriate technique
		that satisfy the target scheme name. If the scheme name is out target RT Shader System
		scheme name we will try to create shader generated technique for it. 
		*/
		virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, 
			const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, 
			const Ogre::Renderable* rend)
		{	
			Ogre::Technique* generatedTech = NULL;

			// Case this is the default shader generator scheme.
			if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
			{
				bool techniqueCreated;

				// Create shader generated technique for this material.
				techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
					originalMaterial->getName(), 
					Ogre::MaterialManager::DEFAULT_SCHEME_NAME, 
					schemeName);	

				// Case technique registration succeeded.
				if (techniqueCreated)
				{
					// Force creating the shaders for the generated technique.
					mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());

					// Grab the generated technique.
					Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

					while (itTech.hasMoreElements())
					{
						Ogre::Technique* curTech = itTech.getNext();

						if (curTech->getSchemeName() == schemeName)
						{
							generatedTech = curTech;
							break;
						}
					}				
				}
			}

			return generatedTech;
		}

	protected:	
		Ogre::RTShader::ShaderGenerator*	mShaderGenerator;			// The shader generator instance.		
	};

	/**
	*	Rtss 助手类
	*
	*   用于初始化，加载，释放RTSS机制
	*/
	class RtssHelper
	{
	public:
		RtssHelper(void):mSceneMgr(nullptr),
		mRoot(nullptr),
		mShaderGenerator(nullptr),
		mMaterialMgrListener(nullptr)
		{
		}

		~RtssHelper(void)
		{}
	public:
		bool initRtss(Ogre::SceneManager* sceneMgr,Ogre::RenderWindow* window)
		{
			mRoot = Ogre::Root::getSingletonPtr();
			// Initialize shader generator.
			// Must be before resource loading in order to allow parsing extended material attributes.
			bool success = initShaderGen(sceneMgr);/*initialiseRTShaderSystem(sm);*/
			if (!success) 
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, 
					"Shader Generator Initialization failed - Core shader libs path not found", 
					"SampleBrowser::createDummyScene");
				return false;
			}

			if(window)
			{
				Ogre::Viewport* viewPort = window->getViewport(0);
				viewPort->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

			}
			if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
			{
				// creates shaders for base material BaseWhite using the RTSS
				Ogre::MaterialPtr baseWhite = Ogre::MaterialManager::getSingleton().getByName("BaseWhite",
					Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
				baseWhite->setLightingEnabled(false);
				bool ret = mShaderGenerator->createShaderBasedTechnique(
					"BaseWhite", 
					Ogre::MaterialManager::DEFAULT_SCHEME_NAME, 
					Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);	
				ret = mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,"BaseWhite");
				if(baseWhite->getNumTechniques() > 1)
				{
					baseWhite->getTechnique(0)->getPass(0)->setVertexProgram(
						baseWhite->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
					baseWhite->getTechnique(0)->getPass(0)->setFragmentProgram(
						baseWhite->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
				}

				// creates shaders for base material BaseWhiteNoLighting using the RTSS
				mShaderGenerator->createShaderBasedTechnique(
					"BaseWhiteNoLighting", 
					Ogre::MaterialManager::DEFAULT_SCHEME_NAME, 
					Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);	
				mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME, 
					"BaseWhiteNoLighting");
				Ogre::MaterialPtr baseWhiteNoLighting = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting", 
					Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
				if(baseWhite->getNumTechniques() > 1)
				{
					baseWhiteNoLighting->getTechnique(0)->getPass(0)->setVertexProgram(
						baseWhiteNoLighting->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
					baseWhiteNoLighting->getTechnique(0)->getPass(0)->setFragmentProgram(
						baseWhiteNoLighting->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
				}
				return true;
			}
			return true;

		}

		bool initShaderGen(Ogre::SceneManager* sceneMgr)
		{
			if (Ogre::RTShader::ShaderGenerator::initialize())
			{
				mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

				mShaderGenerator->addSceneManager(sceneMgr);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_NACL && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
			// Setup core libraries and shader cache path.
				Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
				Ogre::StringVector::iterator itGroup = groupVector.begin();
				Ogre::StringVector::iterator itGroupEnd = groupVector.end();
				Ogre::String shaderCoreLibsPath;
				Ogre::String shaderCachePath;

				for (; itGroup != itGroupEnd; ++itGroup)
				{
					Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
					Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
					Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
					bool coreLibsFound = false;

					// Try to find the location of the core shader lib functions and use it
					// as shader cache path as well - this will reduce the number of generated files
					// when running from different directories.
					for (; it != itEnd; ++it)
					{
						if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
						{
							shaderCoreLibsPath = (*it)->archive->getName() + "/cache/";
							shaderCachePath = shaderCoreLibsPath;
							coreLibsFound = true;
							break;
						}
					}
					// Core libs path found in the current group.
					if (coreLibsFound) 
						break; 
				}

				// Core shader libs not found -> shader generating will fail.
				if (shaderCoreLibsPath.empty())			
					return false;			

#ifdef _RTSS_WRITE_SHADERS_TO_DISK
			// Set shader cache path.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
				shaderCachePath = Ogre::macCachePath();
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
				shaderCachePath = Ogre::macCachePath() + "/org.ogre3d.RTShaderCache";
#endif
				mShaderGenerator->setShaderCachePath(shaderCachePath);		
#endif
#endif
			// Create and register the material manager listener if it doesn't exist yet.
				if (mMaterialMgrListener == NULL) {
					mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
					Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
				}
			}
			return true;
		}
		void finish()
		{
			// Restore default scheme.
			Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

			// Unregister the material manager listener.
			if (mMaterialMgrListener != NULL)
			{			
				Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
				delete mMaterialMgrListener;
				mMaterialMgrListener = NULL;
			}

			// Destroy RTShader system.
			if (mShaderGenerator != NULL)
			{				
				Ogre::RTShader::ShaderGenerator::destroy();
				mShaderGenerator = NULL;
			}
		}
		void locateRtssResource()
		{
			// add 
			Ogre::String sec, type, arch;
			const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList("General");
			arch = genLocs.front()->archive->getName();


			arch = Ogre::StringUtil::replaceAll(arch, "Media/../../Tests/Media", "");  
			arch = Ogre::StringUtil::replaceAll(arch, "media/../../Tests/Media", ""); 

			type = "FileSystem";
			sec = "Popular";

			// Add locations for supported shader languages
			if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
			}
			else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
			{
				if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
				{
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
				}
				else
				{
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
				}

				if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
				{
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
				}
			}
			else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
			}
#			ifdef OGRE_BUILD_PLUGIN_CG
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/Cg", type, sec);
#			endif


			if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSLES", type, sec);
			}
			else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSL", type, sec);
				if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
				{
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSL150", type, sec);
				}
			}
			else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/HLSL", type, sec);
			}
#			ifdef OGRE_BUILD_PLUGIN_CG
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/Cg", type, sec);
#			endif

		}

		Ogre::RTShader::ShaderGenerator* GetShaderGen()
		{
			return  mShaderGenerator;
		}

	private:
		Ogre::SceneManager* mSceneMgr;
		Ogre::Root*			mRoot;
		Ogre::RTShader::ShaderGenerator* mShaderGenerator;					// The Shader generator instance.
		ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;	// Shader generator material manager listener.	
	};
}

#endif //VRAPPENGINE_RTSSHELPER_H
