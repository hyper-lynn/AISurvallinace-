// StreamPackage.h: interface for the StreamPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_)
#define AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(_WIN32)
	#ifdef SG_EXPORTS_DLL
		#define SG_PACKAGE_API __declspec(dllexport)
	#elif defined SG_USE_DLL
		#define SG_PACKAGE_API __declspec(dllimport)
	#else
		#define SG_PACKAGE_API
	#endif
	#define CALLMETHOD __stdcall
	#define CALLBACK   __stdcall
#else
	#define CALLMETHOD
	#define CALLBACK
	#define SG_PACKAGE_API
#endif

#if defined(_WIN32)
typedef __int64 SGint64;
#else /*linux*/
typedef long long SGint64;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*码流封装错误类型*/
typedef enum
{
	SG_ERR_NOERR = 0,
	SG_ERR_HANDLE_EMPTY,
	SG_ERR_INIT_FAIL,
	SG_ERR_PARAM_ERR,
	SG_ERR_MEMORY_OUT,
	SG_ERR_ENCODE_UNSUPPORT,
	SG_ERR_EMPTY_POINTER,
}SG_ERR_TYPE;

/*码流封装类型*/
typedef enum
{
	SG_STREAM_TYPE_MP4,			/* 封装格式 回写MP4 */
	SG_STREAM_TYPE_ASF,			/* 封装格式 ASF */
	SG_STREAM_TYPE_AVI,			/* 封装格式 AVI */
	SG_STREAM_TYPE_DAV,			/* 封装格式 DAV */
	SG_STREAM_TYPE_FLV,			/* 封装格式 FLV */
	SG_STREAM_TYPE_STREAM_ASF,	/* 封装格式 流式 ASF */
	SG_STREAM_TYPE_MOV,			/* 封装格式 MOV */
	SG_STREAM_TYPE_3GP,			/* 封装格式 3GP*/
	SG_STREAM_TYPE_STREAM_FLV,	/* 封装格式 流式 FLV */
	SG_STREAM_TYPE_RTP,			/* 封装格式 RTP */
	SG_STREAM_TYPE_TS		= 10,	/*标准TS封装*/
	SG_STREAM_TYPE_PS		= 11,	/*标准PS封装*/
	SG_STREAM_TYPE_MP4_NOSEEK = 12,	/* 封装格式 顺序写MP4，如光盘类不允许回写 */
	SG_STREAM_TYPE_MKV		= 13,	/* 封装格式为MKV */
	SG_STREAM_TYPE_MP4_64	= 14,	/*封装格式为64位MP4*/
	SG_STREAM_TYPE_MOV_64	= 15,	/*封装格式为64位MOV*/
	SG_STREAM_TYPE_WAV		= 16,	/*封装格式为WAV*/

	SG_STREAM_TYPE_DHPS		= 17,	/* 封装格式为大华PS */
	SG_STREAM_TYPE_GAYSPS	= 18,	/* 公安一所PS */
	SG_STREAM_TYPE_DAV_STREAM = 19,	/* RTSP传输码流 */
	SG_STREAM_TYPE_GDPS		= 20,	/* 广电PS*/
	SG_STREAM_TYPE_CDJFPS	= 21,	/*成都佳发PS*/
	SG_STREAM_TYPE_CDJFTS	= 22,	/*成都佳发TS*/
	SG_STREAM_TYPE_RAWDATA  = 23,	/*恒信加密码流*/
	SG_STREAM_TYPE_TZDZTS	= 24,	/*同洲电子TS*/
	SG_STREAM_TYPE_DHTS		= 25,	/*大华TS*/
}SG_STREAM_TYPE;

/*帧类型*/
typedef enum
{
	SG_FRAME_TYPE_VIDEO = 1,	/* 视频帧 */
	SG_FRAME_TYPE_AUDIO,		/* 音频帧 */
	SG_FRAME_TYPE_EXT			/* 大华扩展帧 */
}SG_FRAME_TYPE;

