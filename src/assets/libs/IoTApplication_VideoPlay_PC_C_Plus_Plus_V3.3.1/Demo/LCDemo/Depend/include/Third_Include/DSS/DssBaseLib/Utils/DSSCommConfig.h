#ifndef DH_DSS_COMPONENT_UTIL_DSS_COMM_CONFIG_H_INCLUDED
#define DH_DSS_COMPONENT_UTIL_DSS_COMM_CONFIG_H_INCLUDED

#include <string>
#include "AX_API/platform.h"

class CDSSCommConfig
{
public:
	CDSSCommConfig();
	virtual ~CDSSCommConfig();
public:
	int32 initialize(const char* configFileName,const char* authBase);
	int32 updateHistory();
	int32 readConfig(std::string& data,int32& len,std::string& authString);
	int32 writeConfig(const char* data,int32 len,const char* authString);

	std::string getAuthString();
	int32 checkAuthString(const char* authString);

protected:
	int32 readFile(const std::string& fileName,std::string& data,int32& len);
	int32 writeFile(const std::string& fileName,std::string& data,int32 len);
	int32 updateAuthString();
protected:
	std::string _fileName;
	std::string _fileName_LastGood;
	std::string _fileName_LastGood2;
	std::string _authBase;
	std::string _authString;
	uint32		_writeCount;
};

#endif//DH_DSS_COMPONENT_UTIL_DSS_COMM_CONFIG_H_INCLUDED
