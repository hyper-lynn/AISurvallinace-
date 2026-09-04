#pragma once
#include "Network/Network.h"
namespace Common
{
	 
	class NetworkPrivate
	{
	public:
		NetworkPrivate(Network *pNetwork, QString strKeyName);
		~NetworkPrivate();
	private:
		QNetworkAccessManager*		m_pNetWorkAccessManager;
		QNetworkRequest*			m_pNetWorkRequest;
		QNetworkReply*				m_pNetWorkReply;

		NetworkTimeOut*				m_pNetWorkTimeout;

		NetworkListener*			m_pNetWorkListener;
		QString						m_strKeyName;
		int							m_iRequestTimeoutTime;
		QByteArray					m_buffer;
		Network *q_ptr;
		Q_DECLARE_PUBLIC(Network)
	};
}
