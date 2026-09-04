//
//  "$Id: StreamParser.h 784551 2019-09-04 09:11:54Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSER_H__
#define __INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSER_H__

#include <map>
#include <deque>
#include "Infra/IntTypes.h"
#include "Infra/String.h"
#include "StreamData.h"
#include "Memory/Packet.h"
#include "Defs.h"

namespace Dahua{
namespace StreamParser{

/// \brief 实时流解析接口类
class STREAMPARSER_API IStreamParser : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IStreamParser() {}

public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建实时流解析实例
		/// \param [in] streamType 码流类型，支持：
		/// "UNKNOWN" 未知
		/// "FLV"  FLV格式					/// "DHTS" 带大华私有信息TS
		/// "AVI" AVI格式					/// "RTP" (未实现)
		/// "WAV"	WAV格式					/// "VOB"	VOB格式
		/// "CGI"		CGI格式
		/// 三方厂商类型
		/// "DHPT" 大华老码流--DHPT			/// "HENGYI"	--恒忆
		/// "NEW" 大华老码流-NEW			/// "HUANGHE"	--黄河
		/// "HB" 大华老码流--HB				/// "LANGCHI" --朗驰
		/// "AUDIO" 大华老码流--语音对讲	/// "TDWY"			--天地伟业
		/// "MPEG2" MPEG2裸码流				/// "DALI"			--大力
		/// "MPEG4" MPEG4裸码流				/// "H3C"				--华三
		/// "H263" H263裸码流				/// "FENGDA"		--丰达
		/// "H264" H264裸码流				/// "ZWSJ"			--中维世纪
		/// "H265" H265裸码流				/// "SANLI"			--金三立
		/// "SVAC" SVAC裸码流				/// "HIKPS"			--海康PS流
		/// "CGI" 大华定制码流--CGI			/// "HIKPRIV"		--海康私有封装
		/// "DHSTD" 大华标准码流			/// "STAR"			--星望
		/// "DHAV" 大华标准码流				/// "LIYUAN"		--立元
		/// "PSSTD" 标准PS					/// "TSSTD" 标准TS
		/// "PS" 标准PS						/// "TS" 标准TS
		/// "DHPS" 带大华私有信息PS			/// "DHTS" 带大华私有信息TS
		/// \retval 非NULL IStreamParser对象实例指针
		/// \retval NULL 失败
		virtual IStreamParser* create(Infra::CString const& streamType = "UNKNOWN") = 0;

		/// 组件接口ID定义
		static const char* iid() { return "StreamParser"; };
	};

	/// 送入解析数据
	/// \param [in] pStream 待解析数据
	/// \param [in] nLength 待解析数据的长度
	/// \retval true 成功
	/// \retval false 失败
	virtual bool put(void const* pStream, uint32_t nLength)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 循环获取一帧数据，直到失败，失败返回非0值。
	/// param [out] frameinfo 帧的相关属性信息，见StreamData.h中 【FrameInfo map 使用说明】
	/// \param [out] frameData 返回的帧数据
	/// \retval true 成功
	/// \retval false 失败
	virtual bool get(std::map<Infra::CString, int64_t> &frameinfo, IStreamParserDataPtr &frameData)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 清空内部保存的数据
	/// \retval true 成功
	/// \retval false 失败
	virtual bool clearBuffer(void)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置参数
	/// param [in] key参数键
	/// param [in] value参数值
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setParam(const char* key, int64_t value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取参数
	/// param [in] key参数键
	/// param [out] value参数值
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getParam(const char* key, int64_t& value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// param [In] type 扩展信息类型，"encryptkey_aes"为aes密钥,"encryptkey_aes256"为aes256密钥
	/// param [In] pExtInfo
	/// param [In] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于获取码流解析支持类型，在put接口成功之后调用
	///  param [out] nParserType，取值parseTypeNoSupport,parseTypeOnlyStream,parseTypeOnlyFile,parseTypeSupportAll,
	/// \retval true 成功
	/// \retval false 失败
	virtual bool GetParseType(int* nParserType)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 以CPacket形式送入解析数据
	/// \param [in] packet 待解析数据
	/// \retval true 成功
	/// \retval false 失败
	virtual bool put(Dahua::Memory::CPacket& packet)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 循环获取一帧数据，直到失败，失败返回非0值。
	/// param [out] cmptInfo 帧的相关属性信息
	/// \param [out] framePacket 返回的裸数据
	/// \retval true 成功
	/// \retval false 失败
	virtual bool get(ParserCmptInfo &cmptInfo, std::deque<Dahua::Memory::CPacket> &framePacket)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

typedef Component::TComPtr<IStreamParser> IStreamParserPtr;

} //	end of StreamParser
} //	end of Dahua

#endif //__INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSER_H__

