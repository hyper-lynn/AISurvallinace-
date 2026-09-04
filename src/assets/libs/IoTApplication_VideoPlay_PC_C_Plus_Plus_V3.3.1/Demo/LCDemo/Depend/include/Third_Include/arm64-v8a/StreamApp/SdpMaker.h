#ifndef __INCLUDE_DAHUA_STREAMAPP_SDPMAKER_H__
#define __INCLUDE_DAHUA_STREAMAPP_SDPMAKER_H__

#include <string>
#include "Infra/IntTypes.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Protocol/SdpParser.h"
#include "StreamApp/Defs.h"

namespace Dahua{
namespace StreamApp{

#define AUDIO_SOURCE     2              ///> 支持的音频通道的数目

///\brief 音频编码格式,  见大华码流协议0x83 字段
enum AudioEncodeType
{
	PCM8      = 7,
	G729      = 8,
	IMA_ADPCM = 9,
	G711U     = 10,
	G721      = 11,
	PCM8_VWIS = 12,
	MS_ADPCM  = 13,
	G711A     = 14,
	PCM16     = 16,
	AAC   	  = 26,
	MP3   	  = 33,
};	

///\brief 视频编码格式,按照《大华码流信息格式.ppt》定义
enum VideoEncodeType
{
	MPEG4 = 1,
	H264 = 2,		//海丝
	MPEG4_LB = 3,
	H264_GBE = 4,
	JPEG = 5,
	JPEG2000 = 6,
	AVS = 7,
	H264_STANDARD = 8,
	MPEG2= 9,
	VNC = 10,
	SVAC = 11,
	H265 = 12,
	H26L = 14,     // 海康H264私有码流
	SVAC2 = 15,	   // SVAC2.0
};


///\brief 大华帧中的视频信息
struct DHVideoInfo
{
	uint32_t width;						///< 宽
	uint32_t height;					///< 高
	uint32_t I_frame_interval;			///< I帧间隔
	uint32_t encode_type;				///< 编码类型，参考@see VideoEncodeType
	uint32_t frame_rate;				///< 帧率
	bool h264_svc_flag;					///< h264编码类型是否使用了svc扩展
	bool h264_smart_flag;				///< h264编码类型smart码流标记

	uint32_t  reserve1[8];
	void     *reserve2[4];
		
