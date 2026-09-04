#ifndef THREADCTRL_H
#define THREADCTRL_H

#include <QThread>
#include "Src/Model/ProtoType.h"

class ThreadCtrl : public QThread
{
    Q_OBJECT

public:
    ThreadCtrl(QObject *parent, PROTOTYPE_E type);
    ~ThreadCtrl();
    void setParamter(void *inputParam, void *outParam);
    void setProtoType(PROTOTYPE_E type);
    PROTOTYPE_E getProtoType();

protected:
    void run();

signals:
    void resultReady(int result);

private:
    void *m_inputParam;
    void *m_outputparam;
    PROTOTYPE_E m_protoType;
};

#endif // THREADCTRL_H
