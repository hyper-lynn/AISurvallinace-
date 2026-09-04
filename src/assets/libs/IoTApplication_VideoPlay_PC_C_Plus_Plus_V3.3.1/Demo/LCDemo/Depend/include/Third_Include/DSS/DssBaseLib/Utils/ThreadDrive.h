#ifndef _DSSC_UTILS__THREAD_DRIVE_H_
#define _DSSC_UTILS__THREAD_DRIVE_H_

#include "AX_API/platform.h"
#include <vector>


// 单个线程处理类
class DOAX_DEPRECATED IThreadDrive
{
public:
	IThreadDrive(void);
	virtual ~IThreadDrive(void);

public:
	virtual int Heartbeat(uint64 threadId = 0) = 0;
	virtual int OnStart(uint64 threadId = 0);
	virtual int OnStop(uint64 threadId = 0);

public:
	int SetThreadNum(int iNum);
	int GetThreadNum();

	void SetDeal(bool bDeal);
	bool IsDeal();

protected:
	int m_iThreadNum;
	bool m_bDeal;
};

typedef std::vector<IThreadDrive*>	HandlerVec;

// 多个放一起
class DOAX_DEPRECATED CThreadMultiDrive: public IThreadDrive
{
public:
	CThreadMultiDrive(void);
	~CThreadMultiDrive(void);

public://IPlateChain
	virtual int Heartbeat(uint64 threadId = 0);

public:
	int	PushHandler(IThreadDrive* pHandler);

protected:
	HandlerVec		m_vecHandler;
};



#endif
