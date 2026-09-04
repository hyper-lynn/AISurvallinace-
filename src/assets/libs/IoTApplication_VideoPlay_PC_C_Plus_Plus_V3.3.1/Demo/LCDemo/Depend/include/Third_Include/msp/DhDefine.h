#ifndef XT_DH_DEFINE_H
#define XT_DH_DEFINE_H

#define H264_I_FRAME 3
#define H264_P_FRAME 4

#define  DH_FRAME_TAIL_LEN  8
#define  DH_VIDEIO_LEN		8
#define  DH_AUDIO_LEN		4

typedef          int int32_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

#pragma pack(push,1)

// 大华时间，日期结构定义
struct DH_DATE_TIME
{
	unsigned int second		:6;		//	秒	0-59
	unsigned int minute		:6;		//	分	0-59
	unsigned int hour		:5;		//	时	0-23
	unsigned int day		:5;		//	日	1-31
	unsigned int month		:4;		//	月	1-12
	unsigned int year		:6;		//	年	2000-2063	
};

//大华帧类型定义
#define DH_VIDEO_I_FRAME  0xFD  //视频I帧
#define DH_VIDEO_P_FRAME  0xFC  //视频P帧
#define DH_VIDEO_B_FRAME  0xFE  //视频B帧
#define DH_PICTURE_STATIC 0xFB  //静止图片
#define DH_AUDIO_FRAME    0xF0  //音频

// 大华帧帧头定义
struct DH_FRAME_HEAD_V06
{
	unsigned char frame_head_flag[4]; // 帧头标志 "DHAV"
	unsigned char type;               // 帧类型
	unsigned char sub_type;           // 子类型
	unsigned char channel_id;         // 通道号
	unsigned char sub_frame_indx;     // 子帧序号
	unsigned int frame_indx;          // 帧序号
	unsigned int frame_len;           // 帧长度
	DH_DATE_TIME  time;               // 时间，日期
	unsigned short time_ms;           // 绝对时间戳
	unsigned char expand_len;         // 扩展长度
	unsigned char verify;	          // 校验和，前23个字节的累加和
};

//大华帧帧尾定义
struct DH_FRAME_TAIL_V06
{
	unsigned char frame_tail_flag[4]; // 帧尾标志 "dhav"
	unsigned int  frame_verify;       // 总长度 = 帧头长度 + 数据长度 + 帧尾长度
};

//大华视频编码类型
#define DH_VIDEO_MPEG4           1
#define DH_VIDEO_H264_HI         2
#define DH_VIDEO_MPEG4_LB        3
#define DH_VIDEO_H264_GBE        4
#define DH_VIDEO_JPEG            5
#define DH_VIDEO_JPEG2000        6
#define DH_VIDEO_AVS             7
#define DH_VIDEO_H264            8
#define DH_VIDEO_MPEG2           9

// 大华音频编码类型
#define DH_AUDIO_PCM8            7
#define DH_AUDIO_G729            8
#define DH_AUDIO_IMA_ADPCM       9
#define DH_AUDIO_G711U           10
#define DH_AUDIO_G721            11
#define DH_AUDIO_PCM8_VWIS       12
#define DH_AUDIO_MS_ADPCM        13
#define DH_AUDIO_G711A           14
#define DH_AUDIO_AMR_NB          15
#define DH_AUDIO_PCM16           16
#define DH_AUDIO_G723_1          25
#define DH_AUDIO_AAC             26

//大华音频采样率定义
#define SAMPLE_FREQ_4000         1
#define SAMPLE_FREQ_8000         2
#define SAMPLE_FREQ_11025        3
#define SAMPLE_FREQ_16000        4
#define SAMPLE_FREQ_20000        5
#define SAMPLE_FREQ_22050        6
#define SAMPLE_FREQ_32000        7
#define SAMPLE_FREQ_44100        8
#define SAMPLE_FREQ_48000        9

#pragma pack(pop)

#endif