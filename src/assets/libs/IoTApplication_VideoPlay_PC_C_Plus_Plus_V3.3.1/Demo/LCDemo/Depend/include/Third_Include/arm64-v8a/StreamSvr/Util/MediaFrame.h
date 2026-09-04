#ifndef __DAHUA_STREAMSVR_MEDIA_FRAME_H__
#define __DAHUA_STREAMSVR_MEDIA_FRAME_H__

#include "StreamSvr/Defs.h"
#include "Stream/MediaFrame.h"
#include "NetFramework/MediaStreamSender.h"

namespace Dahua {
namespace StreamSvr {

class CMediaFrameImpl;///> 前向声明


#define IS_AUDIO_FRAME_TYPE(type)		((type) == 'A' )	
#define IS_VIDEO_FRAME_TYPE(type)		(((type) == 'P') || ((type) == 'I') || ((type) == 'B') || ((type) == 'J') \
												 || ((type) == Stream::DHFRAME_SMART_I_FRAME) || ((type) == Stream::DHFRAME_SMART_P_FRAME))	
#define IS_VIDEO_FRAME_I_TYPE(type)		(((type) == 'I') || ((type) == 'J') || ((type) == Stream::DHFRAME_SMART_I_FRAME))
#define IS_VIDEO_FRAME_P_TYPE(type)		(((type) == 'P') || ((type) == 'B') || ((type) == Stream::DHFRAME_SMART_P_FRAME))

///< 拷贝帧信息
#define COPY_MEDIA_FRAME_INFO(outframe, inframe)   \
{\
	(outframe).setType((inframe).getType()); \
	(outframe).setLevel((inframe).getLevel()); \
	(outframe).setSequence((inframe).getSequence()); \
	(outframe).setSlice((inframe).getSlice()); \
	(outframe).setPts((inframe).getPts()); \
	(outframe).setPts((inframe).getPts(Stream::CMediaFrame::ptsBeforeEnc), Stream::CMediaFrame::ptsBeforeEnc); \
	(outframe).setPts((inframe).getPts(Stream::CMediaFrame::ptsAfterEnc),  Stream::CMediaFrame::ptsAfterEnc);  \
	(outframe).setPts((inframe).getPts(Stream::CMediaFrame::ptsLib), 	   Stream::CMediaFrame::ptsLib); \
	(outframe).setPts((inframe).getPts(Stream::CMediaFrame::ptsApp),       Stream::CMediaFrame::ptsApp); \
	(outframe).setPts((inframe).getPts(Stream::CMediaFrame::ptsNet),       Stream::CMediaFrame::ptsNet); \
}

///\brief 内存单元适配类
class STREAMSVR_API CMediaFrame : public NetFramework::CMediaPacket
{
public:
	///\brief 内存管理方式
	enum MemoryType
	{
		memoryTypePacket,				///> Packet内存池
		fragmemtTypePacket,				///> 引用帧的片段内存
		memoryTypeNumber,				///> 种类数
	};	

	///\brief 数据类型
	enum DataType
	{
		dataTypeMedia,	///> 媒体数据
		dataTypeOther,	///> 非媒体数据
		dataTypeRtmpMeta,	///> Rtmp元数据
		dataTypeRtmpMedia,	///> Rtmp媒体数据
		dataTypeUnknown,	///> 未知 
	};

	///\brief 帧切片标识, 表示该帧是新的一个切片起点,还是属于当前的切片
	enum SliceFlag
	{
		dateInSlice = 0,  ///< 切片内的帧
		dateNewSlice,	  ///< 新的切片起点帧, 必须为I帧
		dateEndSlice,	  ///< 切片内的结束帧
	};
		
	///\brief 构造函数，生成一个无效的包，需要赋值才能使用
	///\note 可以用于给有效包赋值，使原包的包数据引用计数递减
	CMediaFrame();
	
	///\brief 构造函数
	///\param [in] bytes-申请内存长度
	///\param [in] type-内存管理类型，参考 @see MemoryType
	CMediaFrame(uint32_t bytes, int type = memoryTypePacket);

	///\brief 构造函数
	///\param [in] CPacket指针
	CMediaFrame(void* ptk_ptr);

	///\brief fragmemtTypePacket 类型的构造函数
	///\param [in] frame -需要引用的frame
	///\param [in] offset -需要使用的内存在frame 中的偏移
	///\param [in] len     - 需要使用的内存长度
	CMediaFrame(Stream::CMediaFrame &frame, uint32_t offset, uint32_t len);
	
	///\brief 拷贝构造函数
	///\param [in] other-内存数据类对象
	CMediaFrame(const CMediaFrame& other);	
	
	///\brief 赋值运算符重载
	///\param [in] other-内存数据类对象
	CMediaFrame& operator=(const CMediaFrame& other);	
	
	///\brief 析构函数
	~CMediaFrame();
	
	///\brief 判断是否为有效包
	///\return 有效-true，无效-false
	bool valid() const;
	
