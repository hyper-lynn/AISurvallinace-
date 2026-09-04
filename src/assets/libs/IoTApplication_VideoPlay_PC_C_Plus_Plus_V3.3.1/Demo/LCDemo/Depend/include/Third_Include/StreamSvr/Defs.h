//
//  "$Id: Defs.h 55398 2012-03-23 04:20:22Z zhou_mingwei $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//					
//

#ifndef __INCLUDE_DAHUA_STREAMSVR_DEFS_H__
#define __INCLUDE_DAHUA_STREAMSVR_DEFS_H__

#include "Infra/IntTypes.h"

#ifdef WIN32

#ifdef STREAMSVR_DLL_BUILD
#define  STREAMSVR_API _declspec(dllexport)
#elif defined STREAMSVR_DLL_USE
#define  STREAMSVR_API _declspec(dllimport)
#else
#define STREAMSVR_API  
#endif

#else
#define STREAMSVR_API  
#endif

#ifndef NULL
#define NULL 0
#endif

namespace Dahua {
namespace StreamSvr {

// 打印streamsvr库版本号
STREAMSVR_API void RegisterStreamSvrVersion();

#define MAX_TIME_ZONE_NUM	33
#define BEIJING_TIME_ZONE 	13

struct TimeZome
{
	int iToken;
	int iSecond;
	char szName[16];
};

const TimeZome g_TimeZone[MAX_TIME_ZONE_NUM] = {
	{0, 0 * 3600,"GMT+00:00"},
	{1, 1 * 3600,"GMT+01:00"},
	{2, 2 * 3600,"GMT+02:00"},
	{3, 3 * 3600,"GMT+03:00"},
	{4, 3 * 3600 + 1800,"GMT+03:30"},
	{5, 4 * 3600,"GMT+04:00"},
	{6, 4 * 3600 + 1800,"GMT+04:30"},
	{7, 5 * 3600,"GMT+05:00"},
	{8, 5 * 3600 + 1800,"GMT+05:30"},
	{9, 5 * 3600 + 1800 + 900,"GMT+05:45"},
	{10, 6 * 3600,"GMT+06:00"},
	{11, 6 * 3600 + 1800,"GMT+06:30"},
	{12, 7 * 3600,"GMT+07:00"},
	{13, 8 * 3600,"GMT+08:00"},
	{14, 9 * 3600,"GMT+09:00"},
	{15, 9 * 3600 + 1800,"GMT+09:30"},
	{16, 10 * 3600,"GMT+10:00"},
	{17, 11 * 3600,"GMT+11:00"},
	{18, 12 * 3600,"GMT+12:00"},
	{19, 13 * 3600,"GMT+13:00"},
	{20, -1 * 3600,"GMT-01:00"},
	{21, -2 * 3600,"GMT-02:00"},
	{22, -3 * 3600,"GMT-03:00"},
	{23, -3 * 3600 - 1800,"GMT-03:30"},
	{24, -4 * 3600,"GMT-04:00"},
	{25, -5 * 3600,"GMT-05:00"},
	{26, -6 * 3600,"GMT-06:00"},
	{27, -7 * 3600,"GMT-07:00"},
	{28, -8 * 3600,"GMT-08:00"},
	{29, -9 * 3600,"GMT-09:00"},
	{30, -10 * 3600,"GMT-10:00"},
	{31, -11 * 3600,"GMT-11:00"},
	{32, -12 * 3600,"GMT-12:00"},
};

#if __BYTE_ORDER == __LITTLE_ENDIAN

///\ brief 网络字节序转换 : 将待转换的网络字节序数据指针 转换为uint16_t类型的值
#define E_NTOHSP(pNetworkPointer) \
		((uint16_t)( \
		    (((uint16_t)(((uint8_t *)(pNetworkPointer))[0])) << 8) | \
		    ((uint16_t)(((uint8_t *)(pNetworkPointer)) [1])) 	     \
		))

///\ brief 网络字节序转换 : 将待转换的网络字节序数据指针 转换为uint32_t类型的值
#define E_NTOHLP(pNetworkPointer) \
		((uint32_t)( \
			(((uint32_t)(((uint8_t *)(pNetworkPointer))[0])) << 24) | \
			(((uint32_t)(((uint8_t *)(pNetworkPointer))[1])) << 16) | \
			(((uint32_t)(((uint8_t *)(pNetworkPointer))[2])) << 8)  | \
			((uint32_t)(((uint8_t *)(pNetworkPointer)) [3])) 	      \
		))
				
///\ brief 网络字节序转换 : 将待转换的网络字节序数据指针 转换为uint64_t类型的值
#define E_NTOHLLP(pNetworkPointer) \
		((uint64_t)( \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[0])) << 56) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[1])) << 48) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[2])) << 40) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[3])) << 32) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[4])) << 24) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[5])) << 16) | \
			(((uint64_t)(((uint8_t *)(pNetworkPointer))[6])) << 8)  | \
			((uint64_t)(((uint8_t *)(pNetworkPointer)) [7])) 	      \
		))
		
