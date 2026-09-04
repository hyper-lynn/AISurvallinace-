//
// Copyright (c) 2010, 浙江大华技术股份有限公司
// All righSC reserved.
//
// 文 件 名：StreamConvertor.h
// 摘    要：提供SC流封装，支持DHAV码流
//
// 修订记录：创建
// 完成日期：2011年01月06日
// 作    者：
//

#ifndef _STREAM_CONVERTOR__H
#define _STREAM_CONVERTOR__H

#define IN
#define OUT

#if (defined(WIN32) || defined(WIN64))
    #ifdef ST_EXPORTS_DLL
        #define SCAPI __declspec(dllexport)
    #elif defined ST_USE_DLL
        #define SCAPI __declspec(dllimport)
	#else
		#define SCAPI
    #endif

    #define CALLMETHOD __stdcall
    typedef __int64 int64_t;

#else /*linux or mac*/

    #define SCAPI
    #define CALLMETHOD
	#include <inttypes.h>
	#include <stdint.h>

#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef void* SCHANDLE;

// 错误码
enum
{
	SCERR_NoError = 0,				/* 成功*/
	SCERR_InvalidHandle,			/* 无效句柄*/
	SCERR_NoSupport,				/* 解析或封装类型不支持*/
	SCERR_Thread,					/* 内部线程出错*/
	SCERR_Param,					/* 转换过程中参数有误*/

	SCERR_FileOpen,					/* 文件打开出错，可能已被互斥打开*/
	SCERR_FileRead,					/* 文件读取出错*/
	SCERR_FileWrite,				/* 文件写入出错*/
	SCERR_Format,					/* 码流格式有误，无法继续解析*/

	SCERR_BufferOverFlow,			/* 内部缓冲溢出*/
	SCERR_SysOutOfMem,				/* 系统内存不足*/

	SCERR_NoIDRFrame,				/* 解析或封装类型不支持*/
	SCERR_NoOutPut,					/* 同步封装或解析逻辑中无数据输出*/
	SCERR_ErrorOrder,				/* 调用顺序有误*/

	SCERR_KeyError,					/* 回放时输入秘钥错误*/
	SCERR_InputParam,				/* 输入参数有误*/
};

typedef enum _SC_TYPE
{
	SC_NONE = -1,
	SC_TS,
	SC_PS,
    SC_RTP,
	SC_MP4,
	SC_GDPS,
	SC_GAYSPS,
	SC_FLV,
	SC_ASF_FILE,
	SC_ASF_STREAM,
	SC_FLV_STREAM,
	SC_MP4_NOSEEK,
	SC_DAV_FILE,
	SC_DAV_STREAM,
	SC_AVI_FILE,
	SC_AVI_STREAM,
	SC_TS_NEW,
	SC_PS_NEW,
	SC_MOV,
	SC_MP464,
	SC_MOV64,
	SC_WAV_FILE,
	SC_DHPS,
	SC_DHPS_STREAM,
	SC_CDJFPS,
	SC_CDJFTS,
	SC_RAW,	//裸数据回调
	SC_TZDZTS,
}SC_TYPE;

