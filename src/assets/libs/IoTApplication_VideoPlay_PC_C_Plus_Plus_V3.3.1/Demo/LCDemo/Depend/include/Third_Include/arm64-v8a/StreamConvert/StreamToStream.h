//
//  "$Id: StreamToStream.h 289900 2015-08-21 07:53:49Z fang_xiaojie $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE_STREAMCONVERTOR_STREAMTOSTREAM_H__
#define __INCLUDE_STREAMCONVERTOR_STREAMTOSTREAM_H__

#include "Component/Unknown.h"
#include "Memory/Packet.h"
#include "Infra/IntTypes.h"
#include "Infra/String.h"
#include "StreamData.h"
#include "Defs.h"
#include <map>

namespace Dahua{
namespace StreamConvertor{

/// \brief 实时流到实时流转换类，支持将实时流转换成指定格式的实时流
class ST_API IStreamToStream : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IStreamToStream() {}

public:
	///组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 建IStreamToStream类对象
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
		///	"FLV","AVI","ASF","DAV","TS","PS","GDPS"(广东电网PS),"GAYSPS"(公安一所PS),
		/// \return 非NULL IStreamToStream 类对象指针
		/// \return NULL 创建失败
		virtual IStreamToStream* create(Infra::CString const& streamType, Infra::CString const& packetType) = 0;
		
		/// 组件接口ID定义
		static const char* iid() { return "StreamToStream"; };
	};
	
	/// 送入实时流数据
	/// \param [in] pData 实时流数据指针
	/// \param [in] nLen  实时流数据长度
	/// \retval true 成功
	/// \retval false 失败
	virtual bool put(void const* pData, uint32_t nLen)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取实时流数据
	/// \param [out] data 实时流数据，包含数据指针和数据长度
	/// \retval true 成功
	/// \retval false 失败
	virtual bool get(StreamConvertor::IStreamConvertorDataPtr& data)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置参数
	///\param [in] type 参数类型
	///\param [in] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool setParam(const char* type, int64_t nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// \param [in] type 扩展信息类型，“encryptkey_aes”为aes密钥
	/// \param [in] pExtInfo
	/// \param [in] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 添加一帧数据
	/// \param [in] 帧数据
	/// \param [in] 帧数据长度
	virtual bool putOneFrame(void const* pData, uint32_t nLen)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取一帧数据
	/// \param [out] 获取的帧数据
	virtual bool getOneFrame(Dahua::Memory::CPacket& packet)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///获取信息
	///\param [in] type 参数类型
	///\param [out] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool getParam(const char* type, int64_t& nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///获取设置扩展信息
	///\param [in] type 扩展信息类型
	///\param [in] pExtInfo
	///\param [out] nLength
	///\retval true 成功
	///\retval false失败
	virtual bool getExtInfo(const char* type, void* pExtInfo, uint32_t& nLength)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(23)
};

typedef Component::TComPtr<IStreamToStream> IStreamToStreamPtr;

} // end of StreamConvertor
} // end of Dahua

#endif //__INCLUDE_STREAMCONVERTOR_STREAMTOSTREAM_H__

