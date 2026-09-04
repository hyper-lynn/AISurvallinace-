/********************************************************************
*	Copyright 1992-2008, ZheJiang Dahua Technology Stock Co.Ltd.
* 						All Rights Reserved
*	File Name: 	        StreamParser.h
*	Description:	    DLL导出的接口函数
*********************************************************************/

#ifndef _SP_STREAM_PARSER_H_
#define _SP_STREAM_PARSER_H_

#define IN
#define OUT

#if (defined(WIN32) || defined(WIN64))
#ifdef SP_EXPORTS_DLL
	#define STREAMPARSER_API __declspec(dllexport)
#elif defined(SP_USE_DLL)
	#define STREAMPARSER_API __declspec(dllimport)
#else
	#define STREAMPARSER_API
#endif
	#define CALLMETHOD __stdcall
#else
	#define STREAMPARSER_API
	#define CALLMETHOD
#endif

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*接口返回值*/
enum SP_RESULT
{
    SP_SUCCESS = 0,                     /*成功*/
    SP_ERROR_INVALID_HANDLE,            /*无效句柄*/
    SP_ERROR_FILE_TYPE_NOSUPPORT,       /*文件类型不支持*/
    SP_ERROR_STREAM_NOSUPPORT,          /*流类型不支持*/
    SP_ERROR_THREAD_CREATE_FAILED,      /*线程创建失败*/
    SP_ERROR_THREAD_CLOSE_FAILED,       /*线程关闭失败*/
    SP_ERROR_PARAMETER,                 /*参数有误*/
    SP_ERROR_INDEX_OUTOFRANGE,	        /*索引超过范围*/
    SP_ERROR_FILE_SIZE_ZERO,			/*文件大小为0*/
    SP_ERROR_BAD_FORMATTED,     	    /*文件格式错误*/
    SP_ERROR_FILE_READ,	                /*读取文件失败*/
    SP_ERROR_FILE_OPEN,                 /*打开文件失败*/
    SP_ERROR_BUFFER_OVERFLOW,           /*内部缓冲区溢出*/
    SP_ERROR_SYSTEM_OUT_OF_MEMORY,      /*系统内存不够*/
    SP_ERROR_LIST_EMPTY,                /*列表为空*/
	SP_ERROR_UNGET_STREAM_TYPE			/*未获取到码流类型*/
};

/*帧类型*/
enum
{
	SP_FRAME_TYPE_UNKNOWN = 0,			/*帧类型不可知*/
	SP_FRAME_TYPE_VIDEO,				/*帧类型是视频帧*/
	SP_FRAME_TYPE_AUDIO,				/*帧类型是音频帧*/
	SP_FRAME_TYPE_DATA					/*帧类型是数据帧*/
};

/*帧子类型*/
enum
{
	SP_FRAME_SUB_TYPE_DATA_INVALID = -1,			/*数据无效*/
	SP_FRAME_SUB_TYPE_VIDEO_I_FRAME = 0 ,			/*I帧*/
	SP_FRAME_SUB_TYPE_VIDEO_P_FRAME,				/*P帧*/
	SP_FRAME_SUB_TYPE_VIDEO_B_FRAME,				/*B帧*/
	SP_FRAME_SUB_TYPE_VIDEO_S_FRAME,				/*S帧*/
	SP_FRAME_SUB_TYPE_WATERMARK_TEXT,				/*水印数据为TEXT类型*/
	SP_FRAME_SUB_TYPE_WATERMARK_JPEG,				/*水印数据为JPEG类型*/
	SP_FRAME_SUB_TYPE_WATERMARK_BMP,				/*水印数据为BMP类型*/
	SP_FRAME_SUB_TYPE_DATA_INTL,					/*智能分析帧*/
	SP_FRAME_SUB_TYPE_VIDEO_JPEG_FRAME,             /*JPEG 帧*/
	SP_FRAME_SUB_TYPE_DATA_ITS,				        /*its信息帧*/
	SP_FRAME_SUB_TYPE_DATA_GPS,					    /*gps*/
	SP_FRAME_SUB_TYPE_DATA_INTLEX,                  /*扩展智能分析帧*/
	SP_FRAME_SUB_TYPE_DATA_MOTION_FULL,				/*全屏动检*/
	SP_FRAME_SUB_TYPE_DATA_MOTION_CARD,				/*全屏动检(板卡)*/
	SP_FRAME_SUB_TYPE_DATA_LIGHT,					/*光照*/
	SP_FRAME_SUB_TYPE_DATA_RAW,						/*原始数据*/
	SP_FRAME_SUB_TYPE_DATA_VIDEO_SYNOPSIS,			/*视频浓缩信息*/
	SP_FRAME_SUB_TYPE_DATA_SDP,						/*SDP信息*/
	SP_FRAME_SUB_TYPE_VIDEO_SMART_I_FRAME,			/*smartH264 I帧*/
	SP_FRAME_SUB_TYPE_VIDEO_SMART_P_FRAME,			/*smartH264 P帧 只参考smart I帧*/
	SP_FRAME_SUB_TYPE_VIDEO_SMART_I_NORENDER,		/*smartH264 I帧,只解码不显示，用于seek和倒放功能*/