/*待转换前码流封装格式*/
typedef enum _SC_SRC_TYPE
{
	SC_SRC_STREAM_TYPE_UNKNOWN = 0, /*未知码流*/
	SC_SRC_STREAM_TYPE_MPEG4,       /*MPEG4*/
	SC_SRC_STREAM_TYPE_DHPT =3,	    /*大华老码流：DHPT*/
	SC_SRC_STREAM_TYPE_NEW,         /*大华老码流：NEW*/
	SC_SRC_STREAM_TYPE_HB,          /*大华老码流：HB*/
	SC_SRC_STREAM_TYPE_AUDIO,       /*音频流*/
	SC_SRC_STREAM_TYPE_PS,          /*MPEG-2：PS*/
	SC_SRC_STREAM_TYPE_DHSTD,       /*大华最新的标准码流*/
	SC_SRC_STREAM_TYPE_ASF,         /*ASF*/
	SC_SRC_STREAM_TYPE_3GPP,        /*3GP*/
	SC_SRC_STREAM_TYPE_RAW,	        /*大华老码流：裸码流*/
	SC_SRC_STREAM_TYPE_TS,          /*MPEG-2：TS*/
	SC_SRC_STREAM_TYPE_SVC,         /*svc*/
	SC_SRC_STREAM_TYPE_AVI,         /*AVI*/
	SC_SRC_STREAM_TYPE_MP4,         /*MP4*/
	SC_SRC_STREAM_TYPE_CGI,         /*CGI*/
	SC_SRC_STREAM_TYPE_WAV,			/*WAV音频*/
	SC_SRC_STREAM_TYPE_FLV,         /*FLV*/

	SC_SRC_STREAM_TYPE_MKV,         /*mkv*/
	SC_SRC_STREAM_TYPE_RTP,			/*RTP*/
	SC_SRC_STREAM_TYPE_RAW_MPEG4,	/*MPEG4裸码流*/
	SC_SRC_STREAM_TYPE_RAW_H264,	/*H264裸码流*/
	SC_SRC_STREAM_TYPE_RAW_H265,	/*H265裸码流*/
	SC_SRC_STREAM_TYPE_WMV,			/*WMV*/
	SC_SRC_STREAM_TYPE_RAW_MPEG2,	/*MPEG2裸码流*/
	SC_SRC_STREAM_TYPE_RAW_SVAC,	/*SVAC裸码流*/
	SC_SRC_STREAM_TYPE_MOV,
	SC_SRC_STREAM_TYPE_VOB,			/*VOB*/
	SC_SRC_STREAM_TYPE_RAW_H263,
	SC_SRC_STREAM_TYPE_RM,
	SC_SRC_STREAM_TYPE_DHPS,		/*MPEG-2：PS*/

	// 第三方厂商类型，从0x81开始，和通用厂商做区分
	SC_SRC_STREAM_TYPE_HENGYI = 0x81,	/*恒易*/
	SC_SRC_STREAM_TYPE_HUANGHE,		/*黄河*/
	SC_SRC_STREAM_TYPE_LANGCHI,		/*朗驰*/
	SC_SRC_STREAM_TYPE_TDWY,		/*天地伟业*/
	SC_SRC_STREAM_TYPE_DALI,		/*大立*/
	SC_SRC_STREAM_TYPE_LVFF,		/*LVFF文件头，未知厂商*/
	SC_SRC_STREAM_TYPE_H3C,			/*华三*/
	SC_SRC_STREAM_TYPE_FENGDA,		/*丰达录像*/
	SC_SRC_STREAM_TYPE_MDVRX,		/*文件头MDVRX，未知厂商*/
	SC_SRC_STREAM_TYPE_PU8000,		/*文件头pu8000，未知厂商*/
	SC_SRC_STREAM_TYPE_DVR,			/*后缀名dvr，未知厂商*/
	SC_SRC_STREAM_TYPE_IFV,			/*后缀名ifv，未知厂商*/
	SC_SRC_STREAM_TYPE_264DV,		/*文件头264dv，未知厂商*/
	SC_SRC_STREAM_TYPE_ZWSJ,		/*中维世纪*/
	SC_SRC_STREAM_TYPE_SANLI,		/*金三立*/
	SC_SRC_STREAM_TYPE_HIK_PRIVATE,	/*海康私有码流*/
	SC_SRC_STREAM_TYPE_HIK_PS,		/*海康PS流*/
	SC_SRC_STREAM_TYPE_STAR,		/*星望私有码流*/
	SC_SRC_STREAM_TYPE_LIYUAN,		/*立元私有码流*/
	SC_SRC_STREAM_TYPE_KAER,		/*北京卡尔视通码流*/
	SC_SRC_STREAM_TYPE_SSAV,		/*SSAV某未知厂商码流*/
	SC_SRC_STREAM_TYPE_ZLAV,		/*ZLAV智诺码流*/
	SC_SRC_STREAM_TYPE_ZSLC_PS,		/*中视里程PS*/
	SC_SRC_STREAM_TYPE_STAR_EX,		/*一种新的星望私有流*/
	SC_SRC_STREAM_TYPE_DONGYANG,	/*东阳的一个特殊码流*/
	SC_SRC_STREAM_TYPE_CREARO,		/*创世码流*/
}SC_SRC_STREAM_TYPE;

/*帧类型*/
typedef enum
{
	SC_FRAME_TYPE_UNKNOWN = 0,			/*帧类型不可知*/
	SC_FRAME_TYPE_VIDEO,				/*帧类型是视频帧*/
	SC_FRAME_TYPE_AUDIO,				/*帧类型是音频帧*/
	SC_FRAME_TYPE_DATA,					/*帧类型是数据帧*/
}SC_FrameType;

