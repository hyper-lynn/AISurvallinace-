#ifndef __INCLUDE_DAHUA_STREAMSVR_SRTPSTREAM_H__
#define __INCLUDE_DAHUA_STREAMSVR_SRTPSTREAM_H__

#include "StreamSvr/Defs.h"
#include "RtspUtil.h"
#include "Component/Unknown.h"

namespace Dahua{
namespace StreamSvr{

class STREAMSVR_API ISrtpStream : public Component::IUnknown
{
public:

	/// 组件工厂实现
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 ISrtpStream 对象实例	
		virtual ISrtpStream* create() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "ISrtpStream";};
	};

public:
	ISrtpStream(){}

	virtual ~ISrtpStream(){}

	///\brief 设置加解密配置，并初始化密钥
	///\param[in]  SrtpEncryptConfig 加密 配置
	///\return 0-success -1-fail
	virtual int set_crypto(const StreamSvr::SrtpEncryptConfig & srtpEnc){return -1;}

	///\brief 数据加密
	///\param[in]   in    加密原始数据指针
	///\param[in]   inlen  加密原始数据的长度
	///\param[out] out  加密后的数据指针
	///\param[out] outlen 加密后的数据指针长度
	///\return 0-success -1-fail
	virtual int srtp_encrypt(const uint8_t * in, uint32_t inlen, uint8_t *out, uint32_t & outlen){return -1;}

	///\brief 数据解密
	///\param[in out]   buf    加密的数据指针，解密后的数据指针也是buf
	///\param[in out]   len   加密的数据长度，解密后的数据长度也是len
	///\return 0-success -1-fail
	virtual int srtp_decrypt(uint8_t * buf, uint32_t & len){return -1;}


	DAHUA_COMPONENT_FUNCTION_REVSERVED(15)
	
};

typedef Component::TComPtr<ISrtpStream> ISrtpStreamPtr;

}
}
#endif
