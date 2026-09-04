//
//  "$Id: StreamData.h 784551 2019-09-04 09:11:54Z 13015 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDED_DAHUA_MEDIAPARSER_STREAMDATA_H__
#define __INCLUDED_DAHUA_MEDIAPARSER_STREAMDATA_H__

#include "Infra/IntTypes.h"
#include "Defs.h"
#include "Memory/SharedPtr.h"
#include "Component/Unknown.h"
#include "Memory/Packet.h"

namespace Dahua{
namespace StreamParser{

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
	frameSubtypeSdpData,             /// SDP信息
	frameSubtypeVideoSynopsisData,   /// 视频浓缩信息
	frameSubtypeSmartIFrame,         /// smart264 重定位I帧，作为当前GOP所有重定位P帧的参考
	frameSubtypeSmartPFrame,         /// smart264 重定位P帧，只参考当前GOP的I帧
	frameSubtypeSmartINoRender,      /// smartH264 I帧,只解码不显示，用于seek和倒放功能
	frameSubtypePopulationPicOverlay,/// 人群密度叠加图片
	frameSubtypeOsdData,             /// 叠加OSD帧

	frameSubtypeMax = 0xff
};

/// 解交错标志
enum Deinterlace
{
	deinterlacePair = 0,             ///解码后拉伸
	deinterlaceDouble,               ///解码两次
	deinterlaceNone                  ///无解交错
};

/// 编码类型
enum VideoEncodeType
{
	encodeTypeUnknown = 0,           /// 未知编码类型

	/// 视频编码类型
	encodeTypeMpeg4,                 /// Mpeg4编码类型 : 1
	encodeTypeH264,                  /// H264编码类型 : 2
	encodeTypeJpeg,                  /// Jpeg编码类型 : 3
	encodeTypeSvac,                  /// Svac编码类型 : 4
	encodeTypeHevc,                  /// Hevc编码类型 : 5
	encodeTypeMpeg2,                 /// Mpeg2编码类型 : 6
	encodeTypeH263,                  /// H263编码类型 : 7
	encodeTypeMsmpe4v1,              /// MsMpeg4v1编码类型 : 8
	encodeTypeMsmpe4v2,              /// MsMpeg4v2编码类型 : 9
	encodeTypeMsmpe4v3,              /// MsMpeg4v3编码类型 : 10
	encodeTypeWmv1,                  /// Wmv1编码类型 : 11
	encodeTypeWmv2,                  /// Wmv2编码类型 : 12
	encodeTypeHikH264,               /// 海康H264编码类型 : 13

	encodeTypeVideoMax = 0xff
};

/// 编码类型
enum AudioEncodeType
{
	/// 音频编码类型
	encodeTypePcm = 21,                   /// Pcm编码类型 : 21
	encodeTypeG729,                  /// G729编码类型 : 22
	encodeTypeIma,                   /// Ima编码类型 : 23
	encodeTypeMulaw,                 /// Mulaw编码类型 : 24
	encodeTypeG721,                  /// G721编码类型 : 25
	encodeTypeVmis,                  /// Vmis编码类型 : 26
	encodeTypeAdpcm,                 /// Adpcm编码类型 : 27
	encodeTypeG711a,                 /// G711a编码类型 : 28
	encodeTypeAmr,                   /// Amr编码类型 : 29
	encodeTypePcm16,                 /// Pcm16编码类型 : 30
	encodeTypeG711u,                 /// G711u编码类型 : 31
	encodeTypeG723,                  /// G723编码类型 : 32
	encodeTypeAac,                   /// Aac编码类型 : 33
	encodeTypeG726_40,               /// G726_40编码类型 : 34
	encodeTypeG726_32,               /// G726_32编码类型 : 35
	encodeTypeG726_24,               /// G726_24编码类型 : 36
	encodeTypeG726_16,               /// G726_16编码类型 : 37
	encodeTypeMp2,                   /// Mp2编码类型 : 38
	encodeTypeOgg,                   /// Ogg编码类型 : 39
	encodeTypeMp3,                   /// Mp3编码类型 : 40
	encodeTypeG722_1,                /// G722_1编码类型 : 41
	encodeTypeAudioMax = 0xff
};

/// 码流类型
enum StreamType
{
	streamTypeUnknown = 0,           /// 未知码流
	streamTypeDhpt,                  /// 大华老码流--DHPT : 1
	streamTypeNew,                   /// 大华老码流--NEW : 2
	streamTypeHb,                    /// 大华老码流--HB : 3
	streamTypeRaw,                   /// 大华老码流--raw mpeg4 : 4
	streamTypeCgi,                   /// 大华定制码流--CGI : 5
	streamTypeDhstd,                 /// 大华标准码流 : 6