/*帧子类型*/
typedef enum _FRAME_SUB_TYPE
{
	SC_FRAME_SUB_TYPE_INVALID = -1,     	/*数据无效*/
	SC_FRAME_SUB_TYPE_I_FRAME,				/*视频I帧*/
	SC_FRAME_SUB_TYPE_P_FRAME,				/*视频P帧*/
	SC_FRAME_SUB_TYPE_B_FRAME,				/*视频B帧*/

}SC_FrameSubType;

/*编码类型*/
typedef enum _VIDEO_ENCODE
{
	SC_ENCODE_VIDEO_UNKNOWN = 0,		/*视频编码格式不可知*/
	SC_ENCODE_VIDEO_MPEG4 ,			    /*视频编码格式是MPEG4*/
	SC_ENCODE_VIDEO_HI_H264,			/*视频编码格式是海思H264*/
	SC_ENCODE_VIDEO_JPEG,				/*视频编码格式是标准JPEG*/
	SC_ENCODE_VIDEO_DH_H264,			/*视频编码格式是大华码流H264*/
	SC_ENCODE_VIDEO_JPEG2000 = 6,		/*视频编码格式是标准JPEG2000*/
	SC_ENCODE_VIDEO_STD_H264 = 8,		/*视频编码格式是标准H264*/
	SC_ENCODE_VIDEO_MPEG2 = 9,          /*视频编码格式是MPEG2*/
	SC_ENCODE_VIDEO_SVAC = 11,          /*视频编码格式是SVAC*/
	SC_ENCODE_VIDEO_DH_H265 = 12,		/*视频编码格式是H265*/

	//私有编码格式
	SC_ENCODE_VIDEO_HIK_H264 = 0x81,		/*海康私有H264码流*/
}SC_VIDEO_ENCODE;

typedef enum
{
	SC_ENCODE_AUDIO_UNKNOWN = 0,
	SC_ENCODE_AUDIO_PCM = 7,			/*音频编码格式是PCM8*/
	SC_ENCODE_AUDIO_G729,				/*音频编码格式是G729*/
	SC_ENCODE_AUDIO_IMA,				/*音频编码格式是IMA*/
	SC_ENCODE_PCM_MULAW,				/*音频编码格式是PCM MULAW*/
	SC_ENCODE_AUDIO_G721,				/*音频编码格式是G721*/
	SC_ENCODE_PCM8_VWIS,				/*音频编码格式是PCM8_VWIS*/
	SC_ENCODE_MS_ADPCM,				    /*音频编码格式是MS_ADPCM*/
	SC_ENCODE_AUDIO_G711A,				/*音频编码格式是G711A*/
	SC_ENCODE_AUDIO_AMR,				/*音频编码格式是AMR-NB 窄带*/
	SC_ENCODE_AUDIO_PCM16,				/*音频编码格式是PCM16*/
	SC_ENCODE_AUDIO_G711U = 22,		    /*音频编码格式是G711U*/
	SC_ENCODE_AUDIO_G723 = 25,			/*音频编码格式是G723*/
	SC_ENCODE_AUDIO_AAC,			    /*音频编码格式是AAC Low Complex*/
	SC_ENCODE_AUDIO_G726_40,            /*40kbps,以下32/24/16*/
	SC_ENCODE_AUDIO_G726_32,            /*分别表示比特率的不同*/
	SC_ENCODE_AUDIO_G726_24,            /*相对于8k采样率的*/
	SC_ENCODE_AUDIO_G726_16,            /*情况下*/
	SC_ENCODE_AUDIO_MP2,				/*音频编码格式是mp2*/
	SC_ENCODE_AUDIO_OGG,				/*音频编码格式是ogg vorbis*/
	SC_ENCODE_AUDIO_MP3,				/*音频编码格式是mp3*/
	SC_ENCODE_AUDIO_G722_1,				/*音频编码格式是G722.1*/
	SC_ENCODE_AUDIO_G722,				/*音频编码格式是G722*/
	SC_ENCODE_AUDIO_G722_1C_48,			/*音频编码格式是G722_1C_48*/
	SC_ENCODE_AUDIO_AAC_LD,				/*音频编码格式是AAC_LD*/
	SC_ENCODE_AUDIO_OPUS,				/*音频编码格式是OPUS*/
	SC_ENCODE_AUDIO_G719,				/*音频编码格式是G719*/
	SC_ENCODE_AUDIO_G728,				/*音频编码格式是G728*/
	SC_ENCODE_AUDIO_G722_1_16,			/*音频编码格式是G722_1_16*/
	SC_ENCODE_AUDIO_G722_1_24,			/*音频编码格式是G722_1_24*/
	SC_ENCODE_AUDIO_G722_1C_24,			/*音频编码格式是G722_1C_24*/
	SC_ENCODE_AUDIO_G722_1C_32,			/*音频编码格式是G722_1C_32*/

	SC_ENCODE_AUDIO_TALK = 0x30,		/*音频编码格式是对讲*/

}SC_AUDIO_ENCODE;

