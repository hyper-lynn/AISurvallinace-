//
//  "$Id: FileToFile.h 699003 2019-03-01 09:25:39Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE_STREAMCONVERTOR_FILETOFILE_H__
#define __INCLUDE_STREAMCONVERTOR_FILETOFILE_H__

#include "Component/Unknown.h"
#include "Infra/IntTypes.h"
#include "Infra/Function.h"
#include "Infra/String.h"
#include "StreamData.h"
#include "Defs.h"
#include <map>

namespace Dahua{
namespace StreamConvertor{

/// \brief 文件到文件转换类，支持将一种文件格式转换成指定的文件格式
class ST_API IFileToFile : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IFileToFile() {}

public:
	///组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 建IFileToFile类对象
		/// \param [in] streamType 源文件格式，支持手动输入原始码流，要求输入码流类型正确，同时格式全大写或者全小写,不支持大小写混拼：支持：
		/// "UNKNOWN" 未知
		/// "DHPT" 大华老码流--DHPT
		/// "NEW" 大华老码流-NEW
		/// "HB" 大华老码流--HB
		/// "RAW" 大华老码流--raw mpeg4
		/// "CGI" 大华定制码流--CGI
		/// "DAV" 大华标准码流
		/// "PS"
		/// "TS"
		/// "RTP"
		/// "WAV"
		/// "RAW264" 裸264码流
		/// "RAW265" 裸265码流
		/// "RAWMPEG4" 裸MPEG4码流
		/// "RAWMPEG2" 裸MPEG2码流
		/// "RAWSVAC" 裸SVAC码流
		/// "AVI"
		/// "FLV"
		/// "HIKPS" 海康码流
		/// "liyuan" nwjk码流
		/// "ZWSJ" 中维世纪码流
		/// "STAR" 星望码流
		/// \param [in] packetType 目的文件格式，支持：
		///  "FLV","AVI","ASF","MP4","DAV","MOV","MP464", "MOV64","MP4NOSEEK","WAV","TS","PS","GAYSPS"
		/// \return 非NULL IFileToFile 类对象指针
		/// \return NULL 创建失败
		virtual IFileToFile* create(Infra::CString const& streamType, Infra::CString const& packetType) = 0;

		/// 组件接口ID定义
		static const char* iid() { return "FileToFile"; };
	};

	/// 文件封装数据回调函数
	/// 返回值是bool类型
	/// std::map<Infra::CString, int64_t>&  通过"fileoffset"获得数据在文件中的偏移位置,通过"offsettype"获取偏移类型
	/// IStreamConvertorData&  码流数据
	/// 流式码流，如dav,ts,ps时，IStreamConvertorData每次存的都是一帧数据
	typedef Infra::TFunction2<bool, std::map<Infra::CString, int64_t>&, IStreamConvertorData&> Proc;

	/// 错误码回调函数
	/// \param [out] bool 暂时无用，后续可以考虑根据返回值，库决定是否继续执行
	/// \param [in] int32_t 文件转换中的错误码，见StreamData.h
	typedef Infra::TFunction1<bool, int32_t> ExceptionProc;

	/// 文件方式打开 打开转换输出文件
	/// \param [in] filepath 输出文件路径，以'/0'结束
	/// \param [out] dstFileName 输出文件路径，以'/0'结束
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(char const* srcFileName, char const* dstFileName)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 开始文件转换
	/// \retval true 成功
	/// \retval false 失败
	virtual bool startTransform(ExceptionProc proc = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取当前文件的转换进度
	/// \param [out] process 转换进度 有效值0~100，100时为转换完成
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getProcess(uint32_t &process)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 关闭转换文件，一般情况下转换如果完毕，内部会自动关闭文件，如果用户想在分析过程中停止转换，可用此接口
	/// \retval true 成功
	/// \retval false 失败
	virtual bool close(void)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置参数
	///\param [in] type 参数类型，见StreamData.h
	///\param [in] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool setParam(const char* type, int64_t nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 回调方式打开，设置数据回调开始转换
	/// \param [in] srcFileName 输入文件路径，以'/0'结束
	/// \param [in] proc 数据回调
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(char const* srcFileName, Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取备份数据，用于数据断电恢复
	/// \param [in] packet 备份数据
	/// \param [in] frameInfo  通过"seektype"，"seekpos"获得数据在文件中所处的位置
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getbackup(IStreamConvertorDataPtr &packet, std::map<Infra::CString, int64_t> &frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// param [In] type 扩展信息类型，	"encryptkey_aes",支持aes解密
	///									"encryptkey_aes_decrypt"支持aes解密
	///									"encryptkey_aes256_decrypt",支持aes256解密
	/// param [In] pExtInfo
	/// param [In] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	///获取信息
	///\param [in] type 参数类型，见StreamData.h
	///\param [out] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool getParam(const char* type, int64_t& nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

typedef Component::TComPtr<IFileToFile> IFileToFilePtr;

} // end of StreamConvertor
} // end of Dahua

#endif //__INCLUDE_STREAMCONVERTOR_FILETOFILE_H__


