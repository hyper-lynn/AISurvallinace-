//
//  "$Id: StreamParser.h 205072 2014-07-17 01:38:36Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_H__

#include "BaseType.h"
#include "StreamFrame.h"
#include <memory.h>
#include <stdlib.h>

namespace Dahua {
namespace StreamParser {

// 错误码定义
enum
{
	EC_Success = 0,
	EC_Unsup,			// 功能不支持
	EC_Noinit,			// 未Init
	EC_Param,			// 参数错误
	EC_Stream,			// 码流错误
	EC_End,				// 解析完毕
	EC_Other,			// 其他错误

	// Input的返回码
	SC_OK = 1000,		// 所有输入的帧已解析完毕，可以调用Output提取
};

// 码流类型
enum
{
	StreamType_Unknown = 0,
	StreamType_RTP,			// RTP包
	StreamType_TS,			// TS流
	StreamType_PS,			// PS流
	StreamType_Dahua,		// 大华流
	StreamType_DahuaHybrid,	// 大华混合流（混合大华新码流，大华老码流，PS流）
	StreamType_RTPoverRTSP, // RTSP封装的RTP流
	StreamType_Raw_Frame,	// 裸码流
	StreamType_Dahua_Frame,	// 大华帧
	StreamType_Frame_Auto,	// 自动判断输入帧(拆包时使用此类型)
	StreamType_MAX
};

inline const char *StreamTypeName(int type)
{
	const char *name[] = {"Unknown", "RTP", "TS", "PS", "Dahua", "DahuaHybrid", "RTP over RTSP", "Raw Frame", "Dahua Frame", "Frame Auto"};
	const char *ret = name[0];
	if (0 < type && type < StreamType_MAX)
		ret = name[type];
	return ret;
}

// 编码类型
enum
{
	EncType_Unknown = 0,
	EncType_H264,
	EncType_Mpeg4,
	EncType_Jpeg,
	EncType_Audio,	// 普通音频类型，RTP使用
	EncType_Mp3,	// 新增：MP3音频格式，TS和PS使用
	EncType_Data,	// 新增：普通数据
	EncType_MAX,
};

inline const char *StreamEncTypeName(int type)
{
	const char *name[] = {"Unknown", "H264", "Mpeg4", "Jpeg", "Audio", "Mp3"};
	const char *ret = name[0];
	if (0 < type && type < EncType_MAX)
		ret = name[type];
	return ret;
}

// 发送头部参数
struct SendHeadParam
{
	int enable;
	int8_t dollar;
	int8_t channel;
	bool all_in_one;	// 将所有包都放在一个IStreamFrame中
};

// RTP发送参数
struct RtpSendParam
{
	int enc_type;		// RTP拆包时需指明编码类型
	uint8_t pt;			// Payload Type
	uint16_t init_seq;	// 初始/当前包序号
	uint32_t init_ts;	// 初始/当前时间戳
	uint32_t ssrc;		// 同步源
	uint32_t hz;		// 采样率，HZ值，一般视频为固定为90000HZ
	// 构造函数会将init_seq， init_ts和ssrc设成随机数
	RtpSendParam(); 
};

// TS发送参数
struct TsSendParam
{
	int enc_type;		// 视频编码类型，若无填0
	int enc_type_audio;	// 音频编码类型，若无填0
	int pack_num;
	// 默认7包
	TsSendParam() : enc_type(0),enc_type_audio(0),pack_num(7) {}
};

// PS发送参数
struct PsSendParam
{
	int enc_type;		// 视频编码类型，若无填0
	int enc_type_audio;	// 音频编码类型，若无填0
	int pes_length;		// PS中每包PES的长度，最大不能超过65000
	int bitrate;		// 设置发送总码率，单位为bit/每秒
	// 默认7包
	PsSendParam() :enc_type(0),enc_type_audio(0),pes_length(8000),bitrate(0) {}
};

// H264 sps和pps buffer
struct H264SpsInfo
{
	uint8_t *sps;
	int sps_len;
	uint8_t *pps;
	int pps_len;
};

// MPEG4 vos buffer
struct Mpeg4VosInfo
{
	uint8_t *vos;
	int vos_len;
};

// 组帧信息
struct FrameConfig
{
	int enc_type;			// 组帧时需指明编码类型
	uint8_t required_pt;	// 需要接收RTP包的PT值

