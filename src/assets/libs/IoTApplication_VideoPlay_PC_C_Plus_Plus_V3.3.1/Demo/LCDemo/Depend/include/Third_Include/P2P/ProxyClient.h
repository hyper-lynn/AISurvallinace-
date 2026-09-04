/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   : 代理客户端对外c++头文件
 **
 ** 修改历史     : 2013年11月14日 zhu_long Modification
*************************************************************************/

#ifndef _DAHUA_TOU_PROXY_CLIENT_H_
#define _DAHUA_TOU_PROXY_CLIENT_H_

#include "ProxyDefs.h"

namespace Dahua {
namespace Tou {

///\brief 代理客户端入口
class CProxyClientImpl;
class TOU_API CProxyClient
{
    DISALLOW_COPY_AND_ASSIGN(CProxyClient);
public:
    ///\brief 创建一个代理客户端
    ///\param[in]       svraddr      服务器IP
    ///\param[in]       svrport      服务器端口
    ///\param[in]       svrkey       密钥
    ///\param[in]       clientType   客户端类型
    CProxyClient(const char* svraddr, uint16_t svrport, const char* svrkey, const EventHandler &handler,
        const char *clientType = NULL, const char* username = NULL);

    ///\brief 析构
    ~CProxyClient();

    ///\brief 通过远程代理打开本地映射(同步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       timeOut     超时时间(单位:毫秒)
    ///\param[in]       type        通道类型
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note timeOut为0， 则不设置超时时间, 直到有结果返回
    ///\return P2P通道状态
    P2PChannelState addPortSync(const char* uuid, uint16_t remotePort, uint16_t &localPort, 
                     uint32_t timeOut = 5000, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(同步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       timeOut     超时时间(单位:毫秒)
    ///\param[in]       type        通道类型
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note timeOut为0， 则不设置超时时间, 直到有结果返回
    ///\return P2P通道状态
    P2PChannelState addPortSync(const char* uuid, uint16_t remotePort, uint16_t &localPort, const char* devUserName, const char* devPassWord, 
                    const char* randSalt, const char* devP2PVersion, uint32_t timeOut = 5000, uint32_t type = 0);

    ///\brief 打开远程代理的本地映射(异步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0，则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addPort(const char* uuid, uint16_t remotePort, uint16_t &localPort, 
                uint32_t type = 0);

    ///\brief 打开远程代理的本地映射(异步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0，则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addPort(const char* uuid, uint16_t remotePort, uint16_t &localPort, const char* devUserName,
        const char* devPassWord, const char* randSalt, const char* devP2PVersion, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(异步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remoteIp    目标IP
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addPort(const char* uuid, const char* remoteIp, uint16_t remotePort,
                 uint16_t &localPort, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(异步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remoteIp    目标IP
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addPort(const char* uuid, const char* remoteIp, uint16_t remotePort, uint16_t &localPort, const char* devUserName,
                    const char* devPassWord, const char* randSalt, const char* devP2PVersion, uint32_t type = 0);


    ///\brief 通过远程代理打开本地映射(TcpRelay, 同步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       timeOut     超时时间(单位:毫秒)
    ///\param[in]       type        通道类型
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note timeOut为0， 则不设置超时时间, 直到有结果返回
    ///\return 通道建立成功/通道建立失败
    P2PChannelState addTcpRelayPortSync(const char* uuid, uint16_t remotePort, uint16_t &localPort, 
            uint32_t timeOut = 5000, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(TcpRelay, 同步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       timeOut     超时时间(单位:毫秒)
    ///\param[in]       type        通道类型
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note timeOut为0， 则不设置超时时间, 直到有结果返回
    ///\return 通道建立成功/通道建立失败
    P2PChannelState addTcpRelayPortSync(const char* uuid, uint16_t remotePort, uint16_t &localPort, const char* devUserName,
        const char* devPassWord, const char* randSalt, const char* devP2PVersion, uint32_t timeOut = 5000, uint32_t type = 0);

    ///\brief 打开远程代理的本地映射(TcpRelay, 异步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0，则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addTcpRelayPort(const char* uuid, uint16_t remotePort, uint16_t &localPort, 
        uint32_t type = 0);

    ///\brief 打开远程代理的本地映射(TcpRelay, 异步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0，则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addTcpRelayPort(const char* uuid, uint16_t remotePort, uint16_t &localPort, const char* devUserName,
        const char* devPassWord, const char* randSalt, const char* devP2PVersion, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(TcpRelay, 异步模式)
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remoteIp    目标IP
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addTcpRelayPort(const char* uuid, const char* remoteIp, uint16_t remotePort,
            uint16_t &localPort, uint32_t type = 0);

    ///\brief 通过远程代理打开本地映射(TcpRelay, 异步模式)，带设备用户名、密码、随机盐值、设备P2P版本号
    ///\param[in]       uuid        远程代理ID
    ///\param[in]       remoteIp    目标IP
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\param[in]       type        通道类型
    ///\return 添加端口映射成功/失败
    ///\note localPort为0， 则由内部随机分配一个端口
    ///\note 通道建立是否成功需调用query接口查询
    bool addTcpRelayPort(const char* uuid, const char* remoteIp, uint16_t remotePort,
        uint16_t &localPort, const char* devUserName,
        const char* devPassWord, const char* randSalt, const char* devP2PVersion, uint32_t type = 0);

    ///\brief 删除一个映射
    ///\param[in]   port 本地映射端口
    ///\return 成功/失败
    bool deletePort(uint16_t port);

    ///\brief 查询当前的P2P连接的状态
    ///\param[out]  stat 当前代理所有p2p链路状态
    void query(P2PStatPtr &stat);

    ///\brief 查询映射端口速率
    ///\param[in]   port 本地映射端口
    ///\param[out]  rate 当前映射速率
    ///\return @see P2PChannelState
    P2PChannelState query(uint16_t port, MapPortRate &rate);

    ///\brief 查询映射端口状态
    ///\param[in]   port 本地映射端口
    ///\param[out]  stat 当前映射状态
    ///\return @see P2PChannelState
    P2PChannelState query(uint16_t port, MapPortStat &stat);

    ///\brief 获取当前客户端状态
    ///\return @see ProxyState
    ProxyState getState();

    ///\brief 查询远程代理的状态
    ///\param[in]   uuid 远程代理ID
    ///\return @see ProxyState
    ProxyState getState(const char* uuid);

    ///\brief 设置远程IP和Port
    ///\param[in]       remoteIp    目标IP
    ///\param[in]       remotePort  目标端口
    ///\param[in,out]   localPort   本地映射端口
    ///\return 成功/失败
    bool setRemoteInfo(const char* remoteIp, uint16_t remotePort, uint16_t localPort);

    ///\brief 设置Proxy选项
    ///\param[in] option ProxyOption枚举
    ///\param[in] value 设置参数值
    ///\note value设置 @see ProxyOption
    bool setProxyOption(ProxyOption option, int value);
    
    ///\brief 获取对应option的值
    ///\param[in] option ProxyOption枚举
    ///\return 返回设置的参数值 @see ProxyState
    int getProxyOption(ProxyOption option);

    ///\brief 设置日志级别,高于该级别的日志不能输出
    ///\param[in] level P2PLogLevel枚举
    ///\note level设置 @see P2PLogLevel
    ///\note 默认日志级别为 P2PLogLevelDebug
    void setProxyLogLevel(P2PLogLevel level);
    
    ///\brief 获取设备信息
    ///\param[in]      dev_id       设备序列号
    ///\param[in]      bufferLen    存储设备信息的缓冲区长度
    ///\param[out]     deviceInfo   设备信息
    ///\param[in]      timeout      超时时间，默认为3秒
    ///\return 成功/失败
    bool getDeviceInfo(const char *dev_id, int bufferLen, char *deviceInfo, uint32_t timeout = 3000); 

    ///\brief 注册上报穿透信息的回调
    ///\param[in]      reportHandler   穿透信息上报的回调函数
    ///\note 该回调仅限于P2P向上层上报穿透信息
    ///\note 请勿在该回调中处理上层业务，防止阻塞P2P内部线程
    void regP2PTraversalInfoHandler(const P2PTraversalInfoHandler reportHandler);

#ifndef P2P_LOG_REPORT_DISABLE
    ///\brief json格式日志打点信息上报回调
    ///\param[in]   jsonLogReportHandler    json格式的日志打点信息上报的回调函数 
    ///\note 请勿在该回调中处理上层业务，防止阻塞P2P内部线程
    void regP2PJsonLogReportHandler(const P2PJsonLogReportHandler jsonLogReportHandler);

    ///\brief 字符串格式日志打点信息上报回调
    ///\param[in]   strLogReportHandler    字符串格式的日志打点信息上报的回调函数 
    ///\note 请勿在该回调中处理上层业务，防止阻塞P2P内部线程
    void regP2PStrLogReportHandler(const P2PStrLogReportHandlder strLogReportHandler);
#endif

    ///\brief 获取P2P监听的Socket Domain
    ///\param[in]      localPort    本地映射端口
    ///\param[out]     family       Socket Domain
    ///\return 成功/失败
    bool getSockFamily(uint16_t localPort, P2PSockFamilyType &family);

    ///\brief   设置P2P session信息
    ///\param[in]       localPort   本地映射端口
    ///\param[in]       ip          上层连接IP
    ///\param[in]       port        上层连接建立后的本地端口
    ///\param[in]       requestId   上层连接唯一唯一标识(requestid)
    bool setSessionInfo(uint16_t localPort, const char *ip, uint16_t port, const char *connId);
    
private:
    CProxyClientImpl    *m_client;
};

}
}

#endif /* _DAHUA_TOU_PROXY_CLIENT_H_ */

