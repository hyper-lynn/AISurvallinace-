/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#ifndef _INCLUDE_FTP_OPT_HEADER_
#define _INCLUDE_FTP_OPT_HEADER_

#include "curl.h"
#include <sys/types.h>
#include <string>

enum TransportMode{
	MODE_PORT,	// 主动模式
	MODE_EPSV,	// 被动扩展模式
	MODE_PASV,	// 被动模式
};

class CURL_EXTERN CFTPCurlOpt
{
public:
	CFTPCurlOpt();
	CFTPCurlOpt(TransportMode mode);
	virtual ~CFTPCurlOpt();

	static int FtpGlobalInit(void);
	static int FtpGlobalCleanup(void);

	size_t FindSubString(const char* szSrc, const char* szSubStr);

	virtual int Init(const char* szFTP);
	virtual int Init(const char* szFTP, const char* szName, const char *szPwd);
	virtual int SetPwd(const char* szName, const char *szPwd);
	virtual TransportMode GetFtpMode();

	virtual int PutFile(const char* szLocalFileName, const char* szFtpFileName = NULL, bool bAppendMode = false);
	virtual int GetFile(const char* szSaveFileName, const char* szFtpFileName = NULL);
	virtual int DelFile(const char* szFtpFileName);

	virtual int GetBuffer(char* szOutBuff, size_t iLen, size_t& iGetLen, const char* szFileName = NULL);
	virtual int PutBuffer(char* szInBuff, size_t iLen, const char* szFileName = NULL);
	virtual int RenameFile(const char* szFtpFileName, const char* szFtpNewFileName);
	virtual int CustomerQuestFileList(const char* szFtpUrl,char* szOutBuff,size_t iLen,size_t& iGetLen);

	virtual int GetLastErrorCode();
private:
	virtual int GetFileName(const char* szFullPath, std::string& strPath, std::string& strFile);
	virtual int Commit(const char* szFile, int iLine);
	virtual void InitTransportMode();

	static size_t write_data(void *buffer, size_t size, size_t nmemb, void *user_p);

	/**
	 *	@brief libcurl接收到数据时的回调函数
	 *
	 *	将接收到的数据保存到本地文件中
	 *	@param [in] buffer 接收到的数据所在缓冲区 
	 *	@param [in] size 数据长度 
	 *	@param [in] nmemb 数据片数量 
	 *	@param [in/out] 用户自定义指针 
	 *	@return 获取的数据长度 
	 */
	static size_t read_data(void *buffer, size_t size, size_t nmemb, void *user_p);

	static size_t write_buff(void *buffer, size_t size, size_t nmemb, void *user_p);
	static size_t read_buff(void *buffer, size_t size, size_t nmemb, void *user_p);
	// 读HEADER内容获取远端文件大小
	static size_t get_content_length(void *buffer, size_t size, size_t nmemb, void *user_p);
	static void MakeErrorCodeMap();
	static const char* GetErrorCode(int error_code);

private:
	CURL *m_easy_handle;
	std::string m_strUser;
	std::string m_strPwd;
	struct curl_slist *m_headerlist; //命令列表
	TransportMode m_ftpMode;
};

typedef CFTPCurlOpt FTPOpt;

#endif /*_INCLUDE_FTP_OPT_HEADER_*/