	SP_FRAME_SUB_TYPE_DATA_I_INDEX = 128,           /*I帧索引帧*/
	SP_FRAME_SUB_TYPE_DATA_MOTION,                  /*动检数据帧*/
	SP_FRAME_SUB_TYPE_DATA_LABEL,                   /*标签帧*/
	SP_FRAME_SUB_TYPE_DATA_SCREEN_CAPTION,          /*字幕*/
	SP_FRAME_SUB_TYPE_DATA_EVENT,                   /*事件帧*/
	SP_FRAME_SUB_TYPE_DATA_FILEHEAD = 255,          /*文件头帧*/
	SP_FRAME_SUB_TYPE_DATA_UNKOWN,                  /*未知类型*/
};
/*lint -save -e849*/
/*编码类型*/
enum SP_ENCODE_VIDEO_TYPE
{
	SP_ENCODE_VIDEO_UNKNOWN = 0,		/*视频编码格式不可知*/
	SP_ENCODE_VIDEO_MPEG4 ,				/*视频编码格式是MPEG4*/
	SP_ENCODE_VIDEO_HI_H264,			/*视频编码格式是海思H264*/
	SP_ENCODE_VIDEO_JPEG,				/*视频编码格式是标准JPEG*/
	SP_ENCODE_VIDEO_DH_H264,			/*视频编码格式是大华码流H264*/
	SP_ENCODE_VIDEO_JPEG2000 = 6,		/*视频编码格式是标准JPEG2000*/
	SP_ENCODE_VIDEO_AVS = 7,			/*视频编码格式是标准AVS*/
	SP_ENCODE_VIDEO_STD_H264 = 8,		/*视频编码格式是标准H264*/
	SP_ENCODE_VIDEO_MPEG2 = 9,			/*视频编码格式是MPEG2*/
	SP_ENCODE_VIDEO_VNC = 10,			/*视频编码格式是VNC*/
	SP_ENCODE_VIDEO_SVAC = 11,			/*视频编码格式是SVAC*/
	SP_ENCODE_VIDEO_DH_H265 = 12,		/*视频编码格式是H265*/

	//视频编码类型扩展类型
	SP_ENCODE_VIDEO_H263 = 35,      /*视频编码格式是H263*/
	SP_ENCODE_VIDEO_PACKET,         /*视频包*/
	SP_ENCODE_VIDEO_MSMPEG4V1,		/*视频编码格式是MS MPEG4 V1*/
	SP_ENCODE_VIDEO_MSMPEG4V2,		/*视频编码格式是MS MPEG4 V2*/
	SP_ENCODE_VIDEO_MSMPEG4V3,		/*视频编码格式是MS MPEG4 V3*/
	SP_ENCODE_VIDEO_WMV1,			/*视频编码格式是MS MPEG4 V4*/
	SP_ENCODE_VIDEO_WMV2,			/*视频编码格式是MS MPEG4 V5*/
	SP_ENCODE_VIDEO_RV10,			/*视频编码格式是RV10*/
	SP_ENCODE_VIDEO_RV20,			/*视频编码格式是RV20*/
	SP_ENCODE_VIDEO_RV30,			/*视频编码格式是RV30*/
	SP_ENCODE_VIDEO_RV40,			/*视频编码格式是RV40*/
	SP_ENCODE_VIDEO_FLV1,			/*视频编码格式是FLV1*/
	SP_ENCODE_VIDEO_FLASHSV,		/*视频编码格式是FLASHSV*/
	SP_ENCODE_VIDEO_FLASHSV2,		/*视频编码格式是FLASHSV2*/
	SP_ENCODE_VIDEO_VP6,			/*视频编码格式是VP6*/
	SP_ENCODE_VIDEO_VP6A,			/*视频编码格式是VP6A*/
	SP_ENCODE_VIDEO_VP6F,			/*视频编码格式是VP6F*/

	//私有编码格式
	SP_ENCODE_VIDEO_HIK_H264 = 0x81,		/*海康私有H264码流*/
	SP_ENCODE_VIDEO_HIK_HKH4 = 0x82,
	SP_ENCODE_VIDEO_LY_N264  = 0x83,		/*立元asf格式中的N264*/
};