/*视频帧子类型*/
typedef enum
{
	SG_FRAME_SUB_TYPE_I,		/* I帧 */
	SG_FRAME_SUB_TYPE_P,		/* P帧 */
	SG_FRAME_SUB_TYPE_B,			/* B帧 */

	SG_FRAME_SUB_TYPE_WATERMARK_TEXT = 4,				/*水印数据为TEXT类型*/
	SG_FRAME_SUB_TYPE_WATERMARK_JPEG = 5,				/*水印数据为JPEG类型*/
	SG_FRAME_SUB_TYPE_WATERMARK_BMP = 6,				/*水印数据为BMP类型*/
	SG_FRAME_SUB_TYPE_DATA_INTL = 7,					/*智能分析帧*/
	SG_FRAME_SUB_TYPE_JPEG_FRAME = 8,             		/*JPEG 帧*/

	SG_FRAME_SUB_TYPE_DATA_INTLEX = 11,                  /*扩展智能分析帧*/
	SG_FRAME_SUB_TYPE_DATA_RAW = 15,						/*原始数据*/
	SG_FRAME_SUB_TYPE_DATA_VIDEO_SYNOPSIS = 16,			/*视频浓缩信息*/

	SG_FRAME_SUB_TYPE_SMART_I = 18,			/*smartH264 I帧*/
	SG_FRAME_SUB_TYPE_SMART_P = 19,			/*smartH264 P帧 只参考smart I帧*/
	SG_FRAME_SUB_TYPE_SMART_I_NORENDER = 20,/*smartH264 I帧,只解码不显示，用于seek和倒放功能(当做普通I帧处理)*/
	SG_FRAME_SUB_TYPE_UNKNOW

}SG_FRAME_SUB_TYPE;

/*编码类型*/
typedef enum
{
	SG_ENCODE_VIDEO_UNKNOWN = 0,		/*视频编码格式不可知*/
	SG_ENCODE_VIDEO_MPEG4 ,			    /*视频编码格式是MPEG4*/
	SG_ENCODE_VIDEO_HI_H264,			/*视频编码格式是海思H264*/
	SG_ENCODE_VIDEO_JPEG,				/*视频编码格式是标准JPEG*/
	SG_ENCODE_VIDEO_DH_H264,			/*视频编码格式是大华码流H264*/
	SG_ENCODE_VIDEO_JPEG2000 = 6,		/*视频编码格式是标准JPEG2000*/
	SG_ENCODE_VIDEO_AVS = 7,			/*视频编码格式是标准AVS*/
	SG_ENCODE_VIDEO_STD_H264 = 8,		/*视频编码格式是标准H264*/
	SG_ENCODE_VIDEO_MPEG2 = 9,          /*视频编码格式是MPEG2*/
	SG_ENCODE_VIDEO_VNC = 10,         	/*视频编码格式是VNC*/
	SG_ENCODE_VIDEO_SVAC = 11,          /*视频编码格式是SVAC*/
	SG_ENCODE_VIDEO_DH_H265 = 12,		/*视频编码格式是H265*/
	SG_ENCODE_VIDEO_SVAC2 = 13,			/*视频编码格式是SVAC2.0*/

	//视频编码类型扩展类型
	SG_ENCODE_VIDEO_H263 = 35,      /*视频编码格式是H263*/
	SG_ENCODE_VIDEO_PACKET,         /*视频包*/
	SG_ENCODE_VIDEO_MSMPEG4V1,		/*视频编码格式是MS MPEG4 V1*/
	SG_ENCODE_VIDEO_MSMPEG4V2,		/*视频编码格式是MS MPEG4 V2*/
	SG_ENCODE_VIDEO_MSMPEG4V3,		/*视频编码格式是MS MPEG4 V3*/
	SG_ENCODE_VIDEO_WMV1,			/*视频编码格式是MS MPEG4 V4*/
	SG_ENCODE_VIDEO_WMV2,			/*视频编码格式是MS MPEG4 V5*/

	//私有编码格式
	SG_ENCODE_VIDEO_HIK_H264 = 0x81,		/*海康私有H264码流*/
	SG_ENCODE_VIDEO_HIK_HKH4 = 0x82,
}SG_ENCODE_VIDEO_TYPE;

