#pragma once

#include "RTSPServer.h"
class CRTPSession;

class CRTSPStdServer : public CRTSPServer
{
public:
	CRTSPStdServer(IRTSPListener* listener, int id = 0);
	virtual ~CRTSPStdServer();
	virtual int sendBinaryData( int clientId, char * data, int len, AX_IAddRefAble* pdu );
public:
	virtual int onData(int engineId, int connId, const char* data, int len); 
	int addRTPSession(int connID, CRTPSession* rtpSession);
	CRTPSession* delRTPSession(int connID);
	std::map<int, CRTPSession*> _mapRtpSessions; //<connID, CRTPSession>
	AX_Mutex _mtxRtpSessions;
protected:

};

