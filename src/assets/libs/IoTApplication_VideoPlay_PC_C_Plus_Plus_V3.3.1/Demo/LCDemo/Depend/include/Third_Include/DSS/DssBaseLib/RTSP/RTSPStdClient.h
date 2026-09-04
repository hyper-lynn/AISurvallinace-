#pragma once

#include "RTSPClient.h"
class CRTPSession;

class CRTSPStdClient : public CRTSPClient
{
public:
	CRTSPStdClient(IRTSPListener* listener, int id = 0);
	virtual ~CRTSPStdClient();
	virtual int sendBinaryData( int clientId, char * data, int len, AX_IAddRefAble* pdu );
public:
	virtual int onData(int engineId, int connId, const char* data, int len); 
	int addRTPSession(int connID, CRTPSession* rtpSession);
	CRTPSession* delRTPSession(int connID);
	CRTPSession* _rtpSession;
protected:

};

