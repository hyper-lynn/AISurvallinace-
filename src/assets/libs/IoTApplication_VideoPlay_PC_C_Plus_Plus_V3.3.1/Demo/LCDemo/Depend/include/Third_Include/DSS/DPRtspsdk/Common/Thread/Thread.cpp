#ifdef DP_REST_PLATFORM_SDK

#include "stdafx.h"
#include "Thread.h"
#include "Mutex.h"
#include "libdsl/DThreadRunner.h"
#include "libdsl/DEvent.h"

namespace Common
{
	class CThreadPrivate
	{
	public:
        CThreadPrivate()
        : m_msWaitTime(0)
		{
            m_thread.SetThreadName("CThreadPrivate");
		}
    public:
        dsl::DRunner<CThread> m_thread;
        dsl::DMutex m_mutexQueue;
        dsl::DEvent m_condition;   // 条件变量
        int m_msWaitTime;//ms
    };


	CThread::CThread()
		: d_ptr(new CThreadPrivate())
	{
	}

	CThread::~CThread()
	{
		StopThread();

		if (NULL != d_ptr)
		{
			delete d_ptr;
			d_ptr = NULL;
		}
	}

	bool CThread::StartThread(unsigned int uWaitTime)
	{
        DS_D(CThread);
        if (d->m_thread.IsRunning())
        {
            return false;
        }
        
        d->m_msWaitTime = uWaitTime;
        d->m_condition.Reset();
        d->m_thread.SetRunner(&CThread::CallThread, this, dsl::DSL_RUNNER_TYPE_REPEAT);
        d->m_thread.Start();
        
        return true;
    }
    
    void CThread::StopThread()
	{
        DS_D(CThread);
        d->m_condition.SetEvent();
        d->m_thread.Stop();
    }

	// 唤醒线程，取消等待
	void CThread::WakeUpOnce()
	{
        DS_D(CThread);
        d->m_condition.SetEvent();
	}

	// 线程是否运行
	bool CThread::IsRunning()
	{
        DS_D(CThread);
        return d->m_thread.IsRunning();
	}

	int CThread::CallThread(dsl::DThread * th)
	{
        DS_D(CThread);
        dsl::DMutexGuard lock(&(d->m_mutexQueue));
        
        do {
            if (!Run())
            {
                break;
            }
            
            if ( d->m_msWaitTime != 0)
            {
                if (d->m_thread.IsRunning())
                {
                    d->m_condition.TimedWait(d->m_msWaitTime);
                }
            }
        } while (0);
        
        return 0;
    }
    
    // 线程睡眠
    void CThread::MySleep(unsigned long iSecs)
	{
        dsl::DThread::SleepMs(iSecs * 1000);
	}

	void CThread::MSleep(unsigned long iMSecs)
	{
        dsl::DThread::SleepMs(iMSecs);
	}

	void CThread::USleep(unsigned long iUSecs)
	{
        dsl::DThread::SleepMs(iUSecs/1000);
	}
}

#endif
