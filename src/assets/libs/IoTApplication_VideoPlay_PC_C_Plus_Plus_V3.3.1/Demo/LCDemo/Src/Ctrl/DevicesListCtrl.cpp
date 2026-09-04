#include "LCOpenSdk_Utils.h"
#include "DevicesListCtrl.h"

#define PNG_IMG_MAX_SIZE (1024 * 1024 * 5)

DevicesListCtrl::DevicesListCtrl(QObject* parent)
: QObject(parent)
, m_DeviceIndex(0)
, m_isLoadChannelPicEnabled(false)
{
    m_pngImgData = (unsigned char*)malloc(PNG_IMG_MAX_SIZE);
    m_CurlDownload = new (std::nothrow) CurlDownload(this);
    connect(m_CurlDownload, SIGNAL(sgnFinished(unsigned char*, unsigned int)), this, SLOT(slotCurlDownloadFinished(unsigned char*, unsigned int)));
}

DevicesListCtrl::~DevicesListCtrl()
{
    clearChannelInfoList();
	clearIOTDeviceInfoList();

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

IOTDeviceInfoList* DevicesListCtrl::getIOTChannelInfoList()
{
	return &m_IOTDeviceInfoList;
}

ChannelInfo* DevicesListCtrl::getChannelInfo(int index)
{
    if (index >= m_ChannelInfoList.size())
    {
        return NULL;
    }
    return m_ChannelInfoList.at(index);
}

IOTDeviceList* DevicesListCtrl::getIOTChannelInfo(int index)
{
	/*if (index >= m_IOTDeviceInfoList.size())
	{
		return NULL;
	}*/
	return m_IOTDeviceInfoList.at(index);
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

void DevicesListCtrl::clearIOTDeviceInfoList()
{
	for (int i = 0; i < m_IOTDeviceInfoList.size(); i++)
	{
		delete m_IOTDeviceInfoList.at(i);
	}
	m_IOTDeviceInfoList.clear();

	return;
}

void DevicesListCtrl::addViewDeviceInfo(int deviceListIndex, int channelIndex)
{
	ViewDeviceInfo info;
	info.deviceListIndex = deviceListIndex;
	info.channelIndex = channelIndex;
	m_ViewDeviceInfoList.push_back(info);
}

void DevicesListCtrl::clearViewDeviceInfoList()
{
	m_ViewDeviceInfoList.clear();
}

ViewDeviceInfo DevicesListCtrl::getViewDeviceInfo(int viewIndex)
{
	ViewDeviceInfo info;
	if (viewIndex >= 0 && viewIndex < m_ViewDeviceInfoList.size())
	{
		info = m_ViewDeviceInfoList.at(viewIndex);
	}
	else
	{
		info.deviceListIndex = -1;
		info.channelIndex = -1;
	}
	return info;
}

int DevicesListCtrl::getViewDeviceInfoCount()
{
	return m_ViewDeviceInfoList.size();
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

    m_CurlDownload->get(channel->channelPicUrl);

    return;
}

void DevicesListCtrl::slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen)
{
    /* 加此判断是为了防止设备列表被清空后引发的数组访问越界问题 */
    if (!m_isLoadChannelPicEnabled)
    {
        return;
    }

    QPixmap pixmap;

    if (NULL != data && dataLen > 0)
    {
        if (m_IOTDeviceInfoList.at(m_DeviceIndex)->platForm == 4)
        {
			const char *devID = "123456bbb";
			const char *devPwd = "admin123";
            int decryptDataLen = dataLen;
            unsigned char* decryptData = (unsigned char*)malloc(decryptDataLen);
            if (0 == LCOpenSdk_Utils::DecryptPic((char*)data, dataLen, m_IOTDeviceInfoList.at(m_DeviceIndex)->decryptKey.c_str(), devID, devPwd, (char*)decryptData, decryptDataLen))
            {
                int pngImgSize = PNG_IMG_MAX_SIZE;
                /*if (LCOpenSdk_Utils::Jpg2Png(decryptData, decryptDataLen, m_pngImgData, pngImgSize))
                {
                    pixmap.loadFromData(m_pngImgData, pngImgSize);
                }*/
            }
            free(decryptData);
            decryptData = NULL;
        } 
        else
        {
            int pngImgSize = PNG_IMG_MAX_SIZE;
            /*if (LCOpenSdk_Utils::Jpg2Png(data, dataLen, m_pngImgData, pngImgSize))
            {
                pixmap.loadFromData(m_pngImgData, pngImgSize);
            }*/
        }
    }

    emit sgnGetChannelPicFinished(m_DeviceIndex, pixmap);

    return;
}
