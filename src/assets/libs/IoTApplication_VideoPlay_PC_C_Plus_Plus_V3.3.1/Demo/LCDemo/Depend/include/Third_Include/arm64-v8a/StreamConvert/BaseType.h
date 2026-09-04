//
//  "$Id: BaseType.h 205072 2014-07-17 01:38:36Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_BASE_TYPE_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_BASE_TYPE_H__

#if defined(_USE_STD_INFRA_INTTYPES)
// 使用标准infra类型定义头文件
#include "IntTypes.h"
#elif defined(_USE_CUSTOM_INTTYPES)
// 使用自定义的类型定义
#else
// 默认使用SP自己的类型定义
#include "SPIntTypes.h"
#endif

#ifdef WIN32
#ifdef STREAM_PARSER_DLL_BUILD
#define STREAM_PARSER_API _declspec(dllexport)
#elif defined STREAM_PARSER_DLL_USE
#define STREAM_PARSER_API _declspec(dllimport)
#else
#define STREAM_PARSER_API
#endif
#else
#define STREAM_PARSER_API
#endif
#endif //__INCLUDED_DAHUA_STREAM_PARSER_BASE_TYPE_H__
