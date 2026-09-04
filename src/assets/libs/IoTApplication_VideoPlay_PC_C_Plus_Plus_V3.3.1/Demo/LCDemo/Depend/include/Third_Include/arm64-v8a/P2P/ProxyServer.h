/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   : 代理服务端对外c++头文件
 **
 ** 修改历史     : 2013年11月14日 zhu_long Modification
*************************************************************************/

#ifndef _DAHUA_TOU_PROXY_SERVER_H_
#define _DAHUA_TOU_PROXY_SERVER_H_

#include "ProxyDefs.h"
#include <vector>

namespace Dahua {
namespace Tou {

typedef std::vector<PTCPInfo>    PTCPInfoVector;

///\brief 代理客户端入口
class CProxyServerImpl;
class TOU_API CProxyServer
{
    DISALLOW_COPY_AND_ASSIGN(CProxyServer);
public:

    ///\brief 构造
    ///\param[in]       svraddr         服务器IP
    ///\param[in]       svrport         服务器端口
    ///\param[in]       svrkey          密钥
    ///\param[in]       uuid            设备序列号
    ///\param[in]       eth             网卡名称
    ///\param[in]       threadNumber    线程数量
    ///\param[in]       username        用户名
    CProxyServer(const char* svraddr, uint16_t svrport, const char* svrkey, const char* uuid, 
                 const char *eth, uint32_t threadNumber, const char *username);

    ///\brief 析构
    ~CProxyServer();

    ///\brief 查询当前的P2P连接的状态
    ///\param[out]  stat 当前代理所有p2p链路状态
    void query(P2PStatPtr &stat);

    ///\brief 获取当前代理状态
    ///\return @see ProxyState
    ProxyState getState();

    ///\brief 设置Proxy选项
    ///\param[in] option ProxyOption枚举
    ///\param[in] value 设置参数值
    ///\note value设置 @see ProxyOption
    bool setProxyOption(ProxyOption option, int value);
    
    ///\brief 获取对应option的值
    ///\param[in] option ProxyOption枚举
    ///\return 返回设置的参数值 @see ProxyOption
    int getProxyOption(ProxyOption option);

    ///\brief 获取PTCP协议栈内部信息
    ///\param[out] infoVector 所有PTCP协议栈内部信息集合
    void getPTCPInfo(PTCPInfoVector &infoVector);

    ///\brief 设置日志级别,高于该级别的日志不能输出
    ///\param[in] level P2PLogLevel枚举
    ///\note level设置 @see P2PLogLevel
    ///\note 默认日志级别为 P2PLogLevelDebug
    void setProxyLogLevel(P2PLogLevel level);
    
    ///\brief 设置设备信息
    ///\param[in]  deviceInfo   设备信息
    ///\return  true 成功/false 失败
    bool setDeviceInfo(const char *deviceInfo);
    
    ///\brief  设置设备上报信息(上报到as的信息)
    ///\param[in]   registReportInfo    上报信息
    ///\param[in]   strExt   扩展字段, json格式字符串, 无时填NULL
    ///\return true成功/false 失败
    bool setRegistReportInfo(const RegistReportInfo &registReportInfo, const char *strExt);

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

    ///\biref 注册获取设备加密密码回调
    ///\param[in]    getDevEnPwdHandler    获取设备加密密码的回调函数
    void regP2PGetDevEnPwdhandler(const P2PGetDevEnPwdHandler getDevEnPwdHandler);

private:
    CProxyServerImpl    *m_server;
};
}
}

#endif /* _DAHUA_TOU_PROXY_SERVER_H_ */
