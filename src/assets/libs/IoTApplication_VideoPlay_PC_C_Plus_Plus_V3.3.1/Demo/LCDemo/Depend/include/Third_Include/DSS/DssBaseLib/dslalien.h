/* Copyright (c) 2011, 浙江大华技术股份有限公司
 * All rights reserved.
 *
 * 文件名称：dslalien.h
 * 摘要：外部库
 *
 */

#ifndef INCLUDED_DSLALIEN_H
#define INCLUDED_DSLALIEN_H

#ifdef _WIN32
#if defined(DSLALIEN_STATIC)
#define DSLALIEN_API
#elif defined(DSLALIEN_EXPORTS)
#define DSLALIEN_API __declspec(dllexport)
#else
#define DSLALIEN_API __declspec(dllimport)
#endif
#else
#define DSLALIEN_API
#endif

extern "C" DSLALIEN_API const char * GetLibInfo_dslalien();
extern "C" DSLALIEN_API const char * GetLibInfo_dslalien_1_3_X();

#define BEGIN_NAMESPACE_DSLALIEN namespace dslalien {
#define END_NAMESPACE_DSLALIEN }

BEGIN_NAMESPACE_DSLALIEN
/////////////////////////////////////////////////

class DSLALIEN_API DslAlienLib
{
public:
	static const char * GetLibInfo();
	static const char * GetLibInfo_1_3_X();

	// 目前实现为空，可以不调用
	static int Init();
	static int Uninit();

protected:
	static int m_ref;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSLALIEN

#endif // INCLUDED_DSLALIEN_H
