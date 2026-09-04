/* Copyright (c) 2011, 浙江大华技术股份有限公司,  All rights reserved.
 *2017-09
 *
 * 文件名称：DSecureUtil.h
 */

#ifndef	INCLUDED_LIBDSLSSL_DSECUREUTIL_H
#define	INCLUDED_LIBDSLSSL_DSECUREUTIL_H

#include "libdsl/dslbase.h"

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DNetEngine;

namespace pugi {
	struct xml_parse_result;
	class xml_document;
}

namespace Json {
	class Value;
}

class DSecureUtil
{
public:
	// localIP为本地使用的IP地址，格式如"IP.1:127.0.0.1,IP.2:192.168.1.201"
	static void Init(const char* localIP);
	static void UnInit(void);

	// 若ca为NULL，将接受所有证书（不安全）
	// mode: 0-单向认证；1-双向认证
	// 单向认证时，允许cert或key为NULL，这时仅支持作为客户端，调用StartTcpServer接口将返回失败
	// 接口返回的指针需要由调用者自行管理释放
	static DNetEngine* NewNetEngineTLS(const char* ca, const char* cert, const char* key, const char* pwd = NULL, int mode = 0);
	// static DNetEngine* NewNetEngineAES(void);

	// index目前无效，填0即可
	static int GetDefaultPwd(int index, char* pwd, int* len);

	// static int LoadFile(const char* path, char* buffer, int& bufLen);
	// static int SaveFile(const char* path, const char* buffer, int bufLen);

	// static pugi::xml_parse_result LoadXmlFile(const char* path, pugi::xml_document &xml, unsigned int options = 116/*parse_default*/, int encoding = 0/*encoding_auto*/);
	// static int SaveXmlFile(const char* path, const pugi::xml_document &xml, unsigned int flags = 1/*format_default*/, int encoding = 0/*encoding_auto*/);

	// static int LoadJsonFile(const char* path, Json::Value &root);
	// static int SaveJsonFile(const char* path, const Json::Value &root);

public:
	DSecureUtil(void);
	virtual ~DSecureUtil(void);

private:
	static char* s_pLocalIP;
	static char* s_pDefaultPwd;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSLSSL_DSECUREUTIL_H