	///\brief 获取基础组件Packet指针，完成该类到基础组件Packet类的转化
	///\return Stream::CMediaFrame对象
	Stream::CMediaFrame getPacket();
	
	///\brief 存储数据
	///\param [in] buffer-追加的数据指针
	///\param [in] length-追加的数据长度
	///\return 实际写入的数据-ok，-1-无效包写入失败
	size_t putBuffer(void * buffer, uint32_t length);
	
	///\brief 包缓冲的起始位置的指针
	///\return 起始位置的指针-ok，NULL-failed
	uint8_t* getBuffer() const;
	
	///\brief 设置包的有效数据长度，刚申请来的包的有效长度是包申请时的大小
	///\param [in] length-新的长度,不会超过包的大小
	///\return  true -成功，false-失败
	bool resize(uint32_t length);
	
	///\brief 包的有效数据长度
	///\return >0-成功，0-无有效数据
	uint32_t size() const;			
	
	///\brief 得到包占用空间的大小，按内部页面对齐，可能比申请的稍大
	///\return 占用的空间大小
	uint32_t capacity() const;
	
	///\brief 取帧产生时的通道号
	///\return channel-成功，-1-失败
	int getChannel() const; 
	
	///\brief 设置帧产生时的通道号
	///\param [in] channel-通道号
	void setChannel(int channel);
	
	///\brief 获取帧类型
	///\return 类型-成功，-1-失败
	///\note 该接口在DataType为dataTypeMedia类型的时候可用
	int getType() const;
	
	///\brief 设置帧类型
	///\param [in] type-类型
	///\note 该接口在DataType为dataTypeMedia类型的时候可用
	void setType(int type);	
	
	///\brief 获取时间戳
	///\param [in] pt-时间戳类型
	///\return 时间戳-ok，0-失败
	uint64_t getPts(Stream::CMediaFrame::PtsType pt = Stream::CMediaFrame::ptsPresentation) const;
	
	///\brief 设置时间戳
	///\param [in] pts-时间戳
	///\param [in] pt-时间戳类型
	void setPts(uint64_t pts, Stream::CMediaFrame::PtsType pt = Stream::CMediaFrame::ptsPresentation);
	
	///\brief 获取帧内图像对应的UTC(1970-1-1 00:00:00)秒数, (最高精确到毫秒)
	///\return UTC时间
	double getUtc() const;
	
	///\brief 设置帧内图像对应的UTC(1970-1-1 00:00:00)秒数, (最高精确到毫秒)
	///\param [in] utc-UTC时间
	void setUtc(double utc);
	
	///\brief 获取帧序号
	///\return 帧序列号
	int getSequence() const;
	
	///\brief 设置帧序号
	///\param [in] sequence-帧序列号
	void setSequence(int sequence);
	
	///\brief 取编码格式变化情况
	///\return 0-none changed, 1-resolution changed, 2-other changed
	int getNewFormat() const;
	
	///\brief 设置编码格式变化情况
	///\param [in] newFormat-格式变化
	///\note 0-none changed, 1-resolution changed, 2-other changed
	void setNewFormat(int newFormat);

	///\brief 设置数据类型
	///\param [in] type-数据类型，参考@see DataType
	void setDataType(int type);

	///\brief 获取数据类型
	///\return 参考@see DataType
	int getDataType() const;

	///\brief 设置传输通道，用于媒体层与传输层传递传输通道信息。
	///\param[in] channel: 该媒体帧所属的传输通道
	void setTransportChannel(uint32_t channel);

	///\brief 获取该媒体帧所属的传输通道
	///\return 该媒体所属的传输通道
	uint32_t getTransportChannel();

	///\brief 设置丢帧级别
	void setLevel(int level);

	///\brief 获取丢帧级别
	///\return 丢帧级别
	int getLevel() const;

	///\brief 设置帧头部数据, 该数据和获得由上层使用者进行管理
	///\return void
	void setExtHead(Stream::CMediaFrame externData);

	///\brief 获得帧头部数据
	///\return 帧头部数据
	Stream::CMediaFrame getExtHead();

	///\brief 释放该数据包。
	///\return void
	virtual void Release();

	///\brief 获取待发送的媒体数据包缓冲区的指针。
	///\return 缓冲区指针
	virtual unsigned char* GetBuffer();
	
	///\brief 设置切片标识 
	///\param[in] flag-设置的切片标识, 见SliceFlag
	///\param[in] reserve: 保留参数
	///\return void
	void setSlice(int flag, void *reserve = NULL);

	///\brief 获得切片标识 
	///\param[in] reserve: 保留参数
	///\return 切片标识, 见SliceFlag
	int getSlice(void *reserve = NULL) const;
private:
	CMediaFrameImpl* m_impl;
};

} // namespace StreamSvr
} // namespace Dahua

#endif	// __DAHUA_STREAM_SVR_MEDIA_FRAME_H__
