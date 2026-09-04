#ifndef _IBP_STREAM_DEFINE_H
#define _IBP_STREAM_DEFINE_H

//IBP帧类型定义
#define IBP_VIDEO_I_FRAME  0xFD  //视频I帧
#define IBP_VIDEO_P_FRAME  0xFC  //视频P帧
#define IBP_VIDEO_B_FRAME  0xFE  //视频B帧
#define IBP_PICTURE_STATIC 0xFB  //静止图片
#define IBP_AUDIO_FRAME    0xF0  //音频

#define IBP_H264_I_FRAME 3
#define IBP_H264_P_FRAME 4

//IBP视频编码类型
#define IBP_VIDEO_MPEG4           1
#define IBP_VIDEO_H264_HI         2
#define IBP_VIDEO_MPEG4_LB        3
#define IBP_VIDEO_H264_GBE        4
#define IBP_VIDEO_JPEG            5
#define IBP_VIDEO_JPEG2000        6
#define IBP_VIDEO_AVS             7
#define IBP_VIDEO_H264            8
#define IBP_VIDEO_MPEG2           9

//IBP音频编码类型
#define IBP_AUDIO_PCM8            7
#define IBP_AUDIO_G729            8
#define IBP_AUDIO_IMA_ADPCM       9
#define IBP_AUDIO_G711U           10
#define IBP_AUDIO_G721            11
#define IBP_AUDIO_PCM8_VWIS       12
#define IBP_AUDIO_MS_ADPCM        13
#define IBP_AUDIO_G711A           14
#define IBP_AUDIO_AMR_NB          15
#define IBP_AUDIO_PCM16           16
#define IBP_AUDIO_G723_1          25
#define IBP_AUDIO_AAC             26

//IBP音频采样率定义
#define IBP_SAMPLE_FREQ_4000         1
#define IBP_SAMPLE_FREQ_8000         2
#define IBP_SAMPLE_FREQ_11025        3
#define IBP_SAMPLE_FREQ_16000        4
#define IBP_SAMPLE_FREQ_20000        5
#define IBP_SAMPLE_FREQ_22050        6
#define IBP_SAMPLE_FREQ_32000        7
#define IBP_SAMPLE_FREQ_44100        8
#define IBP_SAMPLE_FREQ_48000        9



#ifndef int32_t
typedef          int int32_t;
#endif

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#ifndef uint16_t
typedef unsigned short uint16_t;
#endif

#ifndef uint8_t
typedef unsigned char  uint8_t;
#endif

#pragma pack(push,1)

//ibp时间结构定义
struct IBP_DATE_TIME
{
	unsigned int second		:6;		//	秒	0-59
	unsigned int minute		:6;		//	分	0-59
	unsigned int hour		:5;		//	时	0-23
	unsigned int day		:5;		//	日	1-31
	unsigned int month		:4;		//	月	1-12
	unsigned int year		:6;		//	年	2000-2063	
};

#pragma pack(pop)

#endif

