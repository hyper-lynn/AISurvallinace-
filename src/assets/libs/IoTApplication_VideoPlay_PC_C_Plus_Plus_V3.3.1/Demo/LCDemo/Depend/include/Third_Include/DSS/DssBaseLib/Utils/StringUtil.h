// #pragma once

#ifndef STRINGUTIL_H_INCLUDE
#define STRINGUTIL_H_INCLUDE

#include <string>
#include <time.h>

#ifndef DOAX_DEPRECATED
#ifdef _WIN32
// 放在class关键字后面，以及函数或者变量定义的前面
#define DOAX_DEPRECATED	__declspec(deprecated)
#else
#define DOAX_DEPRECATED	__attribute__ ((deprecated))
#endif // #ifdef WIN32
#endif // #ifndef DOAX_DEPRECATED

class DOAX_DEPRECATED CStringUtil
{
public:
	static std::string get_value_from_string(const char* str,const char* strBefore,const char* strAfter,bool trim);
	static std::string get_gmt_rtsp_time(time_t t);
};

#endif // STRINGUTIL_H_INCLUDE
