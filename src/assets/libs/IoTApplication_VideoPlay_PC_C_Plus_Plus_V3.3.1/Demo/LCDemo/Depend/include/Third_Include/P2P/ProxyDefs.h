/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   : 常用定义
 **
 ** 修改历史     : 2013年11月14日  zhu_long Modification
*************************************************************************/

#ifndef _DAHUA_TOU_PROXY_DEFS_H_
#define _DAHUA_TOU_PROXY_DEFS_H_

#include "Infra/Function.h"
#include "Memory/SharedPtr.h"
#include "Defs.h"
#ifndef P2P_LOG_REPORT_DISABLE
#include "Json/json.h"
#endif

namespace Dahua {
namespace Tou {

///\brief 代理状态
enum ProxyState
{
    proxyStateUnauthorized,             ///< 服务认证失败（序列号非法、密钥错误）
    proxyStateForbidden,                ///< 服务禁止登陆（设备ID重复、服务器拒绝）
    proxyStateOffline,                  ///< 服务离线
    proxyStateOnline,                   ///< 服务在线
    proxyStateRequestFail,              ///< 客户端请求失败
};

///\brief 代理状态
enum P2PChannelState
{
    P2PChannelStateInit,                ///< p2p通道初始化中
    P2PChannelStateActive,              ///< p2p通道已连通
    P2PChannelStateNonExist,            ///< p2p通道不存在
    P2PChannelUnauthorized,             ///< 与服务器鉴权失败
    P2PChannelDevPwdAuthFail,           ///< 设备登录密码校验失败
    P2PChannelDevSaltInvalid,           ///< 设备随机盐值不正确
};


///\brief 映射端口速率统计
struct MapPortRate
{
    uint64_t             recvBytes;     ///< 总接收字节KB
    uint64_t             sendBytes;     ///< 总发送字节KB

    double               curRecvRate;   ///< 当前接收速率Kb/s
    double               curSendRate;   ///< 当前发送速率Kb/s

    double               avgRecvRate;   ///< 平均接收速率Kb/s
    double               avgSendRate;   ///< 平均发送速率Kb/s

    double               lostRate;      ///< 丢包率

    uint64_t             liveTime;      ///< 通道活动时间(秒S)
};

///\brief 映射端口状态
struct MapPortStat
{
    char                mapId[64];      ///< 服务器ID
    char                mapIp[64];      ///< 映射IP
    uint16_t            mapPort;        ///< 映射端口
};

///\brief 单个p2p通道的状态
struct P2PChannelStat
{
    P2PChannelState     state;          ///< 当前通道状态
    uint16_t            localPort;      ///< 本地端口（客户端）
    MapPortStat         stat;           ///< 当前通道详细信息
    MapPortRate         rate;           ///< 速率统计
};

///\brief 客户端事件信息
enum EventType
{
    eventTypeAddPortFail,           ///< 添加端口失败
    eventTypeAddPortSucess,         ///< 添加端口成功
    eventTypeStunFail,              ///< 获取stun信息失败（服务器异常）
    eventTypeIceFail,               ///< 连通检测失败（对端无响应、NAT类型不匹配）
    eventTypeP2PInitFail,           ///< p2p通道初始化失败
    eventTypeP2PInitSucess,         ///< p2p通道初始化成功
    eventTypeDisConnect,            ///< p2p通道断开连接
    eventTypeNumber,                ///< 事件数量
};


///\brief p2p链路统计
struct P2PStat
{
    uint32_t            p2pCount;       ///< p2p通道数量
    P2PChannelStat      *stat;          ///< p2p链路信息

    ///\brief 构造
    P2PStat();

