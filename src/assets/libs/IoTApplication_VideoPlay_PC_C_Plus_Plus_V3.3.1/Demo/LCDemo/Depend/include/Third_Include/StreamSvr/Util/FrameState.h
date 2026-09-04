#ifndef __INCLUDE_DAHUA_FRAME_STATE_H__
#define __INCLUDE_DAHUA_FRAME_STATE_H__

#include "StreamSvr/Defs.h"
#include "Infra/File.h"
#include "Utils/NumberStat.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamSvr/Media/MediaSession.h"
#include "NetFramework/MediaStreamSender.h"
#include "Component/Unknown.h"

namespace Dahua{
namespace StreamSvr{

///\brief 发送的帧信息
class CFrameInfo : public NetFramework::CMediaPacket
{
public:
	struct FrameInfo
	{
		int channel_id;			///< 发送媒体id 为交织头通道号
		int frame_index;		///< 发送媒体帧索引
		int frame_type;			///< 发送媒体帧类型
		uint64_t put_time;		///< 送入发送工具的时间戳
		uint64_t pts;			///< 音视频帧产生时的时间戳		
		uint64_t ptsBeforeEnc;	///< 音视频帧编码前的时间戳
		uint64_t ptsAfterEnc;	///< 音视频帧编码后的时间戳
		uint64_t ptsLib;		///< 编码库从驱动取到本数据包的时间戳
		uint64_t ptsApp;		///< 应用层取到本数据包后的时间戳
		uint64_t ptsNet;		///< 网络模块取到本数据包后的时间戳

		FrameInfo()
		{
			channel_id		= 0;
			frame_index		= 0;
			frame_type		= 0;
			put_time		= 0;
			pts				= 0;
			ptsBeforeEnc	= 0;
			ptsAfterEnc		= 0;
			ptsLib			= 0;
			ptsApp			= 0;
			ptsNet			= 0;
		}
	}m_frameInfo;

	CFrameInfo();

	// 供网络框架使用的销毁函数, 注意内存不要在上层delete
	void Release();

	unsigned char* GetBuffer();
private:
	~CFrameInfo();
};


///\brief 帧状态信息统计组件,负责统计帧的延时统计及丢帧统计信息
class STREAMSVR_API IFrameState : public Component::IUnknown
{
public:
	///\brief 帧耗时调试相关配置
	typedef enum 
	{
		fstatPrint = 0,      ///< 打开或关闭帧耗时调试
		fstatWfile,			 ///< 打开或关闭耗时调试写入文件
		fstatWarning,		 ///< 设置帧耗时异常阈值
	}fstatParamConfig;
	
	///\brief 网络框架发送工具配置
	enum frametype
	{
		frameNaa = 0,		///< NNA发送工具
		frameMedia,			///<MediaStreamSender发送工具
	};
	
	///\brief 帧信息不同功能使能位选项
	enum fstatevent
	{
		fstatlostframe     = 0x1,	///< 丢帧事件使能位
		fstatframeinfo     = 0x2,	///< 帧信息回调使能位
		fstatdropframecalc = 0x4,	///< 丢帧事件统计使能位
		fstatdelaycalc	   = 0x8,	///< 延时事件统计使能位
	};

	///\brief 帧发送事件配置
	struct FrameStateConfig
	{
		uint32_t eventmask;				///< 使能的事件掩码,见fstatevent
		uint32_t dropduration;			///< 丢帧统计的周期, 单位毫秒
		uint32_t delayduration;			///< 帧延时统计的周期, 单位毫秒
		uint32_t videodelaythreshold;	///< 视频帧延时的阈值,单位毫秒
		uint32_t audiodelaythreshold;	///< 音频帧延时的阈值,单位毫秒

		FrameStateConfig(): eventmask(0), dropduration(DEFAULT_CHECKLOSTFRAME_DURATION * 1000), 
								 delayduration(DEFAULT_CHECKFRAMEDELAY_DURATION * 1000), videodelaythreshold(DEFAULT_CHECKFRAMEDELAY_VIDEOTHRESHOLD), audiodelaythreshold(DEFAULT_CHECKFRAMEDELAY_AUDIOTHRESHOLD)
		{}
	};

public:
	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IFrameState 对象实例, 设置静态变量时, observer可为NULL
		virtual IFrameState* create(IMediaEventObserver* observer) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "StreamSvr::FrameState";}
	};	
	
public:
	/// 析构函数
	virtual ~IFrameState(){}

public:	
	///\brief 设置网络延时调试配置
	///\param [in] config-配置名
	///\param [in] argv-配置对应的参数
	virtual bool SetFrameStatParm(fstatParamConfig config, void *argv)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得网络延时调试使能状态
	///\return 网络延时调试使能状态
	virtual bool GetFrametimestateEnable()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置帧状态事件配置
	///\param[in]  config    - 帧状态配置
	///\return true - 是, false-否
	virtual bool setConfig(FrameStateConfig &config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\breif 获得发送帧信息接收使能状态
	///\return 帧信息接收的使能状态
	virtual bool getSendProcFlag()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\音视频数据信息回调函数
	///\param [in] packet-发送完数据帧的信息
	///\param [in] infoSize - 已发送帧信息大小
	///\param [in] frameSize - 已发送帧数据大小
	virtual bool onSendProc(NetFramework::CMediaPacket* packet, int infoSize, int frameSize)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\统计帧耗时函数
	///\param [in] FrameInfo-发送完数据帧的信息		
	virtual bool FrameStat(CFrameInfo *frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得naa 库发送的帧信息
	///\param[out]  frameinfo  -  存放帧信息的指针
	///\param[in]   channelid  -  发送的帧通道号,即交织头通道
	///\param[in]   frametype  -  发送帧的帧类型
	///\param[in]   frame      -  NNA发送帧的指针
	///\param[in]   put_time   -  NNA发送帧之前的时间
	///\return 0--成功  -1--不需要通知上层,一般指rtcp 等非大华帧
	virtual bool GetFrameInfo(CFrameInfo *frameinfo, int channelid, int frametype , void *frame, uint64_t put_time)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief TCP方式下帧数据未发送完全信息回调函数
	///\param[in]  frameinfo      存放帧信息的指针
	///\param[in]  sendbyte       已发送长度
	///\param[in]  length         应发送长度
	virtual bool onSendPartProc(CFrameInfo *frameinfo, int sendbyte, int length)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 待发送帧统计回调函数
	///\param[in]  channelId     媒体的交织通道
	///\param[in]  type      	 帧类型
	///\param[in]  putnaapts     帧送入Naa库的时间
	///\param[in]  encodepts     帧编码时间
	///\param[in]  length        帧长度信息
	virtual bool onInputFrame(int channelId, int type, uint64_t putnaapts, uint64_t encodepts, int length)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 是否需要统计码流信息
	///\return true - 是, false-否
	virtual bool IsNeedCalcBitrate()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief TCP方式下帧数据未发送完全信息回调函数
	///\param[in]  proc      帧发送回调指针
	///\return true 成功, false 失败
	virtual bool getOnSendProc(NetFramework::CMediaStreamSender::Proc &proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(21)

};

typedef Dahua::Component::TComPtr<IFrameState> IFrameStatePtr;


}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_FRAME_STATE_H__
