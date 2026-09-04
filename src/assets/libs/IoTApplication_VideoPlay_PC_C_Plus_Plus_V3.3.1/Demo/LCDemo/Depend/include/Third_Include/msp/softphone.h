/**
 * \mainpage	软话机sdk开发包
 * \section		介绍
 *				1、提供标准的二次开发接口； \n
 *				2、只提供语音到声卡，无法主动获取语音数据； \n
 *				3、支持windows、android平台。 \n
 * \file		softphone.h
 * \brief		softphone接口的头文件，定义了所有的sdk接口
 * \author		dahuasys
 * \date		2013-12-16
 * \note		只提供语音到声卡，无法主动获取语音数据
 * \defgroup	软话机sdk
 * \{
 */
#ifndef _SOFTPHONE_SDK_H_
#define _SOFTPHONE_SDK_H_
#pragma once

#if defined WIN64 || defined(WIN32)
//SOFTPHONE_SDK_EXPORTS
#if defined(SOFTPHONE_SDK_EXPORTS) 
#define DLIB_API	__declspec(dllexport)
#else
#define DLIB_API    __declspec(dllimport)
#endif
#elif defined(__linux) || defined(__linux)
#define DLIB_API
#endif

#ifdef	__cplusplus
extern "C"
{
#endif

/**
* \defgroup 回调函数原型
* \{
*/
enum
{
	SOFTPHONE_STANDBY = 0,	///< 待机
	SOFTPHONE_INCOMING,		///< 呼入
	SOFTPHONE_RINGING,		///< 回铃
	SOFTPHONE_ANSWER,		///< 应答
	SOFTPHONE_HANGUP,		///< 挂机
	SOFTPHONE_REGISTER,		///< 注册成功
	SOFTPHONE_UNREGISTER,	///< 取消注册成功
	SOFTPHONE_FORBIDDEN,	///< 注册超时或失败
};

/**
 * \brief		消息回调函数定义
 * \param		[in] code		消息代码,参考SOFTPHONE_STANDBY等定义和说明
 * \param		[in] number		用户
 * \param		[in] user_data	来电号码
 * \author		dahuasys
 * \date		2015-01-19
 * \remarks		消息回调函数. 注册/呼叫共用
 */
typedef int (*softphone_callback)(int code, const char * number, void * user_data);

/** \}
*/
/**
* \defgroup 系统初始化
* \{
*/

/**
 * \brief		系统初始化
 * \param		[in] port		默认填0
 * \param		[in] pfn		回调函数地址)
 * \param		[in] user_data	用户数据
 * \retval		0				成功
 * \retval		-1				创建资源失败
 * \retval		-2				初始化失败失败
 * \retval		-3				创建SIP端口失败
 * \retval		-4				启动资源失败
 * \author		dahuasys
 * \date		2016-8-5
 * \remarks		初始化SDK，在所有的SDK函数之前调用
 * \see			softphone_destroy
 */
DLIB_API int softphone_initial(int port, softphone_callback pfn, void * user_data);

/** \}
*/
/**
* \defgroup 系统销毁
* \{
*/
/**
 * \brief		释放资源
 * \author		dahuasys
 * \date		2016-8-5
 * \remarks		在退出之前调用, 释放内部资源
 * \see			softphone_initial
 */
DLIB_API void softphone_destroy(void);

/** \}
*/
/**
* \defgroup 自动应答
* \{
*/
/**
 * \brief		是否自动对来电应答
 * \param		[in] enable		0:不自动应答,1:自动应答
 * \author		dahuasys
 * \date		2016-8-5
 * \remarks		如果对来电自动应答, 则无需调用 softphone_answer 函数
 * \see			softphone_answer
 */
DLIB_API void softphone_set_auto_answer(int enable);

/** \}
*/
/**
* \defgroup 注册
* \{
*/
/**
 * \brief		注册账号
 * \param		[in] username	登录用户名
 * \param		[in] password	登录密码
 * \param		[in] domain		域名
 * \param		[in] expires	注册周期(默认300)
 * \return		返回值只说明接口调用成功，注册是否成功，需要在回调中判断
 * \retval		0				成功
 * \retval		<0				失败
 * \author		dahuasys
 * \date		2013-12-16
 * \remarks		用户注册，SDK初始化完成后，调用此函数进行注册用户
 * \see			softphone_callback
 */
DLIB_API int softphone_set_account(const char * username, const char * password, const char * domain, int expires);

/** \}
*/
/**
* \defgroup 反注册
* \{
*/
/**
 * \brief		反注册接口
 * \retval		0				成功
 * \retval		1				失败
 * \retval		其他			出错
 * \author		dahuasys
 * \date		2013-12-16
 * \remarks		用户反注册
 */
DLIB_API void softphone_clear_account(void);

/** \}
*/
/**
* \defgroup 拨号
* \{
*/
/**
* \brief		呼出接口
* \param		[in] tel    	完整的号码
* \retval		0				成功
* \retval		-1				系统未初始化,请先调用softphone_initial
* \retval		-2				已经存在会话,请先调用softphone_hangup
* \retval		-3				被叫号码不能为空,请设置tel参数的值
* \retval		-4				未设置账户,或账户未注册成功
* \retval		-5				呼叫ID检查失败
* \retval		-6				调用呼叫失败
* \author		dahuasys
* \date			2016-8-7
* \remarks		对指定号码发起呼叫
*/
DLIB_API int softphone_callout(const char * tel);

/** \}
*/
/**
* \defgroup 应答
* \{
*/
/**
* \brief		应答接口
* \retval		0				成功
* \retval		-1				失败, 当前不存在呼叫或不是呼入的会话
* \author		dahuasys
* \date			2016-8-7
* \remarks		收到SOFTPHONE_INCOMING消息时，调用
*/
DLIB_API int softphone_answer(void);

/** \}
*/
/**
* \defgroup 挂机
* \{
*/
/**
* \brief		挂机接口
* \retval		0				成功
* \author		dahuasys
* \date			2016-8-7
* \remarks		主动挂断
*/
DLIB_API void softphone_hangup(void);

/** \}
*/
/**
* \defgroup 保持
* \{
*/
/**
* \brief		保持接口
* \retval		0				成功
* \retval		-1				失败
* \author		dahuasys
* \date			2013-12-16
* \remarks		保持来电通话,取消保持多次调用即可
*/
DLIB_API int softphone_hold(void);

/** \}
*/
/**
* \defgroup 音量调节
* \{
*/
/**
* \brief		输入音量调节
* \param		[in] volume 	音量大小
* \author		dahuasys
* \date			2013-12-16
* \remarks		输入音量调节(默认为1,表示正常音量, 设置为0表示静音)
*/
DLIB_API void softphone_set_input_volume(int volume);

/**
* \brief		输出音量调节
* \param		[in] volume 	音量大小
* \author		
* \date			2013-12-16
* \remarks		输出音量调节(默认为1,表示正常音量, 设置为0表示静音)
*/
DLIB_API void softphone_set_output_volume(int volume);

/** \}
*/
/**
* \defgroup 回声消除
* \{
*/
/**
* \brief		回音消除
* \param		[in] ndelay		间隔
* \retval		其他			出错
* \author		dahuasys
* \date			2013-12-16
* \remarks		回音消除（单位为毫秒，一般填40效果较好,默认为0表示不需要EC）
*/
DLIB_API void softphone_set_ec_delay(int delay);

/** \}
*/
/**
* \defgroup 按键
* \{
*/
/**
* \brief		发送DTMF
* \param		[in] dtmf		按键字符串, 只能是0-9,*,#,A,B,C,D一共16个字符.
* \retval		0				成功
* \retval		其他			出错
* \author		dahuasys
* \date			2013-12-16
* \remarks		发送DTMF字符串.
*/
DLIB_API int softphone_send_dtmf(const char * dtmf);

/** \}
*/
/**
* \defgroup 录音
* \{
*/
/**
* \brief		开始录音
* \param		[in] filename 	录音文件名或者路径, 当前只支持.wav扩展名
* \retval		0				成功
* \retval		其他			出错
* \author		dahuasys
* \date			2013-12-16
* \remarks		本地开始录音
*/
DLIB_API int softphone_start_record(const char * filename);

/**
* \brief		结束录音
* \retval		0				成功
* \retval		其他			出错
* \author		dahuasys
* \date			2013-12-16
* \remarks		结束已经开始的录音, 挂机时会自动结束录音不需要调用本函数.
*/
DLIB_API void softphone_stop_record(void);

/**
\} 
*/
/**
\} 
*/

#ifdef	__cplusplus
}
#endif

#endif
