#include "lcopensdk_utils/LCOpenSdk_Utils.h"
#include "DevicesListCtrl.h"
#include "OpenApiCtrl.h"
#include "qbytearray.h"

#define PNG_IMG_MAX_SIZE (1024 * 1024 * 5)

DevicesListCtrl::DevicesListCtrl(QObject* parent)
	: QObject(parent)
	, m_DeviceIndex(0)
	, m_isLoadChannelPicEnabled(false)
{
	m_pngImgData = (unsigned char*)malloc(PNG_IMG_MAX_SIZE);
	m_CurlDownload = new (std::nothrow) CurlDownload(this);
	connect(m_CurlDownload, SIGNAL(sgnFinished(unsigned char*, unsigned int, QString)), this, SLOT(slotCurlDownloadFinished(unsigned char*, unsigned int, QString)));
}

DevicesListCtrl::~DevicesListCtrl()
{
	clearChannelInfoList();

	if (NULL != m_CurlDownload)
	{
		delete m_CurlDownload;
		m_CurlDownload = NULL;
	}

	if (NULL != m_pngImgData)
	{
		free(m_pngImgData);
		m_pngImgData = NULL;
	}
}

DevicesListCtrl* DevicesListCtrl::getInstance()
{
	static DevicesListCtrl instance;
	return &instance;
}

ChannelInfoList* DevicesListCtrl::getChannelInfoList()
{
	return &m_ChannelInfoList;
}

ChannelInfo* DevicesListCtrl::getChannelInfo(int index)
{
	if (index >= m_ChannelInfoList.size())
	{
		return NULL;
	}
	return m_ChannelInfoList.at(index);
}

ChannelInfo* DevicesListCtrl::getChannelInfoByChannel(QString deviceID, int channel)
{
	for (int i = 0; i < m_ChannelInfoList.size(); i++)
	{
		if (m_ChannelInfoList[i]->deviceId == deviceID &&
			m_ChannelInfoList[i]->channelId == channel)
		{
			return m_ChannelInfoList[i];
		}
	}
	
	return NULL;
}

void DevicesListCtrl::clearChannelInfoList()
{
	for (int i = 0; i < m_ChannelInfoList.size(); i++)
	{
		delete m_ChannelInfoList.at(i);
	}
	m_ChannelInfoList.clear();

	return;
}

void DevicesListCtrl::enableLoadChannelPic(bool enabled)
{
	m_isLoadChannelPicEnabled = enabled;
}

QString DevicesListCtrl::getDecryptKeyByDeviceID(QString deviceID)
{
	QString ret;

	for (int i = 0; i < m_ChannelInfoList.size(); i++)
	{
		if (deviceID == m_ChannelInfoList.at(i)->deviceId)
		{
			ret = m_ChannelInfoList.at(i)->decryptKey;
			break;
		}
	}

	return ret;
}

void DevicesListCtrl::slotGetChannelPic(int deviceIndex)
{
	if (deviceIndex >= m_ChannelInfoList.size())
	{
		return;
	}

	ChannelInfo* channel = m_ChannelInfoList.at(deviceIndex);
	if (NULL == channel)
	{
		return;
	}

	m_DeviceIndex = deviceIndex;

	m_CurlDownload->get(channel->channelPicUrl, "");

	return;
}

void DevicesListCtrl::slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen, QString deviceId)
{
	/* 加此判断是为了防止设备列表被清空后引发的数组访问越界问题 */
	if (!m_isLoadChannelPicEnabled)
	{
		return;
	}

	QPixmap pixmap;

	if (NULL != data && dataLen > 0)
	{
		if (m_ChannelInfoList.at(m_DeviceIndex)->accessType == "PaaS")
		{
			int decryptDataLen = dataLen;
			unsigned char* decryptData = (unsigned char*)malloc(decryptDataLen);
			std::string decryptKey = (m_ChannelInfoList.at(m_DeviceIndex)->decryptKey).toLatin1().data();
			std::string deviceId = (m_ChannelInfoList.at(m_DeviceIndex)->deviceId).toLatin1().data();
			std::string token = OpenApiCtrl::getInstance()->getToken().toLatin1().data();

			if (0 == LCOpenSdk_Utils::DecryptPicEx((char*)data, dataLen, decryptKey.c_str(), token.c_str(), deviceId.c_str(), (char*)decryptData, decryptDataLen))
			{
				int pngImgSize = PNG_IMG_MAX_SIZE;
				pixmap.loadFromData(decryptData, decryptDataLen, "JPG");
			}
			free(decryptData);
			decryptData = NULL;
		}
		else
		{
			int pngImgSize = PNG_IMG_MAX_SIZE;
			pixmap.loadFromData(m_pngImgData, pngImgSize);
		}
	}

	emit sgnGetChannelPicFinished(m_DeviceIndex, pixmap);

	return;
}
