
//
//#if USE_NV_STEREO 
//#	ifdef _WIN64
//#	pragma comment(lib,"amd64/nvapi64.lib")
//#	else
//#	pragma comment(lib,"../x86/nvapi.lib")
//
//#	endif 
//#endif 

#ifdef _WIN64

#	ifdef _DEBUG
#pragma  comment(lib,"boost_atomic-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_thread-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_system-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_filesystem-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"OIS_d.lib;dbghelp.lib")
#pragma  comment(lib,"OgreMain_d.lib")
#pragma  comment(lib,"OgreHLMS_d.lib")
#pragma  comment(lib,"OgreOverlay_d.lib")

#	else

#pragma  comment(lib,"boost_atomic-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_thread-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_system-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_filesystem-vc100-mt-1_55.lib")
#pragma  comment(lib,"OIS.lib")
#pragma  comment(lib,"OgreMain.lib")
#pragma  comment(lib,"OgreHLMS.lib")
#pragma  comment(lib,"OgreOverlay.lib")
#pragma  comment(lib,"OgreRTShaderSystem.lib")

#	endif

#else  
// win32

// debug
#	ifdef _DEBUG
#pragma  comment(lib,"boost_atomic-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_thread-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_system-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"boost_filesystem-vc100-mt-gd-1_55.lib")
#pragma  comment(lib,"OIS_d.lib")
#pragma  comment(lib,"OgreMain_d.lib")
#pragma  comment(lib,"OgreHLMS_d.lib")
#pragma  comment(lib,"OgreOverlay_d.lib")
#pragma  comment(lib,"OgreRTShaderSystem_d.lib")
//#pragma  comment(lib,"RenderSystem_Direct3D11_d.lib")
//#pragma  comment(lib,"RenderSystem_Direct3D9_d.lib")

#	else
//release

#pragma  comment(lib,"boost_atomic-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_thread-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_system-vc100-mt-1_55.lib")
#pragma  comment(lib,"boost_filesystem-vc100-mt-1_55.lib")
#pragma  comment(lib,"OIS.lib")
#pragma  comment(lib,"OgreMain.lib")
#pragma  comment(lib,"OgreHLMS.lib")
#pragma  comment(lib,"OgreOverlay.lib")
#pragma  comment(lib,"OgreRTShaderSystem.lib")
#	endif 

#endif

#ifndef NO_BASEAPPFRAME
#pragma  comment(lib,"BaseAppFrame.lib")
#endif 

