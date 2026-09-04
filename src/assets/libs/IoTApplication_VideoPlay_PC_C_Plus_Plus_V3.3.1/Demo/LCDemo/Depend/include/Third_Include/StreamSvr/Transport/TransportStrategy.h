#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSPORTSTRATEGY_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSPORTSTRATEGY_H__

#include "StreamSvr/Defs.h"
#include "NetAutoAdaptor/EncodeConfig.h"
#include "NetAutoAdaptor/NAAPolicy.h"
#include "NetAutoAdaptor/StreamChannel.h"
#include "NetAutoAdaptor/MediaFrame.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "NetFramework/Sock.h"

namespace Dahua {
namespace StreamSvr {

// 外部使用前必须先调用过 globalInit静态函数
class CTransportStrategyImpl;///> 前向声明

class STREAMSVR_API CTransportStrategy
{
public:
	///\brief 通道发送策略,用于均匀发送
	struct ChannelPolicy
	{
		PolicyParam param;          ///< 发送策略配置
		int         maxRtpLen;      ///< RTP最大发送长度
		int         bitrate;        ///< 码流值大小
		int         bitrateCtrl;    ///< 0-CBR固定码流 1-VBR可变码流
		int         reserved[7];    ///< 保留字段
	
		ChannelPolicy()
		{
		    maxRtpLen = 1456;
		    bitrate = 0;
		    bitrateCtrl = 0;
		    memset(reserved, 0, sizeof(reserved));
		}
	};

	///\brief Naa传输通道初始化参数信息
	struct InitInfo
	{
		NetAutoAdaptor::SrcMode       src_mode;			///< 源类型
		NetAutoAdaptor::HandlePolicy  handlePolicy;		///< 处理策略 
		int 					      sendMode; 		///< 发送模式, 见NetAutoAdaptor::SendMode
		ConfigStreamSendStrategy      stream_config;	///< NAA码流缓存策略配置
		int                           transProtocol;	///< 传输协议, 见NetAutoAdaptor::TransProtocol
		InitInfo(): src_mode(NetAutoAdaptor::SrcInvalid), 
					handlePolicy(NetAutoAdaptor::HdlInvalid), 
					sendMode(NetAutoAdaptor::SendModeInvalid), 
					transProtocol(NetAutoAdaptor::TranProUnkown)
		{}
	};

public:
	///\brief 默认构造函数。
	CTransportStrategy();
	~CTransportStrategy();

public:
	///\brief 全局初始化函数，初始化NAA库和通道
	///\param[in] threadNum 线程池中线程数
	///\param[in] priority	线程优先级
	///\param[in] policy	线程策略
	///\param[in] slot		循环周期
	static int globalInit(int threadNum, int priority = 0, int policy = 0, int slot = 10);

	///\brief 全局反初始化函数，销毁线程池
	static void globalDeInit();

	///\brief 对象初始化函数。
	///\param[in] initinfo   初始化信息
	///\param[in] usr_info 用户信息
	///\param[in] enc_config 用户根据接口实现的对象，用于码流自适应，如填NULL，则不启用码流自适应
	int init(InitInfo &initinfo, const NetAutoAdaptor::UserInfo * usr_info = NULL, NetAutoAdaptor::IEncodeConfig *config = NULL);

public:
	///\brief 数据入口1：NAA通过proc从外部获取帧数据
	///\param[in] proc用户实现的帧提供函数
	int setPushFrameProc(NetAutoAdaptor::INAAPolicy::PushProc proc);

	///\brief 数据入口2：该接口向NAA提供帧数据
	///\param[in] frame: 待放入的帧
	///\return -1: 失败，0: 成功
	int pushFrame(NetAutoAdaptor::MediaFramePtr& frame);

	///\brief 数据出口：设置帧回调函数
	///\param[in] callback:NAA通过此回调接口对外提供经过策略处理的帧数据
	int setFrameCallback(NetAutoAdaptor::CStreamChannel::HandleProc callback);
	
	///\brief 用户定义带宽统计入口：
	///\param[in] proc 用户实现的带宽统计数据提供函数
	///\return -1: 失败，0: 成功
	int setBandWidthProc(NetAutoAdaptor::INAAPolicy::BandwidthProc proc);

	///\brief 设定用户数据，配合 @see setBandWidthProc 使用
	///\param[in] data 用户设定的数据，会在@see setBandWidthProc回调时作为回调函数的参数传入
	int setUserData(const void * data);

	///\brief 获取设定的用户数据，配合 @see setUserData 使用
	///\return 用户调用 @see setUserData 设置的用户数据
	const void * getUserData() const;
		
	///\brief 配置传输策略
	///\param[in] config 
	///\return -1: 失败，0: 成功
	int configTransStrategy(const NetAutoAdaptor::NAAConfig& config);

	///\brief 配置通道策略
	///\brief 可配置 使能 UDP均匀发送 、带宽限速 以及相关参数
	///\brief 可配置 源类型为 实时、下载或回放
	///\param[in] config
	///\return -1: 失败，0: 成功
	int setChannelStrategy(const NetAutoAdaptor::ChannelInfo& config);

	///\brief 使用预设的@see NetAutoAdaptor::NAAConfig 参数配置传输策略
	///\param[in] config,配置外部选择或自设完成后传入
	///\return -1: 失败，0: 成功
	int setTransStrategy(StreamSvr::ConfigStreamSendStrategy& config);

	///\brief 获取当前的策略
	///\return @see StrategyType 枚举
	int getTransStrategy();

	///\brief 设置帧保护标志
	///\param[in] type 是 @see NetAutoAdaptor::FrameType 类型，可以对其进行'或'运算后设置
	///\return -1: 失败， 0: 成功
	int setFrameShieldLevel(int type);

	///\brief 设置算法
	///\param[in] algorithm	算法类型 , 见NetAutoAdaptor::Algorithm
	///\0-none 0x1-slow resume 0x1<<1-force sync 0x1<<2-dropall 0x1<<3-svc	
	int setAlgorithm(int algorithm);
	
	///\brief 开启
	///\return 0: 成功 -1:失败
	int start();

	///\brief 暂停
	///\return 0: 成功 -1:失败
	int pause();

	///\brief 关闭对象
	////\return 0: 成功 -1:失败
	int close();

	///\brief 清空发送缓冲
	////\return 0: 成功 -1:失败
	int resetbuffer();

	///\brief 缓冲策略配置类
    ///\param [in] strategy 缓冲策略
    ///\return -1 失败 0 成功
    int setBufferStrategy(int strategy);

	///\brief 获取当前缓存某等级帧数
    ///\param [in] level 媒体帧等级, 默认0获取所有等级
    ///\return -1 失败 0 成功
	int frameSize(int level = 0);
	
	///\brief 配置通道发送策略 目前主要适用于均匀发送
	///\param[in] policy，策略参数
	///\return -1: 失败，0: 成功
	int setChannelStrategy(const ChannelPolicy& policy);

	/// \brief 绑定socket 到Naa 发送对象, 该套接字仅用来获得IP 等信息,Naa 不进行fd 资源管理
	/// \param [in] sock socket数组
	/// \param [in] sockNum socket个数
	///\return -1: 失败，0: 成功
	int attachSock(Memory::TSharedPtr<NetFramework::CSock> *sock, int sockNum);
private:
	CTransportStrategyImpl * m_impl;
public:
	static bool s_naa_thread_init;		///> 静态变量，标识naa的使用线程是否已经创建并初始化
};


	}
}

#endif
