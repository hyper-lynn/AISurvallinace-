//
//  "$Id: FilePackage.h 236049 2014-11-28 09:00:41Z shu_wang $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_FILE_PACKAGE_H__
#define __INCLUDED_DAHUA_FILE_PACKAGE_H__


#include "Component/Unknown.h"
#include "Infra/IntTypes.h"
#include "Infra/Function.h"
#include "StreamData.h"
#include "Defs.h"
#include <map>

namespace Dahua{
namespace StreamPackage{

/// \brief 文件封装类，支持将裸码流封装成特定的文件格式
class STREAMPACKAGE_API IFilePackage : public Component::IUnknown
{
protected:
	/// 析构函数
	virtual ~IFilePackage() {};
	
public:
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建文件封装器
		/// \param [in] packetType 封装类型，支持："FLV","AVI","ASF","MP4","3GP","MOV","DAV"
		/// \retval 非NULL 创建IFilePackage类对象指针
		/// \retval NULL 创建失败
		virtual IFilePackage* create(Infra::CString const& packetType = "FLV") = 0;

		/// 组件接口ID定义
		static const char* iid() { return "FilePackage"; };
	};
	
	/// 文件封装数据回调函数
	/// 返回值是bool类型
	/// CStreamInfo&  通过"fileoffset"获得数据在文件中的偏移位置
	/// IStreamData&  码流数据
	typedef Infra::TFunction2<bool, std::map<Infra::CString, int64_t>&, IStreamPackageData&> Proc;

	/// 打开输出文件
	/// \param [in] filepath 目的文件路径，以'/0'结束
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(char const* filepath)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 按帧输入裸数据，以及帧信息
	/// \param [in] pbuffer 一帧裸数据
	/// \param [in] nlen 裸数据长度
	/// \param [in] frameinfo 帧信息，必须包含帧类型，和音视频参数等，视频帧[通用帧属性+视频帧属性],音频帧[通用帧属性+音频帧属性],详见StreamData.h中注释
	/// \retval true 成功
	/// \retval false 失败
	virtual bool inputFrame(void const* pbuffer, uint32_t nlen, std::map<Infra::CString, int64_t> const &frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 文件封装结束后，关闭文件
	/// \retval true 成功
	/// \retval false 失败
	virtual bool close(void)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 打开输出文件
	/// \param [in] proc 文件数据回调
	/// \retval true 成功
	/// \retval false 失败
	virtual bool open(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取备份数据，用于数据断电恢复
	/// \param [in] packet 备份数据
	/// \param [in] frameInfo  通过"seektype"，"seekpos"获得数据在文件中所处的位置	
	/// \retval true 成功
	/// \retval false 失败
	virtual bool getbackup(IStreamPackageDataPtr &packet, std::map<Infra::CString, int64_t> const &frameInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(26)
};

typedef Component::TComPtr<IFilePackage> IFilePackagePtr;

} //	end of StreamPackage
} //	end of Dahua

#endif //__INStreamPackageCLUDED_DAHUA_FILE_PACKAGE_H__

