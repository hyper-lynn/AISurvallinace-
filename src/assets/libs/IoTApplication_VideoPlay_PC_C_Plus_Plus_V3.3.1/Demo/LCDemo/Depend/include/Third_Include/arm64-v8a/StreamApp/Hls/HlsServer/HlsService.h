#ifndef __DAHUA_STREAMAPP_HLSSERVICE_H__
#define __DAHUA_STREAMAPP_HLSSERVICE_H__

#include <string>
#include "HlsUtil.h"

namespace Dahua{
namespace StreamApp{

class HlsServerImpl;
class CHlsService
{
private:
	CHlsService();
	~CHlsService();

public:
	///\brief 获得hls 服务单例
	///\return hls 服务对象指针
	static CHlsService * instance();

	///\brief 开启hls 服务
	///\param [in] port:  开启hls 服务的端口
	///\return 0 成功, -1 失败
	int start(unsigned short port);

	///\brief 停止hls 服务
	///\return 0 成功, -1 失败
	int stop();

	///\brief 设置hls 服务的配置
	///\param [in] name:  配置的名称
	///\param [in] value:  配置的值
	///\return 0 成功, -1 失败
	int setConfig(hls_svr_config_t name, void *value);

	///\brief 获得hls 服务的配置
	///\param [in] name:  配置的名称
	///\param [in] value:  配置的值
	///\return 0 成功, -1 失败
	int getConfig(hls_svr_config_t name, void *value);		

	///\brief  获得非加密hls 服务有效的hls 会话的数目
	///\return hls 会话的数目
	uint64_t getSessionCount(); 

	///\brief  初始化分片m3u8 列表 , 初始化的结果会通过HlsConfigTsEventProc 设置的函数回调出来, 返回值可不关注
	///\param [in] url:  分片对应的url, 即.m3u8前的部分
	///\return 0 成功, -1 失败
	int initm3u8list(const std::string &url);

	///\brief 验证请求是否为HLS 请求
	///\param [in] buf: 请求缓冲
	///\param [in] len: 缓冲长度
	///\return  0 验证通过, -1验证未通过, -2缓冲区长度不够
	int isHlsRequest(const char *buf, int len);	

	///\brief 添加新的HLS 连接
	///\param [in] sock: 套接字句柄
	///\param [in] buf: 请求缓冲
	///\param [in] len: 缓冲长度
	///\return 0 成功, -1 失败
	int addNewConnect(int sock, const char* buf, int len);
	
	///\brief 开启ssl HLS 服务
	///\param [in] port:  开启hls 服务的端口
	///\param [in] pempath：证书文件的路径
	///\return 0 成功, -1 失败
	int startSslSvr(unsigned short port, const char * pempath);

	///\brief 停止hls ssl服务
	///\return 0 成功, -1 失败
	int stopSslSvr();
	
	///\brief 获取HLS流量统计信息
	///\param [in] type: 统计的事件类型,见hlsStatisticType
	///\param [out] value: 统计的值
	///\param [in] svrtype: 服务类型，默认为非加密服务streamServer
	///\return 0 成功, -1 失败
	int GetStatisticInfo (hlsStatisticType type, void *value, int svrtype = streamServer);

	///\brief HLS服务端口复用接口，将HTTP请求回调给上层应用处理
	///\param [in] svrtype: 服务类型，默认为非加密服务streamServer
	///\param [in] filter_ptr: 过滤函数对象
	///\param [in] func_ptr: 处理函数对象
	///\return 0 成功, -1 失败
	int	setPortReuseCallback(int svrtype, HlsPortReuseFilterProc filter_ptr, HlsPortReuseProc func_ptr);
private:
	HlsServerImpl *m_Imp;
};

}
}

#endif

