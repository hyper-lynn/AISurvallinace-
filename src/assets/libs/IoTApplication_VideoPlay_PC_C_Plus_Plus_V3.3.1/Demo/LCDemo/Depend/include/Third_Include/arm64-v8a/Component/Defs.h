//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA_COMPONENT_DEFS_H__
#define __DAHUA_COMPONENT_DEFS_H__


#include "Infra/PreProcessor.h"


// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef COMPONENT_DLL_BUILD
#define  COMPONENT_API _declspec(dllexport)
#elif defined COMPONENT_DLL_USE
#define  COMPONENT_API _declspec(dllimport)
#else
#define COMPONENT_API
#endif

#else

#define COMPONENT_API

#endif


//////////////////////////////////////////////////////////////////////////
// use the unified 'DEBUG' macro
#if (!defined(NDEBUG)) && !defined(DEBUG)
#	define DEBUG
#endif

namespace Dahua {

/////////////////////////////////////////////////////////////////////////
// Error Number Define For Component
enum ComponentError
{
	componentErrorInterfaceNotFound		= 0x10030000,///< 组件接口没有找到
	componentErrorClassNotFound			= 0x10030001,///< 组件实现类没有找到
	componentErrorClientNotFound		= 0x10030002,///< 需要的客户端组件没有找到
	componentErrorClientNotExist		= 0x10030003,///< 客户端实例不存在
	componentErrorNotLoginYet			= 0x10030004,///< 没有登录
	componentErrorTryingLogin			= 0x10030005,///< 非阻塞登录，正在尝试
	componentErrorUserNameNotValid		= 0x10030006,///< 用户名无效
	componentErrorPasswordNotValid		= 0x10030007,///< 密码无效
	componentErrorPeerHasBeenBlocked	= 0x10030008,///< 地址被屏蔽了
	componentErrorPeerInBlackList		= 0x10030009,///< 地址在黑名单中
	componentErrorUserNameHasBeenUsed	= 0x1003000a,///< 用户名已经在使用，而且不能复用
	componentErrorTooManyConnections	= 0x1003000b,///< 超出了最大用户连接数
	componentErrorHasNoAuthority		= 0x1003000c,///< 没有对应的操作权限
	componentErrorCreateObjectFailed	= 0x1003000d,///< 组件工厂创建对象失败
	componentErrorGetInstanceFailed		= 0x1003000e,///< 组件工厂获取实例失败
	componentErrorLoginChallenge		= 0x1003000f,///< 登录质询，需要根据返回的随机字符串再次登录
	componentErrorUnimplementedOperation= 0x10030010,///< 组件接口方法没有实现
	componentErrorAccountHasBeenBlocked	= 0x10030011,///< 帐号被锁定
	componentErrorLoginConnectFailed	= 0x10030012,///< 登陆时网络连接失败
	componentErrorLoginTimeout			= 0x10030013,///< 登陆连接成功，但收响应超时
	componentErrorLoginFailure			= 0x10030014,///< 登陆失败，原因未知
	componentErrorUserOrPwdNotValid		= 0x10030015,///< 登陆失败，用户名或密码错误
};

} // namespace Dahua


/// 空的接口实现
#define COMPONENT_UNIMPLEMENTED_OPERATION						\
{																\
	Dahua::Infra::setLastError(Dahua::componentErrorUnimplementedOperation);	\
	return false;												\
}

/// 返回NULL的空接口实现
#define COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_NULL			\
{																\
	Dahua::Infra::setLastError(Dahua::componentErrorUnimplementedOperation);	\
	return NULL;												\
}

/// 用于DAHUA_PP_FOR的判别，当操作结果为0，宏的展开即停止
#define DAHUA_COMPONENT_PRED(r, state)	\
	DAHUA_PP_NOT_EQUAL(	\
		DAHUA_PP_TUPLE_ELEM(4, 0, state),	\
		DAHUA_PP_TUPLE_ELEM(4, 1, state)	\
		)

///  用于DAHUA_PP_FOR,当宏为1时，宏会被执行
#define DAHUA_COMPONENT_OP(r, state)	\
	(	\
		DAHUA_PP_DEC(	\
			DAHUA_PP_TUPLE_ELEM(4, 0, state)	\
		),	\
		DAHUA_PP_TUPLE_ELEM(4, 1, state),	\
		DAHUA_PP_TUPLE_ELEM(4, 2, state),	\
		DAHUA_PP_DEC(	\
			DAHUA_PP_TUPLE_ELEM(4, 3, state)	\
		)	\
	)

/// 当DAHUA_COMPONENT_PRED为1时，这个宏会被展开，否则不会
#define DAHUA_COMPONENT_MACRO(r, state)	\
	virtual bool \
	DAHUA_PP_CAT(	\
		DAHUA_PP_TUPLE_ELEM(4, 2, state),	\
		DAHUA_PP_TUPLE_ELEM(4, 0, state)	\
	)	\
	()COMPONENT_UNIMPLEMENTED_OPERATION


/// 保留的函数接口,展开结果:DAHUA_COMPONENT_MACRO(r, s) (DAHUA_COMPONENT_OP(r, s), DAHUA_COMPONENT_MACRO(r, s)) ...
#define DAHUA_COMPONENT_FUNCTION_REVSERVED(number)	\
	DAHUA_PP_FOR(	\
		(number, 0, rev_func, number),	\
		DAHUA_COMPONENT_PRED, DAHUA_COMPONENT_OP, DAHUA_COMPONENT_MACRO	\
	)


#endif //__DAHUA_COMPONENT_DEFS_H__
