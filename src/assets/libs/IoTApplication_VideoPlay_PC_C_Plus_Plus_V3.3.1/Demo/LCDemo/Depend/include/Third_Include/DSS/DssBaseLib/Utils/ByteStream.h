#ifndef DH_DSS_COMPONENT_ENVFS_BYTESTREAM_H_INCLUDED
#define DH_DSS_COMPONENT_ENVFS_BYTESTREAM_H_INCLUDED


#include "AX_API/platform.h"

// 注意，当buf的len不够时，会throw exception，外部使用时需进行try/catch

class DOAX_DEPRECATED CByteStream
{
public:
	CByteStream(char* buf, uint32 len);
	~CByteStream();
public:
	CByteStream& operator<<(const int8 i);
	CByteStream& operator<<(const uint8 u);
	CByteStream& operator<<(const int16 i);
	CByteStream& operator<<(const uint16 i);
	CByteStream& operator<<(const int32 i);
	CByteStream& operator<<(const uint32 i);
	CByteStream& operator<<(const int64 i);
	CByteStream& operator<<(const uint64 i);
	CByteStream& operator<<(const float32 i);
	CByteStream& operator<<(const float64 i);
	CByteStream& write(const char* buf, int32 len);

	CByteStream& operator>>(int8& i);
	CByteStream& operator>>(uint8& u);
	CByteStream& operator>>(int16& i);
	CByteStream& operator>>(uint16& i);
	CByteStream& operator>>(int32& i);
	CByteStream& operator>>(uint32& i);
	CByteStream& operator>>(int64& i);
	CByteStream& operator>>(uint64& i);
	CByteStream& operator>>(float32& i);
	CByteStream& operator>>(float64& i);
	CByteStream& read(char* buf, int32 len);

public:
	char* getBuffer();
	uint32 getLength();
	uint32 tell();
	void seek(int32 pos);
	void skip(int32 len);
	void fill(char c,int32 len);
protected:
	uint32	_len;
	char*	_buf;
	char*	_cur;
	char*	_end;
};

#endif//DH_DSS_COMPONENT_ENVFS_BYTESTREAM_H_INCLUDED

