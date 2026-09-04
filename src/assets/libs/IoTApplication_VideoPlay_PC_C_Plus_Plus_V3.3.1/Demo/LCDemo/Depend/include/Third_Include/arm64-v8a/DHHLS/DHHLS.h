#ifndef __DAHUA_LCHLS_HLS_CLIENT_H__
#define __DAHUA_LCHLS_HLS_CLIENT_H__
#include "DHHLSDefine.h"

namespace Dahua {
namespace LCHLS {

class CHLSClientImp;

class CHLSClient {

public:
    /**
    * 构造函数
    *
    * @return void
    */
    CHLSClient();

    /**
    * 构造函数
    *
    * @return void
    */
    ~CHLSClient();

    /**
    * 初始化HLS（在调用此接口之前,其他接口均不效)
    *
    * @param para:  初始化参数，详细内容参考HlsPara
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool init(HLS_CLIENT_PARAMS *para);
    /**
    * 播放中seek操作
    *
    * @param time: seek到的时间点
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool seek(float time);

    /**
    * 开始下载/播放操作
    * @param index: 从第index个切片开始下载
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool start(int index=0);

    /**
    * 停止下载/停止播放
    *      注意：此接口为同步接口，会等待HLS库所有线程停掉以后才会返回
    *
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool stop();

    /**
    * 暂停操作
    *
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool pause();

    /**
    * 从暂停中恢复操作
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
    bool resume();

    /**
    * 获取HLS总时长
    *        注意：需要用户接收到HLS_DOWNLOAD_BEGIN后才能操作此接口
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
	int getDuration();

	/**
    * 获取HLS总时长
    *        注意：需要用户接收到HLS_DOWNLOAD_BEGIN后才能操作此接口
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
	int getTotalSlice();
    
    bool frameExtract(float FrameExtractStartTime, int FrameExtractInv);
    
    int getFrameExtractInv();


private:
    CHLSClientImp *m_HLSClientImp;

};

}
}
#endif