///\ brief 网络字节序转换 : 将待转换的网络字节序数据指针 转换为double类型的值
#define E_NTOHDP(pNetworkPointer,hostDoubleVal) \
			do{ 								\
				union double_and_uint64_buffer  \
				{								\
					double   *doublebuffer;     \
					uint64_t *uint64buffer;     \
				};								\
				uint64_t ___tempENTOHDP = E_NTOHLLP(pNetworkPointer); 			 \
				double_and_uint64_buffer __buffer;					  			 \
				__buffer.uint64buffer = &___tempENTOHDP;		     			 \
				hostDoubleVal = (double)(*((double *)__buffer.doublebuffer));   \
			}while(0)

///\ brief 网络字节序转换:将待转换数据 转换为uint64_t类型的网络字节序
#define E_HTONLL(x) \
			((uint64_t)( \
				((((uint64_t)(x)) & 0xff00000000000000LL) >> 56) | \
				((((uint64_t)(x)) & 0x00ff000000000000LL) >> 40) | \
				((((uint64_t)(x)) & 0x0000ff0000000000LL) >> 24) | \
				((((uint64_t)(x)) & 0x000000ff00000000LL) >> 8)  | \
				((((uint64_t)(x)) & 0x00000000ff000000LL) << 8)  | \
				((((uint64_t)(x)) & 0x0000000000ff0000LL) << 24) | \
				((((uint64_t)(x)) & 0x000000000000ff00LL) << 40) | \
				((((uint64_t)(x)) & 0x00000000000000ffLL) << 56)   \
			))

///\ brief 网络字节序转换 : 将待转换数据 转换为uint64_t类型的网络字节序
#define E_HTOND(hostDoubleVal,networkUI64Val) networkUI64Val=E_HTONLL(*((uint64_t *)(&(hostDoubleVal))))

#else

#define E_HTONLL(x) (x)

///\ brief 网络字节序转换 : 将待转换数据 转换为uint64_t类型的网络字节序
#define E_HTOND(hostDoubleVal,networkUI64Val) networkUI64Val=E_HTONLL(*((uint64_t *)(&(hostDoubleVal))))

#endif //__BYTE_ORDER == __LITTLE_ENDIAN

///\brief 退出错误码组装宏
#define EXIT_CAUSE_ERRNO(mainreason, extrareason)		(((mainreason) << 16) | (extrareason))

///\brief 退出主错误以及辅错误提取宏
#define EXIT_CAUSE_MAIN(exitCauseErrno)     (((exitCauseErrno) & 0xffff0000) >> 16)
#define EXIT_CAUSE_EXTRA(exitCauseErrno)	((exitCauseErrno)  & 0x0000ffff)

///\brief 检测帧丢失事件默认周期,单位秒
#define DEFAULT_CHECKLOSTFRAME_DURATION      60

///\brief 检测帧延时事件默认周期,单位秒
#define DEFAULT_CHECKFRAMEDELAY_DURATION     60

///\brief 检测视频帧延时事件阈值, 单位毫秒
#define DEFAULT_CHECKFRAMEDELAY_VIDEOTHRESHOLD    1000

///\brief 检测音频帧延时事件阈值, 单位毫秒
#define DEFAULT_CHECKFRAMEDELAY_AUDIOTHRESHOLD    200

///\brief 检测重新取流超时事件阈值, 单位毫秒
#define DEFAULT_CHECKSTREAMTIMEOUT_THRESHOLD    5000

///\brief 追加日志数据长度, 单位字节
#define DEFAULT_APPENDDATA_LENGTH    1024

///\brief 设置srand值
///\param [in] seed-种子值
///\return
STREAMSVR_API void srand_value(unsigned int seed);

///\brief 获取rand值
///\return 随机值
STREAMSVR_API int rand_value();

///\brief 获取random值
///\return 随机值
STREAMSVR_API long int random_value();

}//StreamSvr
}//Dahua

#endif  //__INCLUDE_DAHUA_STREAMSVR_DEFS_H__
