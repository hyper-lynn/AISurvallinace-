
#include "Network.h"
#include "NetworkTimeout.h"
#include "libdsl/DPrintLog.h"
#include "NetworkPrivate.h"
#include <QSslError>
#include <QMutex>

namespace Common
{
	QString Network::m_strAllContentType = "application/json;charset=utf-8";
	QString Network::m_strAllLanguage = "zh-CN";

	void Network::setAllContentType(QString strContentType)
	{
		m_strAllContentType = strContentType;
	}

	void Network::setAllAcceptLanguage(QString strLanguage)
	{
		m_strAllLanguage = strLanguage;
	}

	Network::Network(QString strKeyName /*= ""*/)
	{
		d_ptr = new NetworkPrivate(this, strKeyName);

		d_ptr->m_pNetWorkAccessManager = new QNetworkAccessManager(this);
		d_ptr->m_pNetWorkRequest = new QNetworkRequest();
	}

	Network::~Network()
	{
		cancleRequest();
		SAFE_DELETE(d_ptr);
	}

	void Network::setContentType(QString strContentType)
	{
		Q_D(Network);
		if (Q_NULLPTR == d->m_pNetWorkRequest)
		{
			return;
		}
		d->m_pNetWorkRequest->setRawHeader("Content-Type", strContentType.toUtf8());
	}

	void Network::setAcceptLanguage(QString strLanguage)
	{
		Q_D(Network);

		if (Q_NULLPTR == d->m_pNetWorkRequest)
		{
			return;
		}
		d->m_pNetWorkRequest->setRawHeader("Accept-Language", strLanguage.toUtf8());
	}

	void Network::setAuthorization(QString strAuthorization)
	{
		Q_D(Network);

		if (Q_NULLPTR == d->m_pNetWorkRequest)
		{
			return;
		}
		d->m_pNetWorkRequest->setRawHeader("Authorization", QString("Bearer ").toUtf8() + strAuthorization.toUtf8());
	}

	void Network::setTimeOffset(QString strTimeOffset)
	{
		Q_D(Network);

		if (Q_NULLPTR == d->m_pNetWorkRequest)
		{
			return;
		}
		d->m_pNetWorkRequest->setRawHeader("timeOffset", strTimeOffset.toUtf8());
	}

	void Network::setTimeoutTime(int iTimeoutTime)
	{
		Q_D(Network);

		d->m_iRequestTimeoutTime = iTimeoutTime;
	}

	void Network::setRequestUrl(QString strUrl)
	{
		Q_D(Network);

		if (Q_NULLPTR == d->m_pNetWorkRequest)
		{
			return;
		}
		d->m_pNetWorkRequest->setUrl(strUrl);
		if (0 == strUrl.indexOf("https://", 0, Qt::CaseInsensitive))
		{
			QSslConfiguration conf = d->m_pNetWorkRequest->sslConfiguration();
			conf.setPeerVerifyMode(QSslSocket::VerifyNone);
			conf.setProtocol(QSsl::TlsV1SslV3);
			d->m_pNetWorkRequest->setSslConfiguration(conf);
		}
	}

	int Network::getRequest()
	{
		Q_D(Network);
		d->m_buffer.clear();
		if (Q_NULLPTR == d->m_pNetWorkAccessManager)
		{
			return QNetworkReply::ConnectionRefusedError;
		}
		if (d->m_pNetWorkAccessManager->networkAccessible() == QNetworkAccessManager::NotAccessible)
		{
			d->m_pNetWorkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
			DLOG_INFO("m_pNetworkAccessManager::NotAccessible");
		}
		d->m_pNetWorkReply = d->m_pNetWorkAccessManager->get(*d->m_pNetWorkRequest);
		connect(d->m_pNetWorkReply, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(onSSLErrors(const QList<QSslError> &)));
		connect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		connect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

		setNetWorkTimeOut();
	}

