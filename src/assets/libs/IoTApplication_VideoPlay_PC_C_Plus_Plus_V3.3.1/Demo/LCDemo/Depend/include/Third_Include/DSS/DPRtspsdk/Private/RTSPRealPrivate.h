#ifdef DP_REST_PLATFORM_SDK

#ifndef __RTSPSDK_RTSPREALPRIVATE_H__
#define __RTSPSDK_RTSPREALPRIVATE_H__

#include "Define.h"
#include "Export/RTSPReal.h"
#include "Common/Pattern/Observable.h"

namespace RTSPSDK
{
	class CRTSPEntityReal;

	class CRTSPRealPrivate
	{
	public:
		CRTSPRealPrivate();
		virtual ~CRTSPRealPrivate();

	public:
		int StartVideo(const VideoParam_t& stuVideoparam, fMediaDataCallback funCB, void* pCBParam);
		int StopVideo();
		bool RegisterObserver(IRTSPRealObserver* pObserver);
		bool UnRegisterObserver(IRTSPRealObserver* pObserver);

	private:
		boost_shared_ptr<CRTSPEntityReal>  m_pRTSPEntity;

	};
}




#endif  //__RTSPSDK_RTSPREALPRIVATE_H__

#endif
