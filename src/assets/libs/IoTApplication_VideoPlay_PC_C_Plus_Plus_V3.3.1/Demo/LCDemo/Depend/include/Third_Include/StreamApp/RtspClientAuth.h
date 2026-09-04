//
//  "$Id: DHFileData.h 11665 2010-08-31 03:36:39Z huang_xiaojin $"
//
//  Copyright (c)1992-2020, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//					2010-8-31		huang_xiaojin	Create
//
#ifndef __INCLUDED_DAHUA_STREAM_SVR_RTSPCLIENT_AUTH_H__
#define __INCLUDED_DAHUA_STREAM_SVR_RTSPCLIENT_AUTH_H__
#include <string>
#include "StreamSvr/Protocol/RtspUtil.h"

namespace Dahua{
namespace NetFramework{
class CStrParser;		
}
 
namespace StreamApp{

// Rtsp客户端认证信息类
// Rtsp Client连接服务器时，如果服务器需要认证消息，由此类提供相应认证支持
// 用户名，密码，服务器URL，需要外部设置

class CRtspClientAuth
{
public:
	enum AUTH_TYPE{
		AUTH_UNKNOWN,
		AUTH_BASIC,
		AUTH_DIGEST,
	};	
public:
	CRtspClientAuth();
	~CRtspClientAuth();	
	//设置用户名和密码
	void SetUserInfo( const std::string &user_name, const std::string &password );
	//获取用户名和密码
	void GetUserInfo( std::string &user_name, std::string &password );
	//设置服务器URL
	void SetUrl( const std::string& url );
	void SetMethod( StreamSvr::RtspMethod method );
	void SetMethod( const std::string& method );	
	//将服务器返回的WWW-Authenticate信息设置进来
	void SetWWWAuthenticate( const std::string &auth_info );
	//获取生成的认证消息，作为Authorization信息，发给Rtsp服务器
	//返回：成功 true， 失败 false
	bool GetAuthorization( std::string& auth_info );
	AUTH_TYPE GetAuthType(){ return m_auth_type; }
private:
	struct http_auth
	{
	    char *p_realm;
	    char *p_domain;
	    char *p_nonce;
	    char *p_opaque;
	    char *p_stale;
	    char *p_algorithm;
	    char *p_qop;
	    
	    int i_nonce;
    	char *p_cnonce;
    	
    	char *psz_HA1; /* stored H(A1) value if algorithm = "MD5-sess" */
    };	
	
	AUTH_TYPE get_auth_type( NetFramework::CStrParser *parser );
	bool get_authorization_basic( NetFramework::CStrParser *parser,  std::string& auth_info );
	bool get_authorization_digest( NetFramework::CStrParser *parser, std::string& auth_info );
	bool parse_auth_diget_header( );
	char *generate_cnonce();
	
	char *auth_digest( http_auth *http_auth,
                         const char *psz_method, const char *psz_path,
                         const char *psz_username, const char *psz_password );	
private:
	std::string 	m_user;
	std::string 	m_password;
	std::string 	m_url;
	std::string 	m_auth_from_svr;
	std::string 	m_auth_to_svr;
	std::string 	m_method;
	http_auth		m_auth;
	AUTH_TYPE       m_auth_type;
};

}//namespace StreamApp
}//namespace Dahua
#endif