	int Network::postRequest(QString strParam)
	{
		Q_D(Network);
		d->m_buffer.clear();
		if (Q_NULLPTR == d->m_pNetWorkAccessManager)
		{
			return QNetworkReply::ConnectionRefusedError;
		}
		// 设置请求头
		if (!d->m_pNetWorkRequest->hasRawHeader("Content-Type"))
		{
			d->m_pNetWorkRequest->setRawHeader("Content-Type", m_strAllContentType.toUtf8());
		}
		if (!d->m_pNetWorkRequest->hasRawHeader("Accept-Language"))
		{
			d->m_pNetWorkRequest->setRawHeader("Accept-Language", m_strAllLanguage.toUtf8());
		}
		if (!d->m_pNetWorkRequest->hasRawHeader("timeOffset"))
		{
			QDateTime currentTime = QDateTime::currentDateTime();
			//int timeOffset = 0 - currentTime.timeZone().offsetFromUtc(currentTime) * 1000;
			QDateTime utcTime(currentTime);
			utcTime.setTimeSpec(Qt::UTC);
			int offset = currentTime.secsTo(utcTime);
			int timeOffset = 0 - offset * 1000;
			d->m_pNetWorkRequest->setRawHeader("timeOffset", QString::number(timeOffset).toUtf8());
		}

		//DataCheckInfo struCheckInfo = CDataCheckTool::instance().getDataCheckInfo(strParam);
		//d->m_pNetWorkRequest->setRawHeader("Content-Signature", struCheckInfo.byteArrSign);
		//d->m_pNetWorkRequest->setRawHeader("Content-MD5", struCheckInfo.strMD5.toUtf8());
		//d->m_pNetWorkRequest->setRawHeader("timestamp", struCheckInfo.strTimestamp.toUtf8());
		//d->m_pNetWorkRequest->setRawHeader("nonce", struCheckInfo.strNonce.toUtf8());

		//TODO：测试打印
		QString url = d->m_pNetWorkRequest->url().toString(); 
		//DLOG_INFO("Network::postRequest; url:[%s],nonce:[%s],strParam:[%s]", url.toStdString().c_str(),
		//	struCheckInfo.strNonce.toStdString().c_str(), strParam.toStdString().c_str());

		if (d->m_pNetWorkAccessManager->networkAccessible() == QNetworkAccessManager::NotAccessible)
		{
			d->m_pNetWorkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
			DLOG_INFO("Network::m_pNetWorkAccessManager::NotAccessible");
		}
		d->m_pNetWorkReply = d->m_pNetWorkAccessManager->post(*d->m_pNetWorkRequest, strParam.toUtf8());
		connect(d->m_pNetWorkReply, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(onSSLErrors(const QList<QSslError> &)));
		connect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		connect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

		setNetWorkTimeOut();
	}

	int Network::postRequest(QString strParam, QMap<QString, QString> mapRawHeader)
	{
		Q_D(Network);
		d->m_buffer.clear();
		if (Q_NULLPTR == d->m_pNetWorkAccessManager)
		{
			return QNetworkReply::ConnectionRefusedError;
		}
		// 设置请求头
		for (QMap<QString, QString>::Iterator it = mapRawHeader.begin(); it != mapRawHeader.end(); it++)
		{
			d->m_pNetWorkRequest->setRawHeader(it.key().toUtf8(), it.value().toUtf8());
		}

		QString url = d->m_pNetWorkRequest->url().toString();
		//DataCheckInfo struCheckInfo = CDataCheckTool::instance().getDataCheckInfo(strParam);
		//d->m_pNetWorkRequest->setRawHeader("Content-Signature", struCheckInfo.byteArrSign);
		//d->m_pNetWorkRequest->setRawHeader("Content-MD5", struCheckInfo.strMD5.toUtf8());
		//d->m_pNetWorkRequest->setRawHeader("timestamp", struCheckInfo.strTimestamp.toUtf8());
		//d->m_pNetWorkRequest->setRawHeader("nonce", struCheckInfo.strNonce.toUtf8());

		//TODO：测试打印
		//DLOG_INFO("Network::postRequest; nonce:[%s],strParam:[%s]",
		//	struCheckInfo.strNonce.toStdString().c_str(), strParam.toStdString().c_str());

		if (d->m_pNetWorkAccessManager->networkAccessible() == QNetworkAccessManager::NotAccessible)
		{
			d->m_pNetWorkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
			DLOG_INFO("Network::m_pNetWorkAccessManager::NotAccessible");
		}
		d->m_pNetWorkReply = d->m_pNetWorkAccessManager->post(*d->m_pNetWorkRequest, strParam.toUtf8());
		connect(d->m_pNetWorkReply, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(onSSLErrors(const QList<QSslError> &)));
		connect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		connect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

		setNetWorkTimeOut();
	}

