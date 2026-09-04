//
//  "$Id: Defs.h 208858 2014-07-31 08:22:08Z hao_shiming $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PACKAGE_COMPONENT_INIT_H__
#define __INCLUDED_DAHUA_STREAM_PACKAGE_COMPONENT_INIT_H__

#if (defined(WIN32) || defined(WIN64))
#	ifdef SG_EXPORTS_DLL
#		define STREAMPACKAGE_API __declspec(dllexport)
#	elif defined SG_USE_DLL 
#		define STREAMPACKAGE_API __declspec(dllimport)
#	else
#		define STREAMPACKAGE_API
#	endif
#else 
#	define STREAMPACKAGE_API
#endif

extern "C" STREAMPACKAGE_API void initStreamPackageComponentLibrary();

#endif //__INCLUDED_DAHUA_STREAM_PACKAGE_COMPONENT_INIT_H__ 

