//
//  "$Id: StreamToFile.h 385431 2016-10-14 01:03:57Z 20429 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE_STREAMCONVERTOR_STREAMTOFILE_H__
#define __INCLUDE_STREAMCONVERTOR_STREAMTOFILE_H__

#include "Component/Unknown.h"
#include "Infra/IntTypes.h"
#include "Infra/Function.h"
#include "Infra/String.h"
#include "StreamData.h"
#include "Defs.h"
#include <map>

namespace Dahua{
namespace StreamConvertor{

/// \brief 实时流到文件转换类，支持将实时流转换成指定格式的文件
class ST_API IStreamToFile : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IStreamToFile() {}

public:
	///组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 建IStreamToFile类对象
		/// \param [in] streamType 源文件格式，支持：
		/// "UNKNOWN" 未知
		/// "DHPT" 大华老码流--DHPT
		/// "NEW" 大华老码流-NEW
		/// "HB" 大华老码流--HB
		/// "RAW" 大华老码流--raw mpeg4
		/// "CGI" 大华定制码流--CGI
		/// "DHSTD" 大华标准码流
		/// "PS"
		/// "TS"
		/// "RTP"
		/// "WAV"
		/// "AVI"
		/// "ASF"
		/// "3GP"
		/// "MOV"
		/// "MP4"
		/// \param [in] packetType 目的文件格式，支持：
		///  "FLV","AVI","ASF","MP4","DAV","MOV","MP464", "MOV64","MP4NOSEEK","WAV"
		/// \return 非NULL IStreamToFile 类对象指针
		/// \return NULL 创建失败
		virtual IStreamToFile* create(Infra::CString const& streamType, Infra::CString const& packetType) = 0;

		/// 组件接口ID定义
		static const char* iid() { return "StreamToFile"; };
	};

	/// 文件转换数据回调函数
	/// 返回值是bool类型
	/// std::map<Infra::CString, int64_t>&  通过"fileoffset"获得数据在文件中的偏移位置
	/// IStreamConvertorData&  码流数据
	typedef Infra::TFunction2<bool, std::map<Infra::CString, int64_t>&, StreamConvertor::IStreamConvertorData&> Proc;

	/// 错误码回调函数
	/// \param [out] bool 暂时无用，后续可以考虑根据返回值，库决定是否继续执行
	/// \param [in] int32_t 文件转换中的错误码，见StreamData.h
	typedef Infra::TFunction1<bool, int32_t> ExceptionProc;

	/// 文件方式 打开转换输出文件
	/// \param [in] filepath 输出文件路径，以'\0'结束
	/// \param [out] dstFileName 输出文件路径，以'\0'结束
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(char const* filepath)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 送入实时流数据
	/// \param [in] pData 实时流数据指针
	/// \param [in] nLen  实时流数据长度
	/// \retval true 成功
	/// \retval false 失败
	virtual bool put(void const* pData, uint32_t nLen)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 关闭转换文件
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

	/// 回调方式打开 设置数据回调 开始转换
	/// \param [in] proc 数据回调
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取备份数据，用于数据断电恢复
	/// \param [in] packet 备份数据
	/// \param [in] frameInfo  通过"seektype"，"seekpos"获得数据在文件中所处的位置
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getbackup(IStreamConvertorDataPtr &packet, std::map<Infra::CString, int64_t> &frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// param [In] type 扩展信息类型，“encryptkey_aes”为aes密钥
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

	/// 设置异常回调，在open之后，put之前调用
	/// \param [in] proc 异常回调
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExceptionProc(ExceptionProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION


	DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

typedef Component::TComPtr<IStreamToFile> IStreamToFilePtr;

} // end of StreamConvertor
} // end of Dahua

#endif //__INCLUDE_STREAMCONVERTOR_STREAMTOFILE_H__

