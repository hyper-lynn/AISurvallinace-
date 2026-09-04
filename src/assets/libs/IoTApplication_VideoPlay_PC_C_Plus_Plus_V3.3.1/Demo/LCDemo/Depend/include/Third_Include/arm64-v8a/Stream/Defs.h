//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA_STREAM_DEFS_H__
#define __DAHUA_STREAM_DEFS_H__


// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef STREAM_DLL_BUILD
#define  STREAM_API _declspec(dllexport)
#elif defined STREAM_DLL_USE
#define  STREAM_API _declspec(dllimport)
#else
#define STREAM_API
#endif

#else

#define STREAM_API

#endif


//////////////////////////////////////////////////////////////////////////
// use the unified 'DEBUG' macro
#if (!defined(NDEBUG)) && !defined(DEBUG)
#	define DEBUG
#endif


////////////////////////////////////////////////////////////////////////////////

#include "Infra/IntTypes.h"

namespace Dahua {

/////////////////////////////////////////////////////////////////////////
// Error Number Define For Stream
enum StreamError
{
	streamErrorFrameException	= 0x100c0001,	///< 帧数据异常
	streamErrorPreviewOpened	= 0x100c0002,	///< 多画面预览已打开，资源不足，压缩回放失败
	streamErrorCompressOpened	= 0x100c0003,	///< 压缩回放功能已打开，资源不足，导致失败
};


namespace Stream {
/// 分组模式，分组是指将多个画面编码成一个画面
enum GroupMode
{
	single,
	group2,				///< 支持split2，pip1
	group4,				///< 支持split4，pip3
	all,				///< 支持所有分割模式
	groupModeNumber,	///< 分组模式种类数
};

/// 码流类型
enum StreamType
{
	main = 0,		///< 主码流
	extra1,			///< 辅码流1
	extra2,			///< 辅码流2
	extra3,			///< 辅码流3
	snapshot,		///< 抓图
	talkback,		///< 对讲流
	tapeIn,			///< 录音输入
	streamNumber	///< 种类数
};

/// 编码类型
enum EncodeType
{
	h264 = 1,			///< h264编码
	mjpeg = 2,		///< mjpeg编码
	mpeg4 = 3,		///< mpeg4编码

};

/// 大华DHAV帧类型
enum DHFrameType
{
	DHFRAME_SMART_I_FRAME	= 0x01,	/// Smart编码(长GOP)重定位I帧，作为当前GOP所有重定位P帧的参考
	DHFRAME_SMART_P_FRAME	= 0x02,	/// 长GOP编码(长GOP)重定位P帧，只参考当前GOP的I帧
	DHFRAME_DTMF_FRAME		= 0x03, /// VDP RFC2833中RTP Event的辅助帧,大华头中辅助帧子类型为0x0F
	DHFRAME_AUDIO_FRAME		= 0x41,	/// 音频帧
	DHFRAME_I_FRAME			= 0x49,	/// 视频I帧
	DHFRAME_P_FRAME			= 0x50,	/// 视频P帧
	DHFRAME_B_FRAME			= 0x42,	/// 视频B帧
	DHFRAME_GPS_FRAME		= 0x47,	/// GPS辅助帧
	DHFRAME_MOTION_FRAME	= 0x4D,	/// 视频动检帧，MediaFrameInfo.type='V'
	DHFRAME_METADATA_FRAME	= 0x4D,	/// 元数据辅助帧，MediaFrameInfo.type='X'
	DHFRAME_SMART_FRAME		= 0x53,	/// 智能分析帧
	DHFRAME_WATER_FRAME		= 0x57,	/// 水印帧
};

/// 统一的媒体帧信息，可以放在CPacket的ExtraData中。128字节
struct MediaFrameInfo
{
	char type;			///< 'A'/'V'/'X', 'X'(辅助帧)
	char head;			///< 0/1, if include a frame head
	char tail;			///< 0/1, if include a frame tail
	char newFormat;		///< for encode format params, 0-none changed, 1-resolution changed, 2-other changed.
	int channel;		///< video channel or audio channel
	uint64_t pts;		///< presentation time stamp, in millisecond
	union
	{
		struct
		{
			uint8_t group;	///< video group mode, see IDevVideoEnc::GroupMode
			uint8_t stream;	///< video stream type, see IDevVideoEnc::StreamType
			uint8_t type;	///< video frame type, 'I','B','P'
							///< DHFRAME_SMART_I_FRAME,DHFRAME_SMART_P_FRAME
							///< (为兼容老版本,以下类型保留:'W','G','M')
			uint8_t mark;	///< 1-255, mark of specified frame, 0-ignore
			uint8_t spec;	///< if include a codec spec info such as PPS/SPS of H.264 codec
			uint8_t encode; ///< stream encode type, 见：enum EncodeType
			uint8_t svcLayer; ///svc层数
		} video;
		struct
		{
			uint8_t stream;		///< audio stream type, see IDevAudioEnc::StreamType
		} audio;
		struct
		{
			uint8_t type;		///< 辅助帧类型，'S'(智能分析帧),'W'(Water),'G'(GPS),'M'(Metadata), 'D'(全屏动检数据-标准模式)
			uint8_t stream;		///< stream type, see IDevVideoEnc::StreamType
		}extra;					///< 辅助帧信息
		char placeholder[8];	///< placeholder for 8 bytes
	} detail;
	uint32_t length;			///< length of a completed frame
	uint32_t utc;				///< seconds from utc(1970-1-1 00:00:00)

	// 以下数据放在CPacket头32字节以后，前提是CPacket头有足够长度，如果没有则不能使用
	uint64_t ptsBeforeEnc;	///< 音视频帧编码前的时间戳
	uint64_t ptsAfterEnc;	///< 音视频帧编码后的时间戳
	uint64_t ptsLib;		///< 编码库从驱动取到本数据包的时间戳
	uint64_t ptsApp;		///< 应用层取到本数据包后的时间戳
	uint64_t ptsNet;		///< 网络模块取到本数据包后的时间戳
	uint32_t sequence;		///< 音视频帧帧序号
	uint16_t utcms;			///< UTC对应毫秒数
	uint8_t flag;			///< 区分原始大图和抠图的标志，0表示大图，其他表示抠图
	uint8_t reserved1;		///< 保留
	uint32_t encodeSequence;///< 合成图片编码序号（由应用生成，用于编码完匹配使用）,非合成图片填0
	uint32_t reserved[11];	///< 保留
};

} // namespace Stream
} // namespace Dahua

#endif // __DAHUA_STREAM_DEFS_H__
