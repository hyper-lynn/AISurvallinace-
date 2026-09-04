#ifndef _H264_H_
#define _H264_H_

#include "Infra/IntTypes.h"

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
struct H264NalHeader
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	unsigned char nal_unit_type:5;
	unsigned char nal_ref_idc:2;
	unsigned char forbidden_zero_bit:1;
#elif __BYTE_ORDER == __BIG_ENDIAN
	unsigned char forbidden_zero_bit:1;
	unsigned char nal_ref_idc:2;
	unsigned char nal_unit_type:5;
#endif
};
#pragma pack(pop)


///\brief H264中的SPS、PPS信息 
struct H264KeyInfo
{
	unsigned char *sps;
	int sps_len;
	unsigned char *pps;
	int pps_len;
};

///\brief 参见H264及svc协议，目前没用到的没有列出.
enum E_NalUnitType
{
	NAL_UNIT_UNDEF					= 0,
	NAL_UNIT_CODED_SLICE			= 1,
	NAL_UNIT_CODED_SLICE_IDR		= 5, 
	NAL_UNIT_SEI					= 6,
	NAL_UNIT_SPS					= 7,
	NAL_UNIT_PPS					= 8,
	NAL_UNIT_DELIMITER				= 9,	///>  NAL 单元分隔符
	NAL_UNIT_SUBSET_SPS				= 15,
	NAL_UNIT_CODED_SLICE_SCALABLE	= 20,
	NAL_UNIT_FU_A					= 28,
};

// H264协议里面规定h264 NAL uint 界定符为0x000001 , 其长度为3 Byte
#define H264_NALU_DELIMITER_LEN		(3UL)

///\brief H264 码流中NAL 单元信息
struct h264_nal_unit
{
	uint8_t  lenbuffer[4];      ///< 4 字节长度信息, 网络字节序
	uint8_t *nalunit;			///< 去除001 开始符的NAL单元
	uint32_t nalunitlen;		///< lenbuffer 的4字节长度和NAL单元长度之和
};

#endif
