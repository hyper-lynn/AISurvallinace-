//
//  "$Id: Defs.h 252415 2015-02-06 01:36:44Z shu_wang $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PARSER_COMPONENT_INIT_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_COMPONENT_INIT_H__


#if (defined(_WIN32) || defined(_WIN64))
#ifdef SP_EXPORTS_DLL
	#define STREAMPARSER_API __declspec(dllexport)
#elif defined(SP_USE_DLL)
	#define STREAMPARSER_API __declspec(dllimport)
#else
	#define STREAMPARSER_API 
#endif
	#define CALLMETHOD __stdcall
	#define CALLBACK   __stdcall
#else 
	#define STREAMPARSER_API
	#define CALLMETHOD
	#define CALLBACK
#endif

#define IN
#define OUT

extern "C" STREAMPARSER_API void initStreamParserComponentLibrary();

#endif //__INCLUDED_DAHUA_STREAM_PARSER_COMPONENT_INIT_H__ 