	streamTypePs,                    /// PS : 7
	streamTypeTs,                    /// TS : 8
	streamTypeRtp,                   /// RTP : 9
	streamTypeWav,                   /// WAV : 10
	streamTypeAvi,                   /// AVI : 11
	streamTypeAsf,                   /// ASF : 12
	streamType3gp,                   /// 3GP : 13
	streamTypeMov,                   /// MOV : 14
	streamTypeMp4,                   /// MP4 : 15
	streamTypeFlv,                   /// FLV : 16
	streamTypeSvc,                   /// SVC : 17
	streamTypeMkv,                   /// MKV : 18
	streamTypeWmv,                   /// WMV : 19
	streamTypeAudio,                 /// 大华纯音频老码流AUDIO : 20

	streamTypeRawMpeg4,              /// Mpeg4裸码流 : 21
	streamTypeRawH264,               /// H264裸码流 : 22
	streamTypeRawH265,               /// H265裸码流 : 23
	streamTypeRawMpeg2,              /// Mpeg2裸码流 : 24
	streamTypeRawSvac,               /// Svac裸码流 : 25
	streamTypeVob,                   /// Vob裸码流 : 26

	streamType3rdCompany = 0x80,
	streamTypeHengyi,                 /// 恒亿码流 : 129
	streamTypeHuanghe,                /// 黄河码流 : 130
	streamTypeLangchi,                /// 朗驰 : 131
	streamTypeTdwy,                   /// 天地伟业 : 132
	streamTypeDali,                   /// 大立 : 133
	streamTypeLvff,                   /// Lvff : 134
	streamTypeH3c,                    /// H3c : 135
	streamTypeFengda,                 /// 丰达 : 136
	streamTypeMdvrx,                  /// Mdvrx : 137
	streamTypePu8000,                 /// Pu8000 : 138
	streamTypeDvr,                    /// Dvr :139
	streamTypeIfv,                    /// Ifv : 140
	streamType264Dv,                  /// 264Dv : 141
	streamTypeZwsj,                   /// 中维世纪 : 142
	streamTypeSanli,                  /// 三立 : 143
	streamTypeHikprivate,             /// 海康私有码流 : 144
	streamTypeHikps,                  /// 海康PS流 : 145
	streamTypeStar,                   /// 星望码流 : 146
	streamTypeLiyuan,                 /// 立元码流 : 147
	streamTypeKaer,                   /// 北京卡尔视通码流 : 148
	streamTypeSsav,                   /// ssav码流 : 149
	streamTypeZlav,                   /// 智诺码流 : 150
	streamTypeZslcPs,                 /// 中视里程PS : 151
	streamTypeStarEx,                 /// 新的星望码流 : 152
	streamTypeDongYang                /// 东阳一种特殊码流 : 153
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
	validFlagsUnknown,               /// 不可知错误
	validFlagsDecryptionFailer,      /// 解密失败
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
	encryptType3DES,                 /// 3DES加密
	encryptTypeKTJM,                 /// 凯天加密
	encryptTypeSYJM,                 /// 晟元加密
	encryptTypeHZSD,                 /// 杭师大加密算法
	encryptTypeZBQL,                 /// 中标麒麟加密算法
	encryptTypeAES256,               /// AES256-OFB-NOPADDING
	encryptTypeSM4,                  /// 国密4-OFB-NOPADDING
};

///数字签名摘要算法
enum DigtalSignatureDigestAlgorithmType
{
	digestAlgorithmUnknown = 0,
	digestAlgorithmSHA1,
};

///数字签名加密算法
enum DigtalSignatureEncryptAlogrithmType
{
	encryptAlogrithmUnknown = 0,
	encryptAlogrithmRSA,
};

enum ParseType
{
	parseTypeNoSupport,
	parseTypeOnlyStream,
	parseTypeOnlyFile,
	parseTypeSupportAll,
};

//帧数据信息
typedef struct ComponentFrameInfo
{
	unsigned int	stream_size;		/*裸数据长度*/
	
	unsigned int	frame_type;			/*帧类型	SG_FRAME_TYPE*/
	unsigned int	frame_sub_type;		/*帧子类型	SG_FRAME_SUB_TYPE*/
	unsigned int	frame_encode;		/*编码类型	SG_ENCODE_VIDEO_TYPE | SG_ENCODE_AUDIO_TYPE*/
	unsigned int	timeStamp;			/*帧时间戳*/

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
}ParserCmptInfo;						//解析库组件接口对外帧信息结构体

/*******************************************************************************/
/*						FrameInfo map 使用说明								   */
/*******************************************************************************/
/// 【通用帧信息】
/// "frameseq"			       = 帧序号
/// "frametype"                = 帧类型，'A'/'V'/'X', 'X'(辅助帧)
/// "framesubtype"             = 帧子类型，取值FrameSubtype
/// "encodetype"               = 编码类型，取值EncodeType
/// "streamtype"               = 码流类型，取值StreamType
/// "valid"                    = 有效帧标志，0值有效，其他值为水印校验错误值
/// "headerlen"                = 头部长度，以此作为偏移值找到裸数据流起始位置;   Ps和Ts流不支持通过偏移值找到裸数据流起始位置,需通过getStreamBuffer()和getStreamLen()来获取裸数据
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
/// "fileduration"             = 播放总时长 (单位s)
/// "createtime"               = 文件创建时间 utc时间
/// "framecount"               = 所有帧个数，文件统计信息
/// "videocount"               = 视频帧个数，文件统计信息
/// "audiocount"               = 音频帧个数，文件统计信息
/// "keyframecount"            = 关键帧个数，文件统计信息(未实现)
/// "pframecount"              = p帧个数，文件统计信息(未实现)
/// "bframecount"              = b帧个数，文件统计信息(未实现)
/// "maxframesize"             = 最大帧长度

/// "fileindex"                = 文件索引序号，在索引数组中的下标
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

///【视频宽高比压缩前后信息】比例0x9B
/// "ratiowidth"               = 编码前宽比例
/// "ratioheigth"			   = 编码前高比例
/// "ratioencodewidth"	       = 编码后宽比例
/// "ratioencodeheight"        = 编码后高比例


//【从裸数据的起始位置开始，偏移多少字节加密】
/// "encryptoffset"            =  加密位置相对于裸数据起始位置的偏移
//
///【数字签名协议】0x9C
/// "digtalsignaturesamplelen"      = 数字签名取样长度
/// "digtalsignatureencdeclen"      = 数字签名加密后数据长度
/// "digtalsignaturedigestalgorithm"  = 数字签名摘要算法，取值DigtalSignatureDigestAlgorithmType
/// "digtalsignatureencryptalogrithm" = 数字签名加密算法，取值DigtalSignatureEncryptAlogrithmType
/// "digtalsignatureencdecptr"      = 指向数字签名加密后数据的指针

///【旋转角度】0x8b
///"rotationangle"                = 旋转角度 1:90°；2:180°；3:270°

///【OSD扩展】0xb1
///"osd"

///【TS流节目信息】
///"programcount"		//节目总数
///"programnumber"		//节目编号


/// \brief 数据类，通过该类提供数据指针和数据长度，可以避免数据指针被用户释放。数据处理对外透明，可以减少解析过程中的内存拷贝。
class STREAMPARSER_API IStreamParserData
{
protected:
	virtual ~IStreamParserData() {}
public:
	virtual const char* getBuffer() = 0;
	virtual unsigned int getLen() = 0;

	virtual const char* getStreamBuffer() = 0;
	virtual unsigned int getStreamLen() = 0;

	DAHUA_COMPONENT_FUNCTION_REVSERVED(6)
};

typedef Memory::TSharedPtr<IStreamParserData> IStreamParserDataPtr;

} // end of StreamParser
} // end of Dahua

#endif //__INCLUDED_DAHUA_MEDIAPARSER_STREAMDATA_H__

