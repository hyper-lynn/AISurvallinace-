//
//  "$Id: StreamData.h 236049 2014-11-28 09:00:41Z shu_wang $"
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
	encodeTypeMpeg4,                 /// Mpeg4编码类型
	encodeTypeH264,                  /// H264编码类型
	encodeTypeJpeg,                  /// Jpeg编码类型
	encodeTeypeSvac,                 /// Svac编码类型
	encodeTeypeHevc,                 /// Hevc编码类型
	encodeTypeVideoMax = 20,
	
	/// 音频编码类型
	encodeTypePcm,                   /// Pcm编码类型
	encodeTypeG729,                  /// G729编码类型
	encodeTypeIma,                   /// Ima编码类型
	encodeTypeMulaw,                 /// Mulaw编码类型
	encodeTypeG721,                  /// G721编码类型
	encodeTypeVmis,                  /// Vmis编码类型
	encodeTypeAdpcm,                 /// Adpcm编码类型
	encodeTypeG711a,                 /// G711a编码类型
	encodeTypeAmr,                   /// Amr编码类型
	encodeTypePcm16,                 /// Pcm16编码类型
	encodeTypeG711u,                 /// G711u编码类型
	encodeTypeG723,                  /// G723编码类型
	encodeTypeAac,                   /// Aac编码类型
	encodeTypeG726_40,               /// G726_40编码类型
	encodeTypeG726_32,               /// G726_32编码类型
	encodeTypeG726_24,               /// G726_24编码类型
	encodeTypeG726_16,               /// G726_16编码类型
	encodeTypeMp2,                   /// Mp2编码类型
	encodeTypeOgg,                   /// Ogg编码类型
	encodeTypeMp3,                   /// Mp3编码类型
	encodeTypeAudioMax
};

/// 码流类型
enum StreamType
{
	streamTypeUnknown = 0,           /// 未知码流		
	streamTypeDhpt,                  /// 大华老码流--DHPT
	streamTypeNew,                   /// 大华老码流--NEW		
	streamTypeHb,                    /// 大华老码流--HB	
	streamTypeRaw,                   /// 大华老码流--raw mpeg4
	streamTypeCgi,                   /// 大华定制码流--CGI
	streamTypeDhstd,                 /// 大华标准码流
	                        
	streamTypePs,                    /// PS
	streamTypeTs,                    /// TS
	streamTypeRtp,                   /// RTP
	streamTypeWav,                   /// WAV
	streamTypeAvi,                   /// AVI
	streamTypeAsf,                   /// ASF
	streamType3gp,                   /// 3GP
	streamTypeMov,                   /// MOV
	streamTypeMp4                    /// MP4
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

/// 【多音频支持】
/// "matotalchannels"          = 多音频总通道数      
/// "macurchannel"             = 当前属于哪个通道         

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

