#ifndef _LCOPENSDK_VIDEOPLAY_H_
#define _LCOPENSDK_VIDEOPLAY_H_

#include "lcopensdk_global.h"
#include "LCOpenSDK_Define.h"
#include "LCOpenSDK_PlayerListener.h"

class LCOPENSDK_EXPORT LCOpenSDK_VideoPlay
{
public:

/* 输出的标准流格式 */
typedef enum
{
    OUTPUT_STREAM_FORMAT_NULL = 0,
    OUTPUT_STREAM_FORMAT_PS,
    OUTPUT_STREAM_FORMAT_TS,
    OUTPUT_STREAM_FORMAT_DHAV,
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

	void setIndex(int index);
	int getIndex() const;

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

    int playRtspReal(const char* token, const char* deviceID, const char* decryptKey, int channelID, int definitionMode, bool isOpt, const char* playInfo, bool isTryP2P);
    int playRtspRealEx1(const char* token, const char* deviceID, const char* decryptKey, int channelID, int definitionMode, bool assistStream, bool isOpt, const char* playInfo, bool isTryP2P);
    int stopRtspReal();
    int playDeviceRecord(const char* token, const char* deviceID, const char* decryptKey, int channelID, const char* fileID, int beginTime, int endTime, int streamType, const char* playInfo, bool isTryP2P);
    int playDeviceRecordByFileName(const char* token, const char* deviceID, const char* decryptKey, const char* fileID, int offsetTime, bool isOpt);
    int playDeviceRecordByUtcTime(const char* token, const char* deviceID, const char* decryptKey, int channelID, int beginTime, int endTime, int definitionMode, bool isOpt);
    int stopDeviceRecord();
    int playCloud(const char* deviceID, int channelID, const char* decryptKey, const char* recordId, int offsetTime, const char* playInfo, const char* signatureUrl, const char* recordPath, const char* recordRegionId);
	int stopCloud();
	int playFile(const char *filePath);
	int stopFile();
	int setPlaySpeed(float speed);
	float getPlaySpeed();
    int playAudio();
    int stopAudio();
    int seek(long seconds);
    int pause();
    int resume();
    int snapShot(const char* filePath);
    int startRecord(const char* filePath, int recordType, long long spaceRemain = 0xFFFFFFFF, int convertMode = 1);
    int stopRecord();
	bool isRecording();
	int rewake();

	/**
	 * 设置或增加显示区域，可以做局部放大显示。
	 *
	 * @param[in] srcRect 局部显示区域
	 * @param[in] enable 打开(设置)或关闭显示区域
	 * @return BOOL，成功返回TRUE，失败返回FALSE
	*/
	bool setDisplayRegion(DISPLAY_RECT *srcRect, bool enable);
	bool setDisplayRegion(int regionNum, void* view, bool bEnable);


	/**
	 * 播放
	 * @param[in] jsonString 播放参数，json格式，不同类型，json串不同，具体参见协议
	 * @return int，成功返回0，失败返回非0
	 */
	int playWithJsonString(const char* jsonString);
	int playBrotherWithJsonString(int baseIndex, const char* jsonString);

	/**
	 * @param[in] yesOrNo 是否需要通过决策服务获取走p2p策略
	 */
	//void isUseReportSvr(bool yesOrNo);

	/**
	 * @return E_STREAM_MODE ,返回当前拉流类型，参见E_STREAM_MODE
	 */
	Dahua::LCOpenSDK::E_STREAM_MODE getCurrentStreamMode();

	void stopPlay();

	bool enableFishEye();
	void disableFishEye();
	bool startFishEye(float x, float y);
	void doingFishEye(float x, float y);
	bool endFishEye();

	/**
	 * @param[in]	mode[-1,0,1,2,3,4],
					 -1不进行噪声消除
					0噪声消除程度最低，对有用语音信号的损害最小
					4噪声消除程度最大，对有用语音信号的损害最大
	 * @return  
	 */
	bool setSEnhanceMode(int mode);

	/**
	 * 设置PlaySDK播放延迟时间
	 * @param[in] startTime,开始播放时间，ms
	 * @param[in] SlowTime 开始慢放的时间，ms
	 * @param[in] FastTime 开始快放的时间，ms
	 * @param[in] 超过此时间投递数据失败，ms
	 */
	void setPlayMethod(int startTime, int slowTime, int fastTime, int failedTime);

	void playNextFrame();

	void playContinuousFrame();

	bool fishEyeSetOptInfo(int installMode, int correctMode);


	typedef struct LCOPEN_FISHEYE_POINT2D_s
	{
		short x;
		short y;
	}LCOpenFishEyePoint2d;
	typedef struct SUBWINDOWINFO_S
	{
		int subWinNum;
		int subWin_UpLeftX;
		int subWin_UpLeftY;
		int subWin_H;
		int subWin_W;
	}LCOpenSubWindowInfo;
	/**
     * 鱼眼获取画线信息 
	 * @param [in] winType 窗口类型：0鱼眼圆，1全景，2子窗口 
	 * @param [in] winId 窗口序号：从0开始，从左至右， 从上至下 
	 * @param [in] screenResolutionH：想要得到的屏幕输出分辨率H 
	 * @param [in] screenResolutionW: 想要得到的屏幕输出分辨率W
	 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线 大小为160*2（int）,SLCOPenFishEyePoint2d
	 * @param [out] pSubWinCoordinate: 子窗口坐标，用于绘制子窗口边框 大小为9*5（int）,SLCOPenSubWindowInfo
     * 
	 * @return 获取坐标是否成功 
	 * - false: 失败 
	 * - true: 成功
	 */
	bool fishEyeGetOptInfo(int winType, int winId, int screenResolutionH, int screenResolutionW, LCOpenFishEyePoint2d* pFishEyeCoordinate, LCOpenSubWindowInfo* pSubWinCoordinate);

	/**
     * 鱼眼检查指定点是否在子窗口内 
	 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下 
	 * @param [in] pointX 指定点的横坐标 
	 * @param [in] pointY 指定点的纵坐标 
	 * 
     * @return 点是否在指定子窗口内 
	 * - false: 不在指定子窗口内
	 * - true：在指定子窗口内 
     */
	bool fishEyeCheckPointPosition(int winId, int pointX, int pointY);

	/**
    * 鱼眼拖动画面功能
	* @param [in] winType 窗口类型：0鱼眼圆，1全景，2子窗口 
	* @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下 
	* @param [in] OffsetX 拖拽的横向偏移长度 
	* @param [in] OffsetY 拖拽的纵向便宜长度 
	* @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线 SLCOPenFishEyePoint2d
	*
	* @return 拖拽是否成功 
	* - flase：拖拽失败 
	* - true：拖拽成功
	*/
	bool fishEyeDragPic(int winType, int winId, int OffsetX, int OffsetY, LCOpenFishEyePoint2d* pFishEyeCoordinate);

	/**
	 * 鱼眼移动功能
	 * @param [in] moveDirection 0左移 1右移 2上移 3下移
	 * @param [in] moveRange  壁装全景移动1~180*128  地装顶装全景移动范围1~360*128 (移动方向需要和安装模式对应)
	 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
	 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
	 *
	 * @return 操作是否成功
	 * - flase：操作失败
	 * - true：操作成功
	 */
	bool fishEyeMove(int moveDirection, int moveRange, int winId, LCOpenFishEyePoint2d* pFishEyeCoordinate);

	/**
 	* 鱼眼放大缩小功能
 	* @param [in] operateMode 0放大 1缩小
 	* @param [in] multiple  放大缩小倍数1~8
 	* @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 	* @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 	*
 	* @return 操作是否成功
 	* - flase：操作失败
 	* - true：操作成功
 	*/
	bool fishEyeExtend(int operateMode, int multiple, int windId, LCOpenFishEyePoint2d* pFishEyeCoordinate);

	/**
	 * 判断当前是否在播放流
	 * @return 是否在播放流
	 */
	bool isStreamPlayed();

	/**
	 * 获取播放状怿
	 * @return 播放状怿
	 */
	int getPlayerStatus();

	void setKey(const char* passwordKey);

	void setDecodeEngine(int engineType);

	/**
     * 设置编码缓冲策略
     *
     * @param realPlayType [in] 码流类型
     * - 2 主码流
     * - 3 从码流1
     * - 4 从码流2
     * - 5 从码流3
     * - 255 测试码流
     * @param playPolicy [in] 缓冲策略
     * - 0 默认
     * - 1 流畅
     * - 2 实时
     * @param waitTime [in] 超时时间

     * @return
     * - 0 成功
     * - 非0 失败
     */
    int setRealPlayPolicy(int realPlayType, int playPolicy, int waitTime);

	/**
	 * 判断共享链路的流媒体句柄是否存在
	 * @param handleKey [in] 共享链路标识
	 * @ return true:存在 ; false:不存在
	 */
	bool isOptHandleOK(char* handleKey);

	/**
	 * 判断共享链路的流媒体句柄是否存在
	 * @return true：是鱼眼码流；false：不是鱼眼码流
	 */
	bool isFishEyeStream();

	/**
	 * 窗口平移
	 * @param x [in] x坐标移动大小
	 * @param y [in] y坐标移动大小
	 */
	void translate(float x, float y);

	/**
	 * 获取窗口移动距离（x坐标＿
	 * @return 移动距离
	 */
	float getTranslateX();

	/**
	 * 获取窗口移动距离（y坐标＿
	 * @return 移动距离
	 */
	float getTranslateY();

	/**
	 * 设置画面缩放比例
	 * @param scale [in] 缩放比例
	 */
	void doScale(float scale);

	/**
	 * 获取画面缩放比例
	 * @return 缩放比例
	 */
	float getScale();

	/**
	 * 获取画面宽高
	 * @return 缩放比例
	 */
	bool getCurPictureWH(int &nPicWidth,int &nPicHeight);
	/**
	 * 设置画面最大缩放比例
	 * @param maxScale [in] 最大缩放比例
	 */
	void setMaxScale(float maxScale);

	/**
	 * 重置画面缩放平移操作
	 */
	void setIdentity();

	int getPlayPort();
private:
    void* m_interfaceLock;
    void* m_hLCOpenSDK_VideoPlay_Inside;
};

#endif /* _LCOPENSDK_VIDEOPLAY_H_ */
