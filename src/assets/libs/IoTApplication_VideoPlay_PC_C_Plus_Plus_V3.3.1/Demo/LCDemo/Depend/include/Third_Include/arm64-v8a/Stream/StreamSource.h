//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//					2011-6-14		qin_fenglin	Create
//

#ifndef DAHUA_STREAM_SOURCE_H__
#define DAHUA_STREAM_SOURCE_H__

#include "Json/value.h"
#include "Infra/Signal.h"
#include "Infra/Time.h"
#include "Infra/File.h"
#include "Component/Unknown.h"
#include "MediaFrame.h"
#include "Defs.h"


/// 废弃，为兼容暂时保留，使用 IStreamSource::ProtocolType 代替
#define STREAMSOURCE_TCP    0
#define STREAMSOURCE_UDP    1


namespace Dahua {
namespace Stream {


/// 流媒体数据源
class IStreamSource : public Component::IUnknown
{
public:
	/// 网络传输协议
	enum ProtocolType
	{
		tcp = 0,
		udp = 1,
	};

	/// 组件工厂, 不同种类的数据源工厂的 clsid 不同, 当前可用的有:
	///     "Local.MediaFileStream", "Local.MediaRealStream"，
	///     "Rtsp.MediaFileStream", "Rtsp.MediaRealStream"
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建 MediaFileStream 数据源对象
		/// 打开文件数据源
		/// \param [in] filename 文件名称
		/// \param [in] protocol 命令协议类型，仅对ClassID("Rtsp.MediaFileStream")
		///				有效，用于内部获取命令协议对应的文件流URL。
		///				参见《大华信息交换格式》组件ID定义
		virtual IStreamSource* create(std::string const& filename,
					std::string const& protocol = "Dahua3")
		{
			return NULL;
		}

		/// 取 MediaRealStream 数据源对象实例
		/// 打开实时数据源
		/// \param [in] channle 通道号
		/// \param [in] stream 码流类型
		/// \param [in] protocol 命令协议类型，仅对ClassID("Rtsp.MediaRealStream")
		///				有效，用于内部获取命令协议对应的实时流URL。
		///				参见《大华信息交换格式》组件ID定义
		virtual IStreamSource* instance(int channel, StreamType stream = Stream::main,
					std::string const& protocol = "Dahua3")
		{
			return NULL;
		}

		/// 创建MediaFileStream数据源对象,按时间回放接口
		/// 打开文件数据源
		/// \param [in] info 流信息
		///	{
		///		"StartTime" : "2010-05-25 00:00:00",	开始时间
		///		"EndTime" : "2010-05-25 23:59:59",	结束时间
		///		"VideoStream" : "Main",	视频码流 	"Main"-主码流 "Extra1"-辅码流1 "Extra2"-辅码流2 "Extra3"-辅码流3
		///		"Flags" : ["Timing", "Manual", "Event"] 录像类型：定时/手动/事件 没有该字段表示全部录像
		///		"Events" : ["AlarmLocal", "VideoMotion", "BankCardInsert "] 事件类型：报警/动检/卡号 没有该字段，表示所有事件
		///		"Channel" : 0,	通道号(从0开始)
		///	}
		/// \param [in] protocol 命令协议类型，仅对ClassID("Rtsp.MediaFileStream")
		///				有效，用于内部获取命令协议对应的实时流URL。
		///				参见《大华信息交换格式》组件ID定义
		virtual IStreamSource* create(const Json::Value& info, std::string const& protocol = "Dahua3")
		{
			return NULL;
		}

		/// 通过url地址，创建文件流数据源。可用于向DSS等标准RTSP流媒体服务器取流
		/// \param [in] url 取流地址
		/// \param [in] protocol 传输协议, 取 ProtocolType 枚举
		virtual IStreamSource* create(const char* url, const int protocol)
		{
			return NULL;
		}

		/// 通过url地址，取实时流数据源。可用于向DSS等标准RTSP流媒体服务器取流
		/// \param [in] url 取流地址
		/// \param [in] protocol 传输协议, 取 ProtocolType 枚举
		virtual IStreamSource* instance(const char* url, int protocol)
		{
			return NULL;
		}

		/// 取 MediaRealStream 数据源对象
		/// \param [in] info 流信息
		///	{
		///		"Channel" : 1,			// 通道号
		///		"ChannelId" : "34020000001320000001", // 通道编号，字符类型通道标识，可用于第三方平台对接
		///		"VideoStream" : "Main",	// 视频码流, "Main"-主码流 "Extra1"-辅码流1 "Extra2"-辅码流2 "Extra3"-辅码流3
		///		"Origin" : false,		// 是否直接从编码器取原始流, 只供智能分析模块使用
		///	}
		virtual IStreamSource* instance(const Json::Value& info)
		{
			return NULL;
		}

