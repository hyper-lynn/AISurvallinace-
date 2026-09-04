#ifndef DHDEV_VERSIONCTL_H
#define DHDEV_VERSIONCTL_H

#define DHNET_NAMESPACE_BEGIN   namespace DH_NET_SDK {
#define DHNET_NAMESPACE_END     };

//------------------------------------------------------
//银行SSL加密版本
//#define NETSDK_VERSION_BOGUSSSL
//------------------------------------------------------
//
//------------------------------------------------------
//普通加密版本
//#define NETSDK_VERSION_ENCRYPT
//------------------------------------------------------
//
//------------------------------------------------------
//解码器设备版本
//#define NETSDK_VERSION_DECODER
//------------------------------------------------------
//
//------------------------------------------------------
//取反加密版本
//#define NETSDK_VERSION_INVERSE
//------------------------------------------------------
//
//------------------------------------------------------
//OEM客户版本
//#define NETSDK_VERSION_OEM
//#define NETSDK_OEM_KEY    "OemChongQinXunMei"
//#define NETSDK_OEM_KEY    "oemqsee"
//#define NETSDK_OEM_KEY    "poiuytrewq"
//------------------------------------------------------
//
//------------------------------------------------------
//SSL加密版本
//#define NETSDK_VERSION_SSL
//------------------------------------------------------
//
//------------------------------------------------------
//SELECT版本
//#define SELECT_MODEL
//------------------------------------------------------
//
//------------------------------------------------------
//防盗版验证版本
//#define VALIDATE_MODEL
//------------------------------------------------------
//
//------------------------------------------------------ 
//内存池使用版本
#define MEMPOOL_MODEL
//------------------------------------------------------
//
//------------------------------------------------------
//AMR对讲使用版本
//#define AMR_AUDIO
//------------------------------------------------------

// dhdvr 做成静态库
#define SDK_DHDVR_STATIC


//////////////////////////////////////////////////////////////////////////
// 版本控制宏：

//#define __BIG_ENDIAN__            // 大端
//#define __UDP_MULTICAST__         // UDP和组播

