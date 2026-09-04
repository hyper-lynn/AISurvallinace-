
#ifndef MTimer_h__
#define MTimer_h__

#include "osIndependent.h"

typedef void (CALLBACK* MyTimerCB)(UINT uTimerID, void* dwUser1, void* dwUser2);

struct TIMER_ITEM
{
	unsigned int	nTimeID;
	unsigned int	delayTime;
	unsigned int	pastTime;
	void*			vPara1;
	void*			vPara2;
	MyTimerCB		cb;

	DWORD			dwPreTick;
};
class INTERFACE_API_CLASS MTimer
{
public:
	void FUNC_CATCHTIMER();

public:
	MTimer();
	~MTimer();

	void RunTimer();
	bool StartTimer();
	bool StopTimer();
	bool AddTimer(TIMER_ITEM& timer);
	bool RemoveTimer(const unsigned int nTimerID);
	bool UpdateTimerDelay(unsigned int nTimerID, unsigned int nDelayTime);

private:
	std::list<TIMER_ITEM>	m_allTimerItems;
	bool					m_bStartFlag;

	MobileApi::OS_THREAD	m_hTimerThread;
	MobileApi::OS_EVENT		m_bExitEvent;
	bool					m_threadExit;
private:
	static const int MAX_TIMER_COUNT = 100;
	static const int DIF_TIME = 2;
};

#endif // MTimer_h__