	// 以下信息在组裸码流帧时可不用设置
	uint8_t channel_id;			// 通道号
	union
	{
		struct
		{
			uint8_t dh_playback_type;	// 大华回放类型
			uint8_t frame_rate;			// 默认帧率
			union
			{
				H264SpsInfo h264;
				Mpeg4VosInfo mpeg4;
			} info;						// 码流sps等相关信息，若码流中存在，上层可不设
		} video;			// 视频信息
		struct
		{
			uint8_t dh_playback_type;	// 大华回放类型
			uint8_t tone_num;			// 声道数
			uint8_t sample_rate;		// 采样率
		} audio;			// 音频信息
	};
	
	// 组帧策略
	struct
	{
		bool discard_frame_if_lost_pack;
		bool use_receive_time_for_pts;
	} strategy;

	FrameConfig() { memset(this, 0, sizeof(FrameConfig)); }
};

// 统计信息
struct StreamStatis
{
	float bit_rate; // bps
	float frame_rate; // fps
	StreamStatis() {memset(this, 0, sizeof(StreamStatis));}
};

/*************************************************************************
* 注：接口使用流程                                                       *
**************************************************************************
1、调用Create创建一个对象，设置要从何种源码流类型转换到何种目标码流类型
2、不断Input码流
3、当Input返回SC_OK时，调用Output获取转换后的码流
4、反复调用Output，直到返回无效的IStreamFrame
5、若没有调用Output直到返回无效的IStreamFrame，此时调用Input会返回EC_End
6、结束用delete销毁对象
*************************************************************************/
class STREAM_PARSER_API CStreamParser
{
public:
	// 创建对象，设置源码流类型和目标码流类型
	// 返回CStreamParser对象。若不支持源和目标之间的码流转换，返回NULL
	static CStreamParser *New(int src_type, int dst_type);

	// 销毁对象
	virtual ~CStreamParser();

	// 输入一包或一帧码流(需要保证包数据的完整性和单一性)
	// 返回错误码
	// !! 注意：外部alloc内存后传入，内部使用完后自动调用release，外部不用释放内存
	// 该内存一般在下一个Output时release
	virtual int Input(IStreamFrame *frame);

	// 主动获取一包或一帧数据
	// 返回错误码
	// !! 注意：内存由内部alloc，外部使用完内存后需要需要调用release释放内存
	virtual int Output(IStreamFrame *frame);

	// 清空输入的数据
	virtual void Clean(); 

	// 发送头部参数
	virtual int SetParam(SendHeadParam &p);
	// 设置RTP发送参数
	virtual int SetParam(RtpSendParam &p);
	virtual int GetParam(RtpSendParam &p);
	// 设置TS发送参数
	virtual int SetParam(TsSendParam &p);
	// 设置PS发送参数
	virtual int SetParam(PsSendParam &p);
	// 设置组帧参数
	virtual int SetParam(FrameConfig &p);

	// 获取统计信息
	virtual int GetStatis(StreamStatis &statis);

	// 打印信息
	virtual void PrintInfo();

protected:
	CStreamParser();
};

/************************************************************************/
/* StreamSync 码流同步，提取出单个包，用于无边界流确界                  */
/************************************************************************/
class STREAM_PARSER_API CStreamSync
{
public:
	// 创建对象
	static CStreamSync *New(int stream_type);

	// 销毁对象
	virtual ~CStreamSync();

	// 放入码流
	virtual void PutBuffer(uint8_t *buf, int len);

	// 放入一段码流，内部不做拷贝，直接demux
	// 使用者需要保证这块内存在使用完之前不被销毁
	virtual void Demux(uint8_t *buf, int len);

	// 获取一包
	// 注意，返回的包引用了PutBuffer时的内存，所以需要注意该内存的生存周期
	virtual CRefStreamFrame *GetPack();

protected:
	CStreamSync();
};

} // namespace StreamParser
} // namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_H__