// 配置功能：
#define __SDK_CFG_PTZ_OPT_ATTR__    // PTZ能力集
#define __SDK_CFG_ALARM__           // 报警配置
#define __SDK_CFG_WLAN__            // 无线设备配置
#define __SDK_CFG_ALARMCENTER__     // 报警中心配置
#define __SDK_CFG_ATMOVERLAY__      // ATM叠加配置，新ATM特有配置
#define __SDK_CFG_DEVICEATTR__      // 设备属性
#define __SDK_CFG_NETWORK__         // 网络配置
#define __SDK_CFG_CHANNELVIDEO__    // 图象通道
#define __SDK_CFG_CAMERAPARAM__     // 摄像头属性配置
#define __SDK_CFG_IPIFILTER__       // IP过滤配置
#define __SDK_CFG_RECORD__          // 录像配置
#define __SDK_CFG_COM__             // 串口配置
#define __SDK_CFG_DEVICETIME__      // 校时
#define __SDK_CFG_PREVIEW__         // 预览参数配置
#define __SDK_CFG_AUTOMATION__      // 自动维护配置
#define __SDK_CFG_VIDEOMATRIX__     // 本机矩阵控制策略配置
#define __SDK_CFG_MUTIDDNS__        // 多ddns服务器配置
#define __SDK_CFG_SNAP__            // 抓图相关配置
#define __SDK_CFG_URL__             // HTTP路径配置
#define __SDK_CFG_FTP__             // FTP上传配置
#define __SDK_CFG_INTERVIDEO__      // 平台接入配置
#define __SDK_CFG_VIDEOCOVER__      // 区域遮挡配置
#define __SDK_CFG_STRATEGY__        // 策略配置
#define __SDK_CFG_AUTOREGISTER__    // 主动注册参数配置
#define __SDK_CFG_SNIFFER__         // Sniffer抓包配置
#define __SDK_CFG_STORAGESTATE__    // 存储位置配置
#define __SDK_CFG_DST__             // 夏令时配置
#define __SDK_CFG_VIDEOOSD__        // 视频OSD叠加配置
#define __SDK_CFG_CDMAGPRS__        // CDMA\GPRS网络配置
#define __SDK_CFG_MAIL__            // 邮件配置
#define __SDK_CFG_SIP__             // SIP配置
#define __SDK_CFG_TALKENCODE__      // 语音对讲编码配置
#define __SDK_CFG_MMSSMS__          // 短信相关配置
#define __SDK_CFG_DIALINACTIVATION__ // 拨号激活无线连接配置
#define __SDK_CFG_VIDEOOUT__        // 视频输出参数配置
#define __SDK_CFG_POINT__           // 预制点使能配置
#define __SDK_CFG_ENCODER__         // 数字通道的前端编码器信息
#define __SDK_CFG_TVADJUST__        // TV调节配置
#define __SDK_CFG_VEHICLE__         // 车载相关配置，北京公交使用
#define __SDK_CFG_DECODERTOUR__     // 解码器解码轮巡配置
#define __SDK_CFG_MACHINE__         // 机器相关配置
#define __SDK_CFG_WATERMARK__       // 图象水印配置
#define __SDK_CFG_SYSLOG__          // SYSLOG 远程服务器配置
#define __SDK_CFG_BACKUP_VIDEOFORMAT__  //设置视频备份格式
#define __SDK_CFG_ALARM_CENTER__        //报警中心附加的配置
#define __SDK_CFG_AUDIO_DETECT__        // 音频检测配置
#define __SDK_CFG_MACIFILTER__          // MAC过滤配置
#define __SDK_CFG_RECORD_PACKET__       //录像打包时间
#define __SDK_CFG_DOWNLOAD_RATE__       // 下载速度限制
#define __SDK_CFG_VICHILE_WIFI_AP__     // wifi ap配置
#define __SDK_CFG_NETCARD__             // 获取卡口参数配置
#define __SDK_CFG_RTSP__                // 获取RTSP参数配置
#define __SDK_CFG_232_COM_CARD__        // 设置232卡号信号事件配置
#define __SDK_CFG_STREAM_ENCRYPT__      // 获取码流加密配置
#define __SDK_CFG_LIMIT_BIT_RATE__      // 获取限码流配置
#define __SDK_CFG_STREAM_ENCRYPT_TIME__ // 获取码流加密计划配置
#define __SDK_CFG_CUSTOM__              // 用户自定义配置
#define __SDK_CFG_LIGHTCONTROL__        // 灯光控制配置
#define __SDK_CFG_3GFLOW__              // 3G网络流量配置获取
#define __SDK_CFG_IPV6__                // IPV6配置获取
#define __SDK_CFG_SNMP__                // 简单网络管理协议配置
#define __SDK_CFG_SNAP_CONTROL__        // 抓图开关配置获取
#define __SDK_CFG_GPS_MODE__            // GPS定位模式配置
#define __SDK_CFG_SNAP_UPLOAD__         // 图片上传配置信息
#define __SDK_CFG_SPEED_LIMIT__         // 限速配置信息
#define __SDK_CFG_ISCSI__               // iSCSI配置
#define __SDK_CFG_WIRELESS_ROUTING__    // 无线路由配置
#define __SDK_CFG_ENCLOSURE__           //电子围栏
#define __SDK_CFG_ENCLOSURE_VERSION__   //电子围栏版本号获取
#define __SDK_CFG_ELEVATOR_ATTRI__      //电梯运行参数
#define __SDK_CFG_URGENCY_RECORD__      //紧急配置
#define __SDK_CFG_DECODER_URL__         // 解码器url配置
#define __SDK_CFG_TOUR_ENABLE__         // 轮巡使能配置
#define __SDK_AUDIO_DETECT__            // 音频检测配置

// 解码器功能
#define __SDK_DECODER__                 // 解码器功能

// 矩阵功能：
#define __SDK_MATRIX__                  // 矩阵M60功能

#ifndef DH_OPTIM_MINMIZESIZE

// 视频浓缩
#define __SDK_VIDEOSYNOPSIS__           // 视频浓缩

// 视频诊断
#define __SDK_VIDEODIAGNOSIS__          // 视频诊断

// IVS-PC
#define __SDK_IVS_PC                    // 智能服务器 人数统计

#define __SDK_INTELLIGENT_TRAFFIC__     // 智能交通

#endif

//////////////////////////////////////////////////////////////////////////


#endif