#pragma pack(1)
/// 视频参数 40字节
typedef struct
{
	unsigned int nEncodeType;	/*视频编码格式,取值SC_VIDEO_ENCODE */
	unsigned int nWidth;		/* 宽 */
	unsigned int nHeight;		/* 高 */
	unsigned int nFrameRate;	/* 帧率 */
	unsigned int nReserved[6];
}SC_Video_INFO;

/// 音频参数 40字节
typedef struct
{
	unsigned int nEncodeType;	/*音频编码格式，取值SC_AUDIO_ENCODE*/
	unsigned int nChannel;		/* 音频通道数*/
	unsigned int nSampleRate;	/* 音频采样频率*/
	unsigned int nBitPerSample;	/* 音频采样位数*/
	unsigned int nReserved[6];
}SC_Audio_INFO;


//每一帧裸数据信息，固定大小256字节
typedef struct
{
	int nFrameType;				/* 帧类型，取值SC_FrameType */
	int nFrameSubType;			/* 帧子类型，取值SC_FrameSubType */

	int nYear;					/* 年 */
	int nMonth;					/* 月 */
	int nDay;					/* 日 */
	int nHour;					/* 小时 */
	int nMinute;				/* 分钟 */
	int nSecond;				/* 秒 */
	int nMilliSecond;			/* 毫秒 */
	int64_t pts;				/* pts 时间戳 */
	int64_t dts;				/* dts 时间戳 */
	union
	{
		SC_Video_INFO video;
		SC_Audio_INFO audio;
	}Info;
	int nValid;					/* 是否包含有效数据，0不包含，1包含 */
	
	int nReserved[40];
}SC_FRAME_INFO;

#pragma pack()

/********************************************************************
*	Funcname: 	    	SC_GetVersion
*	Purpose:	        获取svn版本信息
*   InputParam:         无
*   OutputParam:		无
*   Return:             库版本号字符串
*********************************************************************/
SCAPI char* CALLMETHOD SC_GetVersion(void);

//
// 封包信息回调，以流方式输出
// pData：  已完成的一帧数据，封装后的数据应从该回调中取得
// iLen:    帧数据长度
// lUser：  用户数据
//
typedef void (CALLMETHOD *pfSCPacketsCallback)(unsigned char* pData, int iLen, void* lUser);


// 封包信息回调,当目的类型为ps,ts，dav可进行实时转发；MP4,flv，asf,avi等类型由于需要回写文件头，不支持实时转发
// pData：  一帧数据，从该回调中取得
// iLen:    帧数据长度
// offset:	偏移
// offsetType:偏移类型
// lUser：  用户数据
//
typedef void (CALLMETHOD* pfSCPacketsCallbackEx)(unsigned char* pData, int iLen, int64_t offset, int64_t offsetType, void* lUser);

//
// 帧数据及帧信息回调，目前仅支持：ps，扩展ps，以及SC_RAW
// pFrmHdr: 音视频帧信息
// pData：  一帧数据，从该回调中取得
// iLen:    帧数据长度
// lUser：  用户数据
//
typedef void (CALLMETHOD *pfSCFrameDataCallback)(SC_FRAME_INFO* pFrmHdr, unsigned char* pData, int iLen, void* lUser);


//
// 功  能：SC流封装库初始化函数
// 参  数：无
// 返回值：TRUE成功，FALSE失败
//
SCAPI bool CALLMETHOD SC_Init(void);

//
// 功  能：打开一个SC流转换通道(MP4不支持)
// 参  数：
//		   IN  eSCType：转换类型
//		   IN  fSCPackeSCCallback：DHAV码流转换为SC流后的数据回调
//		   IN  lUser：用户数据，回调函数中使用
//		   OUT pSCHandle：SC流转换通道句柄
//
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_Open(IN SC_TYPE eSCType, IN pfSCPacketsCallback fSCPacketsCallback, IN void* lUser, OUT SCHANDLE* pSCHandle);


