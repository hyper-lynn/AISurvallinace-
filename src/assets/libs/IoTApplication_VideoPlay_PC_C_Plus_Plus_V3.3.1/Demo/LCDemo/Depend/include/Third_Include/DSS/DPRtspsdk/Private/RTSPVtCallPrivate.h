#ifdef DP_REST_PLATFORM_SDK

#ifndef __RTSPSDK_RTSPVTCALLPRIVATE_H__
#define __RTSPSDK_RTSPVTCALLPRIVATE_H__

#include "Define.h"
#include "Export/RTSPVtCall.h"
#include "Common/Pattern/Observable.h"

namespace RTSPSDK
{
	class CRTSPEntityVtCall;

	class CRTSPVtCallPrivate
	{
	public:
		CRTSPVtCallPrivate();
		virtual ~CRTSPVtCallPrivate();

		int PreStartVtCall(const PreStartVtCallParam_t& stuParam, PreStartVtCallResp_t& stuPreResp, fMediaDataCallback funCB, void* pCBParam);
		int StartVtCall(const StartVtCallParam_t& stuParam);
		int StopVtCall();
		int InviteVtCall(const InviteVtCallParam_t& stuParam, InviteVtCallResp_t& stuResp, fMediaDataCallback funCB, void* pCBParam);
		int ModifyVtCallStatus(int iCallStatus);
		int SendAudioData( char* pData, int dataLen);
		int GetId();
		bool RegisterObserver(IRTSPRealObserver* pObserver);
		bool UnRegisterObserver(IRTSPRealObserver* pObserver);

	private:
		boost_shared_ptr<CRTSPEntityVtCall>  m_pRTSPEntity;
	};
}




#endif  //__RTSPSDK_RTSPTALKPRIVATE_H__

#endif