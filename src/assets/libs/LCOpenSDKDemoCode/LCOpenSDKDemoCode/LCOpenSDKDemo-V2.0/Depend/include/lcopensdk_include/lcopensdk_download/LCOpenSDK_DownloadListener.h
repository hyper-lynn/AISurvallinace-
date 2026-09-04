#ifndef _LCOPENSDK_DOWNLOADLISTENER_H_
#define _LCOPENSDK_DOWNLOADLISTENER_H_

class LCOpenSDK_DownloadListener
{
public:
    virtual ~LCOpenSDK_DownloadListener(){};

    /**
     * 数据长度回调
     *
     * @param index   [in] 下载索引号
     * @param datalen [in] 数据长度
     *
     */
    virtual void onDownloadReceiveData(int index, int datalen) = 0;

    /**
     * 状态回调
     *
     * @param index       [in] 下载索引号
     * @param code        [in] 错误码
     * @param type        [in] 错误类型
     *
     */
    virtual void  onDownloadState(int index, const char* code, int type) = 0;

};

#endif /* _LCOPENSDK_DOWNLOADLISTENER_H_ */
