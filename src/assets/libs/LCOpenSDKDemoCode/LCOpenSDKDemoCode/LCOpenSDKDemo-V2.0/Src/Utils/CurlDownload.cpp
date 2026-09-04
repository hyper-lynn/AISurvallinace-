#include "curl.h"
#include "CurlDownload.h"

#define JPG_IMG_DATA_INIT_SIZE (1024 * 1024)

CurlDownload::CurlDownload(QObject* parent)
: QThread(parent)
, m_jpgImgDataSize(0)
, m_jpgImgDataLen(0)
{
    m_jpgImgData = (unsigned char*)malloc(JPG_IMG_DATA_INIT_SIZE);
    if (NULL != m_jpgImgData)
    {
        m_jpgImgDataSize = JPG_IMG_DATA_INIT_SIZE;
    }
}

CurlDownload::~CurlDownload()
{
    if (NULL != m_jpgImgData)
    {
        free(m_jpgImgData);
        m_jpgImgData = NULL;
    }
}

void CurlDownload::get(const QString& url, const QString& deviceId)
{
    m_url = url;
	m_deviceId = deviceId;
    m_jpgImgDataLen = 0;
    if (isRunning())
    {
        quit();
    }
    start();
    return;
}

void CurlDownload::run()
{
    bool isCurlDownloadSucceed = false;

    CURL* curl = NULL;
    do 
    {
        curl = curl_easy_init();
        if (NULL == curl)
        {
            break;
        }

        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L))
        {
            break;
        }

        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10000))
        {
            break;
        }

        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlDownload::cbCurlDownload))
        {
            break;
        }

        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEDATA, this))
        {
            break;
        }

        if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, m_url.toLatin1().data()))
        {
            break;
        }

        if (CURLE_OK != curl_easy_perform(curl))
        {
            break;
        }

        isCurlDownloadSucceed = true;

    } while (0);

    curl_easy_cleanup(curl);

    if (isCurlDownloadSucceed)
    {
        emit sgnFinished(m_jpgImgData, m_jpgImgDataLen, m_deviceId);
    } 
    else
    {
        emit sgnFinished(NULL, 0, "");
    }
}

size_t CurlDownload::cbCurlDownload(void* data, size_t size, size_t count, void* pParam)
{
    CurlDownload* ins = (CurlDownload*)pParam;
    if (ins->m_jpgImgDataSize < ins->m_jpgImgDataLen + size * count)
    {
        unsigned char* newJpgImgData = (unsigned char*)malloc(ins->m_jpgImgDataLen + size * count);
        if (NULL == newJpgImgData)
        {
            return 0;
        }
        memcpy(newJpgImgData, ins->m_jpgImgData, ins->m_jpgImgDataLen);
        free(ins->m_jpgImgData);
        ins->m_jpgImgData = newJpgImgData;
        ins->m_jpgImgDataSize = ins->m_jpgImgDataLen + size * count;
    }
    memcpy(ins->m_jpgImgData + ins->m_jpgImgDataLen, data, size * count);
    ins->m_jpgImgDataLen += (size * count);
    return size * count;
}
