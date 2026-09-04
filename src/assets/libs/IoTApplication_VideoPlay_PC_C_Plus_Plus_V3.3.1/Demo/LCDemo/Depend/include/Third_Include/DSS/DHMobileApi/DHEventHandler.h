#ifndef DHEventHandler_h__
#define DHEventHandler_h__

#include "../globaldef.h"

class INTERFACE_API_CLASS DHEventHandler
{
public:
	DHEventHandler(bool bRelease = false);
	virtual ~DHEventHandler(void);

	bool IsNeedRelease(){return m_bRelease;};

	virtual void HandleEvent( int param1, int param2 ) = 0;
	virtual void HandleCommand( int nMsgComand, int param1, int param2 ) = 0;

private:
	bool m_bRelease;
};

#endif // DHEventHandler_h__