enum SP_ENCODE_AUDIO_TYPE
{
	SP_ENCODE_AUDIO_UNKNOWN = 0,
	SP_ENCODE_AUDIO_PCM = 7,			/*音频编码格式是PCM8*/
	SP_ENCODE_AUDIO_G729,				/*音频编码格式是G729*/
	SP_ENCODE_AUDIO_IMA,				/*音频编码格式是IMA*/
	SP_ENCODE_PCM_MULAW,				/*音频编码格式是PCM MULAW*/
	SP_ENCODE_AUDIO_G721,				/*音频编码格式是G721*/
	SP_ENCODE_PCM8_VWIS,				/*音频编码格式是PCM8_VWIS*/
	SP_ENCODE_MS_ADPCM,					/*音频编码格式是MS_ADPCM*/
	SP_ENCODE_AUDIO_G711A,				/*音频编码格式是G711A*/
	SP_ENCODE_AUDIO_AMR,				/*音频编码格式是AMR*/
	SP_ENCODE_AUDIO_PCM16,				/*音频编码格式是PCM16*/
	SP_ENCODE_AUDIO_G711U = 22,			/*音频编码格式是G711U*/
	SP_ENCODE_AUDIO_G723 = 25,			/*音频编码格式是G723*/
	SP_ENCODE_AUDIO_AAC,				/*音频编码格式是AAC*/
	SP_ENCODE_AUDIO_G726_40,            /*40kbps,以下32/24/16*/
	SP_ENCODE_AUDIO_G726_32,            /*分别表示比特率的不同*/
	SP_ENCODE_AUDIO_G726_24,            /*相对于8k采样率的*/
	SP_ENCODE_AUDIO_G726_16,            /*情况下*/
	SP_ENCODE_AUDIO_MP2,				/*音频编码格式是mp2*/
	SP_ENCODE_AUDIO_OGG,				/*音频编码格式是ogg vorbis*/
	SP_ENCODE_AUDIO_MP3,				/*音频编码格式是mp3*/
	SP_ENCODE_AUDIO_G722_1,				/*音频编码格式是G722_1*/

	SP_ENCODE_AUDIO_TALK = 0x30,		/*音频编码格式是对讲*/
	SP_ENCODE_AUDIO_AC3,				/*音频编码格式是AC3*/
};

/*码流封装格式*/
enum
{
	SP_STREAM_TYPE_UNKNOWN = 0, /*未知码流*/
	SP_STREAM_TYPE_MPEG4,       /*MPEG4*/
	SP_STREAM_TYPE_DHPT =3,	    /*大华老码流：DHPT*/
	SP_STREAM_TYPE_NEW,         /*大华老码流：NEW*/
	SP_STREAM_TYPE_HB,          /*大华老码流：HB*/
	SP_STREAM_TYPE_AUDIO,       /*音频流*/
	SP_STREAM_TYPE_PS,          /*MPEG-2：PS*/
	SP_STREAM_TYPE_DHSTD,       /*大华最新的标准码流*/
	SP_STREAM_TYPE_ASF,         /*ASF*/
	SP_STREAM_TYPE_3GPP,        /*3GP*/
	SP_STREAM_TYPE_RAW,	        /*大华老码流：裸码流*/
	SP_STREAM_TYPE_TS,          /*MPEG-2：TS*/
	SP_STREAM_TYPE_SVC,         /*svc*/
	SP_STREAM_TYPE_AVI,         /*AVI*/
	SP_STREAM_TYPE_MP4,         /*MP4*/
	SP_STREAM_TYPE_CGI,         /*CGI*/
	SP_STREAM_TYPE_WAV,			/*WAV音频*/
	SP_STREAM_TYPE_FLV,         /*FLV*/

	SP_STREAM_TYPE_MKV,         /*mkv*/
	SP_STREAM_TYPE_RTP,			/*RTP*/
	SP_STREAM_TYPE_RAW_MPEG4,	/*MPEG4裸码流*/
	SP_STREAM_TYPE_RAW_H264,	/*H264裸码流*/
	SP_STREAM_TYPE_RAW_H265,	/*H265裸码流*/
	SP_STREAM_TYPE_WMV,			/*WMV*/
	SP_STREAM_TYPE_RAW_MPEG2,	/*MPEG2裸码流*/
	SP_STREAM_TYPE_RAW_SVAC,	/*SVAC裸码流*/
	SP_STREAM_TYPE_MOV,
	SP_STREAM_TYPE_VOB,			/*VOB*/
	SP_STREAM_TYPE_RAW_H263,
	SP_STREAM_TYPE_RM,
	SP_STREAM_TYPE_DHPS,		/*MPEG-2：PS*/

	// 第三方厂商类型，从0x81开始，和通用厂商做区分
	SP_STREAM_TYPE_HENGYI = 0x81,	//恒易
	SP_STREAM_TYPE_HUANGHE,		//黄河
	SP_STREAM_TYPE_LANGCHI,		//朗驰
	SP_STREAM_TYPE_TDWY,		//天地伟业
	SP_STREAM_TYPE_DALI,		//大立
	SP_STREAM_TYPE_LVFF,		//LVFF文件头，未知厂商
	SP_STREAM_TYPE_H3C,			//华三
	SP_STREAM_TYPE_FENGDA,		//丰达录像
	SP_STREAM_TYPE_MDVRX,		//文件头MDVRX，未知厂商
	SP_STREAM_TYPE_PU8000,		//文件头pu8000，未知厂商
	SP_STREAM_TYPE_DVR,			//后缀名dvr，未知厂商
	SP_STREAM_TYPE_IFV,			//后缀名ifv，未知厂商
	SP_STREAM_TYPE_264DV,		//文件头264dv，未知厂商
	SP_STREAM_TYPE_ZWSJ,		//中维世纪
	SP_STREAM_TYPE_SANLI,		//金三立
	SP_STREAM_TYPE_HIK_PRIVATE,	//海康私有码流
	SP_STREAM_TYPE_HIK_PS,		//海康PS流
	SP_STREAM_TYPE_STAR,		//星望私有码流
	SP_STREAM_TYPE_LIYUAN,		//立元私有码流
	SP_STREAM_TYPE_KAER,		//北京卡尔视通码流
	SP_STREAM_TYPE_SSAV,		//SSAV某未知厂商码流
	SP_STREAM_TYPE_ZLAV,		//ZLAV智诺码流
};

