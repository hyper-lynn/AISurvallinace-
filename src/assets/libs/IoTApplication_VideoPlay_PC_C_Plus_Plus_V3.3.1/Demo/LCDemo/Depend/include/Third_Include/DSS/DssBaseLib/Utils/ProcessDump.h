#ifndef DH_DSS_COMPONENT_UTIL_PROCESS_DUMP_H_INCLUDED
#define DH_DSS_COMPONENT_UTIL_PROCESS_DUMP_H_INCLUDED

#include <string>
#include <vector>
#include "AX_API/AX_Mutex.h"
#include "AX_API/platform.h"

#if defined(_WIN32) || defined(_WIN64)

class DOAX_DEPRECATED CProcessDump
{
public:
    const static int32 SUCCESS=0;
public:
    CProcessDump();
    virtual ~CProcessDump();
private:
    CProcessDump(const CProcessDump&);
    CProcessDump& operator=(const CProcessDump&);
public:
    static CProcessDump& getInstance();
    static CProcessDump _instance;
public:
    void dump(std::string& result);
protected:
    int makeReadyNames();
    int getFiles(const std::string& dirFullName,const std::string& filePattern, std::vector<std::string>& files);
    int deleteOldPkgFile(const std::string& oldPkgFileName);
    int miniDump(const std::string dumpFileFullName);
    int pkgAllFiles();
    int cleanTempFiles();
    int pkgFile(const std::string& fileFullName);
    int moveDestToFinal();
protected:
    AX_Mutex _mutex;
    std::string _workFullDir;
    std::string _destPkgFullName;
    std::string _finalPkgFullName;
    std::string _dumpFileFullName;
    std::vector<std::string> _addFiles;
};

#endif // WIN32

#endif//DH_DSS_COMPONENT_UTIL_PROCESS_DUMP_H_INCLUDED

