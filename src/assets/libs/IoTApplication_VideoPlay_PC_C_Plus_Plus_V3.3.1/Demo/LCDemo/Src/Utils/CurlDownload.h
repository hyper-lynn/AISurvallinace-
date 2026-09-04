#ifndef _CURLDOWNLOAD_H_
#define _CURLDOWNLOAD_H_

#include <QString>
#include <QThread>

class CurlDownload : public QThread
{
    Q_OBJECT

public:
    CurlDownload(QObject* parent = 0);
    ~CurlDownload();
    void get(const QString& url);

protected:
    virtual void run();

private:
    static size_t cbCurlDownload(void* data, size_t size, size_t count, void* pParam);

private:
    QString                     m_url;
    unsigned char*              m_jpgImgData;
    unsigned int                m_jpgImgDataSize;
    unsigned int                m_jpgImgDataLen;

signals:
    void sgnFinished(unsigned char* data, unsigned int dataLen);
};

#endif /* _CURLDOWNLOAD_H_ */
