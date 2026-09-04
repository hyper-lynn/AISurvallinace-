// StreamPackage.h: interface for the StreamPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_)
#define AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (defined(WIN32) || defined(WIN64))
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
}SG_ERR_TYPE;

/*码流封装类型*/
typedef enum
{
	SG_STREAM_TYPE_MP4,			/* 封装格式 MP4 */
	SG_STREAM_TYPE_ASF,			/* 封装格式 ASF */
	SG_STREAM_TYPE_AVI,				/* 封装格式 AVI */
	SG_STREAM_TYPE_DAV,			/* 封装格式 DAV */
	SG_STREAM_TYPE_FLV,			/* 封装格式 FLV */
	SG_STREAM_TYPE_STREAM_ASF,			/* 封装格式 流式 ASF */
	SG_STREAM_TYPE_MOV,			/* 封装格式 MOV */
	SG_STREAM_TYPE_3GP,			/* 封装格式 3GP*/
	SG_STREAM_TYPE_STREAM_FLV,	/* 封装格式 流式 FLV */
	SG_STREAM_TYPE_RTP,			/* 封装格式 RTP */
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
	SG_FRAME_SUB_TYPE_B,				/* B帧 */
	SG_FRAME_SUB_TYPE_JPEG_FRAME = 8,	/*JPEG 帧*/
}SG_FRAME_SUB_TYPE;

/*编码类型*/
typedef enum
{
	SG_ENCODE_VIDEO_UNKNOWN = 0,		/*视频编码格式不可知*/
	SG_ENCODE_VIDEO_MPEG4 ,				/*视频编码格式是MPEG4*/
	SG_ENCODE_VIDEO_HI_H264,			/*视频编码格式是海思H264*/
	SG_ENCODE_VIDEO_JPEG,				/*视频编码格式是标准JPEG*/
	SG_ENCODE_VIDEO_DH_H264,			/*视频编码格式是大华码流H264*/
	SG_ENCODE_VIDEO_INVALID,			/*视频编码格式无效*/

	SG_ENCODE_AUDIO_PCM = 7,				/*音频编码格式是PCM8*/
	SG_ENCODE_AUDIO_G729 = 8,				/*音频编码格式是G729*/
	SG_ENCODE_AUDIO_IMA = 9,				/*音频编码格式是IMA*/
	SG_ENCODE_PCM_MULAW = 10,				/*音频编码格式是PCM MULAW*/
	SG_ENCODE_AUDIO_G721 = 11,				/*音频编码格式是G721*/
	SG_ENCODE_PCM8_VWIS = 12,				/*音频编码格式是PCM8_VWIS*/
	SG_ENCODE_MS_ADPCM = 13,				/*音频编码格式是MS_ADPCM*/
	SG_ENCODE_AUDIO_G711A = 14,				/*音频编码格式是G711A*/
	SG_ENCODE_AUDIO_AMR = 15,				/*音频编码格式是AMR*/
	SG_ENCODE_AUDIO_PCM16 = 16,				/*音频编码格式是PCM16*/
	SG_ENCODE_AUDIO_HiSi2 = 17,				/*音频编码格式是HiSi2*/
	SG_ENCODE_AUDIO_HiSi3 = 18,				/*音频编码格式是HiSi3*/
	SG_ENCODE_AUDIO_HiSi4 = 19,				/*音频编码格式是HiSi4*/
	SG_ENCODE_AUDIO_HiSi5 = 20,				/*音频编码格式是HiSi5*/
	SG_ENCODE_AUDIO_MPEG = 21,				/*音频编码格式是MPEG AUDIO*/
	SG_ENCODE_AUDIO_G711U = 22,				/*音频编码格式是G711U*/
	SG_ENCODE_AUDIO_G723 = 23,				/*音频编码格式是G723*/
	SG_ENCODE_AUDIO_G7231 = 25,				/*音频编码格式是G723_1*/
	SG_ENCODE_AUDIO_AAC = 26,				/*音频编码格式是AAC*/
	SG_ENCODE_AUDIO_TALK = 30,				/*音频编码格式是TALK*/
	SG_ENCODE_AUDIO_MP2 = 31,				/*音频编码格式是MP2*/
	SG_ENCODE_AUDIO_OGG = 32,				/*音频编码格式是OGG*/
	SG_ENCODE_AUDIO_MP3	= 85,				/*音频编码格式是MP3*/
	SG_ENCODE_AUDIO_AVI = 1000,				/*音频编码格式是AVI*/
}SG_ENCODE_TYPE;

/*解交错标志*/
typedef enum
{
	SG_DEINTERLACE_PAIR = 0,				/*解码后拉伸*/
	SG_DEINTERLACE_SINGLE,					/*解码两次*/
	SG_DEINTERLACE_NONE						/*无解交错*/
}SG_DEINTERLACE_TYPE;

/*文件头信息*/
typedef struct 
{
	unsigned int struct_size;
}SGHeaderInfo;

typedef struct
{
	unsigned int struct_size;
}SGTailerInfo;

//分块图像信息
typedef struct
{
	short left;
	short top;
	short right;
	short bottom;	
	int offset;			//分块图像数据在帧数据中的偏移
	int reserved;
}SGBlockInfo;

//图像拼接信息
typedef struct
{
	int flag;				//是否需要添加flag信息
	int block_n;
	int block_m;

	SGBlockInfo* pblock;	//分块图像信息，长度为n*m*sizeof(SGBlockInfo)
}SGSplitInfo;

//帧数据信息
typedef struct  
{
	unsigned int	struct_size;

	unsigned char*	frame_pointer;		/*帧数据指针*/
	unsigned int	frame_size;			/*帧数据长度*/
	unsigned int	frame_type;			/*帧类型	SG_FRAME_TYPE*/
	unsigned int	frame_sub_type;		/*帧子类型	SG_FRAME_SUB_TYPE*/
	unsigned int	frame_encode;		/*编码类型	SG_ENCODE_TYPE*/
	unsigned int	frame_time;			/*帧时间戳*/
	unsigned int	frame_data;			/*日期时间，UTC时间*/

	unsigned int	width;				/*视频宽度*/
	unsigned int	heigth;				/*视频高度*/
	unsigned int	frame_rate;			/*视频帧率*/
	unsigned int	deinter_lace;		/*解交错信息*/

	unsigned int	sample_rate;		/*音频采样率*/
	unsigned int	bit_per_sample;		/*音频采样位数*/
	unsigned int	channels;			/*音频通道数*/

	SGSplitInfo		split_info;
}SGFrameInfo;

typedef struct
{
	unsigned int	struct_size;

	unsigned char*	data_pointer;		/*数据指针*/
	int				data_size;			/*数据长度*/
	int				offset_type;		/*数据偏移类型*/
	unsigned int	offset_pos;			/*数据偏移位置*/
}SGOutputData;

typedef void* (*SGMalloc_t)(int memory_size);
typedef void  (*SGFree_t)(void* memory_pointer, int memory_size);
typedef void  (*SGDataCB_t)(SGOutputData* data, void* user);

//帧数据信息
typedef struct  
{
	unsigned int	struct_size;
	
	void*			user;
	SGMalloc_t		sg_malloc;
	SGFree_t		sg_free;
	SGDataCB_t		sg_datacb;
}SGCreateParam;


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

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_STREAMPACKAGE_H__014CF316_354F_47ED_B30D_D39912DD250D__INCLUDED_)

