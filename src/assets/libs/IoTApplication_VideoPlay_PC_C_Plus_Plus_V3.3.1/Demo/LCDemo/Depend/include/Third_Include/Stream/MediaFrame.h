//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA_MEDIA_FRAME_PACKET_H__
#define __DAHUA_MEDIA_FRAME_PACKET_H__

#include "Infra/IntTypes.h"
#include "Memory/Packet.h"
#include "Defs.h"

namespace Dahua {
namespace Stream {


/// 媒体帧数据包
class STREAM_API CMediaFrame : public Memory::CPacket
{
public:
	/// PTS 类型
	enum PtsType
	{
		ptsPresentation,	///< 音视频帧产生时的时间戳
		ptsBeforeEnc,		///< 音视频帧编码前的时间戳
		ptsAfterEnc,		///< 音视频帧编码后的时间戳
		ptsLib,				///< 编码库从驱动取到本数据包的时间戳
		ptsApp,				///< 应用层取到本数据包后的时间戳
		ptsNet,				///< 网络模块取到本数据包后的时间戳
		ptsNumber			///< 种类数
	};

	/// 构造函数
	CMediaFrame();

	/// 构造函数
	/// \param bytes 申请的包包含的有效数据缓冲的字节数。
	explicit CMediaFrame(size_t bytes);

	/// 从大包中构造帧对象，引用大包中的局部内存，如果参数不正确，构造一个无效帧
	/// \param huge 被引用的大包
	/// \param offset 被引用的内存在大包中的起始字节数
	/// \param bytes 被引用的内存字节数
	CMediaFrame(const Memory::CPacket& hugePacket, size_t offset, size_t bytes);

	/// 取帧产生时的通道号
	int getChannel() const;

	/// 设置帧产生时的通道号
	void setChannel(int channel);

	/// 取帧产生时的StreamType, 参数 IStreamSource::StreamType
	StreamType getStreamType() const;

	/// 设置帧产生时的StreamType
	void setStreamType(StreamType stream);

	/// 获取帧类型: 'A','I','B','P','W','G'
	/// 完整取值范围见 Dahua::Stream::DHFrameType
	int getType() const;

	/// 设置帧类型: 'A','I','B','P','W','G'
	/// 完整取值范围见 Dahua::Stream::DHFrameType
	void setType(int type);

	/// 设置时间戳
	uint64_t getPts(PtsType pt = ptsPresentation) const;

	/// 获取时间戳
	void setPts(uint64_t pts, PtsType pt = ptsPresentation);

	/// 获取帧内图像对应的UTC(1970-1-1 00:00:00)秒数, (最高精确到毫秒)
	double getUtc() const;

	/// 设置帧内图像对应的UTC(1970-1-1 00:00:00)秒数, (最高精确到毫秒)
	void setUtc(double utc);

	/// 获取帧序号
	int getSequence() const;

	/// 设置帧序号
	void setSequence(int sequence);

	/// 取编码格式变化情况, 0-none changed, 1-resolution changed, 2-other changed.
	/// 3-码流内容改变(比如零通道分割改变或通道组成变化)
	int getNewFormat() const;

	/// 设置编码格式变化情况, 0-none changed, 1-resolution changed, 2-other changed.
	/// 3-码流内容改变(比如零通道分割改变或通道组成变化)
	void setNewFormat(int newFormat);

	/// 设置编码模式：参见enum Stream::EncodeType
	int getEncodeType();

	/// 获取编码模式：参见enum Stream::EncodeType
	void setEncodeType(int type);
};

} // namespace Stream
} // namespace Dahua

#endif // __DAHUA_MEDIA_FRAME_PACKET_H__

