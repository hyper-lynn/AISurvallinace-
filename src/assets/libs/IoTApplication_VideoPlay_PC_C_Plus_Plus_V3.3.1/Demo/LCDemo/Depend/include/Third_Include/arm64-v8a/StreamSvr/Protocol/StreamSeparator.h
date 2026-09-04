#ifndef __INCLUDE_DAHUA_STREAMSVR_STREAMSEPARATOR_H__
#define __INCLUDE_DAHUA_STREAMSVR_STREAMSEPARATOR_H__

#include <string.h>
#include "StreamSvr/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "Memory/SharedPtr.h"
#include "Infra/Error.h"
#include "Component/Defs.h"
#include "StreamSvr/Util/PrintLog.h"

namespace Dahua{
namespace StreamSvr{

///\brief 码流分离器接口
class STREAMSVR_API IStreamSeparator
{
public:
	///\brief 码流分离动态内存分配策略
	enum DynMemPolicy
	{
		MinMemPolicy = 0,  	///< 固定内存策略, 为32 K ，内存占用最小,但会产生拷贝，性能较低
		IFrameSizePolicy,	///< 按最大I 帧进行分配策略,  可以减少一次拷贝，性能较优
		DynMemPolicyNum,	///< 动态内存分配策略数目
	};
	
	///\brief 分离包结构定义
	struct SeparatorFrame
	{
		CMediaFrame frame;	///> 数据包
		int	channelId;		///> 数据通道，表示RTP,还是RTCP,或者是RTSP等
		int	length;			///> 数据包对应的长度
		SeparatorFrame():channelId(-1234),length(-1234){}
	};
	
	enum
	{
		MaxPacketNum = 32,				///> 分离的包的个数参考值, 用于单次大小调整单位
		SeparatorBufferLen = 32 * 1024,	///> 分离器缓冲大小参考值, 用于单次大小调整单位
	};
	
	struct SeparatorStatus
	{
		uint32_t			m_buf_len;					///>缓冲区的总长度
		uint32_t			m_recv_len;					///> 接收到的有效数据长度
		uint32_t			m_offset_len;				///> 当前待处理的数据的起始偏移
		int					m_packet_size;				///> 分离出的包的缓冲数组大小
		int				    m_packet_num;				///> 分离出的包的个数
		Stream::CMediaFrame	m_recv_buf;					///> 分离器接收缓冲	
		SeparatorFrame 	   *m_packet;					///> 分离出的包的缓冲数组地址
		SeparatorFrame		m_current_packet;			///> 当前的未分离完毕的包
		bool				m_getstream;				///> 是否收到码流,目前仅私有协议使用

		SeparatorStatus():m_buf_len(SeparatorBufferLen), m_recv_len(0),   m_offset_len(0),
							  m_packet_size(MaxPacketNum),   m_packet_num(0), m_getstream(false)					  
		{
			m_recv_buf = Stream::CMediaFrame(m_buf_len);
			m_packet   = new SeparatorFrame[m_packet_size]();

			if ((NULL == m_recv_buf.getBuffer()) || (NULL == m_packet))
			{
				DLOG_ERR_THIS("buffer invalid, buffer:%p, packet:%p \n", m_recv_buf.getBuffer(), m_packet);
			}
		}

		~SeparatorStatus()
		{
			if (NULL != m_packet)
			{
				delete [] m_packet;
			}
		}	
	
		SeparatorStatus& operator=(const SeparatorStatus & status)
		{
			m_buf_len     = status.m_buf_len;
			m_recv_len    = status.m_recv_len;
			m_offset_len  = status.m_offset_len;
			m_packet_size = status.m_packet_size;
			m_packet_num  = status.m_packet_num;
		
			m_recv_buf = status.m_recv_buf;

			if (NULL != m_packet)
			{
				delete [] m_packet;
				m_packet = new SeparatorFrame[m_packet_size]();
			} 
						
			for (int i = 0; i < m_packet_size; i++)
			{
				m_packet[i] = status.m_packet[i];
			}

			m_current_packet = status.m_current_packet;
			m_getstream      = status.m_getstream;
			return *this;
		}
	};

	IStreamSeparator();
	///\brief 虚析构接口
	virtual ~IStreamSeparator() {}
	
public:

	///\brief 将从网络上接收到的数据分离，分离的原因是接收的数据既有数据也有信令。
	///\param [in] recvLen-本次接收到的数据长度
	///\return -1-失败, 0-成功
	virtual int separate(uint32_t recvLen) = 0;

	///\brief 获取剩余缓冲指针和剩余大小
	///\param [in] length-剩余缓冲大小
	///\return 剩余缓冲的起始地址
	virtual uint8_t* getBuffer(int &length);

	///\brief 获取分离器内部状态
	Memory::TSharedPtr<SeparatorStatus> getStatus();

	///\brief 拷贝分离器状态
	int copyStatus(const Memory::TSharedPtr<SeparatorStatus>& status);

	///\brief 获取分离的结果，通过返回值返回
	///\param [in/out] frameCount-存放分离的包的个数
	///\return NULL-失败，剩余包的数组指针-成功
	struct SeparatorFrame* getFrames(int &frameCount);

	///\brief 当前码流分离是否缓存为空
	///\return true-完成, false-未完成, 待继续处理
	virtual bool isBufferEmpty();

	///\brief 设置分离内存动态分配策略
	///\param [in] policy-设置的动态分配策略
	virtual void setDynMem(DynMemPolicy policy){}

	///\brief 当策略为IFrameSizePolicy 时的最大I 帧大小
	///\param [in] size-最大I 帧大小
	virtual void setMemSize(uint32_t size){}

	DAHUA_COMPONENT_FUNCTION_REVSERVED(27);

protected:
	Memory::TSharedPtr<SeparatorStatus> m_status;
};

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_STREAMSEPARATOR_H__
