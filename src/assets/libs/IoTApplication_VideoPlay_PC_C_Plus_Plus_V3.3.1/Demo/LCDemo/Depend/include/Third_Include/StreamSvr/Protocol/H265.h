#ifndef _H265_H_
#define _H265_H_

#include "Infra/IntTypes.h"


#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
struct H265NalUnitHead
{
#if __BYTE_ORDER == __BIG_ENDIAN
	unsigned char flag:1;
	unsigned char nal_type:6;
	unsigned char h_layer_id:1;

	unsigned char l_layer_id:5;
	unsigned char tid:3;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	unsigned char h_layer_id:1;
	unsigned char nal_type:6;
	unsigned char flag:1;
	
	unsigned char tid:3;
	unsigned char l_layer_id:5;
#endif
};

#pragma pack(pop)//恢复对齐状态

#define H265_NAL_UNIT_HEAD_LEN	(sizeof(struct H265NalUnitHead))

typedef struct H265NalUnitHead H265PayLoadHead;
#define H265_NAL_PAYLOAD_HEAD_LEN		(sizeof(H265PayLoadHead))

struct H265KeyInfo
{
	unsigned char *sps;
	int sps_len;
	unsigned char *pps;
	int pps_len;
	unsigned char *vps;
	int vps_len;
};

///\brief H265 解码参数信息, 具体字段含义见H265	协议文档
struct H265DecoderConfigurationRecord 
{
	uint8_t  general_profile_space;
	uint8_t  general_tier_flag;
	uint8_t  general_profile_idc;
	uint32_t general_profile_compatibility_flags;
	uint64_t general_constraint_indicator_flags;
	uint8_t  general_level_idc;
	uint8_t  chromaFormat;
	uint8_t  bitDepthLumaMinus8;
	uint8_t  bitDepthChromaMinus8;
	uint8_t  temporalIdNested;
};

//NAL TYPE的值 ， 小于32都是数据值
enum H265NalType
{
	H265_NAL_TRAIL_N				= 0,		//Coded slice segment of a non-tsa, non-stsa
	H265_NAL_TRAIL_R				= 1,		//同上
	H265_NAL_TSA_N					= 2,
	H265_NAL_TSA_R					= 3,
	H265_NAL_STSA_N					= 4,
	H265_NAL_STSA_R					= 5,
	H265_NAL_RADL_N					= 6,
	H265_NAL_RADL_R					= 7,
	H265_NAL_RASL_N					= 8,
	H265_NAL_RASL_R					= 9,
	H265_NAL_BLA_W_LP				= 10,
	H265_NAL_BLA_W_RADL				= 11,
	H265_NAL_BLA_N_LP				= 12,
	H265_NAL_IDR_W_RADL				= 19,		//Coded slice segment of a IDR picture
	H265_NAL_IDR_N_LP				= 20,		//同上
	H265_NAL_CRA_NUT				= 21,
	H265_NAL_VPS					= 32,		//Video parameter set
	H265_NAL_SPS					= 33,		//Sequence parameter set
	H265_NAL_PPS					= 34,		//Picture parameter set
	H265_NAL_PREFIX_SEI				= 39,		//Supplemental enhancement information(SEI)
	H265_NAL_SUFFIX_SEI				= 40,

	//the type of pay load header
	H265_AGGREGATION_UNIT_TYPE		= 48,		//see chapter 4.7 of draft-ietf-payload-rtp-h265-06.pdf
	H265_FRAGMENT_UNIT_TYPE			= 49,		//see chapter 4.8 of draft-ietf-payload-rtp-h265-06.pdf

	H265_NAL_UNIT_UNSPECIFIED_63	= 63,		//扩展的NAL类型
};

//h265 NAL uint 界定符0x000001的长度为3 Byte
#define NALU_DELIMITER_LEN		(3UL)


#endif




