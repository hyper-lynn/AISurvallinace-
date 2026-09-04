//
//  "$Id: StreamData.h 338088 2016-04-12 06:06:53Z 20429 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE__STREAMCONVERTOR_STREAMDATA_H__
#define __INCLUDE__STREAMCONVERTOR_STREAMDATA_H__

#include "Infra/IntTypes.h"
#include "Defs.h"
#include "Memory/SharedPtr.h"

namespace Dahua{
namespace StreamConvertor{

enum FuncResult
{
	errorNoError = 0,				// 成功
	errorInvalidHandle,				// 无效句柄
	errorNoSupport,					// 解析或封装类型不支持
	errorThread,					// 内部线程出错
	errorParam,						// 参数有误

	errorFileOpen,					// 文件打开出错，可能已被互斥打开
	errorFileRead,					// 文件读取出错
	errorFileWrite,					// 文件写入出错
	errorFormat,					// 码流格式有误，无法继续解析

	errorBufferOverFlow,			// 内部缓冲溢出
	errorSysOutOfMem,				// 系统内存不足

	errorNoIDRFrame,				// 缺少I帧
	errorNoOutPut,					// 同步封装或解析逻辑中无数据输出
	errorOrder,						// 调用顺序有误

	errorEncryptKey,				// 回放时输入秘钥错误
};

enum ConvertMode
{
	modeSingleFile = 0,         /// 只转成一个文件
	modeMultipleFile = 1,     /// 支持转换成多个文件
};

// SetParam类型
// "convertmode" 设置转换模式，具体值见ConvertMode；

// GetParam 类型
// "filecount" 获取转换后的文件个数

/// \brief 数据类，通过该类提供数据指针和数据长度，可以避免数据指针被用户释放。数据处理对外透明，可以减少解析过程中的内存拷贝。
class ST_API IStreamConvertorData
{
protected:
	virtual ~IStreamConvertorData() {}
public:
	virtual const char* getBuffer() = 0;
	virtual unsigned int getLen() = 0;
};

typedef Memory::TSharedPtr<IStreamConvertorData> IStreamConvertorDataPtr;

} // end of StreamParser
} // end of Dahua

#endif //__INCLUDE__STREAMPARSER_STREAMINFO_H__

