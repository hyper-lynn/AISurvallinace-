//
//  "$Id: StreamData.h 784551 2019-09-04 09:11:54Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE__STREAMPACKAGE_STREAMDATA_H__
#define __INCLUDE__STREAMPACKAGE_STREAMDATA_H__

#include "Infra/IntTypes.h"
#include "Defs.h"
#include "Memory/SharedPtr.h"

namespace Dahua{
namespace StreamPackage{

#if defined(_WIN32)
	typedef __int64 int_64;
#else /*linux*/
	typedef long long int_64;
#endif

/// 帧子类型
enum FrameSubtype
{
	frameSubtypeUnknown = 0,         /// 未知子类型
	frameSubtypeIFrame,              /// I帧
	frameSubtypePFrame,              /// P帧
	frameSubtypeBFrame,              /// B帧
	frameSubtypeSFrame,              /// S帧
	frameSubtypeWatermarkText,       /// 水印数据为TEXT类型
	frameSubtypeWatermarkJpeg,       /// 水印数据为JPEG类型
	frameSubtypeWatermarkBmp,        /// 水印数据为BMP类型
	frameSubtypeIntlData,            /// 智能分析帧
	frameSubtypeJpegFrame,           /// JPEG 帧
	frameSubtypeItsData,             /// its信息帧
	frameSubtypeGpsData,             /// gps
	frameSubtypeIntlexData,          /// 扩展智能分析帧
	frameSubtypeMotionFullData,      /// 全屏动检
	frameSubtypeMotionCardData,      /// 全屏动检(板卡)
	frameSubtypeLightData,           /// 光照
	frameSubtypeRawData,             /// 原始数据
	frameSubtypeIndexI,              /// I帧索引帧
	frameSubtypeMotionData,          /// 动检数据帧
	frameSubtypeLabelData,           /// 标签帧
	frameSubtypeScreenCaptionData,   /// 字幕
	frameSubtypeEventData,           /// 事件帧
	frameSubtypeFileHeadData,        /// 文件头帧
	frameSubtypeSdpData,             /// SDP信息，新增
	frameSubtypeVideoSynopsisData,   /// 视频浓缩信息
	frameSubtypeSmartIFrame,         /// smart264 重定位I帧，作为当前GOP所有重定位P帧的参考
	frameSubtypeSmartPFrame,         /// smart264 重定位P帧，只参考当前GOP的I帧
	frameSubtypeSmartINoRender,      /// smartH264 I帧,只解码不显示，用于seek和倒放功能

	frameSubtypeMax
};

/// 解交错标志
enum Deinterlace
{
	deinterlacePair = 0,             ///解码后拉伸
	deinterlaceDouble,               ///解码两次
	deinterlaceNone                  ///无解交错
};

/// 编码类型
enum EncodeType
{
	encodeTypeUnknown = 0,           /// 未知编码类型

	/// 视频编码类型
	encodeTypeMpeg4 = 1,                 /// Mpeg4编码类型
	encodeTypeH264 = 2,                  /// H264编码类型
	encodeTypeJpeg = 3,                  /// Jpeg编码类型
	encodeTypeSvac = 4,                  /// Svac编码类型
	encodeTypeHevc = 5,                  /// Hevc编码类型
	encodeTypeMpeg2 = 6,                 /// Mpeg2编码类型
	encodeTypeH263 = 7,                  /// H263编码类型
	encodeTypeMsmpe4v1 = 8,              /// MsMpeg4v1编码类型
	encodeTypeMsmpe4v2 = 9,              /// MsMpeg4v2编码类型
	encodeTypeMsmpe4v3 = 10,              /// MsMpeg4v3编码类型
	encodeTypeWmv1 = 11,                  /// Wmv1编码类型
	encodeTypeWmv2 = 12,                  /// Wmv2编码类型
	encodeTypeHikH264 = 13,               /// 海康H264编码类型

	encodeTypeVideoMax = 20,