		/// 取MediaPreRecordStream预录码流
        /// 获取预录队列码流,取完后再转实时流
        /// \param [in] channle 通道号
        /// \param [in] stream 码流类型,只支持主码流和辅码流
		/// \param [in] channle 通道号
        /// \param [in] stream 码流类型
        /// \param [in] protocol 命令协议类型，仅对ClassID("Local.MediaPreRecordStream")
        ///             有效，用于内部获取命令协议对应的预录码流转实时流。
        ///             参见《大华信息交换格式》组件ID定义
        virtual IStreamSource* create(int channel, StreamType stream = Stream::main,
                std::string const& protocol = "Dahua3")
        {
            return NULL;
        }

		/// 组件接口ID定义
		static const char* iid() {return "StreamSource";}
	};

public:
	/// 定义数据观察者类型，接收帧数据
	/// 返回值是void
	/// 参数是帧数据对象，视频帧和图片帧都包括大华帧头。如果有错误发生，观察者会
	/// 收到无效包，可以用 getError 取出错误号，并在维护线程里调用stop/start重启。
	/// 如果文件结束，回调无效包，且 getError 取出的错误号为 0
	typedef	Infra::TSignal1<CMediaFrame const&> Signal;
	typedef Signal::Proc Proc;

	typedef Stream::StreamType			StreamType;
	typedef Infra::CFile::SeekPosition	SeekPosition;

	/// 接收回放帧数据回调
	/// 参数1, 帧数据
	/// 参数2, 回放操作序号，与setControlInfo返回的operateId一致
	/// 返回值，回调数据是否处理成功。
	///			数据回调给网络发送模块，发送成功true，发送失败false
	///			数据回调给GUI解码模块，送解码成功true，失败false
	typedef Infra::TFunction2<bool, CMediaFrame const&, uint32_t> ProcPlayback;

