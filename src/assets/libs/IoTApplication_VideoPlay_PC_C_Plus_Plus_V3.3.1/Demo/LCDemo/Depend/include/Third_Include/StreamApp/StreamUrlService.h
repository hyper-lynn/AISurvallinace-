#ifndef __INCLUDE_DAHUA_STREAMAPP_STREAMURL_SERVICE_H__
#define __INCLUDE_DAHUA_STREAMAPP_STREAMURL_SERVICE_H__

#include <string>
#include <vector>
#include <Component/Unknown.h>
#include "StreamApp/Defs.h"
#include "Infra/Function.h"


namespace Dahua {
namespace StreamApp {

///\brief 流媒体协议url 服务组件
class STREAMAPP_API IStreamUrlService : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		///\brief 取 IStreamUrlService 对象实例
		///\return IStreamUrlService 对象实例
		virtual IStreamUrlService* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "StreamApp::StreamUrlService";}
	};

	///\brief 流媒体协议
	enum StreamProtocol
	{
		RtmpProtocol = 0,			///< Rtmp 协议
		ProtocolNum,
	};

	///\brief 流媒体url 类型
	enum StreamUrlType
	{
		StreamUrlLive = 0,			///< 直播url
		StreamUrlVodFile,			///< 按文件回放url
		StreamUrlVodTimeSection,	///< 按时间段回放url
		StreamUrlTypeNum,			///< url 类型数目
	};

	///\brief 流媒体直播url 选项信息 256字节
	typedef struct StreamUrlOpt
	{
		int channel;				///< 视频通道号,从1开始
		int subtype;				///< 码流类型
		char filename[128];			///< 文件名称信息
		Infra::CTime starttime; 	///< 回放开始时间
		Infra::CTime endtime;		///< 回放结束时间
		int reserved[14];
	} StreamUrlOpt;

	///\brief url 中流源部分的url 组装函数, 不包含令牌等鉴权信息
	///\param [in] 第一个int 流媒体业务协议,  见StreamProtocol
	///\param [in] 第二个int 流类型(实时/文件), 见StreamUrlType
	///\param [in/out] StreamUrlOpt& 流选项信息, 注意按文件回放时,需要回传通道号信息
	///\param [out] std::vector<std::string>& 流媒体业务对应的url , vector 是为了支持可能返回多个url的情况, 例如跨文件回放
	///\return true 成功, false 失败
	typedef	Infra::TFunction4<bool, int, int, StreamUrlOpt&, std::vector<std::string>& > SourceUrlProc;

protected:
	///\brief 析构函数
	virtual ~IStreamUrlService(){}

public:
	///\brief 获得流媒体协议对应的url , 包含 token 令牌信息
	///\param [in] protocol 流媒体业务协议,  见StreamProtocol
	///\param [in] type 流类型(实时/文件), 见StreamUrlType
	///\param [in] streamopt 流选项信息
	///\param [out] url 流媒体业务对应的url , vector 是为了支持可能返回多个url的情况, 例如跨文件回放
	///\return true 成功, false 失败
	virtual bool getUrl(int protocol, int type, StreamUrlOpt &streamopt, std::vector<std::string> &url)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 注册对应协议url 中流源部分的url 组装函数
	///\param [in] protocol 流媒体协议,  见StreamProtocol
	///\param [in] type 流媒体url 类型, 见StreamUrlType
	///\param [in] proc url中流源部分的url 组装函数
	///\return true 成功, false 失败
	virtual bool registerSourceProc(int protocol, int type, SourceUrlProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 校验url 是否有效
	///\param [in/out] url 流媒体协议的url , 传入包括token 的url, 经过校验后,会将token 信息去掉
	///\return true url有效, false url无效
	virtual bool verifyUrl(std::string &url)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	DAHUA_COMPONENT_FUNCTION_REVSERVED(29)
};

typedef Component::TComPtr<IStreamUrlService> IStreamUrlServicePtr;

}//StreamApp
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMAPP_STREAMURL_SERVICE_H__