typedef enum
{
	SG_ENCODE_AUDIO_UNKNOWN = 0,
	SG_ENCODE_AUDIO_PCM = 7,			/*音频编码格式是PCM8*/
	SG_ENCODE_AUDIO_G729,				/*音频编码格式是G729*/
	SG_ENCODE_AUDIO_IMA,				/*音频编码格式是IMA*/
	SG_ENCODE_PCM_MULAW,				/*音频编码格式是PCM MULAW*/
	SG_ENCODE_AUDIO_G721,				/*音频编码格式是G721*/
	SG_ENCODE_PCM8_VWIS,				/*音频编码格式是PCM8_VWIS*/
	SG_ENCODE_MS_ADPCM,				    /*音频编码格式是MS_ADPCM*/
	SG_ENCODE_AUDIO_G711A,				/*音频编码格式是G711A*/
	SG_ENCODE_AUDIO_AMR,				/*音频编码格式是AMR*/
	SG_ENCODE_AUDIO_PCM16,				/*音频编码格式是PCM16*/
	SG_ENCODE_AUDIO_G711U = 22,		    /*音频编码格式是G711U*/
	SG_ENCODE_AUDIO_G723 = 25,			/*音频编码格式是G723*/
	SG_ENCODE_AUDIO_AAC,			    /*音频编码格式是AAC*/
	SG_ENCODE_AUDIO_G726_40,            /*40kbps,以下32/24/16*/
	SG_ENCODE_AUDIO_G726_32,            /*分别表示比特率的不同*/
	SG_ENCODE_AUDIO_G726_24,            /*相对于8k采样率的*/
	SG_ENCODE_AUDIO_G726_16,            /*情况下*/
	SG_ENCODE_AUDIO_MP2,                /*音频编码格式是mp2*/
	SG_ENCODE_AUDIO_OGG,                /*音频编码格式是ogg vorbis*/
	SG_ENCODE_AUDIO_MP3,           /*音频编码格式是mp3*/
	SG_ENCODE_AUDIO_G722_1,				/*音频编码格式是G722_1*/

	SG_ENCODE_AUDIO_TALK = 0x30,		/*音频编码格式是对讲*/
}SG_ENCODE_AUDIO_TYPE;


/*解交错标志*/
typedef enum
{
	SG_DEINTERLACE_PAIR = 0,				/*解码后拉伸*/
	SG_DEINTERLACE_SINGLE,					/*解码两次*/
	SG_DEINTERLACE_NONE						/*无解交错*/
}SG_DEINTERLACE_TYPE;

/*加密类型*/
typedef enum
{
	SG_ENCRYPT_AES,			/*AES加密*/
	SG_ENCRYPT_DES,			/*DES加密*/
	SG_ENCRYPT_3DES			/*3DES加密*/
}SG_ENCRYPT_TYPE;

#pragma pack(1)
/*视频信息 128Bytes*/
typedef struct
{
	int		bVideo;			/*视频信息是否有效*/
	int		videoencode;	/*视频编码信息 见SG_ENCODE_VIDEO_TYPE*/
	int		width;			/*视频宽度*/
	int		height;			/*视频高度*/
	int		framerate;		/*视频帧率*/
	unsigned char reserved[108];	/*保留字段*/
}SGVideoInfo;

/*音频信息 128Bytes*/
typedef struct
{
	int		bAudio;			/*音频信息是否有效*/
	int		audioencode;	/*音频编码信息 见SG_ENCODE_AUDIO_TYPE*/
	int		channels;		/*音频通道数*/
	int		sampledepth;	/*音频采样位数*/
	int		samplerate;		/*音频采样率*/
	int		bitrate;		/*音频比特率*/
	unsigned char reserved[104];	/*保留字段*/
}SGAudioInfo;