/*码流支持的解析类型，通过 SP_GetParseType 接口返回*/
enum
{
	SP_PARSE_TYPE_NOT_SUPPORT = 0,
	SP_PARSE_TYPE_ONLY_STREAM = 1,
	SP_PARSE_TYPE_ONLY_FILE = 2,
	SP_PARSE_TYPE_SUPPORT_ALL = 3,
};

/*错误标志位*/
enum
{
	SP_ERROR_FLAGS_NOERROR = 0,		    /*数据校验无误*/
	SP_ERROR_FLAGS_TIMESTAND,			/*时间戳错误*/
	SP_ERROR_FLAGS_LENGTH,				/*长度出错*/
	SP_ERROR_FLAGS_HEAD_VERIFY,		    /*帧头内部数据校验*/
	SP_ERROR_FLAGS_DATA_VERIFY,		    /*数据校验失败*/
	SP_ERROR_FLAGS_LOST_HEADER,		    /*数据丢失帧头*/
	SP_ERROR_FLAGS_UNKNOWN,			    /*不可知错误*/
	SP_ERROR_FLAGS_LOSTFRAME,           /*丢帧*/
	SP_ERROR_FLAGS_WATERMARK,           /*水印校验错误*/
	SP_ERROR_FLAGS_CONTEXT,             /*上下文错误*/
	SP_ERROR_FLAGS_NOSUPPORT,           /*不支持的码流*/
    SP_ERROR_FLAGS_FRAME_HALF_BAKED     /*帧不完整*/
};

/*解交错标志*/
enum
{
	SP_DEINTERLACE_PAIR = 0, /*解码后拉伸*/
	SP_DEINTERLACE_SINGLE,   /*解码两次*/
	SP_DEINTERLACE_NONE      /*无解交错*/
};

/*索引类型标志位*/
enum
{
	SP_INDEX_BIT_FLAG_VIDEO_I = 1,         /*视频I帧*/
	SP_INDEX_BIT_FLAG_VIDEO_P = 2,         /*视频P帧*/
	SP_INDEX_BIT_FLAG_VIDEO_B = 4,         /*视频B帧*/
	SP_INDEX_BIT_FLAG_AUDIO = 8,           /*音频帧*/
	SP_INDEX_BIT_FLAG_DATA = 16,           /*数据帧*/
	SP_INDEX_BIT_FLAG_ALL = 0xffffffff     /*所有帧*/
};

/*时间信息*/
typedef struct
{
	int nYear;			/*年*/
	int nMonth;			/*月*/
	int nDay;			/*日*/
	int nHour;			/*小时*/
	int nMinute;		/*分钟*/
	int nSecond;		/*秒*/
	int nMilliSecond;	/*毫秒*/
} SP_TIME;

/*透雾参数*/
typedef struct
{
    int bIsExist;          /*是否存在此结构 0:不存在 1:存在*/
    int nMode;             /*透雾模式 1:关闭 2:自动 3:手动 其它:保留*/
    int nIntension;        /*透雾强度0-2*/
    int nAirLightMode;     /*大气光模式1:自动 2: 手动 其它:保留*/
    int nAirLightIntesion; /*大气光强度0-15*/
}SP_FOG_THROUGH;

/*厂商类型*/
enum
{
    SP_COMPANY_TYPE_HIK = 1,                    /*海康码流*/
    SP_COMPANY_TYPE_HANBANG,                    /*汉邦码流*/
    SP_COMPANY_TYPE_YUSHI,                      /*宇视码流*/
    SP_COMPANY_TYPE_INTERNATIONAL_DEVICE_PS,    /*国际设备PS码流*/
    SP_COMPANY_TYPE_XINCHAN,                    /*信产码流*/
    SP_COMPANY_TYPE_LIYUAN,                     /*立元码流*/
    SP_COMPANY_TYPE_BIT,                        /*比特码流*/
    SP_COMPANY_TYPE_OLD_DH,                     /*老大华码流*/
    SP_COMPANY_TYPE_STD_TS,                     /*标准ts流*/
    SP_COMPANY_TYPE_TDYG,                       /*天地阳光*/
    SP_COMPANY_TYPE_ANXUNSHI,                   /*安迅士*/
    SP_COMPANY_TYPE_DFWL,                       /*东方网力*/
    SP_COMPANY_TYPE_JUFENG,                     /*巨峰*/
    SP_COMPANY_TYPE_KEDA,                       /*科达*/
    SP_COMPANY_TYPE_LG,                         /*LG*/
    SP_COMPANY_TYPE_MAISHI,                     /*迈视*/
    SP_COMPANY_TYPE_TONGZUN,                    /*同尊*/
    SP_COMPANY_TYPE_VIVO,                       /*vivo*/
    SP_COMPANY_TYPE_WEIHAO,                     /*伟昊*/
    SP_COMPANY_TYPE_XINGWANG,                   /*星望*/
    SP_COMPANY_TYPE_BJWS,                       /*北京蛙视*/
    SP_COMPANY_TYPE_XJSX,                       /*先进视讯*/
    SP_COMPANY_TYPE_SZXY,                       /*深圳信义*/
    SP_COMPANY_TYPE_ZSYH,                       /*中盛益华*/
    SP_COMPANY_TYPE_ZXLW,                       /*中兴力维*/
    SP_COMPANY_TYPE_ZXTX,                        /*中兴通讯*/
	SP_COMPANY_TYPE_HIK_NOHEAD	= 57,		/*海康码流 无40字节头*/
};

