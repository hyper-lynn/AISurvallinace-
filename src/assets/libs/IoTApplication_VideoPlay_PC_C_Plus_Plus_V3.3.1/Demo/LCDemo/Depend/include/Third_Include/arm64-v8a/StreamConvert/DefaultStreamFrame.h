//
//  "$Id: DefaultStreamFrame.h 205072 2014-07-17 01:38:36Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_DEFAULTSTREAMFRAME_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_DEFAULTSTREAMFRAME_H__

#include "StreamFrame.h"

namespace Dahua {
namespace StreamParser {
		
//
// 一般情况下可使用这个类做内存块
//
class STREAM_PARSER_API CDefaultStreamFrame : public IStreamFrame
{
public:
	CDefaultStreamFrame()
	{
		m_buf = NULL;
		m_len = 0;
	}
	
	virtual ~CDefaultStreamFrame()
	{
	}
	
	// 分配内存
	virtual bool alloc(int len)
	{
		m_buf = new uint8_t[len];
		m_len = len;
		return (m_buf != NULL);
	}
	// 释放内存
	virtual void release()
	{
		if (m_buf)
		{
			delete [] m_buf;
			m_buf = NULL;
			m_len = 0;
		}
	}
	// new自身，必须实现
	virtual IStreamFrame *create()
	{
		return new CDefaultStreamFrame;
	}
	// 拷贝自身，必须实现
	virtual void copy(IStreamFrame *dst)
	{
		CDefaultStreamFrame *tmp = (CDefaultStreamFrame *)dst;
		tmp->m_buf = m_buf;
		tmp->m_len = m_len;
	}
	// 获取内存
	virtual uint8_t *buffer()
	{
		return m_buf;
	}
	// 获取长度
	virtual int length()
	{
		return m_len;
	}
	
private:
	uint8_t *m_buf;
	int m_len;
};

} // namespace StreamParser
} // namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_DEFAULTSTREAMFRAME_H__