    ///\brief 析构
    ~P2PStat();
};

enum ProxyOption
{
    P2POptionPortGuess,                 ///< 端口猜测选项 参数值: 0 关闭 1 开启
    P2POptionSetMTU,                    ///< MTU选项    参数值: 整数值
    P2POptionUPNP,                      ///< UPNP选项   参数值: 0 关闭 1 开启
    P2POptionRelay,                     ///< Relay选项        参数值：0 关闭 1 开启
    P2POptionPTCPThreadNum,             ///< PTCP线程数目选项  参数值: 整数值
    P2POptionRecvBufSize,               ///< P2P接收缓冲区大小，单位:字节
    P2POptionPTCPSendBuffer,            ///< PTCP发送缓冲区大小，单位:字节
    P2POptionPTCPRecvBuffer,            ///< PTCP接收缓冲区大小，单位:字节
    P2POptionSendBufSize,               ///< TCP发送缓冲区大小，单位:字节
    P2POptionLocal,                     ///< Local选项     参数值：0 不支持局域网连接 1 支持局域网连接
    P2POptionLinkSwitch,                ///< 链路切换选项  参数值: 0 关闭链路切换  1 支持链路切换,本选项只对代理客户端有效
    P2POptionRemoteCommand,             ///< 远程命令选项  参数值：0 关闭 1 开启
    P2POptionMultiHolePunch,            ///< 多重打洞选项  参数值: 0 关闭 1 开启, 默认开启
    P2POptionIceDefaultRange,           ///< ICE默认场景下的猜测范围
    P2POptionIceConeVsSymmRange,        ///< ICE圆锥型与对称型场景下的猜测范围
    P2POptionIceSymmVsSymmRange,        ///< ICE对称型与对称型场景下的猜测范围
    P2POptionLinkSwitchSpace,           ///< 链路切换间隔
    P2POptionTcpRelayRecvBufSize,       ///< TcpRelay接收缓冲区大小
    P2POptionTcpRelaySendBufSize,       ///< TcpRelay发送缓冲区大小
    P2POptionP2P,                       ///< P2P打洞        参数值: 0 关闭 1 开启
    P2POptionTcpRelay,                  ///< Tcp转发选项    参数值: 0 关闭 1 开启
    P2POptionAuthEnable,                  ///< 设备对客户端请求鉴权选项    参数值：0 不鉴权  1 鉴权， 默认不鉴权
};

///\brief P2P通道类型
enum P2PChannelType
{
    P2PUndefineChannelType,            ///< 未定义类型
    P2PAudioChannelType,               ///< 音频通道
    P2PVideoChannelType,               ///< 视频通道
};

///\brief 日志级别
enum P2PLogLevel
{
    P2PLogLevelSilent,                 /// < 该级别不打印信息
    P2PLogLevelErr,                    /// < 致命错误
    P2PLogLevelWarning,                /// < 可能导致出错
    P2PLogLevelInfo,                   /// < 告知用户，当前运行状态
    P2PLogLevelTrace,                  /// < 调试信息
    P2PLogLevelDebug,                  /// < 详细调试信息
};

///\brief P2P监听的Socket Domain
enum P2PSockFamilyType
{
    P2PSockIPv4,                       ///< IPv4协议
    P2PSockIPv6,                       ///< IPv6协议
    P2PSockUnknown,                    ///< 未知协议
};

///\brief PTCP协议栈内部信息
struct PTCPInfo
{
    uint32_t            channelType;    ///< P2P通道的类型，见P2PChannelType
    uint32_t            bandWidth;      ///< 估算的链路带宽，单位bps
    uint32_t            roundTripTime;  ///< 估算的链路RTT，单位ms
    uint64_t            delayTime;      ///< 待发送数据的最大延时，单位ms
    uint32_t            totalSndBuf;    ///< 总共的发送缓冲区大小，单位Byte
    uint32_t            leftSndBuf;     ///< 剩余的发送缓冲区大小，单位Byte
};

struct RegistReportInfo
{
    char          devid[64];            ///< 设备序列号
    char          oemName[64];          ///< oem厂商名
    char          deviceMode[64];       ///< 设备外部型号
    char          devType[32];          ///< 设备类型
    char          version[32];          ///< 版本
    uint16_t      privPort;             ///< 二代协议端口(tcp端口)
    uint16_t      httpPort;             ///< http端口
    uint16_t      rtspPort;             ///< rtsp端口
    uint16_t      tlsPrivPort;          ///< tls端口
    char          p2pType[32];          ///< P2P类型
    char          webver[32];           ///< web version
    char          webSpec[32];          ///< web spec
    char          webSubVer[32];         ///< web sub version
    char          mac[32];               ///< mac
    char          ditcalCert[64];        ///< 数字证书及路径
    char          manufacturer[64];      ///< 厂商
    char          registerServer[64];    ///< 注册上报地址
    uint16_t      registerPort;          ///< 注册上报端口
};

///\brief p2p链路状态计数指针
typedef Memory::TSharedPtr<P2PStat> P2PStatPtr;

///\breif 客户端事件回调
///\param uint16_t      对应事件通道产生的本地端口
///\param EventType     @see EventType
///\param const char *  事件描述
typedef Infra::TFunction3<void, uint16_t, EventType, const char *> EventHandler;

///\brief 客户端穿透信息上报回调
///\param 1:const char *    设备序列号
///\param 3:const char *    设备端NAT后的IP
///\param 4:const int       设备端NAT后的端口
///\param 5:const char *    客户端NAT后的IP
///\param 5:const int       客户端NAT后的端口
///\param 6:const int       连接类型(0:局域网; 1:P2P; 2:udp转发; 3:tcp转发)
typedef Infra::TFunction6<void, const char *, const char *, const int, const char *, const int, const int> P2PTraversalInfoHandler;

#ifndef P2P_LOG_REPORT_DISABLE

///\brief  打点日志上报(json格式)
///\param 1: const Json::Value&    json格式的上报日志
typedef Infra::TFunction1<void, const Json::Value& > P2PJsonLogReportHandler;

///\brief  打点日志上报(字符串格式)
///\param 1: const char *     字符串格式的上报日志
///\param 2: const int        字符串长度
typedef Infra::TFunction2<void, const char *, const int> P2PStrLogReportHandlder;

#endif

///\brief  获取设备加密后密码
///\param 1: const char *      登录用户名
///\param 2: char *            按指定算法加密后的密码
///\param 3: int               密码缓存长度
///\return 用户不存在，返回false, 否则返回true        
typedef Infra::TFunction3<bool, const char *, char *, int> P2PGetDevEnPwdHandler;

}
}

#endif /* _DAHUA_TOU_PROXY_DEFS_H_ */