/*加密类型*/
enum
{
    SP_ENCRYPT_UNKOWN = 0,
    SP_ENCRYPT_AES,
    SP_ENCRYPT_DES,
    SP_ENCRYPT_3DES,
    SP_ENCRYPT_KTJM,                        /*凯天加密算法*/
    SP_ENCRYPT_SYJM,                        /*晟元加密算法*/
	SP_ENCRYPT_HZSD,                        /*杭师大加密算法*/
	SP_ENCRYPT_ZBQL,                        /*中标麒麟加密算法*/
};

/*数字签名摘要算法类型*/
enum
{
	SP_DIGEST_ALGORITHM_UNKOWN = 0,
	SP_DIGEST_ALGORITHM_SHA1,
};

/*数字签名加密算法类型*/
enum
{
	SP_DIGTAL_SIGNATURE_ENCRYPT_UNKOWN = 0,
	SP_DIGTAL_SIGNATURE_ENCRYPT_RSA,

};

typedef struct
{
    int nVideoEncodeType;         /*视频编码类型*/
    int nFrameRate;               /*帧率*/
    int nWidth;                   /*宽*/
    int nHeight;                  /*高*/
    int nSPS_PPSLen;              /*sps和pps信息长*/
    unsigned char* pSPS_PPSData;  /*sps和pps信息*/
    int nAudioEncodeType;         /*音频编码类型*/
    int nSamplerPerSec;           /*音频采样率*/
    int bitsPerSample;            /*音频采样位数*/
}SP_SDP_INFO;

typedef struct
{
	unsigned char chType;		// 1:按字节（无符号数）进行算数＋
	unsigned char chLength;		// type中规定的操作单元长度
	unsigned char chValue;		// 操作数
	unsigned char nReserved;
}SP_DATA_CUSTOM_CHANGE;

