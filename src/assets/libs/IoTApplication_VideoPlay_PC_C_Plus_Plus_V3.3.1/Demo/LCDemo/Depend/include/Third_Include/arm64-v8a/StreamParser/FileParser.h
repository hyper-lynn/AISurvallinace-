//
//  "$Id: FileParser.h 361945 2016-07-18 01:34:08Z 20429 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE_STREAMPARSER_FILEPARSER_H__
#define __INCLUDE_STREAMPARSER_FILEPARSER_H__

#include <map>
#include "Component/Unknown.h"
#include "Infra/IntTypes.h"
#include "Infra/Function.h"
#include "StreamData.h"
#include "Defs.h"

namespace Dahua{
namespace StreamParser{

/// \brief 纯文件方式解析接口
class STREAMPARSER_API IFileParser : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IFileParser() {}

public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建文件解析实例
		/// \param [in] streamType 码流类型，支持：
		/// "UNKNOWN" 未知
		/// "FLV"  FLV格式						/// "WMV" WMV格式
		/// "ASF" ASF格式						/// "WAV"	WAV格式
		/// "AVI"	AVI格式						/// "MKV" MKV格式
		/// "MP4" MP4格式						/// "CGI"	大华定制码流CGI格式
		/// "3GP" 3GP格式
		/// "MOV" MOV格式
		/// 三方厂商类型
		/// "DHPT" 大华老码流--DHPT				/// "HENGYI"	恒忆
		/// "NEW" 大华老码流--NEW				/// "HUANGHE"	黄河
		/// "HB" 大华老码流--HB					/// "LANGCHI" 朗驰
		/// "AUDIO" 大华老码流--语音对讲		/// "TDWY"		天地伟业
		/// "MPEG2" MPEG2裸码流					/// "DALI"			大力
		/// "MPEG4" MPEG4裸码流					/// "FENGDA"		丰达
		/// "H263" H263裸码流					/// "ZWSJ"			中维世纪
		/// "H264" H264裸码流					/// "SANLI"			金三立
		/// "H265" H265裸码流					/// "HIKPRIV"		海康私有封装
		/// "SVAC" SVAC裸码流					/// "STAR"			星望
		/// "DHSTD" 大华标准码流
		/// "DHAV" 大华标准码流
		/// \retval 非NULL IFileParser对象实例指针
		/// \retval NULL 失败
		virtual IFileParser *create(Infra::CString const& streamType = "UNKNOWN") = 0;

		/// 组件接口ID定义
		static const char* iid() { return "FileParser"; };
	};

public:

	/// 文件解析回调函数
	/// 返回值是bool类型
	/// 第一个参数是码流信息，见StreamData.h中 【FrameInfo map 使用说明】，
	///					其中"fileindex"值非常重要，可以通过该值获取帧数据.
	/// 第二个参数是码流数据
	typedef Infra::TFunction2<bool, std::map<Infra::CString, int64_t>&, IStreamParserData&> Proc;

	/// 打开待解析的文件
	/// \param [in] fileName待解析的文件名，以'/0'结束
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(char const* fileName)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 关闭解析文件，一般情况下分析如果完毕，内部会自动关闭文件。如果用户想在分析过程中停止解析，可用此接口
	/// \retval true 成功
	/// \retval false 失败
	virtual bool close(void)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 开始解析文件，在open成功之后调用
	/// \param [in] proc:设置每帧索引的回调
	/// \retval true 成功
	/// \retval false 失败
	virtual bool startParse(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

    /// 获得文件解析的进度
	/// \param [out] process 进度值，用0到100表示，100表示分析结束
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getProcess(uint32_t &process)
		COMPONENT_UNIMPLEMENTED_OPERATION

    /// 通过帧信息获取帧数据，该接口统一了两种情况的帧数据的正确获取
	/// 	1. 帧数据在文件中完整存放，利用偏移值可自行读取到正确的数据
	/// 	2. 帧数据在文件中分包存放，利用偏移值只能读取到第一个分包的数据
	/// 	用户根据帧数据回调中的indexInfo，主动去获取某个偏移值上的完整帧信息,
	/// \param [in] indexInfo 必须含有"fileindex"，从IIndexListener::onIndex回调中获得
	/// \param [out] frameData indexInfo结构对应的帧数据
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getFrameDataByIndexInfo(std::map<Infra::CString, int64_t> &indexinfo, IStreamParserDataPtr &frameData)
		COMPONENT_UNIMPLEMENTED_OPERATION

    /// 获取文件统计信息，可获取的统计信息见StreamComm对CSTInfo的说明
	/// \param [out] fileInfo，见StreamData.h中 【FrameInfo map 使用说明】->【文件统计信息】
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getFileInfo(std::map<Infra::CString, int64_t> &fileinfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 用于设置扩展信息
	/// param [In] type 扩展信息类型，"encryptkey_aes"为密钥
	/// param [In] pExtInfo
	/// param [In] nLength
	/// \retval true 成功
	/// \retval false 失败
	virtual bool setExtInfo(const char* type, void const* pExtInfo, uint32_t nLength )
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(24)
};

typedef Component::TComPtr<IFileParser> IFileParserPtr;

} // end of StreamParser
} // end of Dahua

#endif //__INCLUDE_STREAMPARSER_FILEPARSER_H__

