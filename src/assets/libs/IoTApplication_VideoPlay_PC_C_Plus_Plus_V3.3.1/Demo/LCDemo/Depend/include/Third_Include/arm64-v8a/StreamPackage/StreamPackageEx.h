// StreamPackage.h: interface for the StreamPackage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _STREAM_PACKAGE_EX_H_
#define _STREAM_PACKAGE_EX_H_

#include "Defs.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	SG_RTP_PARAM_TYPE_PACKAGE,				//打包
}SG_RTPPARAMTYPE;

typedef struct
{
	unsigned int struct_size;					//结构体长度

	unsigned int max_packet_length;				//最大包长
	unsigned int sequence_number;				//序列号
	unsigned int timestamp;						//时间戳
	unsigned int ssrc;							//SSRC
	unsigned int audio_sample;					//采样率
	unsigned int payload_type;					//负载类型
	unsigned char* extension_data;				//包扩展数据
	unsigned int extension_data_length;			//包扩展数据长度
	unsigned char* custom_data;					//包前自定义数据
	unsigned int custom_data_length;			//包前自定义数据长度
	unsigned int rtp_packet_all_output_flag;	//设置一帧数据打包成RTP包是否一次性输出标识
	unsigned int audio_payload_type;			//设置音频数据载荷值
	unsigned char* audio_custom_data;			//包前自定义音频数据
	unsigned int audio_custom_data_length;		//包前自定义音频数据长度
	unsigned int audio_sequence_number;			//音频打包序列号
	unsigned int audio_timestamp;				//音频打包时间戳
	unsigned int audio_ssrc;					//音频打包同步时间源
}SGRtpPackageParam;								//RTP打包参数


/************************************************************************
*	FuncName:			SG_SetParam
*	Purpose:				设置参数
*	InputParam:			handle: 打包句柄
								nParamType:参数类型
								pParam:参数地址
								nParamLength:参数大小
*	Return:					成功返回SG_ERR_NOERR, 失败返回错误
*	Created:				2015.01.29
*	Revision:				Ver 1.0: Harry
************************************************************************/
STREAMPACKAGE_API int CALLMETHOD SG_SetParam(void* handle, unsigned int nParamType, const void* pParam, unsigned int nParamLength);

/************************************************************************
*	FuncName:			SG_GetParam
*	Purpose:				获取参数
*	InputParam:			handle:打包句柄
								nParamType:参数类型
*	OutputParam:		pParam:参数地址
*	InoutParam:			pParamLength:参数大小，调用前表示pParam大小，调用后表示获取的pParam大小
*	Return:					成功返回SG_ERR_NOERR, 失败返回错误
*	Created:				2015.01.29
*	Revision:				Ver 1.0: Harry
************************************************************************/
STREAMPACKAGE_API int CALLMETHOD SG_GetParam(void* handle, unsigned int nParamType, void* pParam, unsigned int* pParamLength);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_)

