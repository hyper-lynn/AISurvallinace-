#ifndef __INCLUDE_DAHUA_STREAMAPP_STREAMSOURCE_FACTORY_H__
#define __INCLUDE_DAHUA_STREAMAPP_STREAMSOURCE_FACTORY_H__

#include <map>

#include "Infra/Guard.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamSvr/Media/VodStreamSource.h"
#include "StreamSvr/Media/LiveStreamSource.h"

namespace Dahua{
namespace StreamApp{

StreamSvr::ILiveStreamSource* defaultLiveStreamSourceCreateProc(const char* srcId);
StreamSvr::IVodStreamSource * defaultVodStreamSourceCreateProc(const char* srcId);

///> 流源工厂
///> 目前已知的类型T: ILiveStreamSource, IVodStreamSource
template <typename T>
class TStreamSourceFactory
{
public:
static T * create(const char* srcId)
{
	if (!srcId)
		return NULL;

	Infra::CGuard g(ms_tableMutex);
	TableIterator it = ms_table.find(srcId);
	if (it != ms_table.end())
		return it->second;

	return  typeid(T) == typeid(StreamSvr::IVodStreamSource)\
			? (T*)defaultVodStreamSourceCreateProc (srcId)\
			: (T*)defaultLiveStreamSourceCreateProc(srcId);
}

static void registerStreamSource(const char* srcId, T *ss)
{
	if (!ss)
		return ;

	Infra::CGuard g(ms_tableMutex);
	ms_table.insert(TableValueType(srcId, ss));
}

private:
typedef std::map<std::string, T*> 		TableType;
typedef typename TableType::iterator 	TableIterator;
typedef typename TableType::value_type 	TableValueType;

static TableType 						ms_table;
static Infra::CMutex 					ms_tableMutex;
};

template<typename T> typename Infra::CMutex TStreamSourceFactory<T>::ms_tableMutex;

template<typename T> typename TStreamSourceFactory<T>::TableType TStreamSourceFactory<T>::ms_table;

}
}

#endif
