#ifndef __INCLUDE_DAHUA_STREAMSVR_SDPHELPER_H__
#define __INCLUDE_DAHUA_STREAMSVR_SDPHELPER_H__

#include "StreamSvr/Protocol/H264.h"
#include "StreamSvr/Protocol/H265.h"
#include "StreamSvr/Protocol/Mpeg4.h"
#include "StreamSvr/Protocol/Vorbis.h"
#include "SdpParser.h"

namespace Dahua{
namespace StreamSvr{

class STREAMSVR_API CSdpHelper
{
public:
	///\brief 构造函数，不负责释放该sdpParser对象,因此SdpHelper的生命期应该只和sdpParser一致
	///\param[in] sdpParser-sdp解析器,该指针需要保证在CSdpHelper生命期间始终有效。
	CSdpHelper(CSdpParser *sdpParser);

	///\brief 获取该sdp中有多少个media track
	///\return 返回该sdp中含有的media track数目
	int getMediaTotal();

	///\brief 获取对应媒体索引的采样率
	///\param [in] mediaIndex-媒体索引
	///\return 媒体索引的采样率-成功，-1-失败
	int getSample( int mediaIndex);

	///\brief 获取对应媒体索引的采样率
	///\param [in] mediaIndex-媒体索引
	///\param [in/out] mainType-媒体类型，参见SdpParser中MediaType定义
	///\param [in/out] pDhType-大华帧头中的编码子类型，参见<<大华码流信息格式>>
	///\return 媒体索引的采样率-成功，-1-失败
	int getEncSubType(int mediaIndex, int &mainType, uint8_t *pDhType=NULL);

	///\brief 解析h264 sdp消息，获取sps，pps信息
	///\param [in]buf-用于存放sps，pps信息
	///\param [in]len-该缓冲的大小
	///\param [in]spsInfo-sps，pps信息地址以及长度信息
	///\return 0-失败，>0 成功
	int parseH264Sdp(uint8_t *buf, int size, H264KeyInfo &spsInfo);

	///\brief 解析h265 sdp消息，获取sps，pps信息
	///\param [in]buf-用于存放sps，pps信息
	///\param [in]size-该缓冲的大小
	///\param [in]keyinfo-sps，pps信息地址以及长度信息
	///\return 0-失败，>0 成功
	int parseH265Sdp(uint8_t *buf, int size, H265KeyInfo &keyinfo);

	///\brief 解析mpeg4 sdp消息，获取vos信息
	///\param [in]buf-用于存放sps，pps信息
	///\param [in]len-该缓冲的大小
	///\param [in]vosInfo-vos信息地址以及长度信息
	///\return 0-失败，>0 成功
	int parseMpeg4Sdp(uint8_t *buf, int size, TMpeg4VosInfo &vosInfo);

	///\brief 获取对应媒体索引的pt值
	///\param [in] mediaIndex-媒体索引
	///\return 对应媒体索引的pt值
	int getPayloadType(int mediaIndex );
	
	///\brief 获取对应PT值的载荷编码名称
	///\param [in] pt-payload type,载荷类型
	///\return 获取失败-NULL，获取成功-该载荷对应的编码名称，如pt为0 对应的name为“PCMU”
	static const char* getPayloadTypeName(int pt);

	///\brief 获取对应PT值的载荷采样率
	///\param [in] pt-payload type,载荷类型
	///\return 采样率-获取成功， -1-获取失败
	static int getFreq(int pt);
			
	///\brief 获取视频的类型，如H264
	///\param [in] videoName-视频编码名称，如“H264”
	///\param [in/out] dh_type-大华帧头中的编码子类型，参见<<大华码流信息格式>>
	///\return 视频编码类型-获取成功， -1-获取失败,返回 EncType_Unknown，参见streamparser.h中 EncType定义
	static int getVideoType(const std::string& videoName, uint8_t &dh_type);
	
	///\brief 获取音频的类型，如PCMU
	///\param [in] audio_name-音频编码名称，如“H264”
	///\param [in/out] dh_type-大华帧头中的编码子类型，参见<<大华码流信息格式>>
	///\return 返回音频对应的编码类型.参见streamparser.h中 EncType定义
	static int getAudioType(const char* audio_name, uint8_t &dh_type);

	///\brief 获取对应音频媒体索引的通道数
	///\param [in] mediaIndex-媒体索引
	///\return 对应媒体索引的通道数
	int getAudioToneNum(int mediaIndex);

	///\brief 获取对应媒体类型的总的track数，比如获取sdp中有几路音频或者几路视频
	///\param [in] mediaIndex-媒体类型，	参见sdpParser中MediaType定义
	///\return 该种媒体类型在这个sdp中有几路
	int getTotalNumByMediaType(int mediaType);

	///\brief 获取对应媒体的收发属性
	///\param [in] mediaIndex-媒体索引(0,1,2,...)
	///\return CSdpParser::SendRecvAttr,UNKNOWN_SR_ATTR表示失败，其它为成功
	CSdpParser::SendRecvAttr getSendRecvAttr(int mediaIndex);

	///\brief 解析vorbis sdp消息，获取vorbis head信息
	///\param [in]buf-用于存放vorbis head信息
	///\param [in]len-该缓冲的大小
	///\param [in]vorbis_head-vobis head的地址和长度信息
	///\return <0-失败，0 成功
	int parseVorbisSdp(uint8_t *buf, int size, vorbis_configuration_head &vorbis_head);
private:
	///\brief 从rtpmap字段中获得采样率
	///\param [in] mediaIndex-媒体索引(0,1,2,...)
	///\return 采样率
	int getRtpmapSample( int mediaIndex);

	///\brief 从rtpmap字段中获得音频通道数目
	///\param [in] mediaIndex-媒体索引(0,1,2,...)
	///\return 音频通道数目
	int getRtpmapAudioToneNum(int mediaIndex);

	///\brief 从AAC荷载信息中的config字段解析出采样率和音频通道数目
	///\param [in/out] sample-采样率
	///\param [in/out] tone_num-音频通道数目
	///\return 0-成功，<0 失败
	int parseAACSdp(int &sample, int &tone_num);

	///\brief 从AAC荷载信息中的config字段解析出采样率枚举获得其采样率
	///\param [in] 	   freq_type-采样率枚举
	///\param [in/out] freq-采样率
	///\return 0-成功，<0 失败
	int getAACsample(uint8_t freq_type, int& freq);

private:	
	CSdpParser *m_sdp_parser;
};

}
}

#endif // __INCLUDE_DAHUA_STREAMSVR_SDPHELPER_H__

