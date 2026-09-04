//
//  "$Id: TinyXmlDefs.h 53323 2012-03-09 05:36:32Z wang_haifeng $"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA_TINYXML_TINYXMLDEFS_H__
#define __DAHUA_TINYXML_TINYXMLDEFS_H__

// 定义跨平台接口类型
#ifdef WIN32 

#ifdef TINYXML_DLL_BUILD
#define  TINYXML_API _declspec(dllexport)
#elif defined TINYXML_DLL_USE
#define  TINYXML_API _declspec(dllimport)
#else
#define TINYXML_API
#endif

#else // WIN32

#define TINYXML_API

#endif // WIN32


#endif //__DAHUA_TINYXML_TINYXMLDEFS_H__

