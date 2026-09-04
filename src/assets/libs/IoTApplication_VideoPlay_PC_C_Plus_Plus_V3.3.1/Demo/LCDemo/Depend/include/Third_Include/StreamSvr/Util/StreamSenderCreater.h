#ifndef __INCLUDE_DAHUA_STREAMSVR_STREAM_SENDER_CREATER_H__
#define __INCLUDE_DAHUA_STREAMSVR_STREAM_SENDER_CREATER_H__

#include "Component/Unknown.h"
#include "Infra/Version.h"
#include "NetFramework/MediaStreamSender.h"
#include "StreamSvr/Defs.h"

namespace Dahua{
namespace StreamSvr{

///< CMediaStreamSender 创建类
class STREAMSVR_API CStreamSenderCreater : public Component::IUnknown
{
	CStreamSenderCreater(){}
	~CStreamSenderCreater(){}
public:

	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual CStreamSenderCreater* create() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "ISenderCreateFactory";}
	};
	void destroy(){delete this;}

	Infra::CVersion getVersion()
	{
		return Infra::CVersion("CStreamSenderCreater", 1, 0, 0, "$Rev: 0 $", __DATE__);
	}
	static CStreamSenderCreater* create(){return new CStreamSenderCreater;}
	
	NetFramework::CMediaStreamSender* CreateSender();
};

class CStreamSenderCreaterFactory : public CStreamSenderCreater::IFactory
{
public:
	CStreamSenderCreaterFactory(){registerFactory(iid());}
	~CStreamSenderCreaterFactory(){unregisterFactory(iid());}

	const char* clsid() {return "Local";}

	CStreamSenderCreater* create()
	{
		return CStreamSenderCreater::create();
	}
};

typedef Component::TComPtr<CStreamSenderCreater> SenderCreaterPtr;
}
}
#endif
