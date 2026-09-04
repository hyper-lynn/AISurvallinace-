//
//  "$Id: StreamToStream.h 699003 2019-03-01 09:25:39Z 13015 $"
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
		/// \param [in] streamType 源文件格式，支持手动输入原始码流，要求输入码流类型正确，同时格式全大写或者全小写,不支持大小写混拼：
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
	/// \param [in] type 扩展信息类型，"encryptkey_aes",支持aes解密
	///									"encryptkey_aes_decrypt"支持aes解密
	///									"encryptkey_aes256_decrypt",支持aes256解密
	/// \param [in] pExtInfo
	/// \param [in] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 添加一帧数据
	/// \param [in] pData 帧数据
	/// \param [in] nLen 帧数据长度
	///\retval true 成功
	///\retval false 失败
	/// 注意：该接口必须与getOneFrame配套使用
	virtual bool putOneFrame(void const* pData, uint32_t nLen)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取一帧数据
	/// \param [out] data 获取的帧数据
	/// \param [out] frameinfo 获取的帧信息,具体说明在StreamDada.h中
	///\retval true 成功
	///\retval false 失败
	/// 注意：该接口必须与putOneFrame配套使用
	virtual bool getOneFrame(IStreamConvertorDataPtr& data, std::map<Infra::CString, int64_t> &frameinfo)
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
	
	/// 帧数据及帧信息回调，目前仅支持：ps,dav,ts,扩展ps，以及SC_RAW
	/// frameinfo:获取的帧信息,具体说明在StreamDada.h中
	/// pData：  一帧数据，从该回调中取得
	/// iLen:    帧数据长度
	/// lUser：  用户数据
	typedef void (*FrameDataCallback)(std::map<Dahua::Infra::CString, int64_t> frameinfo, unsigned char* pData, int iLen, void* lUser);

	///设置回调函数
	///\param [in] fSCFrameDataCallback 回调函数
	///\retval true 成功
	///\retval false失败
	virtual bool SetDataCallBack(FrameDataCallback fSCFrameDataCallback)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

typedef Component::TComPtr<IStreamToStream> IStreamToStreamPtr;

} // end of StreamConvertor
} // end of Dahua

#endif //__INCLUDE_STREAMCONVERTOR_STREAMTOSTREAM_H__

