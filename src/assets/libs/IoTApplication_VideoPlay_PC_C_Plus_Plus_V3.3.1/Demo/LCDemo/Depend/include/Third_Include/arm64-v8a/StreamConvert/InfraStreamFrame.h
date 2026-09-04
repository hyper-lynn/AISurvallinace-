//
//  "$Id: InfraStreamFrame.h 205072 2014-07-17 01:38:36Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_INFRASTREAMFRAME_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_INFRASTREAMFRAME_H__

#include "StreamFrame.h"
#include "Memory/Packet.h"
using namespace Dahua::Memory;

namespace Dahua {
namespace StreamParser {

/************************************************************************/
/* 使用CPacket实现StreamFrame                                           */
/************************************************************************/
class STREAM_PARSER_API CInfraStreamFrame : public IStreamFrame
{
public:
	CInfraStreamFrame()
	{

	}
	~CInfraStreamFrame()
	{
		m_packet = CPacket();
	}

public:
	// 分配内存
	virtual bool alloc(int len)
	{
		m_packet = CPacket(len);
		return m_packet.valid();
	}
	// 释放内存
	virtual void release()
	{
		m_packet = CPacket();
	}
	// 获取内存
	virtual uint8_t *buffer()
	{
		return m_packet.getBuffer();
	}
	// 获取长度
	virtual int length()
	{
		return m_packet.size();
	}
	// new自身，必须实现
	virtual IStreamFrame *create()
	{
		return new CInfraStreamFrame;
	}
	// 拷贝自身到dst中，必须实现
	virtual void copy(IStreamFrame *dst)
	{
		CInfraStreamFrame *tmp = (CInfraStreamFrame *)dst;
		tmp->m_packet = m_packet;
	}

public:
	CPacket m_packet;
};

} // namespace StreamParser
} // namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_INFRASTREAMFRAME_H__
