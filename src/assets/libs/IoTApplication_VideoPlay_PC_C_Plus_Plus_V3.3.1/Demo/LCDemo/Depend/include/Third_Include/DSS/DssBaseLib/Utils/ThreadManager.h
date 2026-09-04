#ifndef _DSSC_UTILS_THREAD_MANAGER_H_
#define _DSSC_UTILS_THREAD_MANAGER_H_

#include <vector>
#include <list>
#include "Utils/Singleton.h"
#include "Utils/ThreadDrive.h"


class CThreadImp;
typedef	std::list<CThreadImp*>	ThreadImpList;

class DOAX_DEPRECATED CThreadManager
{
public:
	CThreadManager(void);
	virtual ~CThreadManager(void);

public:
	virtual int CreateThreadModel() {return Start();}
	virtual int DestroyThreadModel() {return Stop();}

public:
	// 放入线程模型中，同时设定线程数，默认为1
	int PushHandler(IThreadDrive* handler, int thread_num = 1);

protected:
	int Start();
	int Stop();

	static int GetCPUNum();

protected:
	HandlerVec		m_vecHandler;
	ThreadImpList	m_listThreadImp;
};


#endif

