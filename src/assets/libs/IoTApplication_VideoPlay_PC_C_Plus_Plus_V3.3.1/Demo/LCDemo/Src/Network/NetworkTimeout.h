/*
* Copyright (c) 2008, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CNetWorkTimeout.h
* 文件标识：
* 摘 要：类型定义
* C++编程规范

* 当前版本：1.0
* 原作者 ：王笑笑
* 完成日期：2021年2月24日
* 修订记录：创建
*/

#ifndef COMMONBUSINESS_NETWORK_TIMEOUT_H
#define COMMONBUSINESS_NETWORK_TIMEOUT_H

#include <QObject>
class QTimer;
class NetworkTimeOut : public QObject
{
	Q_OBJECT

public:
	NetworkTimeOut(const int timeout);
	~NetworkTimeOut();
	void stopTimer();
signals:
	// 超时信号 - 供进一步处理
	void timeout();

	private slots:
	//超时处理
	void onTimeout();
private:
	void startTimer();

private:
	QTimer*				m_pTimer;
	int					m_iOuttime;
};

#endif //COMMONBUSINESS_NETWORK_TIMEOUT_H