#ifndef _ACC_H_
#define _ACC_H_

#define MAX_ADTS_SAPMLES   13
#define ADTS_HEAD_LEN      7

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
struct AdtsMap
{
	int sampling_frequency_index;	///< ADTS格式下采样率id 索引
	int Dh_sampling_index;			///< 大华协议0x83扩展字段采样率id索引
	int sample;
};
#pragma pack(pop)

//当大华扩展字段中没有对应的分辨率时，0x83扩展字段默认设置为8000，即索引为2
const AdtsMap g_AdtsMap[MAX_ADTS_SAPMLES] = 
{
	{0,  10, 96000},
	{1,  2,  88200},
	{2,  13, 64000},
	{3,  9,  48000},
	{4,  8,  44100},
	{5,  7,  32000},
	{6,  2,  24000},
	{7,  6,  22050},
	{8,  4,  16000},
	{9,  2,  12000},
	{10, 2,  11020},
	{11, 2,  8000},
	{12, 2,  7350},
};


#endif
