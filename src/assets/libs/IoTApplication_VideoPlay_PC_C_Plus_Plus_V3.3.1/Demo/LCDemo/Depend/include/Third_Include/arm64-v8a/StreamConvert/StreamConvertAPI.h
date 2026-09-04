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

#else /*linux or mac*/

    #define SCAPI
    #define CALLMETHOD

#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef void* SCHANDLE;

// 错误码
enum
{
	SCERR_NoError = 0,				// 成功
	SCERR_InvalidHandle,			// 无效句柄
	SCERR_NoSupport,				// 解析或封装类型不支持
	SCERR_Thread,					// 内部线程出错
	SCERR_Param,					// 参数有误

	SCERR_FileOpen,					// 文件打开出错，可能已被互斥打开
	SCERR_FileRead,					// 文件读取出错
	SCERR_FileWrite,				// 文件写入出错
	SCERR_Format,					// 码流格式有误，无法继续解析

	SCERR_BufferOverFlow,			// 内部缓冲溢出
	SCERR_SysOutOfMem,				// 系统内存不足

	SCERR_NoIDRFrame,				// 解析或封装类型不支持
	SCERR_NoOutPut,					// 同步封装或解析逻辑中无数据输出
	SCERR_ErrorOrder,				// 调用顺序有误

	SCERR_KeyError,					// 回放时输入秘钥错误
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
}SC_TYPE;

//
// 封包信息回调
// pData：  已完成的一帧数据，RTP封包信息应从该回调中取得
// iLen:    帧数据长度
// lUser：  用户数据
//
typedef void (CALLMETHOD *pfSCPacketsCallback)(unsigned char* pData, int iLen, void* lUser);

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


#ifdef __cplusplus
}
#endif

#endif

