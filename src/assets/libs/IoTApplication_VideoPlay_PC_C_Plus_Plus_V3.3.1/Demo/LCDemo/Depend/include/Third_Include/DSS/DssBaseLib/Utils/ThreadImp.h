#ifndef _DSSC_UTILS_THREAD_IMP_H_
#define _DSSC_UTILS_THREAD_IMP_H_

#include "Utils/ThreadBase.h"
#include "Utils/ThreadDrive.h"


class DOAX_DEPRECATED CThreadImp: protected ThreadBase
{
public:
	CThreadImp(IThreadDrive* pHandler);
	~CThreadImp(void);

public:
	int Start();
	int Stop();

protected:
	virtual int run();
	
protected:
	IThreadDrive* m_pHandler;
};


#endif

