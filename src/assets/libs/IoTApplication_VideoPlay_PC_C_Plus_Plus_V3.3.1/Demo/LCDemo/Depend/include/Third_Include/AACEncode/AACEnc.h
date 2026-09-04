/********************************************************************
*	Copyright         1992-2008, ZheJiang Dahua Technology Stock Co.Ltd.
* 					   All Rights Reserved
*	File name:         AACEnc.h    	
*	Author:	           
*	Description:	   AAC编码
*	Created:	       
*	Revision Record:   2013:09:07 modify by gaoya
*					   1.修改了接口函数，函数的输入输出参数形式
*********************************************************************/
#ifndef _AACENC_H_
#define _AACENC_H_

#include "audio_typedef.h"

 
/*---------------------------------------------------*/
#if defined(_WIN32) && !defined(__MINGW32__)
    #ifndef AACENC_LIB_EXPORTS
        #ifdef  AACENC_DLL_EXPORTS
            #define AACENCAPI __declspec(dllexport)
        #else
            #define AACENCAPI __declspec(dllimport)
        #endif
   #else
   #define AACENCAPI 
   #endif
#else
#define AACENCAPI 
#endif
/*---------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* The type of API parameters */
#define IN
#define INOUT
#define OUT

typedef enum
{
    RUN_OK                   =  0, /* 正确执行             */
    ALLOC_FAILED             = -1, /* 分配内存失败         */
    POINTER_NULL             = -2, /* 指针为空             */
    IN_LEN_ERROR             = -3, /* 输入长度错误         */
	CLOSE_ERROR              = -4, /* 一般错误             */
	BUFLEN_ERROR             = -5, /* 缓存长度错误         */     
	SETCONF_ERROR            = -6, /* 配置失败             */
	OFFSET_ERROR             = -7, /* 偏移错误             */
	CHANNEL_ERROR            = -8, /* 通道数设置错误       */
}AAC_ENC_RESULT;

typedef struct
{
    WORD32   frequency;  /* 输入采样频率，单位；Hz                               */
    WORD32   channels;   /* 通道数                                               */
    WORD32   bitRate;    /* 码率，码率低于采样率时，编码的结果基本相同，         */
						 /* 码率最大不能大于采样率的6倍                          */
					     /* 大于采样时音质比较好，一般取采样率两倍，单位：bips   */
	WORD32   block_switch;/* 窗的选择，0-normal,1-noshort,2-nolong */
}AAC_ENC_Format;

/********************************************************************
*	Funcname: 			AACEnc_GetVersion
*	Purpose:			获取svn版本号  	
*   InputParam:   		
*   Return:             
*   Created:	        2015.10.12:gaoya
*   Rivision Record:    
*********************************************************************/
WORD8 *AACEnc_GetVersion( void );

/********************************************************************
*	Funcname: 	       AAC_Enc_Init   	
*	Purpose:	       初始化
*   InputParam:        INOUT  Audio_Handle *handle: 句柄 
*   OutputParam:        
*   Return:            AAC_ENC_RESULT
*   Created:	       2013:09:07 by gaoya
*   Revision Record:   1.将一些分配内存独立出来
*********************************************************************/
AAC_ENC_RESULT AACENCAPI AAC_Enc_Init( INOUT  Audio_Handle *handle );


/********************************************************************
*	Funcname: 	       AAC_Enc_SetFormat  	
*	Purpose:	       打开编码通道，返回编码句柄
*   Param:             IN AAC_ENC_Format *pFormat:  配置参数
		               INOUT  Audio_Handle *handle: 句柄

*   Return:            AAC_ENC_RESULT
*   Created:	       2013:07:27  
*   Revision Record:   2013:09:07 modify by gaoya
*                      1.函数接口，输入参数用结构体表示                  
*********************************************************************/
AAC_ENC_RESULT AACENCAPI AAC_Enc_SetFormat( IN     AAC_ENC_Format *pFormat, 									   
									  INOUT  Audio_Handle   *handle );

/********************************************************************
*	Funcname: 	      AAC_Enc_Encode   	
*	Purpose:	      音频编码
*   InputParam:       IN  Audio_Handle handle:      句柄
		              IN  AudioBuf    *pAudioInBuf: 输入音频结构
		              OUT Audio_Handle pOutBuf:		 输出数据地址
		              OUT UWORD32     *nDstLen:	 编码后数据大小
*   Return:           AAC_ENC_RESULT
*   Created:	      2013:09:05  
*   Revision Record:  1，修改了输入输出接口，输入用结构体表示
*                     2.增加了offset  
*********************************************************************/
AAC_ENC_RESULT AACENCAPI AAC_Enc_Encode( IN  Audio_Handle handle, 
										 IN	 AudioBuf    *pAudioInBuf,
										 OUT Audio_Handle pOutBuf, 
										 OUT UWORD32     *nDstLen );

/********************************************************************
*	Funcname: 	      AAC_Enc_DeInit 	
*	Purpose:	      关闭编码通道
*   InputParam:       IN Audio_Handle handle:	编码通道句柄
*   Return:           AAC_ENC_RESULT
*   Created:	      2013:09:05  
*   Revision Record:  1.修改了接口函数
*********************************************************************/
AAC_ENC_RESULT AACENCAPI AAC_Enc_DeInit  ( IN Audio_Handle handle );

#ifdef __cplusplus
}
#endif

#endif /* _DLL_AACENC_H_ */

