//
//  "$Id: StreamFrame.h 205072 2014-07-17 01:38:36Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_MEDIAFRAME_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_MEDIAFRAME_H__

#include "BaseType.h"
#include <stdio.h>

namespace Dahua {
namespace StreamParser {

/************************************************************************/
/* StreamParser::IStreamFrame 内存块接口类                              */
/************************************************************************/
class STREAM_PARSER_API IStreamFrame
{
public:
	// 重载下列函数由外部实现自己的内存管理：
	// 分配内存
	virtual bool alloc(int len) = 0;
	// 释放内存
	virtual void release() = 0;
	// 获取内存
	virtual uint8_t *buffer() = 0;
	// 获取长度
	virtual int length() = 0;
	// new自身，必须实现
	virtual IStreamFrame *create() = 0;
	// 拷贝自身到dst中，必须实现
	virtual void copy(IStreamFrame *dst) = 0;

public:
	IStreamFrame();
	virtual ~IStreamFrame();

	// 新增一个引用对象
	IStreamFrame *add_ref();
	// 销毁本次引用
	void del_ref();

	inline int getType() {return m_type;}
	inline int getSequence() {return m_seq;}
	inline uint64_t getPts() {return m_pts;}
	inline uint64_t getUtc() {return m_utc;}
	inline int getChannel() {return m_channel;}
	
	inline void setType(int type) {m_type = type;}
	inline void setSequence(int seq) {m_seq = seq;}
	inline void setPts(uint64_t pts) {m_pts = pts;}
	inline void setUtc(uint64_t utc) {m_utc = utc;}
	inline void setChannel(int chn) {m_channel = chn;}
	
private:
	int *m_ref;
	IStreamFrame *m_obj;
	int m_type;
	int m_seq;
	uint64_t m_pts;
	uint64_t m_utc;
	int m_channel;
};

//
// 使用已知内存的StreamFrame，一般可用于数据引用
//
class STREAM_PARSER_API CRefStreamFrame : public IStreamFrame
{
public:
	CRefStreamFrame();
	virtual ~CRefStreamFrame();
	virtual bool alloc(int len);
	virtual void release();
	virtual uint8_t *buffer();
	virtual int length();
	virtual IStreamFrame *create();
	virtual void copy(IStreamFrame *dst);

	// 设置buffer，同时可指定引用的源IStreamFrame
	void use(uint8_t *buff, int size, IStreamFrame *src = NULL);
	// 设置获取码流类型
	void set_stream_type(int stype);
	int get_stream_type();

private:
	uint8_t *m_buf;
	int m_len;
	int m_stream_type;
	IStreamFrame *m_src;
};

} // namespace StreamParser
} // namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_MEDIAFRAME_H__
