//
//  "$Id: Defs.h 622202 2018-08-24 03:27:47Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_CONVERTOR_COMPONENT_INIT_H__
#define __INCLUDED_DAHUA_STREAM_CONVERTOR_COMPONENT_INIT_H__

#if (defined(WIN32) || defined(WIN64))
#	ifdef ST_EXPORTS_DLL
#		define ST_API __declspec(dllexport)
#	elif defined ST_USE_DLL
#		define ST_API __declspec(dllimport)
#	else
#		define ST_API 
#	endif
#else 
#	define ST_API
#endif

extern "C" ST_API void initStreamConvertorComponentLibrary();
extern "C" ST_API char* GetStreamConvertorComponentLibraryVersion();

#endif //__INCLUDED_DAHUA_STREAM_CONVERTOR_COMPONENT_INIT_H__ 

