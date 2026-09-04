//
//  "$Id: StreamData.h 699003 2019-03-01 09:25:39Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE__STREAMCONVERTOR_STREAMDATA_H__
#define __INCLUDE__STREAMCONVERTOR_STREAMDATA_H__

#include "Infra/IntTypes.h"
#include "Defs.h"
#include "Memory/SharedPtr.h"

namespace Dahua{
namespace StreamConvertor{

enum FuncResult
{
	errorNoError = 0,				// 成功
	errorInvalidHandle,				// 无效句柄
	errorNoSupport,					// 解析或封装类型不支持
	errorThread,					// 内部线程出错
	errorParam,						// 参数有误

	errorFileOpen,					// 文件打开出错，可能已被互斥打开
	errorFileRead,					// 文件读取出错
	errorFileWrite,					// 文件写入出错
	errorFormat,					// 码流格式有误，无法继续解析

	errorBufferOverFlow,			// 内部缓冲溢出
	errorSysOutOfMem,				// 系统内存不足

	errorNoIDRFrame,				// 缺少I帧
	errorNoOutPut,					// 同步封装或解析逻辑中无数据输出
	errorOrder,						// 调用顺序有误

	errorEncryptKey,				// 回放时输入秘钥错误
};

enum ConvertMode
{
	modeSingleFile = 0,         /// 只转成一个文件
	modeMultipleFile = 1,     /// 支持转换成多个文件
};

// SetParam类型
// "convertmode" 设置转换模式，具体值见ConvertMode；

/****************************当目的类型为dav格式时*************************************************/
// "package_dav_use_system_time" 具体值为：参数设置为1，用户可以根据需要，设置转换使用系统时间
// "package_dav_sync_time_scale" 表示同步间隔，以帧率为单位，取值为0表示不同步，只在package_dav_use_system_time为1时有效
// "package_dav_exheaderdata_checkType"表示大华0x88扩展帧数据校验类型，取值为1表示Sum32校验，2为Xor32校验，3为CRC32校验
// "package_dav_bosch_osd_len" 表示大华帧添加bosch定制0xB1辅助帧长度，取值包含0xb1帧头
// "package_dav_unable_ext_header_data_check" 大华帧添加0x88数据校验封装，取值为1表示不封装0x88扩展帧头，0表示封装0x88扩展帧头
// "package_dav_use_extern_time" 具体值为：参数设置为1，用户可以根据需要，设置转换使用用户自定义时间
// "package_dav_extern_time_base_time" 表示起始的绝对日期时间(UTC时间)，只在package_dav_use_extern_time为1时有效
// "package_dav_fisheye_install_style" 表示鱼眼安装的位置。0：无意义；1：顶装；2：壁装；3.地装
// "package_dav_fisheye_correct_mode"  表示鱼眼模式。 1: "Original"原始图像模式； 2："Config" 配置模式
//										3: "Panorama"全景模式；		4: "DoublePanorama"双全景模式；
//										5: "OriginalPlusThreeEPtsRegion" 1+3模式  6:"Single"单画面EPts模式
//										7: "FourEPtsRegion"4画面模式	8:"Normal" Normal模式 
// "package_dav_fisheye_correct_mode_circleX"	表示鱼眼圆心坐标X
// "package_dav_fisheye_correct_mode_circleY"	表示鱼眼圆心坐标Y
// "package_dav_fisheye_radius"					表示鱼眼半径
/***************************************************************************************************/

/***************************************当原始码流类型为rtp*****************************************/
//需要强指定码流类型为RTP,同时需要指定如下变量参数
//"parser_rtp_payload_type"				表示视频payload值
//"parser_rtp_encode_type"				视频编码格式，取值为StreamParserAPI中编码格式
//"parser_rtp_audio_channels"			音频声道数
//"parser_rtp_audio_sample_rate"		音频采样率
//"parser_rtp_channel_count"			音频或者视频路数
//"parser_rtp_channel_id"				当前音视频为第几路
//"parser_rtp_discard_flag"				丢弃丢帧flag
//"parser_rtp_audio_payload_type"		表示音频payload值
//"parser_rtp_audio_encode_type"		表示音频编码格式，取值为StreamParserAPI中的枚举值
/***************************************************************************************************/


// GetParam 类型
// "filecount" 获取转换后的文件个数

/// \brief 数据类，通过该类提供数据指针和数据长度，可以避免数据指针被用户释放。数据处理对外透明，可以减少解析过程中的内存拷贝。
class ST_API IStreamConvertorData
{
protected:
	virtual ~IStreamConvertorData() {}
public:
	virtual const char* getBuffer() = 0;
	virtual unsigned int getLen() = 0;
};

typedef Memory::TSharedPtr<IStreamConvertorData> IStreamConvertorDataPtr;

/*******************************************************************************/
/*						FrameInfo map 使用说明								   */
/*******************************************************************************/
/// 【通用帧信息】
/// "frametype"							  = 帧类型，SC_FrameType
/// "framesubtype"						  = 帧子类型，取值SC_FrameSubType
/// "Year"								  = 年
/// "Month"								  = 月			
/// "Day"	                              = 日
/// "Hour"								  = 时
/// "Minute								  = 分
/// "Second"							  = 秒
/// "MilliSecond"						  = 毫秒
/// "PTS"								  = PTS 时间戳
/// "DTS"								  = DTS 时间戳
/// "Valid"								  = 是否包含有效数据，0不包含，1包含 

/// 【视频帧属性】
/// "VideoEncodeType"				      = 编码类型，取值
/// "VideoWidth"						  = 宽
/// "VideoHeight"						  = 高
/// "VideoFrameRate"					  = 帧率

/// 【音频帧属性】
/// "AudioEncodeType"			          = 编码类型，取值
/// "AudioChannel"						  = 通道数
/// "AudioSampleRate"				      = 采样率
/// "AudioBitPerSample"				      = 采样位数

} // end of StreamConvertor
} // end of Dahua

#endif //__INCLUDE__STREAMPARSER_STREAMINFO_H__