	/// 回放控制信息,128字节
	struct ControlInfo
	{
		float 	speed;			///回放速度
		uint32_t speedValid;	///回放速度是否有效
		uint32_t time;			///定位的时间点, 从1970-1-1 00:00:00开始，单位秒
		uint32_t timeValid;		///定位的时间点是否有效
		uint32_t reserve[28];	///保留
	};

public:
	/// 绑定回调,开始取流
	/// \param proc 回调函数，只能注册一次，重复注册返回失败
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除绑定,停止取流
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 暂停
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 继续
	virtual bool resume()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置速率
	virtual bool setSpeed(float speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 定位到参考位置开始处偏移offset后的位置
	virtual bool seek(int offset, SeekPosition)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 定位到指定时间附近的I帧
	virtual bool seekByTime(Infra::CTime const&)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳帧; num 为负数表示向前跳帧, isIFrame 表示是否跳I帧
	virtual bool stepFrame(int num, bool isIFrame = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前流的时间
	virtual bool getTime(Infra::CTime&) const
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前速率
	virtual bool getSpeed(float& speed) const
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取错误号
	virtual bool getError(int& eno) const
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置码流源的参数
	/// \param [in] options 参数，定义如下：
	/// \code
	///	{
	///		"KeyFrameSpeed": 2,	// speed 不小于此值时跳 I 帧, 为 0 表示都不跳 I 帧
	///		"TransType" : "RtpOverRtsp",	// "RtpOverRtsp"表示tcp模式，其它字符串会转为udp模式
	///		"Multicast" : true,				// bool 型，true表示组播，false表示非组播；
	///		"UserAgent" : "Rtsp Client/3.0",// 字符串格式，rtsp信令里的UserAgent字段定义，自定义
	///		"TransmitProperty" : 1,			// int型，为1表示每个RTP包当做一个完整的帧处理；其他值异常
	///		"Audio" : [0],					// 获取音频数据方式，是个数组，通道号从0开始。null表示不获取音频流。暂时只支持RTSP
	///										// 不设置或不存在Audio项，表示默认拉音频流
	///		"talkback" : true,				// true表示开启对讲; 不设置或者为false表示不开启对讲
	///		"EncryptParameters" : {	// 表示加密参数，有如下成员：
	///			"Level" : 1,	// int 型，表示加密等级，有如下取值：
	///							// NO_ENCRYPT = 0,  //不加密
	///							// I_FRAME_256,     //简单加密，I帧前256字节加密
	///							// I_FRAME_WHOLE,   //整个I帧加密
	///							// ENCRYPT_LEVEL_UNKNOW, //初始化用
	///			"Algorithm" : 0,// int型，表示加密算法，有如下取值：
	///							// ALGO_AES = 0,   //AES
	///							// ALGO_DES,       //DES
	///							// ALGO_3DES,      //Triple DES
	///							// ENCRYPT_ALGORITHM_UNKNOW,  //初始化用
	///			"KeyExchangeType" : 3,	// int型，表示密钥交换的方式，有如下取值：
	///									// KEY_EXCHANGE_PSK = 0,  //PSK
	///									// KEY_EXCHANGE_PK,       //PK
	///									// KEY_EXCHANGE_DH,       //DH
	///									// KEY_EXCHANGE_DHHMAC,   //DHHMAC
	///									// KEY_EXCHANGE_RSA_R,    //RSA_R
	///									// KEY_EXCHANGE_UNKNOW,   //初始化用
	///			"KeyPsk" : "123456",	// String类型，表示秘钥内容，无建议值
	///			"KeyPskLen" : 6,		// int 型，表示秘钥长度，及秘钥所含字节数
	///			"Unvarnished" : 0		// int型，表示是否进行加解密，0值表示交互MIKEY后，
	///									// 对数据进行加/解密，非0值表示交互MIKEY后让数据不进行加/解密；
	///		},
	///		"SockRecvBufSize" : 32768,  // 设置套接字接收缓冲,单位:字节
	///		"MainUrl" : "rtsp://10.1.2.3/record.dav"	//主码流URL，不再使用
	///		"SubUrl" : "rtsp://10.1.2.3/record.dav"		//辅码流URL，不再使用
	///		"protocol" : "TCP"							//协议，不再使用
	///	}
	/// \endcode
	virtual bool setOptions(Json::Value const& options)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 定位到参考位置处偏移 seconds 秒数后的位置
	virtual bool seekBySeconds(int seconds, SeekPosition)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 限定流数据的时间，只取流数据的一部分；仅对文件流有效。
	/// \param startTime 开始时间
	/// \param endTime 结束时间
	virtual bool limit(Infra::CTime const& startTime, Infra::CTime const& endTime)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 【仅供本地文件流使用】读文件数据。读操作后文件指针自动累加。
	/// \param [in] buffer 存放数据的缓冲区指针。
	/// \param [in, out] count 输入为要读出的字节数，输出为实际读出的字节数
	virtual bool read(void* buffer, size_t& count)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 【仅供本地文件流使用】获取当前帧的类型（注：只在回调中调用才有效）
	/// \param [out]  packetType 0-正常类型, 1-数据流最末截止包，（其他以后可扩展,）
	virtual bool getPacketType(int& packetType)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 本地文件流得到流的编码格式
	/// MediaFrameInfo::newFormat变化时，可以取到新的编码格式。
	/// \param format编码格式，参加《DVR信息交换格式》Config.Encode[MainFormat]
	/// \return 获取格式是否成功
	virtual bool getEncodeFormat(Json::Value & format)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// Onvif多play回放场景下，用来处理第二个及后面的play请求,设置limit时间后调用即可发送数据
	virtual bool newPlay()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取当前下载位置，只对按文件下载的文件流有效
	/// \param [out] position 文件偏移位置
	virtual bool getPosition(uint64_t& position)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 强制I帧，调用该接口流源需要快速回调一个I帧出去
	virtual bool setIFrame()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 应用场景：回放有seek/变倍操作，seek/变倍后需要丢弃seek/变倍前的码流
	/// 使用方式：每次回放操作后返回惟一的operateId(非0值)
	/// 同时码流回调(startPlayback)也返回相同的operateId
	/// 通过比较operateId，达到区分是操作前或操作后的码流
	/// \param [in] controlInfo 回放控制信息
	/// \param [out] controlInfo 回放操作的编号 >0
	/// \return 设置回放控制信息是否成功
	virtual bool setControlInfo(const ControlInfo& controlInfo, uint32_t& operateId)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 绑定回调,开始回放取流，与setControlInfo配合使用
	/// 如果未调用setControlInfo，返回的operateId为0
	/// \param [in] proc 回调函数，只能注册一次，重复注册返回失败
	/// \return 取流是否成功
	virtual bool startPlayback(ProcPlayback proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除绑定,停止回放取流
	/// \param [in] proc 回调函数
	/// \return 停止取流是否成功
	virtual bool stopPlayback(ProcPlayback proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(9)
};

/// 定义 IStreamSource 的智能指针
typedef Component::TComPtr<IStreamSource> IStreamSourcePtr;


} // namespace Stream
} // namespace Dahua


#endif	//DAHUA_STREAM_SOURCE_H__

