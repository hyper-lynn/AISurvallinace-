#ifndef __INCLUDED_DAHUA_STREAM_PARSER_STAT_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_STAT_H__


#include "StreamSvr/Util/MediaFrame.h"

namespace Dahua {
namespace StreamSvr {

struct CFrameStatisImpl;

class CFrameStatis
{
public:
	///\brief 构造函数
	CFrameStatis();

	///\brief 析构函数
	~CFrameStatis();
			
public:
	///\brief 帧信息统计，包括帧率和码流值
	void DoStatis(CMediaFrame &frame);
	
	float m_frame_rate;		///< 帧率
	float m_bit_rate;		///< 码率
	
private:
	CFrameStatisImpl* m_impl;
};
		
} // namespace StreamParser
} // namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_STAT_H__