/*文件头信息 376Bytes*/
typedef struct
{
	unsigned int struct_size;	/*结构体长度校验位*/
	SGVideoInfo video;			/*视频编码信息*/
	SGAudioInfo audio;			/*音频编码信息*/

	unsigned int pre_header_len;/*预设文件头长度*/
	unsigned int timestamp_base;/*基准时间戳，-1(0xFFFFFFFF)表示不设定*/

	unsigned int use_system_time;	/* 是否强制使用系统时间，0表示不强制使用，1表示强制使用*/
	unsigned int sync_time_scale;	/* 同步间隔，以帧率为单位，0表示不同步，只在use_system_time为1时有效*/

	unsigned char BoschOsdCreated;	/* Bosch定制码流携带OSD，0表示默认不封装0xB1扩展帧头，1表示码流携带0xB1扩展帧头*/
	unsigned char nBoschOSDLen;		/* Bosch OSD扩展帧长度，包含此扩展帧头和size字节*/
	unsigned char nExtHeaderDataCheckType;	/*大华帧0x88数据校验类型，0表示默认使用sum32数据校验封装，1表示Sum32校验封装，2表示Xor32校验封装；3表示crc32校验封装*/
	unsigned char nUnableExtHeaderDataCheck;	/*大华帧是否封装0x88数据校验和，0：添加0x88校验和；1:不添加0x88校验和*/

	unsigned char reserved[104];	/*保留字段*/
}SGHeaderInfo;

typedef struct
{
	unsigned int struct_size;	/*结构体长度校验位*/
}SGTailerInfo;

/*分块图像信息 16Bytes*/
typedef struct
{
	short left;			/*当前分块在整个图像中的位置 左*/
	short top;			/*当前分块在整个图像中的位置 上*/
	short right;		/*当前分块在整个图像中的位置 右*/
	short bottom;		/*当前分块在整个图像中的位置 下*/
	int offset;			/*分块图像数据在帧数据中的偏移*/
	int reserved;		/*对齐字节*/
}SGBlockInfo;

//图像拼接信息
typedef struct
{
	int flag;				/*分屏信息是否有效*/
	int block_n;			/*分块横向块数*/
	int block_m;			/*分块纵向块数*/

	SGBlockInfo* pblock;	/*分块图像信息，长度为n*m*sizeof(SGBlockInfo)*/
}SGSplitInfo;

//帧数据信息
typedef struct
{
	unsigned int	struct_size;		/*结构体长度校验位*/

	unsigned char*	frame_pointer;		/*帧数据指针*/
	unsigned int	frame_size;			/*帧数据长度*/
	unsigned int	frame_type;			/*帧类型	SG_FRAME_TYPE*/
	unsigned int	frame_sub_type;		/*帧子类型	SG_FRAME_SUB_TYPE*/
	unsigned int	frame_encode;		/*编码类型	SG_ENCODE_VIDEO_TYPE | SG_ENCODE_AUDIO_TYPE*/
	unsigned int	frame_time;			/*帧时间戳*/
	unsigned int	frame_data;			/*日期时间，UTC时间*/

	unsigned int	width;				/*视频宽度*/
	unsigned int	heigth;				/*视频高度*/
	unsigned int	frame_rate;			/*视频帧率*/
	unsigned int	deinter_lace;		/*解交错信息*/

	unsigned int	sample_rate;		/*音频采样率*/
	unsigned int	bit_per_sample;		/*音频采样位数*/
	unsigned int	channels;			/*音频通道数*/
	unsigned int	bit_rate;			/*输出码率，单位kbps*/

	unsigned char	rtp_channel;		/*通道号 RTP使用*/
	unsigned char	align;				/*对齐位*/
	unsigned short	encrypt_offset;		/*加密数据偏移*/
	unsigned int	encrypt_datalen;	/*加密数据长度*/

	unsigned int	frame_seq;			/*帧序号*/

	unsigned char	lost_frame;			/*标记是否丢帧，0表示没有丢帧，1表示丢帧*/
	unsigned char   fisheye_Mode;		/*鱼眼模式*/
	unsigned short  fisheye_Radius;		/*鱼眼半径*/
	unsigned short  fisheye_CircleX;	/*鱼眼X坐标*/
	unsigned short  fisheye_CircleY;	/*鱼眼Y坐标*/
	
	unsigned char   fisheye_Style;		/*鱼眼安装位置*/
	unsigned char	reserved[135];		/*保留字段*/

	unsigned int	nOSDLen;			/*OSD信息的长度*/
	unsigned char*  pOSDData;			/*OSD信息的数据*/

	unsigned char   allLevels;          /*svc总层数*/
	unsigned char   levelOrder;         /*当前帧处于SVC的第几层*/

	// 0x96扩展帧头
	unsigned char   channel_count;      /*通道数，若帧类型为视频帧，则表示视频流的个数，若为音频帧，则表示音频流的个数*/
	unsigned char   channel_id;         /*通道号，从0开始*/

	SGSplitInfo		split_info;			/*图像拼接信息*/
	unsigned int	rotation_angle;		/*码流旋转角度*/
	unsigned short	company_type;		/*厂商类型*/
	unsigned short	tpstream_header_length;	/*三方码流文件头信息长度，tp:third party*/
}SGFrameInfo;


