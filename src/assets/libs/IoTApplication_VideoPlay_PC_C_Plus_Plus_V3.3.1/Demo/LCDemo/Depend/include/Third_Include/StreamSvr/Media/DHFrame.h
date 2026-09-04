#ifndef __INCLUDED_DAHUA_STREAM_PARSER_DHFRAME_H__
#define __INCLUDED_DAHUA_STREAM_PARSER_DHFRAME_H__

#include "StreamSvr/Defs.h"

namespace Dahua {
namespace StreamSvr {


/************************************************************************/
/* 生成或者解析DH帧, 流媒体内部使用                                                          */
/************************************************************************/
struct CDHFrameImpl;
class CDHFrame
{
public:
	///\brief 构造、析构函数
	CDHFrame();
	~CDHFrame();

	///\brief 设置、获取大华标准帧头通道号
	void SetChannelID(uint8_t channel_id);
	void GetChannelID(uint8_t &channel_id);

	///\brief 设置、获取帧类型
	void SetFrameType(uint8_t type);
	void GetFrameType(uint8_t &type);

	///\brief 设置、获取帧序号
	void SetFrameSeq(uint32_t seq);
	void GetFrameSeq(uint32_t &seq);

	///\brief 设置、获取时间戳
	void SetFramePts(uint16_t pts);
	void GetFramePts(uint16_t &pts);

	///\brief 设置、获取帧时间	
	void SetFrameUtc(uint64_t utc);
	void GetFrameUtc(uint64_t &utc);

	///\brief 设置、获取帧宽高信息
	void SetFrameRes(uint16_t width, uint16_t height);
	void GetFrameRes(uint16_t &width, uint16_t &height);

	///\brief 设置、获取帧率
	void SetFrameRate(uint8_t frame_rate);
	void GetFrameRate(uint8_t &frame_rate);

	///\brief 设置、获取编码类型
	void SetDHType(int dh_playback_type);
	void GetDHType(int &dh_playback_type);

	//根据大华码流信息格式，1表示场编码格式，0表示帧编码格式
	void SetFrameCodec(int codec_method);
	void GetFrameCodec(int &codec_method);

	///\brief 设置、获取音频声道数和采样率
	void SetAudioParams(uint8_t tone_num, uint8_t sample_rate);
	void GetAudioParams(uint8_t &tone_num, uint8_t &sample_rate);

	//设置多音频通道数和通道号
	void SetAudioChannel(uint8_t audio_channel_count, uint8_t channel);

	///\brief 设置帧子类型
	void SetSubType(int type);

	//设置毫秒时间(0~999)
	void SetFrameMs(int millisecond);

	///\brief 确定组大华帧所需空间的长度
	///\param [in] raw_size-媒体数据长度
	///\param [in/out] head_len-大华头长度
	///\return 整个大华帧长度
	int SetLength(int raw_size, int &head_len);
	
	///\brief 组大华帧，buf的长度由SetLength()确定
	///\param [in] buf-存放大华帧的内存地址
	///\param [in] len-大华帧长度
	///\return 大华帧头部长度
	int Make(uint8_t *buf, int len);

	// 解析大华帧，返回裸帧数据偏移位置
	// 若不是大华帧，则返回0
	int Parse(uint8_t *buf, int len, int &raw_size);

	///\brief 设置优化属性，目前支持不加校验字段
	int setOptimizingFlag(int flag);

	// 获得大华头的长度
	// 若不是大华帧，则返回0
	static int GetHeaderLength(uint8_t *buf, int len, int &raw_size);

	//获取辅助帧的子类型
	static int GetAssistFrameSubType(uint8_t* buf, int len);

	//获取是否需要打上扩展字段"绝对毫秒时间"
	bool GetMsFlag();
	
	///\brief 设置当前帧丢帧状态；
	///\param [in] state-状态值
	void SetFrameErrorState(bool state);
	
	//获取是否需要设置大华丢帧扩展字段
	bool GetFrameErrorFlag();
private:

	///\brief 判断是否需要高清图像扩展
	///\param [in] width-宽值
	///\param [in] heigth-高值
	///\return 1 需要使用图像尺寸扩展，0 不需要使用图像尺寸扩展
	int is_extended_res(int width, int heigth);
	
private:
	CDHFrameImpl* m_impl;
};

}//StreamSvr
}//Dahua

#endif //__INCLUDED_DAHUA_STREAM_PARSER_DHFRAME_H__