	/// 音频编码类型
	encodeTypePcm = 21,                   /// Pcm编码类型
	encodeTypeG729 = 22,                  /// G729编码类型
	encodeTypeIma = 23,                   /// Ima编码类型
	encodeTypeMulaw = 24,                 /// Mulaw编码类型
	encodeTypeG721 = 25,                  /// G721编码类型
	encodeTypeVmis = 26,                  /// Vmis编码类型
	encodeTypeAdpcm = 27,                 /// Adpcm编码类型
	encodeTypeG711a = 28,                 /// G711a编码类型
	encodeTypeAmr = 29,                   /// Amr编码类型
	encodeTypePcm16 = 30,                 /// Pcm16编码类型
	encodeTypeG711u = 31,                 /// G711u编码类型
	encodeTypeG723 = 32,                  /// G723编码类型
	encodeTypeAac = 33,                   /// Aac编码类型
	encodeTypeG726_40 = 34,               /// G726_40编码类型
	encodeTypeG726_32 = 35,               /// G726_32编码类型
	encodeTypeG726_24 = 36,               /// G726_24编码类型
	encodeTypeG726_16 = 37,               /// G726_16编码类型
	encodeTypeMp2 = 38,                   /// Mp2编码类型
	encodeTypeOgg = 39,                   /// Ogg编码类型
	encodeTypeMp3 = 40,                   /// Mp3编码类型
	encodeTypeG722_1 = 41,                /// G722.1编码类型
	encodeTypeAudioMax
};

/// 码流类型
enum StreamType
{
	streamTypeUnknown = 0,           /// 未知码流
	streamTypeDhpt = 1,                  /// 大华老码流--DHPT
	streamTypeNew = 2,                   /// 大华老码流--NEW
	streamTypeHb = 3,                    /// 大华老码流--HB
	streamTypeRaw = 4,                   /// 大华老码流--raw mpeg4
	streamTypeCgi = 5,                   /// 大华定制码流--CGI
	streamTypeDhstd = 6,                 /// 大华标准码流

	streamTypePs = 7,                    /// PS
	streamTypeTs = 8,                    /// TS
	streamTypeRtp = 9,                   /// RTP
	streamTypeWav = 10,                   /// WAV
	streamTypeAvi = 11,                   /// AVI
	streamTypeAsf = 12,                   /// ASF
	streamType3gp = 13,                   /// 3GP
	streamTypeMov = 14,                   /// MOV
	streamTypeMp4 = 15,                   /// MP4
	streamTypeFlv = 16,                   /// FLV
	streamTypeSvc = 17,                   /// SVC
	streamTypeMkv = 18,                   /// MKV
	streamTypeWmv = 19,                   /// WMV
	streamTypeAudio = 20,                 /// 大华纯音频老码流AUDIO

	streamTypeRawMpeg4 = 21,              /// Mpeg4裸码流
	streamTypeRawH264 = 22,               /// H264裸码流
	streamTypeRawH265 = 23,               /// H265裸码流
	streamTypeRawMpeg2 = 24,              /// Mpeg2裸码流
	streamTypeRawSvac = 25,               /// Svac裸码流

