#ifndef __INCLUDE_DAHUA_STREAMSVR_MEDIAADAPTER_H__
#define __INCLUDE_DAHUA_STREAMSVR_MEDIAADAPTER_H__

#include <string>
#include "StreamSvr/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"

namespace Dahua{
namespace StreamSvr{

class STREAMSVR_API IMediaAdapterParameter
{
public:
	virtual ~IMediaAdapterParameter(){};
};

class STREAMSVR_API IMediaAdapter
{
public:
	///\brief 虚析构接口
	virtual ~IMediaAdapter() {}
	
public:
	enum MaResult
	{
		maResultFailed = -1,		//失败
		maResultSuccess = 0,	//成功，需要继续
		maResultFin = 1,			//完成
	};
	///\brief 设置参数信息
	///\param [in] parameter-适配参数
	///\return -1-失败，0-成功
	virtual int setParameter(const IMediaAdapterParameter& parameter){return 0;};
	
	///\brief 将数据放入到适配器中，由适配器修改之后，将数据返回出来
	///\param [in] inData-待修改的数据
	///\return -1-失败，0-成功，需要继续put数据，1-可以调用get去取数据，参考maResultFailed定义
	virtual int put(int mediaIndex, const CMediaFrame& inData) = 0;

	///\brief 获取数据
	///\param [in] mediaIndex-对应的MediaIndex
	///\param [in/out] frame-修改后的数据
	///\return -1-获取失败，0-还需要继续get，1-get空了，参考maResultFailed定义
	virtual int get(int mediaIndex, CMediaFrame &frame) = 0;
	
	///\brief 获取参数
	///\param [in] index-对应的MediaIndex
	///\param [in/out] seq-包的序列号	
	///\param [in/out] ts-包的时间戳
	///\param [in] ssrc-媒体的ssrc
	virtual void getParam(int index, uint16_t &seq, uint32_t &ts, uint32_t ssrc) {};

	///\brief 释放对象
	virtual void destroy() = 0;
};

STREAMSVR_API IMediaAdapter* create_mediaAdapter(const std::string& url);

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_MEDIAADAPTER_H__
