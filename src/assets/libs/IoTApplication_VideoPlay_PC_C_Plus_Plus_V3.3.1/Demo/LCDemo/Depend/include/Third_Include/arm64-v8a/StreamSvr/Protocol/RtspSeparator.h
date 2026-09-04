#ifndef __INCLUDED_DAHUA_STREAMSVR_RTSPSEPARATOR_H__
#define __INCLUDED_DAHUA_STREAMSVR_RTSPSEPARATOR_H__

#include "StreamSvr/Defs.h"
#include "StreamSeparator.h"

namespace Dahua{
namespace StreamSvr{

class RtspSeparatorImp;

///\brief RTP Over RTSP方式下的分离器
class STREAMSVR_API CRtspSeparator : public IStreamSeparator
{
public:
	///\brief 构造函数
	CRtspSeparator();

	///\brief 析构函数
	~CRtspSeparator();

	///\brief 将从网络上接收到的数据分离，分离的原因是接收的数据既有数据也有信令。
	///\param [in] recvLen-本次接收到的数据长度
	///\return -1-失败, 0-成功
	int separate(uint32_t recvLen);

	///\brief 设置动态分离内存,  用于减少拷贝次数
	///\param[in] policy 动态内存策略
	void setDynMem(DynMemPolicy policy);

	///\brief 设置动态分离内存策略为IFrameSizePolicy 时的最大内存大小, 默认为32 K
	///\param[in] size 动态内存大小
	void setMemSize(uint32_t size);

	///\brief 设置转义字符映射标志
	///\param [bool] enable-使能标志
	void setCharMap(bool enable);
private:
	///\brief get_packet_rtp, get_packet_private的封装入口
	///\param [out] ret_val分离出来的包的数目
	///\return 返回分离后完整包的首地址
	char* get_packet(int &ret_val);

	///\brief 获取RTSP信令字符串中Content-Length字段携带的数值
	///\param [in] recv_ptr--RTSP信令字符串的起始地址
	///\param [in] content_mark--RTSP信令字符串中Content-Length字段的起始地址
	///\return -1-失败，其它-成功, 返回提取出的Content-Length字段的值
	int get_content_length(const char *recv_ptr, const char *content_mark);

	//\brief 上一次分离是否还遗留数据需要处理
	///\return true-是, false -否
	bool IsHasLeftData();

	///\brief 上一次分离的遗留数据处理
	///\param [in/out] buf--待处理数据的首地址,输出处理后的地址起始位置
	///\return 0-成功, -1-失败, 1 -还未处理完成
	int dealLeftRtpData(char* &buf);

	///\brief 处理完整的一个rtp包数据
	///\param [out] mediaframe--处理完成的一个rtp 包
	///\param [out] buffer           --待处理的一个rtp 包起始地址
	///\param [out] pkt_len        --待处理的一个rtp 包长度信息
	///\return 0-成功, -1-失败
	int dealMediaData(CMediaFrame &mediaframe, char *buffer, int pkt_len);

	///\brief 缓存未处理完成的一个rtp 包的部分数据
	///\param [out] recv_len  --待处理的所有数据长度
	///\param [in] buffer       --待处理的一个rtp 包起始地址
	///\param [in] pkt_len    --待处理的一个rtp 包长度信息
	///\param [in] channel    --待处理的一个rtp 包交织通道信息
	///\return 0-成功, -1-失败
	int cacheData(uint32_t &recv_len, char *&buffer, uint32_t pkt_len, int channel);

	///\brief 处理此次分离后的剩余数据
	///\param [in] bufused      --缓存中已接收的所有数据长度信息
	///\param [in] currptr        --未分离完成的所有rtp 包的起始地址
	///\param [in] currptrlen   --未分离完成的所有rtp 包的长度信息
	int dealLeftData(uint32_t bufused, char* currptr, uint32_t currptrlen);

	///\brief 最小分离内存策略, 该策略固定32K内存接收和处理, 存在多一次拷贝
	///\param [in] currptr        --未分离完成的所有rtp 包的起始地址
	///\param [in] currptrlen   --未分离完成的所有rtp 包的长度信息
	int dealMinMemPolicy(char* currptr, uint32_t currptrlen);

	///\brief 根据I 帧最长长度动态调整内存进行分离策略,  其内存为I 帧大小+ 32 K
	///\         需要调用setMemSize 接口设置最长的I  帧信息, 保证I 帧时才进行一次拷贝
	///\param [in] bufused      --缓存中已接收的所有数据长度信息
	///\param [in] currptr        --未分离完成的所有rtp 包的起始地址
	///\param [in] currptrlen   --未分离完成的所有rtp 包的长度信息
	int dealIFrameSizePolicy(uint32_t bufused, char* currptr, uint32_t currptrlen);
		
private:
	RtspSeparatorImp *m_internalmpl;	///< rtsp 码流分离私有成员信息
	
};

}//StreamSvr
}//Dahua

#endif //__INCLUDED_DAHUA_STREAMSVR_RTSPSEPARATOR_H__