	streamType3rdCompany = 0x80,
	streamTypeHengyi = 129,                 /// 恒亿码流
	streamTypeHuanghe = 130,                /// 黄河码流
	streamTypeLangchi = 131,                /// 朗驰
	streamTypeTdwy = 132,                   /// 天地伟业
	streamTypeDali = 133,                   /// 大立
	streamTypeLvff = 134,                   /// Lvff
	streamTypeH3c = 135,                    /// H3c
	streamTypeFengda = 136,                 /// 丰达
	streamTypeMdvrx = 137,                  /// Mdvrx
	streamTypePu8000 = 138,                 /// Pu8000
	streamTypeDvr = 139,                    /// Dvr
	streamTypeIfv = 140,                    /// Ifv
	streamType264Dv = 141,                  /// 264Dv
	streamTypeZwsj = 142,                   /// 中维世纪
	streamTypeSanli = 143,                  /// 三立
	streamTypeHikprivate = 144,             /// 海康私有码流
	streamTypeHikps = 145,                  /// 海康PS流
	streamTypeStar = 146,                   /// 星望码流
};

/// Flags信息
enum ValidFlags
{
	validFlagsNoerror = 0,           /// 数据校验无误
	validFlagsTimeStand,             /// 时间戳错误
	validFlagsLength,                /// 长度出错
	validFlagsHeadVerify,            /// 帧头内部数据校验
	validFlagsDataVerify,            /// 数据校验失败
	validFlagsLostHeader,            /// 数据丢失帧头
	validFlagsLostTailer,            /// 数据丢失帧尾
	validFlagsLostFrame,             /// 丢帧
	validFlagsWaterMark,             /// 水印校验错误
	validFlagsContext,               /// 上下文错误
	validFlagsUnknown                /// 不可知错误
};

/// 厂商类型
enum CompanyType
{
	companyTypeUnknown = 0,          /// 未知码流
	companyTypeHIK,                  /// 海康码流
	companyTypeHanBang,              /// 汉邦码流
	companyTypeYuShi,                /// 宇视码流
	companyTypeInterDevicePS,        /// 国际设备PS码流
	companyTypeXinChan,              /// 信产码流
	companyTypeLiYuan,               /// 立元码流
	companyTypeBit,                  /// 比特码流
	companyTypeOldDH,                /// 老大华码流
	companyTypeStdTS,                /// 标准ts流
	companyTypeTDYG,                 /// 天地阳光
	companyTypeAXS,                  /// 安迅士
	companyTypeDFWL,                 /// 东方网力
	companyTypeJuFeng,               /// 巨峰
	companyTypeKEDA,                 /// 柯达
	companyTypeLG,                   /// LG
	companyTypeMaiShi,               /// 迈视
	companyTypeTongZun,              /// 同尊
	companyTypeVIVO,                 /// vivo
	companyTypeWeiHao,               /// 伟昊
	companyTypeXingWang,             /// 星望
	companyTypeBJWS,                 /// 北京蛙视
	companyTypeXJSX,                 /// 先进视讯
	companyTypeSZXY,                 /// 深圳信义
	companyTypeZSYH,                 /// 中盛益华
	companyTypeZXLW,                 /// 中兴力维
	companyTypeZXTX,                 /// 中兴通讯
};

/// 加密类型
enum EncryptType
{
	encryptTypeNone = 0,             /// 无加密类型
	encryptTypeAES,                  /// AES加密
	encryptTypeDES,                  /// DES加密
	encryptType3DES                  /// 3DES加密
};

typedef enum
{
	capacityVideo = 0,			/* 视频编码参数集*/
	capacityAudio				/* 音频编码参数集*/
}CapacityType;

typedef struct
{
	unsigned int encode_type;		/* 视频编码类型，取值参考EncodeType*/
	unsigned int width;				/* 视频宽*/
	unsigned int height;			/* 视频高*/
	unsigned int frame_rate;		/* 帧率*/
	unsigned int reserved[4];		/* 保留字段*/
}VideoConstraint;

typedef struct  
{
	unsigned int encode_type;		/* 音频编码类型，取值参考EncodeType*/
	unsigned int sample_rate;		/* 采样率*/
	unsigned int bit_per_sample;	/* 采样位数*/
	unsigned int channels;			/* 通道数*/
	unsigned int bit_rate;			/* 比特率*/
	unsigned int reserved[3];		/* 保留字段*/
}AudioConstraint;

//帧数据信息
typedef struct
{
	unsigned int	stream_size;		/*裸数据长度*/

	unsigned int	frame_type;			/*帧类型	SG_FRAME_TYPE*/
	unsigned int	frame_sub_type;		/*帧子类型	SG_FRAME_SUB_TYPE*/
	unsigned int	frame_encode;		/*编码类型	SG_ENCODE_VIDEO_TYPE | SG_ENCODE_AUDIO_TYPE*/
	unsigned int	timeStamp;			/*帧时间戳*/

	int_64			pts;
	int_64			dts;

	unsigned int	nYear;				/*年*/
	unsigned int	nMonth;				/*月*/
	unsigned int	nDay;				/*日*/
	unsigned int	nHour;				/*小时*/
	unsigned int	nMinute;			/*分钟*/
	unsigned int	nSecond;			/*秒*/
	unsigned int	nMilliSecond;		/*毫秒*/

	unsigned int	width;				/*视频宽度*/
	unsigned int	heigth;				/*视频高度*/
	unsigned int	frame_rate;			/*视频帧率*/
	unsigned int	deinter_lace;		/*解交错信息*/

	unsigned int	sample_rate;		/*音频采样率*/
	unsigned int	bit_per_sample;		/*音频采样位数*/
	unsigned int	channels;			/*音频通道数*/
	unsigned int	bit_rate;			/*输出码率，单位kbps*/

	unsigned int	frame_seq;			/*帧序号*/
	unsigned int	errorFlags;			/*按错误标志位*/
	unsigned int	valid;				/* 是否包含有效数据，0不包含，1包含 */

	unsigned char	reserved[200];		/*保留字段*/
}PackageCmptInfo;						//封装库组件接口对外帧信息结构体

/*******************************************************************************/
/*						FrameInfo map 使用说明								   */
/*******************************************************************************/
/// 【通用帧信息】
/// "frametype"                = 帧类型，'A'/'V'/'X', 'X'(辅助帧)
/// "framesubtype"             = 帧子类型，取值FrameSubtype
/// "encodetype"               = 编码类型，取值EncodeType
/// "streamtype"               = 码流类型，取值StreamType
/// "valid"                    = 有效帧标志，0值有效，其他值为水印校验错误值
/// "headerlen"                = 头部长度，以此作为偏移值找到裸数据流起始位置
/// "framedatalen"             = 完整的帧数据长度
/// "framebodylen"             = 裸数据长度

/// 【视频帧属性】
/// "width"                    = 宽
/// "height"                   = 高
/// "rate"                     = 帧率
/// "deinterlace"              = 解交错，取值Deinterlace

/// 【音频帧属性】
/// "channels"                 = 通道数
/// "samplespersec"            = 采样率
/// "bitspersample"            = 采样位数


/// 【文件统计信息】
/// "filelength"               = 文件长度
/// "framecount"               = 所有帧个数，文件统计信息
/// "videocount"               = 视频帧个数，文件统计信息
/// "audiocount"               = 音频帧个数，文件统计信息
/// "keyframecount"            = 关键帧个数，文件统计信息
/// "pframecount"              = p帧个数，文件统计信息
/// "bframecount"              = b帧个数，文件统计信息
///

/// "fileoffset"               = 文件偏移，指帧数据在文件中的偏移位置

/// 【其他大华协议需要的属性】

/// 【兼容老码流】
/// "mediaflag"                = 该标示兼容老码流

/// 【时间信息】
/// "year"                     = 年
/// "month"                    = 月
/// "day"                      = 日
/// "hour"                     = 小时
/// "minute"                   = 分钟
/// "second"                   = 秒
/// "millisecond"              = 毫秒
/// "timestamp"                = 绝对时间戳

/// 【透雾参数】
/// "fogthmode"                = 透雾模式 1:关闭 2:自动 3:手动 其它:保留
/// "fogthintension"           = 透雾强度0-2
/// "fogairlightmode"          = 大气光模式 1:自动 2: 手动 其它:保留
/// "fogairlightintension"     = 大气光强度0-15

/// 【svc信息】
/// "svcalllevels"             = svc总层数
/// "svclevelorder"            = 当前帧属于第几层

/// 【三方厂商头信息】
/// "tpcompanytype"            = 厂商类型，取值CompanyType
/// "tpstreamheaderlen"        = 厂商头信息长度

/// 【多音视频通道支持】
/// "matotalchannels"          = 总通道数，若帧类型为视频帧，则表示视频流的个数，若为音频帧，则表示音频流的个数
/// "macurchannel"             = 通道号，从0开始

/// 【加密信息】
/// "encrypttype"              = 加密类型，取值EncryptType
/// "encryptlen"               = 加密信息长度

/// 【用户自定义数据操作】
/// "customchangetype"         = 1:按字节（无符号数）进行算数＋
/// "custonchangelen"          = type中规定的操作单元长度
/// "custonchangevalue"        = 操作数

/// 【分数帧率支持】
/// "ratevalue"                = 分数帧率分子
/// "ratedenominator"          = 分数帧率分母
//

/// 【分屏支持】
/// "n_slice"                  = n
/// "m_slice"                  = m,总图像块数(n * m)

/// 【单块图像信息】根据n*m值增加后缀，取值
/// "blockpos_left_k"          = k 取值[1, n*m]
/// "blockpos_top_k"           =
/// "blockpos_right_k"         =
/// "blockpos_bottom_k;        =
/// "blockdata_offset_k"       = 第k块图像数据在帧数据中的偏移

///【旋转角度】0x8b
///"rotationangle"                = 旋转角度 1:90°；2:180°；3:270°

///【TS流节目信息】
///"programcount"		//节目总数
///"programnumber"		//节目编号

/// \brief 数据类，通过该类提供数据指针和数据长度，可以避免数据指针被用户释放。数据处理对外透明，可以减少解析过程中的内存拷贝。

class STREAMPACKAGE_API IStreamPackageData
{
protected:
	virtual ~IStreamPackageData() {}
public:
	virtual const char* getBuffer() = 0;
	virtual unsigned int getLen() = 0;
};

typedef Memory::TSharedPtr<IStreamPackageData> IStreamPackageDataPtr;

} // end of StreamParser
} // end of Dahua

#endif //__INCLUDE__STREAMPARSER_STREAMINFO_H__

