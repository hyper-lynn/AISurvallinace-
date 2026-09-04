#ifdef DP_REST_PLATFORM_SDK

#ifndef __RTSPSDK_RTSPTALKPRIVATE_H__
#define __RTSPSDK_RTSPTALKPRIVATE_H__

#include "Define.h"
#include "Export/RTSPTalk.h"
#include "Common/Pattern/Observable.h"

namespace RTSPSDK
{
	class CRTSPEntityTalk;

	class CRTSPTalkPrivate
	{
	public:
		CRTSPTalkPrivate();
		virtual ~CRTSPTalkPrivate();

		int StartTalk(const TalkParam_t& stuParam, fMediaDataCallback funCB, void* pCBParam);
		int StopTalk();
		int SendAudioData( char* pData, int dataLen);
		bool RegisterObserver(IRTSPTalkObserver* pObserver);
		bool UnRegisterObserver(IRTSPTalkObserver* pObserver);
		int GetId();

	private:
		boost_shared_ptr<CRTSPEntityTalk>  m_pRTSPEntity;
	};
}




#endif  //__RTSPSDK_RTSPTALKPRIVATE_H__

#endif
