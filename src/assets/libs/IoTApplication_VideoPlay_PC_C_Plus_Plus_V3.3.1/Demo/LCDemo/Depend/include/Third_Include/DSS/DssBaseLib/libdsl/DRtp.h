/* Copyright (c) 2011, 浙江大华技术股份有限公司, All rights reserved.
 * 2012-12
 *
 * DRtp.h : Rtp解析库
 */

#ifndef INCLUDED_LIBDSL_DRTP_H
#define INCLUDED_LIBDSL_DRTP_H

#include "DRefObj.h"

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DRtp :
	public dsl::DRefObj
{
public:
	DRtp(void);
	~DRtp(void);

	int SetBuffer(char* data, int len);
	int GetBufferMaxLen(void) const;
	int GetBufferLen(void) const;

	/* RTP头长度 */
	unsigned long GetHeaderSize() const;

	/* 版本号, 根据RFC3550定义, 版本号为2 */
	int  GetVersion() const;
	void SetVersion(int version);

	bool GetPadding() const;
	void SetPadding(bool pad);

	/* RTP头部扩展, 目前不支持 */
	bool GetExtension() const;
	void SetExtension(bool ext);

	int GetContribSrcCount() const;
	void SetContribSrcCount(int cc);

	/* 标记, 用来标记I帧 */ 
	bool GetMarker() const;
	void SetMarker(bool mark);

	/* 包体数据类型, DVR的流媒体数据类型设为DynamicBase */
	int GetPayloadType() const;
	void SetPayloadType(int t);

	/* 包序号 */
	unsigned short GetSequenceNumber() const;
	void SetSequenceNumber(unsigned short n);

	/* 包时戳 */
	unsigned long GetTimestamp() const;
	void SetTimestamp(unsigned long time);

	/* SSRC, 同步源标识 */
	unsigned long GetSyncSource() const;
	void SetSyncSource(unsigned long ssrc);

	/* CSRC, 可选同步源标识	 */
	unsigned long GetContribSource(int index) const;
	void SetContribSource(int index, unsigned long csrc);

	/* RTP头部扩展, 目前不支持 */
	unsigned short GetExtensionType() const;
	void SetExtensionType(unsigned short type);

	unsigned short GetExtensionSize() const;
	void SetExtensionSize(unsigned short len);

	const char* GetExtensionBuf() const;
	char* GetExtensionPtr();

	unsigned long GetPayloadSize() const;
	void SetPayloadSize(unsigned long len);

	const char* GetPayloadBuf() const;
	char* GetPayloadPtr();

	unsigned char GetPaddingSize() const;
	void SetPaddingSize(unsigned char len);

	const char* GetPaddingBuf() const;
	char* GetPaddingPtr();

private:
	char m_buffer[8192];
	unsigned long m_length;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif
