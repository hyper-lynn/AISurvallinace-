#ifndef _LCOPENSDK_VIDEOPLAY_H_
#define _LCOPENSDK_VIDEOPLAY_H_

#include "lcopensdk_global.h"
#include "LCOpenSDK_PlayerListener.h"
#include "LCOpenSDK_Param.h"
#include "lcopensdk_api/LCOpenSDK_Define.h"

class LCOPENSDK_EXPORT LCOpenSDK_VideoPlay
{
public:

/* 输出的标准流格式 */
typedef enum
{
    OUTPUT_STREAM_FORMAT_NULL = 0,
    OUTPUT_STREAM_FORMAT_PS,
    OUTPUT_STREAM_FORMAT_TS,
    OUTPUT_STREAM_FORMAT_LCAV,
}OUTPUT_STREAM_FORMAT;


/* 解码类型 */
typedef enum
{
	DECORD_TYPE_NOTSET = 0, /* 未设置,默认硬解 */
	DECORD_TYPE_SW,/* 软解 */
	DECORD_TYPE_HW,/* 硬解码拷贝模式(如使用windows平台，使用d3d9接口) */
	DECORD_TYPE_FAST,/* 硬解码直接显示模式(如使用windows平台，使用d3d9接口) */
}DECORD_TYPE;

/* 局部放大区域 */
typedef struct RECT
{
	long left;								
	long top;								
	long right;								
	long bottom;							
}DISPLAY_RECT;

public:
    LCOpenSDK_VideoPlay();
    ~LCOpenSDK_VideoPlay();

    int initVideoPlay(int index, void* hWnd);
	int updatePlayhWnd(int index, void* hWnd);

    void uninitVideoPlay();
    /**
	 * 设置解码类型
	 */
	void setEngine(DECORD_TYPE decordType);
    void setPlayerListener(LCOpenSDK_PlayerListener* playerListener);
    LCOpenSDK_PlayerListener* getPlayerListener();

    /**
     * 设置标准流回调
     *
     * @param streamFormat [IN] 输出的标准流格式，OUTPUT_STREAM_FORMAT_NULL表示关闭标准流回调
     *
     */
    void setStreamCallback(OUTPUT_STREAM_FORMAT streamFormat);

    int playRtspReal(const char* token, const char* deviceID, const char* decryptKey, int channelID, int definitionMode, bool isOpt);
    int playRtspRealEx1(const char* token, const char* deviceID, const char* decryptKey, int channelID, int definitionMode, bool assistStream, bool isOpt);
    int stopRtspReal();
    int playDeviceRecord(const char* token, const char* deviceID, const char* decryptKey, int channelID, const char* fileID, int beginTime, int endTime, int offsetTime, bool isOpt);
    int playDeviceRecordByFileName(const char* token, const char* deviceID, const char* decryptKey, const char* fileID, double offsetTime, bool isOpt);
    int playDeviceRecordByUtcTime(const char* token, const char* deviceID, const char* decryptKey, int channelID, int beginTime, int endTime, int definitionMode, bool isOpt, double offsetTime);
    int stopDeviceRecord();
    int playCloud(const char* token, const char* deviceID, int channelID, const char* decryptKey, const char* recordRegionID, int offsetTime, int cloudRecordType, int timeout);
    int stopCloud();
	int playFile(const char *filePath);
	int stopFile();
	int setPlaySpeed(float speed);
    int playAudio();
    int stopAudio();
    int seek(long seconds);
    int pause();
    int resume();
    int snapShot(const char* filePath);
    int startRecord(const char* filePath);
    int stopRecord();

	/**
	 * 新接口(建议使用新接口，老接口不在维护);
	 */
	int playRtspRealEx(LCOpenSDK_ParamReal *paramReal);  
	int playDeviceRecordByFileNameEx(LCOpenSDK_ParamDeviceRecordFileName *paramDevRecord);
    int playDeviceRecordByUtcTimeEx(LCOpenSDK_ParamDeviceRecordUTCTime *paramDevRecord);
	int playCloudEx(LCOpenSDK_ParamCloudRecord *paramCloud);
	//云台操控优化接口
	int controlMovePTZ(LCOpenSDK_ParamControlPTZ *paramControlPTZ);

	/**
	 * 设置或增加显示区域，可以做局部放大显示。
	 *
	 * @param[in] srcRect 局部显示区域
	 * @param[in] enable 打开(设置)或关闭显示区域
	 * @return BOOL，成功返回TRUE，失败返回FALSE
	*/
	bool setDisplayRegion(DISPLAY_RECT *srcRect, bool enable);
	 /**
    * 设置播放（对讲）码流保存路径
    * @param   [in] const char * saveStreamPath     默认为空
     * @return  int                                  0/非0 成功/失败
    */
    int setSaveStreamPath(const char* saveStreamPath=NULL);

	/**
    * 获取当前拉流类型
    * @return  LCOpenSDK_STREAM_MODE        当前拉流类型(参考LCOpenSDK_STREAM_MODE定义)
    * @note  建议该接口在收到OnPlayerBegan回调后调用(否则获取的状态未确定)
    */
	LCOpenSDK_STREAM_MODE getCurrentStreamMode();

	/**
    * 获取埋点数据
    */
	const char* getAnalysisData(int *len);
	
	/**
	* 创建同步播放组
	*/
	static void* createPlayGroup();

	/**
	* 同步播放组添加播放源
	* groupid 同步播放组对象
	* isGroupBase 是否是基准
	*/
	bool addToPlayGroup(void* groupid, bool isGroupBase);
	
	/**
     * 以共享方式打开声音
     * @param bOpen [in] 是否开启 true:开启  false:关闭
     */
	bool controlSoundShare(bool bOpen);

private:
    void* m_interfaceLock;
    void* m_hLCOpenSDK_VideoPlay_Inside;
};

#endif /* _LCOPENSDK_VIDEOPLAY_H_ */
