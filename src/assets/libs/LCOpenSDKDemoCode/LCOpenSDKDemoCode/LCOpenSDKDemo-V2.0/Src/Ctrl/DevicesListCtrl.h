#ifndef _DEVICESLISTCTRL_H_
#define _DEVICESLISTCTRL_H_

#include <QPixmap>
#include "Src/Utils/CurlDownload.h"
#include "Src/Model/ChannelsListInfo.h"

class DevicesListCtrl : public QObject
{
	Q_OBJECT

public:
	~DevicesListCtrl();
	static DevicesListCtrl* getInstance();
	ChannelInfoList* getChannelInfoList();
	ChannelInfo* getChannelInfo(int index);
	ChannelInfo* DevicesListCtrl::getChannelInfoByChannel(QString deviceID, int channel);
	void clearChannelInfoList();
	void enableLoadChannelPic(bool enabled);
	QString getDecryptKeyByDeviceID(QString deviceID);

signals:
	void sgnGetChannelPicFinished(int deviceIndex, QPixmap pixmap);

private slots:
	void slotGetChannelPic(int deviceIndex);
	void slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen, QString deviceId);

private:
	DevicesListCtrl(QObject* parent = 0);

private:
	ChannelInfoList             m_ChannelInfoList;
	CurlDownload*               m_CurlDownload;
	int                         m_DeviceIndex;  /* 获取设备列表封面图专用 */
	bool                        m_isLoadChannelPicEnabled;

	/* Jpg2Png存储Png图片数据的缓冲区 */
	unsigned char*              m_pngImgData;
};

#endif /* _DEVICESLISTCTRL_H_ */
