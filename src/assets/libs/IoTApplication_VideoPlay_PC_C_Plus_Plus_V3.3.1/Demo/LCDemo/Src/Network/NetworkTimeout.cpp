#include "libdsl/dslbase.h"
#include "NetworkTimeOut.h"
#include <QObject>
#include <QTimer>
#include <QNetworkReply>

NetworkTimeOut::NetworkTimeOut(const int timeout)
	: m_pTimer(nullptr)
	, m_iOuttime(timeout)
{
	startTimer();
}

NetworkTimeOut::~NetworkTimeOut()
{
	stopTimer();
	SAFE_DELETE(m_pTimer);
}

void NetworkTimeOut::startTimer()
{
	if (nullptr == m_pTimer)
	{
		m_pTimer = new QTimer();
		connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	}
	stopTimer();
	m_pTimer->start(m_iOuttime);
}

void NetworkTimeOut::stopTimer()
{
	if (nullptr != m_pTimer)
		//&& m_pTimer->isActive())
	{
		//	DLOG_INFO("zjnTest here stopTimer m_pTimer->stop");
		m_pTimer->stop();
	}
}

void NetworkTimeOut::onTimeout()
{
	// ¥¶¿Ì≥¨ ±
	stopTimer();
	emit timeout();
}