	DHVideoInfo()
	{
		width				= 0;
		height				= 0;
		I_frame_interval	= 0;
		encode_type			= 0;
		frame_rate			= 0;
		h264_svc_flag		= false;
		h264_smart_flag		= false;

		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief 大华帧中的视频编码信息
struct VideoEncodeInfo
{
	bool					initFlag;	///> 是否初始化视频编码信息成功
	DHVideoInfo				videoInfo;	///> 视频编码信息
	std::string				keyInfo;	///> 视频关键信息(如H264中的SPS 等)

	VideoEncodeInfo():initFlag(false)
	{}
};

///\brief 大华帧中的音频信息
struct DHAudioInfo
{
	uint32_t encode_type;	///< 编码类型,参考@see AudioEncodeType
	uint32_t frequency;		///< 采样率,  真实的采样率, 非枚举值
	uint32_t channel_num;	///< 声道数, 见大华码流协议0x83 字段

	uint32_t  reserve1[8];
	void     *reserve2[4];

	DHAudioInfo()
	{
		encode_type = 0;
		frequency   = 0;
		channel_num = 0;

		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief 音频通道编码信息
struct DHAudioChannelEncodeInfo
{	
	bool        enable;				///< 音频通道使能情况
	bool        initd;				///< 是否初始化编码信息完成, 如果audioEncodeInfo 有效, 置为true
	int 		audioChannelNO;		///< 音频通道, 0x96 字段中的通道号, 如果不知道通道号，填-1即可
	DHAudioInfo	audioEncodeInfo;	///< 音频编码信息

	uint32_t    reserve1[8];
	void       *reserve2[4];

	DHAudioChannelEncodeInfo()
	{
		enable         = false;
		initd		   = false;
		audioChannelNO = -1;		

		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief 支持多音频最大通道数
enum MaxAudioChanel
{	
	MaxAudioChanelCount = 5	  		///< 最大音频个数
};

///\brief 音频通道个数及编码信息 
struct AudioChannelInfo
{	
	int 					 ChannelCount;    								///< 由外部传入音频通道数,应不超过 MaxAudioChanelCount
	DHAudioChannelEncodeInfo audioChannelEncodeInfo[MaxAudioChanelCount]; 	///< 音频通道信息, 下标表示大华帧头中0x96 的通道号
	
	AudioChannelInfo()
	{
		ChannelCount = 0;
	}
};

///\brief 音频编码信息 
struct AudioEncodeInfo
{
	bool				initFlag;		///< 是否初始化音频编码信息成功
	AudioChannelInfo	audioInfo;  	///< 音频编码信息
	
	AudioEncodeInfo()
	{
		initFlag = false;
	}
};


///\brief sdp选项配置
enum sdp_option
{
	SdpOptionFishEyeInfo = 0,	///< 鱼眼配置，对应value为bool*
	SdpOptionVideoPt,			///< 视频rtp payload配置
	SdpOptionTalkInfo,			///< 语音对讲配置
	SdpOptionNum,
};

///\brief 前置声明
struct CSdpMakerImpl;

///\brief SDP 组装类
class STREAMAPP_API CSdpMaker
{
public:
	///\brief 构造函数
	CSdpMaker();

	///\brief 析构函数
	~CSdpMaker();

	///\brief 初始化sdp 会话域部分
	///\return 0-成功, -1-失败
	int init();

	///\brief 初始化sdp 中的直播 时长域部分, 直播需要调用该接口
	///\return 0-成功, -1-失败
	int init_live_range();
	
	///\brief 初始化sdp 中的点播 时长域部分, 点播需要调用该接口
	///\param [in] duration-点播流时长, 单位为秒
	///\return 0-成功, -1-失败
	int init_vod_range(double duration);

	///\brief 从一个帧里面初始化视频编码信息
	///\param [in] frame-大华码流的一个关键帧(I 帧或J 帧)
	///\param [in] videoEncInfo-视频编码信息, 如果初始化完成, initFlag 标志会置为true
	///\return 0-成功, -1-失败
	int init_video_encode_info(StreamSvr::CMediaFrame &frame, VideoEncodeInfo &videoEncInfo);

	///\brief 从一个帧里面初始化音频编码信息
	///\param [in] frame-大华码流的一个音频帧
	///\param [out] audioEncInfo-音频编码信息, 如果初始化完成, initFlag 标志会置为true
	///\return 0-成功, -1-失败
	int init_audio_encode_info(StreamSvr::CMediaFrame &frame, AudioEncodeInfo &audioEncInfo);

	///\brief 通过视频编码信息初始化sdp 中的视频媒体部分
	///\param [in] videoEncInfo-视频编码信息
	///\return 0-成功, -1-失败
	int init_video_sdp(const VideoEncodeInfo &videoEncInfo);

	///\brief 通过音频编码信息初始化sdp 中的音频媒体部分
	///\param [in] audioEncInfo-音频编码信息
	///\return 0-成功, -1-失败
	int init_audio_sdp(const AudioEncodeInfo &audioEncInfo);

	///\brief 初始化sdp 中的辅助帧媒体部分, 例如动检帧,水印帧等
	///\return 0-成功, -1-失败
	int init_assist_sdp();

	///\brief 初始化sdp 中的onvif 元数据媒体部分, 如果该通道需要支持onvif 测试,需要初始化
	///\return 0-成功, -1-失败
	int init_onvifmetadata_sdp();

	///\brief 初始化sdp 中的反向音频媒体部分, 如果该通道需要支持rtsp 对讲, 需要初始化
	///\param [in] audioEncInfo-音频编码信息
	///\return 0-成功, -1-失败
	int init_backchannel_audio_sdp(const AudioEncodeInfo &audioEncInfo);

	///\brief 获得sdp 类, 用于获得sdp 以及自定义添加sdp 信息
	///\return sdp 类指针, 失败返回NULL
	StreamSvr::CSdpParser *getSdpParser();

	///\brief 设置SDP选项
	///\param [in] opt，选项枚举
	///\param [in] value，指向具体option结构体的指针，具体传入方式参考sdp_option定义
	///\return 0-成功，-1-失败
	int setSdpOption(sdp_option opt, void* value);

	///\brief 获取当前音频帧所对应的SDP信息的trackID的索引
	///\param [in] audioencInfo-SDP信息所参考的音频编码信息,与初始化音频SDP信息的init_audio_sdp所传入的音频编码信息一致
	///\param [in] frame-音频帧
	///\return 0-成功，-1-失败
	int get_audio_index(const AudioEncodeInfo &audioencInfo, const StreamSvr::CMediaFrame &frame);
	
private:
	///\brief 解析关键帧(I 帧或J 帧) 中的编码信息
	///\param [in] frame              -关键帧(I 帧或J 帧)
	///\param [in] encode_type -编码类型
	///\param [out] keyInfo	      -视频关键信息
	///\param [out] h264svcflag -是否是svc 扩展H264 编码
	///\return 0-成功, -1-失败
	int parse_video_key_info(const StreamSvr::CMediaFrame& frame, int encode_type, std::string	&keyInfo, bool &h264svcflag);

	///\brief 组装mpeg格式下sdp 信息中的fmp 字段信息
	///\param [in] keyInfo -视频关键信息
	///\param [out] fmtp 	 -fmp字段信息
	///\param [int] fmtp_len  -fmp指针长度
	///\return 0-成功, -1-失败
	int get_mpeg4_fmtp_info(const std::string &keyInfo, char* fmtp, int fmtp_len);

	///\brief 组装h264 格式下sdp 信息中的fmp 字段信息
	///\param [in] keyInfo -视频关键信息
	///\param [out] fmtp 	 -fmp字段信息
	///\param [int] fmtp_len  -fmp指针长度
	///\return 0-成功, -1-失败
	int get_h264_fmtp_info(const std::string &keyInfo, char* fmtp, int fmtp_len);

	///\brief 组装h265 格式下sdp 信息中的fmp 字段信息
	///\param [in] keyInfo -视频关键信息
	///\param [out] fmtp 	 -fmp字段信息
	///\param [int] fmtp_len  -fmp指针长度
	///\return 0-成功, -1-失败
	int get_h265_fmtp_info(const std::string &keyInfo, char* fmtp, int fmtp_len);
	
private:	
	CSdpMakerImpl *m_Impl;								///< 内嵌实现类
};

}
}

#endif // __INCLUDE_DAHUA_STREAMAPP_SDPMAKER_H__