typedef struct
{
	unsigned int	struct_size;

	unsigned char*	data_pointer;			/*数据指针*/
	int				data_size;				/*数据长度*/
	int				offset_type;			/*数据偏移类型*/
	unsigned int	offset_pos;				/*数据偏移位置*/
	SGint64			offset_pos64;			/*数据偏移位置*/
}SGOutputData;

// 156字节
typedef struct
{
	int valid;			///< 是否包含有效数据，0不包含，1包含
	int frame_type;		///< 帧类型，取值SG_FRAME_TYPE
	int frame_subtype;	///< 帧子类型，取值SG_FRAME_SUB_TYPE
	SGint64 pts;		///< pts 时间戳
	SGint64 dts;		///< dts 时间戳
	union
	{
		SGVideoInfo video;	///< 视频信息
		SGAudioInfo audio;	///< 音频信息
	} u;
}SGOutputInfo;

typedef void* (*SGMalloc_t)(int memory_size);
typedef void  (*SGFree_t)(void* memory_pointer, int memory_size);
typedef void  (*SGDataCB_t)(SGOutputData* data, void* user);
typedef void  (*SGDataCBEx_t)(SGOutputData* data, SGOutputInfo* output_info, void* user);

//帧数据信息
typedef struct
{
	unsigned int	struct_size;

	void*			user;
	SGMalloc_t		sg_malloc;
	SGFree_t		sg_free;
	SGDataCB_t		sg_datacb;
	SGDataCBEx_t	sg_datacbEx;	/* 扩展的数据回调接口，附带额外的帧信息 */
}SGCreateParam;

typedef enum
{
	SG_CAPACITY_VIDEO = 0,			/* 视频编码参数集*/
	SG_CAPACITY_AUDIO				/* 音频编码参数集*/
}SG_CAPACITY_TYPE;

typedef struct
{
	unsigned int encode_type;		/* 视频编码类型，取值参考SG_ENCODE_VIDEO_TYPE*/
	unsigned int width;				/* 视频宽*/
	unsigned int height;			/* 视频高*/
	unsigned int frame_rate;		/* 帧率*/
	unsigned int reserved[4];		/* 保留字段*/
}SGVideoConstraint;

typedef struct
{
	unsigned int encode_type;		/* 音频编码类型，取值参考SG_ENCODE_AUDIO_TYPE*/
	unsigned int sample_rate;		/* 采样率*/
	unsigned int bit_per_sample;	/* 采样位数*/
	unsigned int channels;			/* 通道数*/
	unsigned int bit_rate;			/* 比特率*/
	unsigned int reserved[3];		/* 保留字段*/
}SGAudioConstraint;

