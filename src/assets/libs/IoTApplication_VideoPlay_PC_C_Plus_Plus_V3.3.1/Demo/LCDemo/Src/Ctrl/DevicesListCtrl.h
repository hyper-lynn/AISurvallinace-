#ifndef _DEVICESLISTCTRL_H_
#define _DEVICESLISTCTRL_H_

#include <QPixmap>
#include <QVector>
#include "Utils/CurlDownload.h"
#include "Model/ChannelsListInfo.h"

class DevicesListCtrl : public QObject
{
    Q_OBJECT

public:
    ~DevicesListCtrl();
    static DevicesListCtrl* getInstance();
    ChannelInfoList* getChannelInfoList();
	IOTDeviceInfoList* getIOTChannelInfoList();
    ChannelInfo* getChannelInfo(int index);
	IOTDeviceList* getIOTChannelInfo(int index);
	// DEVICE_INFO* getDeviceInfo(int index);
    void clearChannelInfoList();
	void clearIOTDeviceInfoList();
    void enableLoadChannelPic(bool enabled);
    QString getDecryptKeyByDeviceID(QString deviceID);

	/** View index mapping: get device index and channel index by view index */
	void addViewDeviceInfo(int deviceListIndex, int channelIndex);
	void clearViewDeviceInfoList();
	ViewDeviceInfo getViewDeviceInfo(int viewIndex);
	int getViewDeviceInfoCount();

signals:
    void sgnGetChannelPicFinished(int deviceIndex, QPixmap pixmap);

private slots:
    void slotGetChannelPic(int deviceIndex);
    void slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen);

private:
    DevicesListCtrl(QObject* parent = 0);

private:
    ChannelInfoList             m_ChannelInfoList;
	IOTDeviceInfoList			m_IOTDeviceInfoList;
	// DeviceInfoList				m_DeviceInfoList;
	QVector<ViewDeviceInfo>     m_ViewDeviceInfoList;  /** viewIndex -> (deviceListIndex, channelIndex) */
    CurlDownload*               m_CurlDownload;
    int                         m_DeviceIndex;  /* 获取设备列表封面图专用 */
    bool                        m_isLoadChannelPicEnabled;

    /* Jpg2Png存储Png图片数据的缓冲区 */
    unsigned char*              m_pngImgData;
};

#endif /* _DEVICESLISTCTRL_H_ */