//
// 功  能：打开一个SC转换通道,目的转换数据是以回调方式输出，由用户自定义做转发或者存储
// 参  数：
//		   IN  eSrcType:原始输入码流类型，取枚举值SC_SRC_STREAM_TYPE，当不确定原始码流类型时，请使用SC_SRC_STREAM_TYPE_UNKNOWN;
//		   IN  eSCType：目的转换类型,取值SC_TYPE，当取值为SC_RAW，仅触发回调fSCFramesDataCallback;
//												  当取值为SC_PS，SC_GAYSPS，既可以触发回调fSCFramesDataCallback，也可以触发fSCPacketsCallbackEx；但仅能触发其中一种;
//												  当取值为其他值，仅触发fSCPacketsCallbackEx;
//		   IN  pfSCPacketsCallbackEx：转换后数据回调
//		   IN  fSCFramesDataCallback：转换后数据回调，以及相应的帧信息
//		   IN  lUser：用户数据，回调函数中使用
//		   OUT pSCHandle：SC流转换通道句柄
//
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_OpenProc(IN SC_SRC_STREAM_TYPE eSrcType, IN SC_TYPE eDstType, IN pfSCPacketsCallbackEx fSCPacketsCallbackEx, IN pfSCFrameDataCallback fSCFramesDataCallback, IN void* lUser, OUT SCHANDLE* pSCHandle);

//
// 功  能：打开一个SC转换方式，保存在文件里面
// 参  数：
//		   IN  eSCType：转换类型
//		   IN  szFileName 要保存的文件名
//			IN nlen   文件名长度
//		   IN  lUser：用户数据，回调函数中使用
//		   OUT pSCHandle：SC流转换通道句柄
//
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_OpenFile(IN SC_TYPE eSCType, IN const char* szFileName,IN int nlen, OUT SCHANDLE* pSCHandle);


// 功  能：根据实际需求设置转换参数
// 参  数：
//		   IN hSCHandle：SC流转换通道，由SC_OpenFile，或者SC_Open产生
//		   IN type：设置转换参数：当type为"mutiMode"，支持转换MP4时变分辨率、帧率等视频参数，将自动以下划线+数字命名方式保存文件；
//		   IN nValue：用户自定义参数type的值,当type为"mutiMode"时，nValue为任意值均可；
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_SetParam( IN SCHANDLE hSCHandle ,IN char* type, IN int nValue);

//
// 功  能：将原始数据送入SC流转换库
// 参  数：
//		   IN hSCHandle：SC流转换通道，由SC_OpenFile产生
//		   IN pData：原始数据
//		   IN iLen：原始数据长度
//
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_InputData(IN SCHANDLE hSCHandle, IN unsigned char* pData, IN int iLen);

//
// 功  能：提示转换库送数据结束
// 参  数：
//		   IN hSCHandle：SC流转换通道，由SC_OpenFile产生,(mp4必须调用)
//
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_EndInput(IN SCHANDLE hSCHandle);
//
// 功  能：关闭SC流转换通道
// 参  数：
//		   IN hSCHandle：SC流转换通道，有SC_Open产生
// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_Close(IN SCHANDLE hSCHandle);

//
// 功  能：SC流封装库清理函数
// 参  数：无
// 返回值：TRUE成功，FALSE失败
//
SCAPI bool CALLMETHOD SC_Cleanup(void);

//
//功能:	1.设置解密类型和密钥及密钥长度,实现解密功能
//		2.转化RTP，设置必要参数
//参数：hSCHandle：SC流转换通道，由SC_Open产生
//		1.实现解密功能，原始码流的加密类型为aes，type设置："Decryptkey_aes",pExtInfo：秘钥，nLength：秘钥长度
//													 设置：	"Decryptkey_aes256"	,pExtInfo：秘钥，nLength：秘钥长度
//		2.转换码流成RTP时，type设置："package_rtp_custom_data"，包前自定义数据,nLength:包前自定义数据长度
//							"package_rtp_extension_data":包扩展数据,nLength:包扩展数据长度
//							"package_rtp_audio_custom_data" :包前自定义音频数据,nLength:包前自定义音频数据长度
/// 返回值：见错误码
//
SCAPI int CALLMETHOD SC_SetExtInfo(IN SCHANDLE hSCHandle, IN const char* type, IN const void* pExtInfo, IN int nLength);

#ifdef __cplusplus
}
#endif

#endif

