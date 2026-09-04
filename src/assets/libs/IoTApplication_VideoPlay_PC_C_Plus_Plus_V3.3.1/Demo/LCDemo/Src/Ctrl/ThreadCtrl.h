#ifndef THREADCTRL_H
#define THREADCTRL_H

#include <QThread>
#include "Model/ProtoType.h"
#include <QJsonObject>
#include <QJsonArray>

class ThreadCtrl : public QThread
{
    Q_OBJECT

public:
    ThreadCtrl(QObject *parent, PROTOTYPE_E type);
    ~ThreadCtrl();
	//void start() { run(); }
	void startBusiness();
    void setParamter(void *inputParam, void *outParam);
    void setProtoType(PROTOTYPE_E type);
    PROTOTYPE_E getProtoType();

protected:
    void run();

signals:
    void resultReady(int result);

signals:
	void sendDeviceRecords(QJsonObject root);

signals:
	void sendCloudRecords(QJsonObject root);


private slots:
	void slotDeviceRecords(QJsonObject root);
	void slotCloudRecords(QJsonObject root);


//connect(m_threadCtrl, SIGNAL(sendDeviceRecords(QJsonObject)), this, SLOT(slotDeviceRecords(QJsonObject)));

private:
    void *m_inputParam;
    void *m_outputparam;
    PROTOTYPE_E m_protoType;
};

#endif // THREADCTRL_H
