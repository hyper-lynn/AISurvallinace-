#ifndef __SECURITYUNIT_CIPHERMANAGER_H__
#define __SECURITYUNIT_CIPHERMANAGER_H__

#include "Component/Unknown.h"
#include "Memory/Packet.h"
#include "Defs.h"

namespace Dahua{
namespace SecurityUnit{


class ICipherManager : public Component::IUnknown
{
public:
	// 加密算法版本
	enum ECipherVer
	{
		E_CIPHER_LASTEST = SECUNIT_CIPHER_LASTEST,				// 最新版本
		E_CIPHER_V1 = SECUNIT_CIPHER_V1,
	};

	// 密钥因子索引
	enum ECipherIndex
	{
		E_OEM_MANUFACTURER = SECUNIT_OEM_MANUFACTURER,				// 对应厂商及设备型号组成
		E_SERIALNO_DEVTYPE = SECUNIT_SERIALNO_DEVTYPE,				// 对应设备类型及设备序列号
	};

public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取单例接口
		virtual ICipherManager* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "SecurityUnit::CipherManager";}
	};

protected:
	virtual ~ICipherManager(){};

public:
	/// 配置秘钥配置因子(算法版本 采用最新版本)
	/// \param [in] keyFixPart 		加密因子,存放的顺序参见ECipherIndex
	/// \param [in] num 			传入的加密因子数量
	virtual bool config(const char** keyFixPart, int num)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 获取密钥
	/// \param [in] index 		密钥索引，和config传入的密钥因子对应
	/// \param [out] outKey 	对称加密的密钥，目前长度统一为32字节
	/// \param [in] version 	加密算法版本,默认采用最新版本
	virtual bool getEncryptKey(ECipherIndex index, Memory::CPacket& outKey,
			ECipherVer version=E_CIPHER_LASTEST)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 获取当前密钥算法版本
	/// \param [out] version 		当前加密算法版本
	virtual bool getEncryptVersion(ECipherVer& version)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 对密码进行评分
	/// \param [in] password 	待评分的密码
	/// \param [out] score 		密码的最终得分(0-100),含有不可显示字符或非法的字符返回false，得分为0
	virtual bool scorePassword(const char* password, uint8_t& score)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 对相应的文件进行解密，解压缩输出,使用之前需要调用config进行设置，密钥因子，使用的是第二个密钥因子进行解密
	/// \param [in] path			文件路径，文件为加密
	/// \param [out] outdata 		文件进行解密，解压缩输出内容(内部会申请缓存)
	virtual bool readFile(const char* path,  Memory::CPacket& outdata)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 对相应的文件进行压缩,加密,然后加密写入文件,使用之前需要调用config进行设置,密钥因子,使用的是第二个密钥因子进行加密
	/// \param [in] path
	/// \param [in] data 		待写入文件的明文数据
	/// \param [in] dataLen 	待写入文件的明文数据，长度
	virtual bool writeFile(const char* path, const void* data, size_t dataLen)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 指定索引信息对相应的文件进行解密，解压缩输出,由于算法版本文件头部有，故不需知道算法版本
	/// \param [in] path			文件路径，文件为加密
	/// \param [in] index 			密钥索引，和config传入的密钥因子对应
	/// \param [out] version 		当前加密算法版本
	/// \param [out] outdata 		文件进行解密，解压缩输出内容(内部会申请缓存)
	virtual bool readFile(const char* path, int index, ECipherVer& version, Memory::CPacket& outdata)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 指定索引及算法版本信息对相应的文件进行压缩,加密,然后加密写入文件
	/// \param [in] path		文件路径，文件为待加密的
	/// \param [in] index 		密钥索引，和config传入的密钥因子对应
	/// \param [in] version 	加密算法版本，推荐使用getEncryptVersion接口获取
	/// \param [in] data 		待写入文件的明文数据
	/// \param [in] dataLen 	待写入文件的明文数据，长度
	virtual bool writeFile(const char* path, int index, ECipherVer version, const void* data, size_t dataLen)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 保留到32个虚函数
	DAHUA_COMPONENT_FUNCTION_REVSERVED(24)
};

typedef Component::TComPtr<ICipherManager> ICipherManagerPtr;

} // namespace SecurityUnit
} // namespace Dahua

extern "C" void initSecurityUnitCipherManagerComponentLibrary();
#endif //__SECURITYUNIT_CIPHERMANAGER_H__
