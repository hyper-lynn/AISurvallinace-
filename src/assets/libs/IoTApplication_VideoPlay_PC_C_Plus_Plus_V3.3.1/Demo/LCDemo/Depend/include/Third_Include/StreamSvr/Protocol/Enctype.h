//
//  "$Id: StreamParser.h $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//					2011-09-05		xu_ping		Create
//
#ifndef __INCLUDED_DAHUA_ENCTYPE_H__
#define __INCLUDED_DAHUA_ENCTYPE_H__
namespace Dahua {
namespace StreamSvr {

// 编码类型
enum
{
	EncType_Unknown = 0,
	EncType_H264,
	EncType_Mpeg4,
	EncType_Jpeg,
	EncType_Mpeg2TS,
	EncType_Assist,			//辅助帧
	EncType_OnvifMetadata,	//Onvif元数据帧
	EncType_H265,			// h265 视频
	EncType_H264_SVC,		//标准svc扩展
	EncType_Dhav_Video,		// 指明打包的荷载为DHAV 视频帧进行等分切割打包 
	EncType_Mpeg2,			// mpeg2视频
	EncType_Mpeg2PS,		// ps over rtp
	EncType_Audio_Min = 50,	// 音频编码格式的最小值
	EncType_Audio,			// 普通音频类型，RTP使用, 
	EncType_Mpeg1or2Audio,	//兼容mpeg1 or mpeg2 audio encode(such as mp2,mp3)
	EncType_Mp3,			// 新增：MP3音频格式，TS和PS使用
	EncType_AAC,			// AAC音频
	EncType_Dhav_Audio,     // 指明打包的荷载为DHAV音频帧进行等分切割打包 
	EncType_L16,
	EncType_Vorbis,			//vorbis音频的rtp封装格式
	EncType_Raw,   			//裸数据
	EncType_MAX, 		    // 后续视频枚举都加到音频前面， 否则Ts 流有问题
};


//大华私有回放类型参见"大华标准码流格式定义"
enum DH_PLAYBACK_TYPE
{
	DH_MPEG4_STANDARD	= 1,
	DH_H264_HISIV		= 2,
	DH_MPEG4_LB			= 3,
	DH_H264_PLUS		= 4,
	DH_JPEG				= 5,
	DH_JPEG2000			= 6,
	DH_AVS				= 7,
	DH_H264_STANDARD	= 8,
	DH_MPEG2			= 9,
	DH_VNC				= 10,
	DH_SVAC				= 11,
	DH_H265				= 12,
};

}
}
#endif //__INCLUDED_DAHUA_ENCTYPE_H__