#ifdef DP_REST_PLATFORM_SDK

#ifndef __RTSPSDK_RTSPPLAYBACKPRIVATE_H__
#define __RTSPSDK_RTSPPLAYBACKPRIVATE_H__

#include "Define.h"
#include "Export/RTSPPlayback.h"
#include "Common/Pattern/Observable.h"

namespace RTSPSDK
{
	class CRTSPEntityPB;

	class CRTSPPlaybackPrivate
	{
	public:
		CRTSPPlaybackPrivate();
		virtual ~CRTSPPlaybackPrivate();

		int StartPlayback(const StartPBParma_t& stuParam, fMediaDataCallback funCB, void* pCBParam);
		int StopPlayback();
		int PausePlayback(const PausePBParma_t& stuParam);
		int ResumePlayback(const ResumePBParma_t& stuParam);
		int SeekPlayabck(const SeekPBParma_t& stuParam);
		int SetPlaybackSpeed(const SetSpeedPBParma_t& stuParam);
		bool RegisterObserver(IRTSPPlaybackObserver* pObserver);
		bool UnRegisterObserver(IRTSPPlaybackObserver* pObserver);

	private:
		boost_shared_ptr<CRTSPEntityPB>  m_pRTSPEntity;
	};
}




#endif  //__RTSPSDK_RTSPPLAYBACKPRIVATE_H__

#endif
