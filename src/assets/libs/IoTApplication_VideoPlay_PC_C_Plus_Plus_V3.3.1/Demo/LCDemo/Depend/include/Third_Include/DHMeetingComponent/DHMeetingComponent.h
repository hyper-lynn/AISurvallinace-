//
//  DHMeetingComponent.h
//  DHMeetingComponent
//
//  Created by yao_bao on 14/12/24.
//  Copyright (c) 2014年 yao_bao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APIMeetingTransfer.h"

@interface DHMeetingComponent:NSObject

/**
 * @function : 初始化
 * @param 对方橙聊ID
 * @param
 * @return 端口号 :>0 成功
 *         0 : 失败
 */
- (int) DahuaMeetingDataInit:(NSString*)clientID;
/**
 * @function : 添加用户
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) DahuaMeetingDataAdd:(NSString*)clientID;
/**
 * @function : 删除用户
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) DahuaMeetingDataDel:(NSString*)clientID;
/**
 * @function : 删除所有用户
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) DahuaMeetingDataDeleteAll;
/**
 * @function : 设置对方清晰度
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */

- (int) DahuaMeetingDataSetPolicy:(NSString*)clientID StreamType:(int)type MinBitRate :(int)minRate maxBitRate:(int)maxRate FPS:(int) fps;
/**
 * @function : 开始收发数据
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) DahuaMeetingDataStartTransfer:(NSString*)clientID AmtType:(int)type Port:(int)port;
/**
 * @function : 停止收发数据
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) DahuaMeetingDataStopTransfer:(NSString*)clientID AmtType:(int)type;

/**
 * @function : 设置播放界面回调
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (void) setWindowCallback:(void *)pWindow;

/**
 * @function : 设置AMT事件回调
 * @param
 * @param
 * @return
 * 
 */

- (void) SetAMTCallback:(AMTCallback)listener;

/**
 *
 * @param
 * @param
 * @return OK : OK
 *         NG : NG
 */
- (void) setVideoHandle:(void*)handle;
/**
 * 暂时不用
 * @param
 * @param
 * @return OK : OK
 *         NG : NG
 */
- (void) setNetworkParameter:(int) waitSeconds;
/**
 * @function : 是否显示画面
 * @param
 * @param
 * @return
 *         0 : 成功
 */
- (void) showVideo:(bool)enable;

/**
 * @function : 播放视频
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) playVideo;
/**
 * @function : 停止播放
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) stopVideo;
/**
 * @function : 打开伴音
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) playSound;
/**
 * @function : 停止伴音
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) stopSound;

/**
 * 暂时不用
 * @param 对方橙聊ID
 * @param
 * @return
 *         0 : 成功
 */
- (int) openVideoRecord:(int)encodeType SampleRate:(int)sampleRate SampleDepth:(int)sampleDepth PackType:(int)packType;
/**
 * 暂时不用
 * @param
 * @param
 * @return OK : OK
 *         NG : NG
 */
- (int) stopVideoRecord;
/**
 * function : 打开语音采集
 * @param SampleRate 采样率
 * @param SampleDepth 采样深度
 * @param PackType 打包类型 参考语音对讲参数
 * @return OK : OK
 *         NG : NG
 */
- (int) openAudioRecord:(int)encodeType SampleRate:(int)sampleRate SampleDepth:(int)sampleDepth PackType:(int)packType;
/**
 *
 * @param
 * @param
 * @return OK : OK
 *         NG : NG
 */
- (int) stopAudioRecord;
/**
 * @function : 发送本地视频采集到数据
 * @param data 码流数据 H264
 * @param len   数据长度
 * @param Width 分辨率 宽
 * @param Height   分辨率 高
 * @param SampleRate 采样率
 * @param RotationAngle   角度
 * @return
 *         0 : 成功
 */
- (void) onVideoData:(unsigned char*)data DataLen:(int)len Width:(int)width Height:(int)height SampleRate:(int)rate RotationAngle:(int)angle;

/**
 * @function : 设置Cpacket内存池大小，需要放在很靠前位置，通常在main函数
 * @param : totalSize 比如20M  为20*1024*1024
 * @param
 * @return
 *         0 : 成功
 */
- (int) initMemory:(int)totalSize;
@end
