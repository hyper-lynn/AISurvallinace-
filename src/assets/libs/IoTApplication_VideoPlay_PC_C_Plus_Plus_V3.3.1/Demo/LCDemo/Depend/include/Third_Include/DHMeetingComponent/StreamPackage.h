//
//  "$Id: StreamPackage.h 238503 2014-12-09 08:40:39Z shu_wang $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_STREAM_PACKAGE_H__
#define __INCLUDED_DAHUA_STREAM_PACKAGE_H__


#include "Component/Unknown.h"
#include "Infra/IntTypes.h"
#include "Memory/Packet.h"
#include "StreamData.h"
#include "Defs.h"
#include <map>

namespace Dahua{
namespace StreamPackage{

/// \brief 实时流封装类，支持将裸码流封装成特定的实时流
class STREAMPACKAGE_API IStreamPackage : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IStreamPackage() {}
	
public:
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建实时流封装器
		/// \param [in] packetType 封装类型，支持："FLV","ASF","DAV"
		/// \retval 非NULL 创建IStreamPackage类对象指针
		/// \retval NULL 创建失败
		virtual IStreamPackage* create(Infra::CString const& packetType = "Dav") = 0;
		
		/// 组件接口ID定义
		static const char* iid() { return "StreamPackage"; };
	};

	/// 按帧输入裸数据，以及帧信息
	/// \param [in] pbuffer 一帧裸数据
	/// \param [in] nlen 裸数据长度
	/// \param [in] frameinfo 帧信息，必须包含帧类型，和音视频参数等，视频帧[通用帧属性+视频帧属性],音频帧[通用帧属性+音频帧属性],详见StreamData.h中注释
	/// \retval true 成功
	/// \retval false 失败
	virtual bool inputFrame(void const* pBuffer, uint32_t nLen, std::map<Infra::CString, int64_t> const &frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取数据包
	/// \param [out] packet 数据包数据，包含数据指针和数据长度
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getPacket(IStreamPackageDataPtr &packet)
		COMPONENT_UNIMPLEMENTED_OPERATION

	// 按帧输入裸数据，以及帧信息
	/// \param [in] pbuffer 一帧裸数据
	/// \param [in] nLength 裸数据长度
	/// \param [in] frameinfo 帧信息，必须包含帧类型，和音视频参数等，视频帧[通用帧属性+视频帧属性],音频帧[通用帧属性+音频帧属性],详见StreamData.h中注释
	///\param [in] extPacket 外部提供的内存区域
	/// \retval true 成功
	/// \retval false 失败
	virtual bool inputFrameEx(void const* pBuffer, uint32_t nLength, std::map<Infra::CString, int64_t> const& frameInfo, Memory::CPacket& extPacket)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置参数
	///\param [in] type 参数类型
	///\param [in] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool setParam(const char* type, int64_t nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///获取信息
	///\param [in] type 参数类型
	///\param [out] nValue 值
	///\retval true 成功
	///\retval false 失败
	virtual bool getParam(const char* type, int64_t& nValue)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// param [In] type 扩展信息类型，"encryptkey"为密钥
	/// param [In] pExtInfo
	/// param [In] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于获取扩展信息
	/// param [In] type 扩展信息类型，"encryptkey"为密钥
	/// param [Out] packet 
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getExtInfo(const char* type, IStreamPackageDataPtr &packet)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(24)
};

typedef Component::TComPtr<IStreamPackage> IStreamPackagePtr;

} //	end of StreamPackage
} //	end of Dahua

#endif //__INCLUDED_DAHUA_STREAM_PACKAGE_H__

