//
//  "$Id: ImageSize.h 16858 2010-12-03 07:19:14Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __STREAM_IMAGE_SIZE_H__
#define __STREAM_IMAGE_SIZE_H__

#include "Defs.h"
#include <string>
#include <vector>


namespace Dahua {
namespace Stream {

enum VideoStandard
{
	videoStandardPAL = 0,	///< PAL制式。
	videoStandardNTSC,		///< NTSC制式。
	videoStandardSECAM,		///< SECAM制式。
	videoStandardNr
};

// 通用图像大小类型
enum ImageSizeType
{
	imageSizeD1 = 0,	///< 704*576(PAL)	704*480(NTSC)
	imageSizeHD1,		///< 352*576(PAL)	352*480(NTSC)
	imageSizeBCIF,		///< 704*288(PAL)	704*240(NTSC)
	imageSizeCIF,		///< 352*288(PAL)	352*240(NTSC)
	imageSizeQCIF,		///< 176*144(PAL)	176*120(NTSC)
	imageSizeVGA,		///< 640*480
	imageSizeQVGA,		///< 320*240
	imageSizeSVCD,		///< 480*480
	imageSizeQQVGA,		///< 160*128
	imageSizeSVGA,		///< 800*592
	imageSizeXVGA,		///< 1024*768
	imageSizeWXGA,		///< 1280*800
	imageSizeSXGA,		///< 1280*1024
	imageSizeWSXGA,		///< 1600*1024
	imageSizeUXGA,		///< 1600*1200
	imageSizeWUXGA,		///< 1920*1200
	imageSizeND1,		///< 240*192
	imageSize720P,		///< 1280*720
	imageSize1080P,		///< 1920*1080
	imageSize1_3M,		///< 1280*960(1.3M)
	imageSize1280_960 = imageSize1_3M,
	imageSize2_5M,		///< 1872*1408(2.5M)
	imageSize1872_1408 = imageSize2_5M,
	imageSize5M,		///< 3744*1408(5M)
	imageSize3744_1408 = imageSize5M,
	imageSize3M,		///< 2048*1536(3M)
	imageSize2048_1536 = imageSize3M,
	imageSize2432_2048, ///< 2432*2048(5M)
	imageSize1216_1024, ///< 1216*1024(1.2M)
	imageSize1408_1024, ///< 1408*1024(1.5M)
	imageSize3296_2472,	///< 3296*2472(8M)
	imageSize2560_1920, ///< 2560*1920(5M)
	imageSize960H,		///< 928*576(PAL) 928*480(NTSC)
	imageSize960_720,	///< 960*720(DV720P)
	imageSize2560_1600,	///< 2560*1600(4M)
	imageSize2336_1752, ///< 2336_1752(4_0M)
	imageSize2592_2048, ///< 2592*2048
	imageSize1920_1440, ///< 1920*1440
	imageSize2448_2048, ///< 2448*2048
	imageSize2752_2208, ///< 2752*2208
	imageSizeWVGA,		///< 800*480
	imageSize3840_2160,	///< 3840*2160(8_0M)
	imageSize4096_2160,	///< 4096*2160(8_8M)
	imageSize3072_2048,	///< 3072*2048(6_3M)
	imageSize2048_2048,	///< 2048*2048(4M)
	imageSize2304_1296,	///< 2304*1296,
	imageSize4000_3000,	///< 4000*3000(12M)
	imageSize2880_2880,	///< 2880*2880(9M)
	imageSize2880_2160,	///< 2880*2160(6M)
	imageSize640_360,	///< 640*360
	imageSize320_180,	///< 320*180
	imageSize3648_2736,	///< 3648*2736
	imageSize2592_1520,	///< 2592*1520(4_1M)
	imageSize2560_2048,	///< 2560*2048
	imageSize1920_1088,	///< 1920*1088
	imageSize2560_1440, ///< 2560*1440
	imageSize2048_1520, ///< 2048*1520(3M)
	imageSize2592_2592,	///< 2592*2592(6M)
	imageSize3392_2008,	///< 3392*2008
	imageSize2592_1944,	///< 2592*1944
	imageSize640_512,   ///< 640*512
	imageSize320_256,   ///< 320*256
	imageSize2688_1520,	///<2688*1520
	imageSize2912_2336,	///<2912*2336
	imageSize960_540,	///< 960*540
	imageSize800_448,	///< 800*448
	imageSize720_404,	///< 720*404
	imageSize480_272,	///< 480*272
	imageSize320_320,	///< 320*320
	imageSize352_360,	///< 352*360
	imageSize480_480,	///< 480*480
	imageSize512_256,	///< 512*256
	imageSize512_512,	///< 512*512
	imageSize576_576,	///< 576*576
	imageSize640_320,	///< 640*320
	imageSize640_640,	///< 640*640
	imageSize704_256,	///< 704*256
	imageSize704_320,	///< 704*320
	imageSize720_360,	///< 720*360
	imageSize720_720,	///< 720*720
	imageSize768_768,	///< 768*768
	imageSize960_480,	///< 960*480
	imageSize960_960,	///< 960*960
	imageSize1024_512,	///< 1024*512
	imageSize1024_1024,	///< 1024*1024
	imageSize1152_576,	///< 1152*576
	imageSize1152_1152,	///< 1152*1152
	imageSize1216_1216,	///< 1216*1216
	imageSize1280_480,	///< 1280*480
	imageSize1440_360,	///< 1440*360
	imageSize1536_768,	///< 1536*768
	imageSize1536_1536,	///< 1536*1536
	imageSize1920_960,	///< 1920*960
	imageSize1920_1920,	///< 1920*1920
	imageSize2048_512,	///< 2048*512
	imageSize2144_1072,	///< 2144*1072
	imageSize2304_576,	///< 2304*576
	imageSize2304_1152,	///< 2304*1152
	imageSize2304_2304,	///< 2304*2304
	imageSize2432_1216,	///< 2432*1216
	imageSize2432_2432,	///< 2432*2432
	imageSize3072_768,	///< 3072*768
	imageSize3840_960,	///< 3840*960
	imageSize4288_1072,	///< 4288*1072
	imageSize4608_1152,	///< 4608*1152
	imageSize4864_1216,	///< 4864*1216
	imageSize1072_1072,	///< 1072*1072
	imageSize2144_2144,	///< 2144*2144
	imageSize336_256,	///< 336*256
	imageSize960_1080,	///< 960*1080
	imageSize4096_832,	///< 4096*832
	imageSize3840_780,	///< 3840*780
	imageSize2560_520,	///< 2560*520
	imageSize1024_208,	///< 1024*208
	imageSize1280_260,	///< 1280*260
	imageSize720_576,	///< 720*576
	imageSize4096_1800,	///< 4096*1800
	imageSize3840_1680,	///< 3840*1680
	imageSize2880_1264,	///< 2880*1264
	imageSize1024_452,	///< 1024*452
	imageSize1920_832,	///< 1920*832
	imageSize1280_560,	///< 1280*560
	imageSize3072_1728,	///< 3072*1728
	imageSize432_240,	///< 432*240
	imageSize784_440,	///< 784*440
	imageSizeNR,		///< 枚举的图形大小种类的数目。
};

/// 基于当前制式，根据图像实际分辨率得到图像分辨率类型
/// \param [in] width 图像宽度，像素为单位
/// \param [in] height 图像高度，像素为单位
/// \param [out] type 图像大小类型
/// \return true-找到了分辨率类型，false-没有找到分辨率类型
bool STREAM_API getImageSizeType(int width, int height, ImageSizeType& type);

/// 基于当前制式，根据图像分辨率类型得到图像实际分辨率
/// \param [in] type 图像大小类型
/// \param [in] vstd 视频制式
/// \param [out] width 图像宽度，像素为单位
/// \param [out] height 图像高度，像素为单位
/// \return true-找到了分辨率像素，false-没有找到分辨率像素
bool STREAM_API getImageSizePixels(ImageSizeType type, VideoStandard vstd, int& width, int& height);

/// 基于当前制式，根据图像实际分辨率得到图像分辨率类型
/// \param [in] width 图像宽度，像素为单位
/// \param [in] height 图像高度，像素为单位
/// \param [out] type 图像大小类型字符串，参见DHIIF
/// \return true-找到了分辨率类型，false-没有找到分辨率类型
bool STREAM_API getImageSizeType(int width, int height, std::string& type);

/// 基于当前制式，根据图像分辨率类型得到图像实际分辨率
/// \param [in] type 图像大小类型字符串，参见DHIIF
/// \param [in] vstd 视频制式
/// \param [out] width 图像宽度，像素为单位
/// \param [out] height 图像高度，像素为单位
/// \return true-找到了分辨率像素，false-没有找到分辨率像素
bool STREAM_API getImageSizePixels(std::string& type, VideoStandard vstd, int& width, int& height);

/// 根据分辨率名称获取图片分辨率类型
/// \param [in] resolution 分辨率名称
/// \param [out] type 图像大小类型
/// \return true 成功
/// \return false 失败
bool STREAM_API getImageSizeType(std::string const& resolution, ImageSizeType& type);

/// 根据分辨率类型获取分辨率名称
/// \param [in] type 分辨率类型
/// \param [out] resolution 分辨率名称
/// \return true 成功
/// \return false 失败
bool STREAM_API getImageSizeType(ImageSizeType type, std::string& resolution);

/// 获取排序后的分辨率类型列表，分辨率由小到大排列
/// \pararam [out] type 排序后的分辨率类型列表
/// \return true 成功
/// \return false 失败
bool STREAM_API getSortedImageSizeTypeList(std::vector<ImageSizeType>& list);

/// 添加分辨率类型信息
/// \param [in] type 图像大小类型
/// \param [in] name 图像大小类型字符串
/// \param [in] vstd 视频制式
/// \param [in] width 图像宽度，像素为单位
/// \param [in] height 图像高度，像素为单位
/// \return true 设置成功
/// \return false 设置失败
bool STREAM_API addImageSizeTypeInfo(ImageSizeType type, std::string const& name, VideoStandard vstd, int width, int heigth);

} // namespace Stream
} //namespace Dahua

#endif // __IMAGE_SIZE_H__


