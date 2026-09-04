
// #pragma once
#ifndef PORTMGR_H_INCLUDE
#define PORTMGR_H_INCLUDE

#include <deque>
#include "AX_API/AX_Mutex.h"

class CPortMgr
{
public:
	CPortMgr();
	virtual ~CPortMgr();
public:
	int getPort();
	void recyclePort(int port);
	void setPort(int basePort, int endPort,int step);
protected:
	AX_Mutex            _rtpPortsMutex;
	std::deque<int>     _rtpPorts;
};

#endif // PORTMGR_H_INCLUDE
