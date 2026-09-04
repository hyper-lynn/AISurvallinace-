#include "libdsl/dslbase.h"
#include "NetworkPrivate.h"
namespace Common
{
	NetworkPrivate::NetworkPrivate(Network *pNetwork, QString strKeyName)
		: q_ptr(pNetwork)
		, m_pNetWorkRequest(Q_NULLPTR)
		, m_pNetWorkReply(Q_NULLPTR)
		, m_pNetWorkListener(Q_NULLPTR)
		, m_strKeyName(strKeyName)
		, m_pNetWorkTimeout(Q_NULLPTR)
		, m_pNetWorkAccessManager(Q_NULLPTR)
		, m_iRequestTimeoutTime(10000)
	{
	}

	NetworkPrivate::~NetworkPrivate()
	{
		SAFE_DELETE(m_pNetWorkRequest);
		SAFE_DELETE(m_pNetWorkReply);
		SAFE_DELETE(m_pNetWorkTimeout);
		SAFE_DELETE(m_pNetWorkAccessManager);
	}
}
