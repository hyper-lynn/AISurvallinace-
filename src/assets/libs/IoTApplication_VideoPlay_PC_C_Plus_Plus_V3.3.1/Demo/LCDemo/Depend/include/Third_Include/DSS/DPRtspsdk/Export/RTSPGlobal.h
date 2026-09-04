#ifdef DP_REST_PLATFORM_SDK

#ifndef __RTSPSDK_GLOBAL_H__
#define __RTSPSDK_GLOBAL_H__

#ifdef WIN32
	#ifdef RTSPSDK_LIB
		#define RTSP_EXPORT __declspec(dllexport)
	#else
		#define RTSP_EXPORT __declspec(dllimport)
	#endif

	#define RTSP_CALLTYPE   __stdcall

#else
	#define RTSP_EXPORT 
	#define	RTSP_CALLTYPE 
#endif

#define BEGIN_NAMESPACE_RTSPSDK	namespace RTSPSDK {
#define END_NAMESPACE_RTSPSDK		}

#endif // __RTSPSDK_GLOBAL_H__

#endif