/*帧信息 256字节*/
typedef struct
{
	/*类型*/
	int				frameType;			/*帧类型*/
	int				frameSubType;		/*帧子类型*/
	int				frameEncodeType;	/*帧编码类型*/
	int				streamType;			/*码流类型*/

	/*数据*/
	unsigned char*	streamPointer;		/*指向码流数据,去除帧头,NULL表示无效数据*/
	int				streamLen;			/*码流长度(不包括帧头、尾)*/
	unsigned char*	framePointer;		/*指向帧头,NULL表示无效数据*/
	int				frameLen;			/*帧长度(包括帧头、帧体、帧尾)*/

	/*时间*/
	SP_TIME			frameTime;			/*时间信息*/
	int				timeStamp;			/*时间戳*/

	/*序号*/
	int				frameSeq;			/*帧序号*/

	/*视频属性，关键帧才有*/
	int				frameRate;			/*帧率*/
	int				width;				/*宽*/
	int				height;				/*高*/
	int				deinterlace;		/*解交错*/
	int				mediaFlag;			/*流类型标记，h264解码用(0：大华码流；2：海思码流)*/

	/*音频属性*/
	int				samplesPerSec;		/*采样频率*/
	int				bitsPerSample;		/*采样位数*/
	int				channels;			/*声道数*/

	/*错误标志*/
	int				errorFlags;			/*按错误标志位*/

    SP_FOG_THROUGH  fogThrough;         /*透雾参数*/

    unsigned char   allLevels;          /*svc总层数*/
    unsigned char   levelOrder;         /*当前帧处于第几层*/

    unsigned short  companyType;        /*厂商类型*/
    unsigned short  tpStreamHeaderLen;  /*三方码流文件头信息长度，tp:third party*/

    /*支持双音频、双视频部分*/
	unsigned char   totalChannels;      /*通道数，若帧类型为视频帧，则表示视频流的个数，若为音频帧，则表示音频流的个数*/
	unsigned char   curChannel;         /*通道号，从0开始*/

    int             nEncryptType;       /*加密类型*/
    int             nEncryptLen;        /*加密长度*/

	SP_DATA_CUSTOM_CHANGE customChangeInfo; /*描述数据被特殊修改的情况，用于用户特殊需求*/

	/*分数帧率支持*/
	unsigned short rateValue;			/*帧率分子*/
	unsigned short rateDenominator;		/*帧率分母*/

	/*分屏支持*/
	unsigned short n_slice;
	unsigned short m_slice;
	unsigned short srcPicWidth;
	unsigned short srcPicHeight;
	unsigned short sliceInfoOffset;		/*相对于framePointer*/
	unsigned short sliceInfoLength;		/*分块图像信息的长度*/

	/*鱼眼信息, 注意：鱼眼的安装方式(0表示不是鱼眼设备，为0，后续字段都无效*/
	unsigned char fishEyeGain;			/*增益，取值0-100*/
	unsigned char fishEyeDenoiseLevel;	/*降噪等级，取值0-100*/
	unsigned char fishInstallStyle;		/*鱼眼安装方式，0：无意义 1：顶装 2：壁装 3：地装*/

	unsigned char fishEyeCorrectMode;	/*鱼眼矫正模式
										1:"Original"原始图像模式
										2:"Config"配置模式
										3:"Panorama"全景模式
										4:"DoublePanorama"双全景模式
										5:"OriginalPlusThreeEPtsRegion"1+3模式
										6:"Single"单画面EPts模式
										7:"FourEPtsRegion"4画面模式
										8:"Normal"Normal模式
										*/
	unsigned short fishEyeCircleX;		/*鱼眼圆心坐标X*/
	unsigned short fishEyeCircleY;		/*鱼眼圆心坐标Y*/
	unsigned short fishEyeRadius;		/*鱼眼半径*/
	unsigned short encryptOffset;		//0x95

	int pictrueStructure;				//0 或 3 为帧编码，1 和 2为场编码

	/*视频宽高比例0x9B*/
	unsigned char ratioWidth;//0x9b /*编码前宽高比例*/
	unsigned char ratioHeigth;
	unsigned char ratioEncodeWidth;/*编码后宽高比例*/
	unsigned char ratioEncodeHeight;

	unsigned int digtalSignatureSamplenlen; //0x9C

	unsigned short digtalSignatureEncdeclen;
	unsigned char digtalSignatureDigestType;
	unsigned char digtalSignatureEncryptType;

	unsigned char* digtalSignatureEncdecDataPtr;

	unsigned char  rotationAngle;  /*码流旋转角度*/

	unsigned char svacEncryptKeyLen;  //0xB0 录像加密帧
	unsigned short svacEncryptDataLen;

	unsigned char* svacEncryptKeyData;

	//音频属性
	unsigned int audioBitrate;			//音频比特率

	unsigned char*	extDataPtr;			//扩展数据
	unsigned int	extDataLen;			//扩展数据长度

	unsigned char bFrameNum;			//两个P帧之间的B帧数

	unsigned char osdExtDataLen;		//OSD扩展长度
	unsigned char resv[2];
	unsigned char* osdExtDataPtr;		//OSD扩展数据

	unsigned int refIFrameSeq;			//重定位P帧参考的I帧帧序号，既frameSeq值

	unsigned int encryptCheckSum;		// 0xB3密钥CRC校验和
	unsigned char	encryptNonse[2];	// 0xB3密钥校验Nonce

	unsigned short	programCount;		// 节目总数
	unsigned short	programNum;			// 节目编号

	// 多目Sensor位置属性
	unsigned char nSliceSensor;			// 多sensor n块
	unsigned char mSliceSensor;			// 多sensor m块
	unsigned short slicePosOffset;		// 帧头偏移量,相对于 framePointer
	unsigned short slicePosLength;		// 多目数据的坐标信息总长度 mSlice*nSlice*8

	/*扩展*/
	unsigned char	reserved[16];		/*保留字节*/
} SP_FRAME_INFO;

#if (defined(WIN32) || defined(WIN64))
typedef __int64 SPint64;
#else /*linux*/
typedef long long SPint64;
#endif

/*文件方式的帧信息*/
typedef	struct
{
	/*索引偏移量*/
	SPint64 streamOffset;	// 码流裸数据的偏移量(去除帧头)
	SPint64 frameOffset;	// 帧头的偏移量
	int		index;			// 帧回调顺序，即第几帧，从0开始。负值为无效值
	/*待扩展*/
	unsigned char	reserved[60];	/*保留字节*/
}SP_INDEX_INFO;

typedef	struct
{
	/*索引偏移量*/
	unsigned char*	modulePath;		//当前模块路径
	void*			moduleHandle;	//模块句柄
	/*待扩展*/
	unsigned char	reserved[56];	/*保留字节*/
}SP_INIT_INFO;

//结构体128字节
typedef	struct
{
	unsigned int filesize;		//文件总长度
	unsigned int createtime;	//创建时间 utc时间
	unsigned int duration;		//总时长(单位s)

	unsigned int framenum;		//总帧数
	unsigned int videonum;		//视频总帧数
	unsigned int audionum;		//音频总帧数

	unsigned int keyframenum;	//关键帧数
	unsigned int maxframesize;	//最大帧长度, 预估值

	/*待扩展*/
	unsigned char	reserved[96];	/*保留字节*/
}SP_FILE_INFO;

