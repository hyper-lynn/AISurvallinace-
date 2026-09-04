#ifndef __INCLUDE_DAHUA_STREAMSVR_ENCRYPT_H__
#define __INCLUDE_DAHUA_STREAMSVR_ENCRYPT_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Protocol/RtspUtil.h"

namespace Dahua {
namespace StreamSvr {

///\brief 大华帧AES加解密功能类
class STREAMSVR_API CAESEncrypt
{
public:
    ///\brief 工作方式
	enum workMode
	{
		workModeIFrameOnly, ///> 仅I帧加密
		workModeAll,        ///> 全部加密
	};

	///\brief 0xB5码流加密使用的算法
	enum B5EncryptAlg
	{
		Encrypt3AlgUnknown = -1,		///< 未知加密方式
		Encrypt3AlgReserve = 0,			///< 保留
		Encrypt3AlgAES256_OFB_NP = 1,   ///< SES256-OFB-NOPADDING 加密方式
	};

	enum {VKIDLength = 16};		///< 生成的 VKID 数据长度
	enum {IVLength = 16};		///< 生成的 IV 数据长度
	enum {VKLengthMax = 256};	///< 最大支持秘钥数据长度

	///\biref 大华帧头0xB5字段协议参数配置
	struct B5EncryptConfig
	{
		B5EncryptAlg	enctype;				///< 参考 @see @B5EncryptAlg,加密类型
		uint32_t		offset;					///< 加密字段的起始偏移，从裸数据的起始开始算起
		uint32_t		encLen;					///< 加密数据的长度
		uint8_t 		vkid[VKIDLength];		///< 视频加密秘钥VK的ID号, 暂不使用, 填0
		uint16_t 		crc16;					///< 加密前数据CRC16校验和, 计算方法为CRC16(SHA256(加密类型:VKID:VK))
		uint8_t 		iv[IVLength];			///< 加密算法初始向量
		char			encKey[VKLengthMax];	///< 加密密钥,密钥最长支持256字节
		int 			keyLen;					///< 密钥长度
	    int             reserve[16];    		///< 保留字段

		B5EncryptConfig()
		{
			enctype = Encrypt3AlgUnknown;
			offset = 0;
			encLen = 0;
			memset(vkid, 0, sizeof(vkid));
			crc16 = 0;
			memset(iv, 0, sizeof(iv));
			memset(encKey, 0, sizeof(encKey));
			keyLen = 0;
	        memset(reserve, 0, sizeof(reserve));
		}
	};
		
public:
	///\brief 大华流AES解密
	///\param[in]  inFrmae 输入加密的大华帧，帧头信息为非加密的
	///\param[out] outFrame 解密后的大华帧
	///\param[in]  key 解密秘钥
	///\param[in]  mode 工作模式 @see workMode
	///\return 0-success -1-fail
	static int aesDecodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const uint8_t * key, workMode mode);

	///\brief 大华流AES加密
	///\param[in]  inFrmae 输入待加密的大华帧
	///\param[out] outFrame 输出加密后的大华帧，帧头信息为非加密
	///\param[in]  key 加密秘钥
	///\param[in]  mode 工作模式 @see workMode
	///\return 0-success -1-fail
	static int aesEncodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const uint8_t * key, workMode mode);

	///\brief 大华流0x95字段AES加密
	///\param[in]  inFrmae 输入待加密的大华帧
	///\param[out] outFrame 输出加密后的大华帧，大华拓展头携带0x95字段
	///\param[in]  config 和慧眼加密配置
	///\return 0-success -1-fail
	static int aesEncodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const struct HHYEncryptConfigExt& config);

	///\brief 大华流0x95字段AES解密
	///\param[in]  inFrmae 输入待解密的大华帧
	///\param[out] outFrame 输出解密后的大华帧，大华拓展头去掉0x95字段
	///\param[in]  config 和慧眼加密配置
	///\return 0-success -1-fail
	static int aesDecodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const struct HHYEncryptConfigExt& config);

	///\brief 生成大华流0xB5字段CRC16值, 计算方法为CRC16(SHA256(加密类型:VKID:VK))
	///\param[in]  encryptType 加密类型
	///\param[in]  vkid 视频加密秘钥VK的ID号
	///\param[in]  vkidLen 视频加密秘钥VK的ID号长度
	///\param[in]  encKey 加密密钥
	///\param[in]  keyLen 加密密钥长度
	///\return crc16计算值
	static uint16_t generateCRC16(uint8_t encryptType, uint8_t *vkid, size_t vkidLen, char *encKey, size_t keyLen);
	
	///\brief 大华加密流加密秘钥校验
	///\param[in]  inFrmae 输入待解密的大华帧
	///\param[in]  encKey 加密密钥
	///\param[in]  keyLen 加密密钥长度
	///\param[in]  encCheckFlag 大华流加密校验扩展帧头标志, 暂只支持0xB5加密秘钥校验, 详细见《大华标准码流格式定义》
	///\return  -1 密钥校验不匹配, 0 密钥校验匹配, 1 未进行密钥校验
	static int checkKey(const CMediaFrame &inFrame, char *encKey, size_t keyLen, int encCheckFlag);
	
	///\brief 大华流0xB5字段AES加密
	///\param[in]  inFrmae 输入待加密的大华帧
	///\param[out] outFrame 输出加密后的大华帧，大华拓展头携带0xB5字段
	///\param[in]  config 0xB5字段协议参数配置
	///\return 0-success -1-fail
	static int aesEncodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const struct B5EncryptConfig& config);

	///\brief 大华流0xB5字段AES解密
	///\param[in]  inFrmae 输入待解密的大华帧
	///\param[out] outFrame 输出解密后的大华帧，大华拓展头去掉0xB5字段
	///\param[in]  config 0xB5字段协议参数配置
	///\return 0-success -1-fail
	static int aesDecodeDHFrame(const CMediaFrame& inFrame, CMediaFrame& outFrame, const struct B5EncryptConfig& config);
};

}//StreamSvr
}//Dahua

#endif //__DAHUA_STREAM_SVR_ENCRYPT_H__