#pragma pack()

/********************************************************************
*	Funcname: 	    	SG_GetVersion
*	Purpose:			获取svn版本信息
*   InputParam:         void
*   Return:             库版本号字符串
*   Created:	        2018.08.24
*   Revision Record:    Ver 1.0:niu_xiaoxue
*********************************************************************/
SG_PACKAGE_API char* CALLMETHOD SG_GetVersion(void);

/********************************************************************
*	Funcname: 	    	StreamPacket_CreateHandle
*	Purpose:			创建打包句柄
*   InputParam:         nType : 打包类型  SG_STREAM_TYPE
*						pFilePath : 目标文件路径
*   Return:             void* : 返回打包句柄， 失败返回NULL
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API void* CALLMETHOD SG_CreateHandle(unsigned int nType, SGCreateParam* pCreateParam);

/********************************************************************
*	Funcname: 	    	StreamPacket_DestroyHandle
*	Purpose:			删除打包句柄
*   InputParam:         handle : 打包句柄
*   Return:             成功返回 SG_ERR_NOERR，失败返回错误码
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_DestroyHandle(void* handle);

/********************************************************************
*	Funcname: 	    	StreamPacket_CreateHeader
*	Purpose:			创建文件头
*   InputParam:         handle : 打包句柄
*						pFilePath : 保存文件路径
*   Return:             成功返回 SG_ERR_NOERR，失败返回错误码
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_CreateHeader(void* handle, SGHeaderInfo* pHeader);

/********************************************************************
*	Funcname: 	    	StreamPacket_InputData
*	Purpose:			传入媒体数据
*   InputParam:         handle : 打包句柄
*						frame_info : 需要打包的媒体信息
*   Return:             成功返回 SG_ERR_NOERR，失败返回错误码
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_InputFrame(void* handle, SGFrameInfo* pFrame);

/********************************************************************
*	Funcname: 	    	StreamPacket_CreateTailer
*	Purpose:			删除打包句柄
*   InputParam:         handle : 打包句柄
*   Return:             成功返回 SG_ERR_NOERR，失败返回错误码
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_CreateTailer(void* handle, SGTailerInfo* pTailer);

/********************************************************************
*	Funcname: 	    	SG_GetBackup
*	Purpose:			获取备份数据，用于数据断电恢复
*   InputParam:         handle : 打包句柄
*   Return:             成功返回 SG_ERR_NOERR，失败返回错误码
*   Created:	        2013.11.28
*   Revision Record:    Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_GetBackup(void* handle, SGOutputData* backup);

/********************************************************************
*	Funcname:			SG_SetEncryptType
*	Purpose:			设置加密类型,密钥及密钥长度,实现加密功能
*	InputParam:			handle : 打包句柄
						type: 加密类型，见SG_ENCRYPT_TYPE
						key: 秘钥指针, key为NULL时，会清空之前的秘钥。
						keylen: 秘钥长度
*	Return:				成功返回 SG_ERR_NOERR，失败返回错误码
*	Created:			2013.11.28
*	Revision Record:	Ver 1.0:z_junjie
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_SetEncryptType(void* handle, int type, unsigned char* key, int keylen);

/********************************************************************
*	Funcname:			SG_GetPacketCapacity
*	Purpose:			获取封装格式建议的编码参数集。注，非线程安全
*	InputParam:			handle: 打包句柄
*						type: 建议编码参数集的类型，取值SG_CAPACITY_TYPE
*						capacity: 建议的编码参数集，存储在结构体SGVideoConstraint和SGAudioConstraint中
*						capacity_count:	建议的编码参数集的数目
*	Return:				成功返回 SG_ERR_NOERR，失败返回错误码
*	Created:			2016.8.4
*	Revision Record:	Ver 1.0: wang_geng
*********************************************************************/
SG_PACKAGE_API int CALLMETHOD SG_GetPacketCapacity(void* handle, SG_CAPACITY_TYPE type, const void** capacity, int* capacity_count);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_)