/********************************************************************
*	Funcname: 	    	fFileIndex
*	Purpose:	        文件索引回调函数
*   InputParam:         handle:	句柄
*                       frameInfo: 帧信息
*                       indexInfo: 索引信息
*                       process: 索引进度条,根据文件大小计算的百分数
*						userData: 用户自定义数据
*   OutputParam:        无
*   Return:             0:调用成功(只返回0)
*********************************************************************/
typedef int (CALLMETHOD *fFileIndex)(IN void* handle,
									 IN SP_FRAME_INFO* frameInfo,
									 IN SP_INDEX_INFO* indexInfo,
									 IN int process,
									 IN void* userData);

/********************************************************************
*	Funcname: 	    	fFileIndex
*	Purpose:	        文件信息回调函数
*   InputParam:         handle:	句柄
*                       fileInfo: 文件信息
*						userData: 用户自定义数据
*   OutputParam:        无
*   Return:             0:调用成功(只返回0)
*********************************************************************/
typedef int (CALLMETHOD *fFileInfo)(IN void* handle,
									 IN SP_FILE_INFO* fileInfo,
									 IN void* userData);

/********************************************************************
*	Funcname: 	    	SP_LoadLibrary
*	Purpose:	        加载动态链接库之后，需首先调用此函数初始化资源
*   InputParam:         initInfo: 初始化参数
*   OutputParam:        无
*   Return:             0:调用成功
*                       其他值：失败，通过SP_GetLastError获取错误码
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_LoadLibrary(SP_INIT_INFO* initInfo = NULL);

 /********************************************************************
 *	Funcname: 	    	SP_ReleaseLibrary
 *	Purpose:	        释放链接库资源，需在释放动态链接库之前调用此函数释放内部资源
 *  InputParam:         无
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_ReleaseLibrary(void);

 /********************************************************************
 *	Funcname: 	    	SP_CreateStreamParser
 *	Purpose:	        创建流分析器
 *  InputParam:         nBufferSize:(参数已失效，可以为任意值)
 *  OutputParam:        无
 *  Return:             NULL: 创建流分析器失败
 *                      其他值：流解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateStreamParser(IN int nBufferSize);

 /********************************************************************
 *	Funcname: 	    	SP_GetStreamType
 *	Purpose:	       获取码流类型，在SP_ParseData成功后调用
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *  OutputParam:		streamtype:	码流类型
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetStreamType(IN void* handle, OUT int* streamType);

/********************************************************************
 *	Funcname: 	    	SP_ParseData
 *	Purpose:	        输入数据流,并同步进行分析
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *		                stream:	数据流缓冲地址
 *		                length:	数据流长度
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_ParseData(IN void* handle, IN unsigned char* stream, IN int length);

/********************************************************************
 *	Funcname: 	    	SP_GetOneFrame
 *	Purpose:	        同步获取一帧信息,反复调用直到失败
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *		                frameInfo: 外部SP_FRAME_INFO的一个结构地址。
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetOneFrame(IN void* handle, IN SP_FRAME_INFO* frameInfo);

#ifndef STREAM_PARSER_FOR_RELEASE
 /********************************************************************
 *	Funcname:			SP_GetParseType
 *	Purpose:			获取解析类型，在SP_ParseData成功后调用
 *  InputParam:			streamtype:	码流类型
 *  OutputParam:		parseType: 支持的解析类型，见SP_PARSE_TYPE_
 *  Return:				0:调用成功
 *						其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetParseType(IN int streamType, OUT int* parseType);

/********************************************************************
 *	Funcname: 	    	SP_GetRemainData
 *	Purpose:	        获取码流分析器中残留数据
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *  OutputParam:        dataPointer: 残留数据的地址,内存为码流分析库内部的分配的内存
 *		                sizePointer: 剩余数据的长度
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetRemainData(IN void* handle, OUT unsigned char** dataPointer, OUT int* sizePointer);

/********************************************************************
 *	Funcname: 	    	SP_ClearBuffer
 *	Purpose:	        清除码流分析器内部的缓冲
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_ClearBuffer(IN void* handle);

/********************************************************************
 *	Funcname: 	    	SP_CreateFileParser
 *	Purpose:	        创建文件分析器
 *  InputParam:         file: 文件名
 *		                fileIndex: 索引信息回调
 *  OutputParam:        无
 *  Return:             NULL: 表示失败
 *                      其他: 文件解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateFileParser(IN char* file, IN fFileIndex fileIndex, IN void* userData);

/********************************************************************
 *	Funcname: 	    	SP_CreateFileParserEx1
 *	Purpose:	        创建文件分析器
 *  InputParam:	nType:指定解析类型
 *							file: 文件名
 *							fileIndex: 索引信息回调
 *							fileInfo:文件信息回调
 *							userData:用户信息
 *  OutputParam:        无
 *  Return:             NULL: 表示失败
 *                      其他: 文件解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateFileParserEx1(IN int nType, IN char* file, IN fFileIndex fileIndex, IN fFileInfo fileInfo, IN void* userData);

/********************************************************************
 *	Funcname: 	    	SP_CreateSliceParser
 *	Purpose:	        创建文件片段分析器
 *  InputParam:         file: 文件名
 *		                fileIndex: 索引信息回调
 *						sliceoffset: 片段在文件中的偏移
 *						slicesize: 片段长度
 *  OutputParam:        无
 *  Return:             NULL: 表示失败
 *                      其他: 文件解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateSliceParser(IN char* file, IN fFileIndex fileIndex, IN void* userData, SPint64 sliceoffset, SPint64 slicesize);

/********************************************************************
 *	Funcname: 	    	SP_GetProcess
 *	Purpose:	        获取文件索引信息进度信息
 *  InputParam:         handle:	通过SP_CreateFileParser返回的句柄
 *  OutputParam:        process: 索引建立的百分比
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetProcess(IN void* handle, OUT int* process);

/********************************************************************
 *	Funcname: 	    	SP_GetOneIndex
 *	Purpose:	        得到指定位置的帧信息和帧偏移信息
 *  InputParam:         handle:	通过SP_CreateFileParser返回的句柄
 *                      index: 指定索引
 *  OutputParam:        indexInfo: 帧偏移信息
 *		                frameInfo: 帧信息
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetOneIndex(IN void* handle, IN int index, OUT SP_INDEX_INFO* indexInfo, OUT SP_FRAME_INFO* frameInfo);

/********************************************************************
 *	Funcname: 	    	SP_GetIndexCount
 *	Purpose:	        返回文件索引条数
 *  InputParam:         handle:	通过SP_CreateFileParser返回的句柄
 *		                flags: 索引类型比特标志位，参见SP_INDEX_BIT_FLAG_xxx
 *  OutputParam:        indexCount: 索引条数
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetIndexCount(IN void* handle, IN int flags, OUT int* indexCount);

/********************************************************************
 *	Funcname: 	    	SP_GetAllIndex
 *	Purpose:	        一次获取多条索引信息
 *  InputParam:         handle:	通过SP_CreateFileParser返回的句柄
 *		                flags: 索引类型比特标志位,参见SP_INDEX_BIT_FLAG_xxx
 *		                structCount: 需要获取的结构个数,indexInfo与frameInfo如果不为NULL,两者的个数需要一致.
 *  OutputParam:        indexCount: 实际返回的索引条数
 *		                indexInfo: 返回索引信息,设置NULL表示不需要返回此信息
 *		                frameInfo: 返回帧信息,设置NULL表示不需要返回此信息
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetAllIndex(IN void* handle, IN int flags, OUT SP_INDEX_INFO* indexInfo, OUT SP_FRAME_INFO* frameInfo, IN int structCount, OUT int* indexCount);

/********************************************************************
 *	Funcname: 	    	SP_GetFrameByIndex
 *	Purpose:	        通过索引得到SP_FRAME_INFO结构体信息。
 *  InputParam:         handle:	通过SP_CreateStreamParser返回的句柄
 *		                indexInfo: 索引信息结构体
 *  OutputParam:        frameInfo: 外部SP_FRAME_INFO的一个结构地址
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetFrameByIndex(IN void* handle, IN SP_INDEX_INFO* indexInfo, OUT SP_FRAME_INFO* frameInfo);

/********************************************************************
 *	Funcname: 	    	SP_StreamEncryptKey
 *	Purpose:	        设置实时流解析秘钥
 *  InputParam:         handle: 通过SP_CreateStreamParser或SP_CreateFileParser返回的句柄。
 *						type : 秘钥类型 ：如SP_ENCRYPT_AES
 *						key：秘钥数据
 *						keylen：秘钥长度
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_StreamEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

/********************************************************************
 *	Funcname: 	    	SP_FileEncryptKey
 *	Purpose:	        设置文件解析秘钥
 *  InputParam:         handle: 通过SP_CreateStreamParser或SP_CreateFileParser返回的句柄。
 *						type : 秘钥类型 ：如SP_ENCRYPT_AES
 *						key：秘钥数据
 *						keylen：秘钥长度
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_FileEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

#endif

/********************************************************************
 *	Funcname: 	    	SP_Destroy
 *	Purpose:	        销毁码流分析器
 *  InputParam:         handle: 通过SP_CreateStreamParser或SP_CreateFileParser返回的句柄。
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码 见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_Destroy(IN void* handle);

/********************************************************************
 *	Funcname: 	    	SP_GetLastError
 *	Purpose:	        获得码流分析库错误码
 *  InputParam:         handle: 通过SP_CreateStreamParser或SP_CreateFileParser返回的句柄。
 *  OutputParam:        无
 *  Return:             错误码
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetLastError(IN void* handle);

#ifndef STREAM_PARSER_FOR_RELEASE
/********************************************************************
 *	Funcname: 	    	SP_ErrorToString
 *	Purpose:	        将错误码转换为字符串
 *  InputParam:         error: 错误码
 *  OutputParam:        text: 指向返回字符串
 *  Return:             见SP_RESULT
*********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_ErrorToString(IN int error, OUT char** text);
#endif

#ifdef __cplusplus
}
#endif

#endif



