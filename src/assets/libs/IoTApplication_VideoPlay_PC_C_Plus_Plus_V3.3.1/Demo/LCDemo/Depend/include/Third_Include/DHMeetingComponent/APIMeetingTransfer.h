//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __API_MEETING_TRANSFER_H__
#define __API_MEETING_TRANSFER_H__

#ifdef __cplusplus
extern "C" {
#endif

/// \n 调用流程图:
///    ============================================
///             AMT_initMemory      //只有手机等没有初始化CPacket内存池的才要调用
///             AMT_init            //只有第一次才是初始化，以后调用这是用于获取监听端口
///                   |
///             AMT_putData         //init之后随时可调用
///       +-----------|------------------+
///       |     AMT_addClinet
///       |  +---------|
///       |  |  AMT_startTransfer
///       |  |  AMT_setPolicy
///       |  |  AMT_stopTransfer    //AMT_stopTransfer可以不调用，AMT_delClinet、AMT_delClinetAll包含AMT_stopTransfer的功能
///       |  |  AMT_pauseSend       //pause后必须显示调用resume才能够恢复发送，与AMT_startTransfer和AMT_stopTransfer无关
///       |  |  AMT_resumeSend
///       |  +---------|
///       |     AMT_delClinet
///       |     AMT_delClinetAll
///       +-----------|------------------+
///             DHMeetingDataStop
///                   |
///    ============================================

#define AMT_ID_LEN          64
typedef char AMTID[AMT_ID_LEN];

///\brief 媒体 类型
typedef enum {
    AMTTYPE_Audio = 0,          ///< 音频类型
    AMTTYPE_Video,              ///< 视频类型
    AMTTYPE_MAX
}AMTTYPE;

///TODO 77
//1.accept成功，开始发送数据给对方    //事件描述见AMT_EVENT_DSC_Net
//2.发送网络断开                      //事件描述见AMT_EVENT_DSC_Net
//3.connect成功，开始接受对方数据     //事件描述见AMT_EVENT_DSC_Net
//4.接收网络断开                      //事件描述见AMT_EVENT_DSC_Net

/* 客户端的网络状
 */
typedef enum
{
    AMT_NET_STATE_Connected = 0,        ///<连接成功
    AMT_NET_STATE_Disconnected,         ///<已断开
    AMT_NET_STATE_BUTT,
}AMT_NET_STATE;

/* 客户端的网络状态事件描述信息
 */
typedef struct
{
    AMTID           id;
    AMTTYPE         type;
    AMT_NET_STATE   state;
}AMT_EVENT_DSC_NetState;

/* 数据到来事件描述信息，在此回调中禁止调用 AMTMeetingTransfer.h 的任何接口
 */
typedef struct
{
    AMTID   id;
    AMTTYPE type;
    void    *data;
    int     len;
}AMT_EVENT_DSC_RecvData;

/* 编码参数调整事件描述信息
 */
typedef struct
{
    AMTID   id;
    AMTTYPE type;       //目前应该都是AMTTYPE_Video，音频不需要调整，不会出现此事件
    int     bitrate;    //kbps
    int     fps;        //帧率
    int     channel;    //编码通道号
    int     streamtype; //编码主辅码流
    //bool    changed;    //取消changed，因为不是网传库直接回调，所以没有返回值必须成功
    int     bitrateold; //kbps，上次的码率，用于外面判断是否需要改变分辨率
}AMT_EVENT_DSC_ChangeEncode;

/* 音频波形数据到来事件描述信息，在此回调中禁止调用 DHMeetingData.h 的任何接口
 * 此事件定期上报(1秒30次)，此事件由libDHMeetingData.a产生，只是定义在此
 */
typedef struct
{
    unsigned int max;        //音量最大值
    unsigned int cur;        //当前音量值
}AMT_EVENT_DSC_AudioWave;

typedef enum
{
	AMT_EVENT_NetState  = 1,    //1.客户端的网络状态事件              //事件描述见AMT_EVENT_DSC_NetState
	AMT_EVENT_RecvData,         //2.接收到一帧数据                    //事件描述见AMT_EVENT_DSC_RecvData
	AMT_EVENT_ChangeEncode,     //3.因网络原因，需要调整编码参数      //事件描述见AMT_EVENT_DSC_ChangeEncode
    AMT_EVENT_AudioWave,        //4.音频波形数据，用于上层展示波形    //事件描述见AMT_EVENT_DSC_AudioWave
    
    AMT_EVENT_BUITT,
}AMT_EVENT;
typedef void ( *AMTCallback ) (AMT_EVENT eventId, void* eventDsc, void *userData);

/* 初始化CPacket的内存池，如果已经在其他地方申请了就不需要调用了
 * 主要给手机调用
 * totalSize(in)    内存池大小，单位字节，比如 AMT_initMemory(20*1024*1024)
 * 返回0成功
 */
int AMT_initMemory(int totalSize);

/* 初始化，注册回调，监听端口，只需要调用一次；
 * 只有第一次调用会初始化(初始工作、设置回调等)，以后调用这是用于获取监听的端口号
 * 监听的端口，如果有人连接，验证OK，并且已经add进来，就会给他发送数据
 * myId(in)         设置自己的ID用于发送verify数据
 * callback(in)     设置回调函数
 * userdata(in)     回调时候的userData
 * listenPort(out)  返回监听的端口，用于呼叫的时候发给对方来连接请求数据
 * 返回0成功
 */
int AMT_init(AMTID myId, AMTCallback callback, void *userdata, int *listenPort);

typedef struct {
    int frameLevel; //帧优先级，I帧和audio帧为1，P帧为2
                    //如果未来音视频数据在一条链路发送，那frameLevel得使用-11来保证语音对讲优先
    int noTail;     //是否不包含大华帧尾，
                    //如果帧很大且分成几次传入，前面几次调用设置为1，最后一次调用设置为0
                    //其他情况都设置为0

    //pkt!=NULL     则使用pkt
    //              否则使用data 和 len
    void *pkt;      //必须是____  new  ___出来的，且调用AMT_putData返回后delete
                    //(Dahua::Memory::CPacket *)类实例，且1个packet必须<=1帧
    
    void *data;     //纯粹码流数据，且1次<=1帧
    int len;        //data的长度
}t_AMT_putData;
/* 放新数据到缓冲，内部会自动发送给需要的客户端
 * channel(in)      用户表明数据的主辅码流，如果没有则设置为0
 * streamtype(in)   用户表明数据的主辅码流，如果没有则设置为0
 * type(in)         说明数据音频还是视频
 * data(in)         大华帧数据，为t_AMT_putData结构体指针
 * 返回0成功
 */
#define D_AMT_TEST_SEND_BACK_DATA  0//为0则AMT_putData起作用，否则AMT_putData_sendback起作用
int AMT_putData(int channel, int streamtype, AMTTYPE type, t_AMT_putData *data);
#if D_AMT_TEST_SEND_BACK_DATA
int AMT_putData_sendback(int channel, int streamtype, AMTTYPE type, t_AMT_putData *data);
#endif

typedef struct {
    int minBitRate;     //最小编码码率，kbps
    int maxBitRate;     //最大编码码率，kbps
    int fps;            //编码帧率
}t_AMT_setPolicy;
/* 设置清晰流畅
 * id(in)           对方橙聊ID
 * channel(in)      用户表明数据的主辅码流，如果没有则设置为0
 * streamtype(in)   用户表明数据的主辅码流，如果没有则设置为0
 * policy(in)       设置的参数，为t_AMT_setPolicy结构体指针，只对视频有效，用于网络自适应调整编码码率
 * 返回0成功
 */
int AMT_setPolicy(AMTID id, int channel, int streamtype, t_AMT_setPolicy *policy);

/* 新用户加入
 * id(in)           对方橙聊ID
 * 返回0成功
 */
int AMT_addClinet(AMTID id);

/* 用户退出
 * id(in)           对方橙聊ID
 * 返回0成功
 */
int AMT_delClinet(AMTID id);

/* 所有用户退出
 * 返回0成功
 */
int AMT_delClinetAll();

/* 开始传输数据，目前只影响接收数据(因为发送数据是由accept触发)
 * connect -> sendVerifyData -> while()recv;
 * accept  -> recvVerifyData -> while()send;
 * id(in)           对方橙聊ID
 * type(in)         说明数据音频还是视频
 * ip(in)           设置为NULL，用于测试时候可以设置其他IP
 * port(in)         对方的端口
 * 返回0成功
 */
int AMT_startTransfer(AMTID id, AMTTYPE type, const char *ip, int port);

/* 停止传输数据，目前只影响接收数据(因为发送数据是由accept触发)
 * id(in)           对方橙聊ID
 * type(in)         说明数据音频还是视频
 * 返回0成功
 */
int AMT_stopTransfer(AMTID id, AMTTYPE type);

/*暂停发送数据，
 *pause后必须显示调用resume才能够恢复发送，与AMT_startTransfer和AMT_stopTransfer无关
 *id(in)
 *type(in)        是音频还是视频
 *port(in)        对方的监听端口
 *返回0成功
 */
int AMT_pauseSend(AMTID id, AMTTYPE type);

/*恢复发送数据，
 *pause后必须显示调用resume才能够恢复发送，与AMT_startTransfer和AMT_stopTransfer无关
 *id(in)
 *type(in)        是音频还是视频
 *port(in)        对方的监听端口
 *返回0成功
 */
int AMT_resumeSend(AMTID id, AMTTYPE type);

#ifdef __cplusplus
}
#endif

#endif //__API_MEETING_TRANSFER_H__


