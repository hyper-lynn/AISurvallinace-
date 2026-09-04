#ifndef __INCLUDE_DAHUA_STREAMAPP_IHLSKEY_H__
#define __INCLUDE_DAHUA_STREAMAPP_IHLSKEY_H__

#include <string>
#include "Component/Unknown.h"
#include "Infra/IntTypes.h"

namespace Dahua{
namespace StreamApp{

/// \brief HLS密钥组件
class IHlsKey : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual IHlsKey* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp::HlsKey";}
	};

protected:

	virtual ~IHlsKey(){}

public:

	///\brief 获得加密状态, 该m3u8 请求的数据是否需要加密
	///\param [in] url - m3u8 请求的url
	///\return true -加密false - 非加密
	virtual bool getEncryptStatus(std::string &url)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得密钥信息
	///\param [in] index - 当前分片索引, 起始从0 开始
	///\param [out] keyurl - 保存密钥的url地址
	///\param [out] key -加密密钥
	///\return true  - 获取成功，false - 获取失败
	virtual bool getKeyInfo(uint32_t index, std::string &keyurl, std::string &key)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(30)
};

typedef Component::TComPtr<IHlsKey> IHlskeyPtr;

} // namespace StreamApp
} //namespace Dahua

#endif//__INCLUDE_DAHUA_STREAMAPP_IHLSKEY_H__
