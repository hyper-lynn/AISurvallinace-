/* $Id: pjsua_app.h 4489 2013-04-23 07:53:25Z riza $ */
/* 
 * Copyright (C) 2008-2011 Teluu Inc. (http://www.teluu.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef __PJSUA_APP_H__
#define __PJSUA_APP_H__

/**
 * Interface for user application to use pjsua with CLI/menu based UI. 
 */

typedef int		pj_status_t;
typedef int		pj_bool_t;
typedef int (*fInComingCallBack)(int iret, void *pUser, char *number);
typedef int (*fRegisterCallBack)(int iret, void *pUser);

//#include "pjsua_app_common.h"

#ifdef __cplusplus
extern "C" 
{
#endif
/*
typedef struct pjsua_app_cfg_t
{
    int       argc;

    char    **argv;

    void (*on_started)(pj_status_t status, const char* title);

    void (*on_stopped)(pj_bool_t restart, int argc, char** argv);

    void (*on_config_init)(pjsua_app_config *cfg);
} pjsua_app_cfg_t;
*/
/**
 * This will initiate the pjsua and the user interface (CLI/menu UI) based on 
 * the provided configuration.
 */
//pj_status_t pjsua_app_init(const pjsua_app_cfg_t *app_cfg);

/**
 * This will run the CLI/menu based UI.
 * wait_telnet_cli is used for CLI based UI. It will tell the library to block
 * or wait until user invoke the "shutdown"/"restart" command. GUI based app
 * should define this param as PJ_FALSE.
 */
pj_status_t pjsua_app_run(pj_bool_t wait_telnet_cli);

/**
 * This will destroy/cleanup the application library.
 */
pj_status_t pjsua_app_destroy();

/**
 * \brief		sPhoneRegister_i
 * \param		[in] id:		本地账户URL
 * \param		[in] registrar:	注册服务器的URL
 * \param		[in] realm:		域名
 * \param		[in] username:	设置用户名
 * \param		[in] password:	设置密码
 * \param		[in] reg_timeout:注册周期
 * \return		SUCCESS:	成功
 * \return		FAIL:		失败
 * \return		ERROR:		出错
 * \author		qw
 * \date		2013-12-16
 * \remarks		用户注册，SDK初始化完成后，调用此函数进行注册用户
 */
pj_status_t sPhoneRegister_i(char *id, char *regestrar, char *realm, char *username, char *password, char *reg_timeout, unsigned tab, fRegisterCallBack cb, void *pUser);

/**
 * \brief		sPhoneUnregister_i
 * \param		void		无
 * \return		SUCCESS:	成功
 * \return		FAIL:		失败
 * \return		ERROR:		出错
 * \author		qw
 * \date		2013-12-16
 * \remarks		用户反注册，仅当客户端关闭时实现
 */
pj_status_t sPhoneUnregister_i(void);

/**
 * \brief		sPhoneInit_i
 * \param		void		无
 * \return		SUCCESS:	成功
 * \return		FAIL:		失败
 * \return		ERROR:		出错
 * \author		qw
 * \date		2013-12-16
 * \remarks		初始化SDK，在所有的SDK函数之前调用
 */
pj_status_t sPhoneInit_i(unsigned port, unsigned autohook, fInComingCallBack cb, unsigned tab, void *pUser);

/**
 * \brief		sPhoneRgInfoGet_i
 * \param		[out] id:		  本地账户URL
 * \param		[out] registrar:  注册服务器的URL
 * \param		[out] realm:	  域名
 * \param		[out] username:	  设置用户名
 * \param		[out] password:	  设置密码
 * \param		[out] reg_timeout:注册周期
 * \return		SUCCESS:	成功
 * \return		FAIL:		失败
 * \return		ERROR:		出错
 * \author		qw
 * \date		2013-12-16
 * \remarks		获取用户配置信息
 */
pj_status_t sPhoneRgInfoGet_i(char *id, char *regestrar, char *realm, char *username, char *password, char *reg_timeout);

/**
* \brief		sPhoneHookOn_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		用户挂机函数
*/
pj_status_t sPhoneHookOn_i(void);

/**
* \brief		sPhonePlaceCall_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		用户呼叫函数
*/
pj_status_t sPhonePlaceCall_i(void);

/**
* \brief		sPhoneDial_i
* \param		[in] num:	拨打的号码
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		用户拨号函数
*/
pj_status_t sPhoneDial_i(char *num);

/**
* \brief		sPhoneHold_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		用户保持函数
*/
pj_status_t sPhoneHold_i(void);

/**
* \brief		sPhoneMuteIn_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		呼入静音
*/
pj_status_t sPhoneMuteIn_i(unsigned enable);

/**
* \brief		sPhoneMuteout_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		呼出静音
*/
pj_status_t sPhoneMuteOut_i(unsigned enable);

/**
* \brief		sPhoneSetInputVolume_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		输入音量调节(一般设置为10效果较好，根据需求自由调节，数字越大音量越大)
*/
pj_status_t sPhoneSetInputVolume_i(float volume);

/**
* \brief		sPhoneSetInputVolume_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		输出音量调节(一般设置为10效果较好，根据需求自由调节，数字越大音量越大)
*/
pj_status_t sPhoneSetOutputVolume_i(float volume);

/**
* \brief		sPhoneSetInputVolume_i
* \param		void		无
* \return		SUCCESS:	成功
* \return		FAIL:		失败
* \return		ERROR:		出错
* \author		qw
* \date			2013-12-16
* \remarks		回音消除（单位为毫秒，一般填40效果较好）
*/
pj_status_t sPhoneSetEchoCancel_i(int ndelay);


#ifdef __cplusplus
}
#endif
    
#endif	/* __PJSUA_APP_H__ */
