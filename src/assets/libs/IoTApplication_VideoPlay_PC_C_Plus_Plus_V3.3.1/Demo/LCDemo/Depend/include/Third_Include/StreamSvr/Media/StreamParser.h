#ifndef _STREAMSVR_STREAMPARSE_H_
#define _STREAMSVR_STREAMPARSE_H_

#include "Infra/IntTypes.h"
#include "StreamSvr/Protocol/H265.h"

///\brief 去除防竞争字节数据结构体
struct stRealInfo
{
	uint8_t			*data;			///< 原始的sps 信息
	uint32_t	 	data_len;		///< 去除冗余编码0x03信息的sps信息长度
	uint32_t     	buffer_len;		///< 包含冗余编码0x03信息的sps信息长度
};

#ifdef __cplusplus
extern "C" {
#endif

///\brief 消除H265编码时"有防竞争"机制引入的冗余编码0x03
///\param [in] input-sps信息
///\param [in] input_len-sps信息的长度
///\param [in] pstRealInfo-去除冗余编码0x03的sps信息
///\return 0-ok, -1-failed
int emulated_prevention(uint8_t *input, int32_t input_len, struct stRealInfo *pstRealInfo);

///\brief 解析H265信息
///\param [in] pBuf-sps信息
///\param [in] nSize-sps信息长度
///\param [out] nWidth-宽信息
///\param [out] nHeight-高信息
///\param [out] info-编解码配置信息
///\return 0-ok, -1-failed
int dahua_stmp_H265Analyse(unsigned char *pBuf, int nSize, int *nWidth, int *nHeight, struct H265DecoderConfigurationRecord *info);

///\brief 获得采样率对应的类型
///\param [in] sample-采样率数值
///\return 采样率数值对应的类型
int getAAcSampleType(int sample);

///\brief 解析H264信息
///\param [in] pBuf-sps信息
///\param [in] nSize-sps信息长度
///\param [out] nWidth-宽信息
///\param [out] nHeight-高信息
///\param [out] framerate-帧率
///\param [out] codectype-编码类型，0表示场编码，1表示帧编码
///\return 0-ok, -1-failed
int dahua_stmp_H264Analyse(unsigned char *pBuf, int nSize, int *nWidth, int *nHeight, int *framerate, int* codectype);

#ifdef __cplusplus
}
#endif


#endif
