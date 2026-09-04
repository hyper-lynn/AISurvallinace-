/*
* Copyright (c) 2008, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CNetWork.h
* 文件标识：
* 摘 要：提供通用方法
* C++编程规范

* 当前版本：1.0
* 原作者 ：王笑笑
* 完成日期：2021年1月29日
* 修订记录：创建
*/

#ifndef COMMONBUSINESS_NETWORK_H
#define COMMONBUSINESS_NETWORK_H

#include <QObject>
#include <QNetWorkAccessManager>
#include <QNetWorkReply>

class NetworkTimeOut;
namespace Common
{
	class Network;
	//网络请求组件
	typedef struct NetworkCom
	{
		Network*		pNetwork;		//网络交互对象
		QByteArray		byteRespone;	//网络响应数据
		int				iReConnectNum;  //网络重连次数
		NetworkCom()
		{
			pNetwork = nullptr;
			byteRespone = QByteArray();
			iReConnectNum = 0;
		}

	}NetworkCom_t;

	typedef struct NetworkError
	{
		int iErrorCode;
		int iHttpStatusCode;

		NetworkError()
		{
			iErrorCode = 0;
			iHttpStatusCode = 0;
		}

	}NetworkError_t;
	Q_DECLARE_METATYPE(NetworkError_t);

	class  NetworkListener
	{
		public :
			virtual void onNetworkDataCallBack(QByteArray, QString strKeyName = "") = 0;
			virtual void onNetworkFinished(QString strKeyName = "") = 0;
			/*
			* iErrorCode = -1000 SSL错误，-1001 请求超时，
			*/
			virtual void onNetworkError(NetworkError_t, QString, QString strKeyName = "") = 0;
			
	};

	class NetworkPrivate;
	class  Network : public QObject
	{
		Q_OBJECT
		public :
			/*
			* 全局设置请求头Content-Type内容
			*/
			 static void setAllContentType(QString strContentType);
			/*
			* 全局设置请求头Accept-Language内容
			*/
			static void setAllAcceptLanguage(QString strLanguage);
			/*
			* 全局设置请求头timeOffset内容
			*/
			static void setAllTimeOffset(QString strTimeOffset);

			Network(QString strKeyName = "");
			
			~Network();
			/*
			* 设置请求头Content-Type内容
			*/
			void setContentType(QString strContentType);
			/*
			* 设置请求头Accept-Language内容
			*/
			void setAcceptLanguage(QString strLanguage);
			/*
			* 设置请求头Authorization内容
			*/
			void setAuthorization(QString strAuthorization);
			/*
			* 设置请求头timeOffset内容
			*/
			void setTimeOffset(QString strTimeOffset);
			/*
			* 设置超时时间
			*/
			void setTimeoutTime(int iTimeoutTime);
			/*
			* 设置请求Url
			*/
			void setRequestUrl(QString strUrl);
			/*
			* 进行get请求
			*/
			int getRequest();
			/*
			* 进行post请求
			*/
			int postRequest(QString strParam);
			/*
			* 进行post请求，自定义头信息
			*/
			int postRequest(QString strParam, QMap<QString, QString> mapRawHeader);
			/*
			进行put请求
			*/
			int putRequest(const QString &strParam);
			/*
			进行deleteResource请求
			*/
			int deleteResource();
			/*
			* 取消网络请求
			*/
			void cancleRequest();
			/*
			* 注册监听者
			*/
			void registerObject(NetworkListener*);
			/*
			* 撤销注册
			*/
			void deregisterObject();

			QList<QNetworkReply::RawHeaderPair> getRawHeaderPairs();

		protected slots:
			void onNetWorkTimeOut();
			void onSSLErrors(const QList<QSslError> &errors);
			void onReadyRead();
			void onFinished();
			void onError(QNetworkReply::NetworkError);

		private:
			void setNetWorkTimeOut();
			void cancleNetWorkTimeOut();
			void doDestoryReplay();
		private:


			static QString				m_strAllContentType;
			static QString				m_strAllLanguage;

			NetworkPrivate* d_ptr;
			Q_DECLARE_PRIVATE(Network)
	};

	class NetworkHelperListener
	{
	public:
		virtual void onNetworkRequestError(NetworkError_t, QString, QString strKeyName = "") = 0;
	};

	class NetworkHelper
	{
	public:
		 static NetworkHelper& instance();

		 void setGlobalDealwithObj(NetworkHelperListener*);

		 NetworkHelperListener* getGlobalDealwithObj();

	protected:
		NetworkHelper();
	private:
		NetworkHelperListener*		m_pGlobalDealwithObj;
	};
}


#endif // !COMMONBUSINESS_NETWORK_H
