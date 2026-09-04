#ifndef INCLUDE_LIBDSLSSL_SHA_H
#define INCLUDE_LIBDSLSSL_SHA_H

#include "libdsl/dslbase.h"

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DSHA
{
	enum {
		DSL_SHA256,
	};
public:
	DSHA(const char* buf, int bufLen, int type = DSL_SHA256);
	~DSHA();

	const char* getBin() { return m_bin; }
	const char* getHex();

private:
	char*	m_bin;
	int		m_binLen;

	char*	m_hex;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif