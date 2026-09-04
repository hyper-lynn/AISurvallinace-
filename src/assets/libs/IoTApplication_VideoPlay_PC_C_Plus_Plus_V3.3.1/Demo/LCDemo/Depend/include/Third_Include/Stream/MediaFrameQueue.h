//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef DAHUA_PACKET_CIRCULAR_QUEUE_H__
#define DAHUA_PACKET_CIRCULAR_QUEUE_H__

#include <Stream/MediaFrame.h>


namespace Dahua {
namespace Stream {


/// 线程安全的内存受限帧缓冲循环队列
class CMediaFrameQueue
{
	CMediaFrameQueue(CMediaFrameQueue const&);
	CMediaFrameQueue& operator=(CMediaFrameQueue const&);

public:
	/// 构造函数
	/// \param maxCount 队列包含的最大帧数
	CMediaFrameQueue(int maxCount);

	/// 析构函数
	~CMediaFrameQueue();

	/// 放入一个帧数据包，达到容量限制时最老的数据包出队
	void putFrame(CMediaFrame const& frame);

	/// 从缓冲队列中获取包，数据包取走后并不出列。推荐使用此接口来
	/// 统一使用包数据，使用者不使用自有缓冲。
	/// \param [in, out] sn 包的序列号，最新的数据包的序列号是依次增加的：-1表示
	///   取最新数据包；0 或者序号偏小则取最老的数据包；取其他值表示如果队列中存
	///   在该数据包，则返回对应的数据包，否则返回空包。sn传出的值是下一个数据包
	///   的序号：如果原序号存在并且而取到了有效的数据包，该值会递增 1；如果偏小
	///   而取到了最老的数据包，该值会被设置为最老数据包的下一个包的序号；如果偏
	///   大而没有取到数据，则维持不变。
	/// \param [out] lostNum 相对 sn 值丢失的帧数，为 0 表示没有丢帧。
	/// \return 取到的数据包，内部数据包可能为空，需要使用valid判断。
	CMediaFrame getFrame(int64_t& sn, int64_t& lostNum) const;

	/// 根据预录时间获取包序号
	int64_t getPreFrameSn(int seconds) const;

	/// 取队列中当前帧数量
	int count() const;

	/// 限制队列的帧数量
	/// \param [in] count 包数量限制
	void limit(int count);

	/// 清空队列
	void clear();

private:
	struct Internal;
	Internal* m_internal;
};

} // namespace Stream
} // namespace Dahua


#endif // DAHUA_PACKET_CIRCULAR_QUEUE_H__