	int Network::putRequest(const QString &strParam)
	{
		Q_D(Network);
		d->m_buffer.clear();
		if (NULL == d->m_pNetWorkAccessManager)
		{
			return QNetworkReply::ConnectionRefusedError;
		}

		d->m_pNetWorkReply = d->m_pNetWorkAccessManager->put(*d->m_pNetWorkRequest, strParam.toUtf8());
		connect(d->m_pNetWorkReply, &QNetworkReply::sslErrors, this, &Network::onSSLErrors);
		connect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		connect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

		setNetWorkTimeOut();
	}

	int Network::deleteResource()
	{
		Q_D(Network);
		d->m_buffer.clear();
		if (NULL == d->m_pNetWorkAccessManager)
		{
			return QNetworkReply::ConnectionRefusedError;
		}

		d->m_pNetWorkReply = d->m_pNetWorkAccessManager->deleteResource(*d->m_pNetWorkRequest);
		connect(d->m_pNetWorkReply, &QNetworkReply::sslErrors, this, &Network::onSSLErrors);
		connect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		connect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

		setNetWorkTimeOut();
	}

	void Network::cancleRequest()
	{
		Q_D(Network);

		if (d->m_pNetWorkReply != Q_NULLPTR)
		{ //如果

			disconnect(d->m_pNetWorkReply, &QNetworkReply::sslErrors, this, &Network::onSSLErrors);
			disconnect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
			disconnect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
			disconnect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));
			if (!d->m_pNetWorkReply->isRunning())
			{
				d->m_pNetWorkReply->abort();
				d->m_pNetWorkReply->deleteLater();
			}
			d->m_pNetWorkReply = Q_NULLPTR;
		}

		d->m_buffer.clear();
	}

	void Network::onError(QNetworkReply::NetworkError error)
	{
		Q_D(Network);
		if (error == 5)
		{
			return;
		}

		cancleNetWorkTimeOut();
		DLOG_INFO("onError [%d]", error);
		if (Q_NULLPTR == d->m_pNetWorkListener)
		{
			return;
		}
		NetworkError_t struNetWorkError;
		struNetWorkError.iErrorCode = -1000;
		d->m_pNetWorkListener->onNetworkError(struNetWorkError, "onSSLError", d->m_strKeyName);
	}

	void Network::registerObject(NetworkListener *pNetWorkListener)
	{
		Q_D(Network);

		d->m_pNetWorkListener = pNetWorkListener;
	}

	void Network::deregisterObject()
	{
		Q_D(Network);

		d->m_pNetWorkListener = Q_NULLPTR;
	}

	QList<QNetworkReply::RawHeaderPair> Network::getRawHeaderPairs()
	{
		Q_D(Network);

		if (Q_NULLPTR != d->m_pNetWorkReply)
		{
			return d->m_pNetWorkReply->rawHeaderPairs();
		}
		return QList<QNetworkReply::RawHeaderPair>();
	}

	void Network::onNetWorkTimeOut()
	{
		Q_D(Network);

		cancleRequest();
		if (Q_NULLPTR == d->m_pNetWorkListener)
		{
			return;
		}
		NetworkError_t struNetWorkError;
		struNetWorkError.iErrorCode = -1001;
		DLOG_INFO("zjnTest here before onNetWorkTimeOut m_strKeyName[%s]", d->m_strKeyName.toStdString().c_str());
		d->m_pNetWorkListener->onNetworkError(struNetWorkError, "onNetworkTimeOut", d->m_strKeyName);
	}

	void Network::onSSLErrors(const QList<QSslError> &errors)
	{
		Q_D(Network);

		cancleNetWorkTimeOut();
		DLOG_ERR("onSSLErrors [%d] [%s]", errors[0].error(), errors[0].errorString().toStdString().c_str());
		if (Q_NULLPTR == d->m_pNetWorkListener)
		{
			return;
		}
		NetworkError_t struNetWorkError;
		struNetWorkError.iErrorCode = -1000;
		d->m_pNetWorkListener->onNetworkError(struNetWorkError, "onSSLError", d->m_strKeyName);
	}

	void Network::onReadyRead()
	{
		Q_D(Network);

		cancleNetWorkTimeOut();

		if (Q_NULLPTR == d->m_pNetWorkReply)
		{
			return;
		}

		if (Q_NULLPTR == d->m_pNetWorkListener)
		{
			return;
		}

		QByteArray buffer = d->m_pNetWorkReply->readAll();
		QString strKeyName = d->m_strKeyName;
		QByteArray nonce = d->m_pNetWorkReply->rawHeader("nonce");
		//TODO：测试打印
		DLOG_INFO("Network::onReadyRead; url:[%s],nonce:[%s],m_buffer:[%s]", 
			d->m_pNetWorkReply->url().toString().toStdString().c_str(),
			nonce.toStdString().c_str(), buffer.toStdString().c_str());

		d->m_buffer.append(buffer);
	}

	void Network::onFinished()
	{
		Q_D(Network);

		cancleNetWorkTimeOut();

		if (Q_NULLPTR == d->m_pNetWorkReply)
		{
			return;
		}

		if (Q_NULLPTR == d->m_pNetWorkListener)
		{
			doDestoryReplay();
			return;
		}

		if (d->m_pNetWorkReply->error() != QNetworkReply::NoError)
		{
			if (d->m_pNetWorkReply->error() == 5)
			{
				doDestoryReplay();
				return;
			}

			QString strError = d->m_pNetWorkReply->errorString();
			int iError = d->m_pNetWorkReply->error(); // 得到内部错误码
			int iHttpStatue = d->m_pNetWorkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); // 得到http头
			NetworkError_t struNetWorkError;
			struNetWorkError.iErrorCode = iError;
			struNetWorkError.iHttpStatusCode = iHttpStatue;
			DLOG_ERR("Network::onFinished getError[%d]", d->m_pNetWorkReply->error());
			d->m_pNetWorkListener->onNetworkError(struNetWorkError, strError, d->m_strKeyName);

			if (NetworkHelper::instance().getGlobalDealwithObj() == NULL)
			{
				doDestoryReplay();

				return;
			}

			NetworkHelper::instance().getGlobalDealwithObj()->onNetworkRequestError(struNetWorkError, strError, d->m_strKeyName);

			doDestoryReplay();
			return;
		}
		else
		{
			d->m_pNetWorkListener->onNetworkDataCallBack(d->m_buffer, d->m_strKeyName);
			d->m_pNetWorkListener->onNetworkFinished(d->m_strKeyName);
		}

		doDestoryReplay();
	}

	void Network::setNetWorkTimeOut()
	{
		Q_D(Network);

		cancleNetWorkTimeOut();
		d->m_pNetWorkTimeout = new NetworkTimeOut(d->m_iRequestTimeoutTime);
		connect(d->m_pNetWorkTimeout, SIGNAL(timeout()), this, SLOT(onNetWorkTimeOut()));
	}

	void Network::cancleNetWorkTimeOut()
	{
		Q_D(Network);

		if (Q_NULLPTR != d->m_pNetWorkTimeout)
		{
			d->m_pNetWorkTimeout->stopTimer();
			disconnect(d->m_pNetWorkTimeout, SIGNAL(timeout()), this, SLOT(onNetWorkTimeOut()));
			SAFE_DELETE(d->m_pNetWorkTimeout);
		}
	}

	void Network::doDestoryReplay()
	{
		Q_D(Network);

		if (d->m_pNetWorkReply != Q_NULLPTR)
		{
			disconnect(d->m_pNetWorkReply, &QNetworkReply::sslErrors, this, &Network::onSSLErrors);
			disconnect(d->m_pNetWorkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
			disconnect(d->m_pNetWorkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
			disconnect(d->m_pNetWorkReply, SIGNAL(finished()), this, SLOT(onFinished()));

			d->m_pNetWorkReply->abort();
			d->m_pNetWorkReply->deleteLater();
			d->m_pNetWorkReply = Q_NULLPTR;
		}
	}

	NetworkHelper & NetworkHelper::instance()
	{
		static std::auto_ptr<NetworkHelper> s_ptrInstance;
		static QMutex m_mutexInstance;

		if (s_ptrInstance.get() == Q_NULLPTR)
		{
			// 避免创建两个
			QMutexLocker locker(&m_mutexInstance);
			// 多线程保护
			if (s_ptrInstance.get() == Q_NULLPTR)
			{
				s_ptrInstance = std::auto_ptr<NetworkHelper>(new NetworkHelper);
			}
		}

		return *s_ptrInstance.get();
	}
	void NetworkHelper::setGlobalDealwithObj(NetworkHelperListener *pObj)
	{
		m_pGlobalDealwithObj = pObj;
	}
	NetworkHelperListener * NetworkHelper::getGlobalDealwithObj()
	{
		return m_pGlobalDealwithObj;
	}
	NetworkHelper::NetworkHelper()
		: m_pGlobalDealwithObj(Q_NULLPTR)
	{
	}
}

