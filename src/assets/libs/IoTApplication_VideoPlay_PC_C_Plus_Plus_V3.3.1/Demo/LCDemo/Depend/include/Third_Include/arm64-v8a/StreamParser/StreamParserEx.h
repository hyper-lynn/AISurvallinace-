/********************************************************************
*	Copyright 1992-2008, ZheJiang Dahua Technology Stock Co.Ltd.
* 						All Rights Reserved
*	File Name: 	        StreamParserEx.h
*	Description:	    扩展接口
*********************************************************************/

#ifndef _SP_STREAM_PARSER_EX_H_
#define _SP_STREAM_PARSER_EX_H_

#include "Defs.h"
#include "StreamParserAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

/*最大的轨迹点个数*/
#define  MAX_TRACKPOINT_NUM  10

/*智能帧的分析方式*/
enum SP_IVS_PARSE_TYPE
{
    IVS_TRACK,      /*分析智能帧物体移动轨迹信息（兼容老码流结构）*/
    IVS_TRACK_EX,    /*轨迹点扩展结构*/
	IVS_TRACK_EX2,

	IVS_TRACK_40 = 0x40,    /*智能结构化信息帧*/
	IVS_TRACK_A1 = 0xA1,	/*NVR浓缩信息轨迹点*/
};

/*扩展的错误类型*/
enum SP_RESULT_EX
{
    SP_ERROR_WRONG_VERSION = 15,       /*版本号不正确*/
    SP_ERROR_BAD_OBJ_COUNT,            /*目标个数不合理*/
    SP_ERROR_PARSE_TYPE_NO_SUPPORT,     /*IVS解析类型不支持*/
	SP_ERROR_IVS_DATA_WRONG				/*智能帧数据错误*/
};

/*轨迹点*/
typedef struct
{
    /*轨迹点是物体外接矩形的中心，根据X，Y及XSize，YSize计算出的物体外接矩形坐标(left，top，right，bottom)*/
    /*RECT=(X-XSize, Y-YSize, X+XSize, Y+YSize)  */
    unsigned short x;
    unsigned short y;
    unsigned short xSize;
    unsigned short ySize;
}SP_IVS_POINT;
typedef struct
{
	unsigned short x;
	unsigned short y;
}SP_IVS_POSITION;

typedef struct
{
    unsigned int obj_id;                        /*物体id*/
    unsigned int enable;						/*0 表示删除物体  1表示物体轨迹信息有效*/
    SP_IVS_POINT track_point[MAX_TRACKPOINT_NUM];
    unsigned int trackpt_num;				    /*轨迹点个数，即track_point有效个数*/
}SP_IVS_OBJ;

typedef struct
{
    int decode_id;
    int	obj_id;
    int	enable;			/*无用*/
    SP_IVS_POINT track_point[MAX_TRACKPOINT_NUM];
    int trackpt_num;
    int	operator_type;	/*操作分为三类：新增物体(1), 增加物体轨迹点(2)，删除物体(3)，隐藏物体轨迹(4),其它值无效*/
    int	frame_part_id;	/*0表示一帧的开始，依次递增*/

    char color;
    char object_type;
	char object_sub_type;
    char reserved1;

	unsigned short ex_info_size;
	unsigned short speed;	//目标运动速度值，0xFFFF表示无效速度
	unsigned short speed_X;	//速度矢量X
	unsigned short speed_Y;	//速度矢量Y

	char speed_unit;	//速度单位，0 px/s, 1 cm/s
	char color_space;	//颜色空间，0 YUV, 1 RGBA, 2 HSV
	unsigned short main_color_num;	//目标主色个数

	unsigned short	main_region_rect_x;		//主色区域外接矩形中心X坐标，相对坐标(坐标系取决于帧类型)
	unsigned short	main_region_rect_y;		//主色区域外接矩形中心Y坐标，相对坐标(坐标系取决于帧类型)
	unsigned short	main_region_rect_width;	//主色区域外接矩形宽度，相对坐标(坐标系取决于帧类型)
	unsigned short	main_region_rect_height;//主色区域外接矩形高度，相对坐标(坐标系取决于帧类型)

	unsigned int main_region_color;	//目标区域主颜色

	char reserved[96];	/*保留*/
	int nRenderNum;
}SP_IVS_OBJ_EX;


/*                         智能结构化信息帧定义                         */

/*属性包定义*/

//车身属性包,64字节
typedef struct
{
	unsigned char colorVailed;	//颜色是否有效
	unsigned char carModel;		//车型
	unsigned short brand;		//品牌车标
	unsigned int color;			//颜色信息，RGBA

	unsigned short subbrand;	//子品牌
	unsigned short year;		//年款
	unsigned char reserved[52];	//预留
}SP_IVS_TRAFFIC_ATTRIBUTE_80;

//车上人员属性包,64字节
typedef struct
{

	SP_IVS_POINT mainPosition;		//主驾驶位
	SP_IVS_POINT coPosition;		//副驾驶位
	unsigned char mainSafetyBelt;	//主驾安全带信息  0-Unknown 1-not 2-yes
	unsigned char coSafetyBelt;		//副驾安全带信息  0-Unknown 1-not 2-yes
	unsigned char mainSunvisor;		//主驾遮阳板信息  0-Unknown 1-not 2-yes
	unsigned char coSunvisor;		//副驾遮阳板信息  0-Unknown 1-not 2-yes
	unsigned char reserved[44];		//对齐
}SP_IVS_TRAFFIC_ATTRIBUTE_81;

//车牌内容属性包,256字节
typedef struct
{
	unsigned char plateEncode;		//车牌编码， 0-ASCII, 1-UCS-4LE
	unsigned char plateInfoLen;		//车牌信息长度
	unsigned char reserved[2];		//对齐

	unsigned char plateInfo[252];	//车牌信息
}SP_IVS_TRAFFIC_ATTRIBUTE_82;

//车牌外形属性包,64字节
typedef struct
{
	unsigned char colorVailed;		//颜色是否有效
	unsigned char reserved[3];		//对齐
	unsigned int color;				//颜色信息，RGBA

	unsigned char strCountry[4];	//车牌国别字符串
	unsigned short plateType;		//车牌类型
	unsigned short plateWidth;		//分析车牌画面的绝对宽度
	unsigned char reserved1[48];	//预留
}SP_IVS_TRAFFIC_ATTRIBUTE_83;

//轨迹点信息,512字节
typedef struct
{
	unsigned char operatorType;		//更新操作类型
	unsigned char pointCount;		//轨迹点个数
	unsigned char fatherCount;		//父ID个数
	unsigned char trackType;		//轨迹类型，0表示IVS物体轨迹，1表示跟踪物体轨迹
	SP_IVS_POINT trackPoint[32];	//轨迹点信息
	unsigned int  fatherID[63];		//父ID列表
}SP_IVS_TRAFFIC_ATTRIBUTE_84;

//颜色定义
typedef struct
{
	SP_IVS_POINT mainColRect;

	unsigned int mainColor;
}SP_IVS_ATTRIBUTE_MAINCOLOR;

//颜色属性,256字节
typedef struct
{
	unsigned char colorSpace;	//颜色空间 0-YUV 1-RGBA 2-HSV
	unsigned char mainColorCount;//颜色个数
	unsigned char reserved[2];
	//颜色数据
	SP_IVS_ATTRIBUTE_MAINCOLOR color[21];
}SP_IVS_TRAFFIC_ATTRIBUTE_85;

//速度属性,64字节
typedef struct
{
	unsigned char speedType;//速度单位，0-px/s ,1-cm/s
	unsigned char reserved;	//对齐
	unsigned short speed;	//目标运动速度值(USHORT) cm/s为单位 0xFFFF表示无效速度
	unsigned short speedX;	//速度矢量X归一化值 计算速度方向和px/s单位下的速度值
	unsigned short speedY;	//速度矢量Y归一化值 计算速度方向和px/s单位下的速度值
	unsigned char reserved1[56];
}SP_IVS_TRAFFIC_ATTRIBUTE_86;

//人脸检测局部轨迹属性,64字节
typedef struct
{
	SP_IVS_POINT trackPoint;		//人脸框位置（格式,8192坐标系）
	unsigned char reserved1[56];
}SP_IVS_TRAFFIC_ATTRIBUTE_87;

//人脸识别特征属性,64字节
typedef struct
{
	unsigned char age;			//年龄段：0表示未识别。2:婴儿，10:幼年，28:青年，50:中年，60:老年
	unsigned char sex;			//性别：0表示未识别，1:女性，2:男性
	unsigned char face;			//表情：0表示未识别，1:愤怒，2:悲伤，3:厌恶，4:恐惧，5:惊讶，6:正常，7:微笑，8:大笑
	unsigned char glass;		//是否戴眼镜：0x00表示未做识别，bit0置1未戴，bit1置1戴眼镜
	unsigned char reserved[60];	//预留
}SP_IVS_TRAFFIC_ATTRIBUTE_88;

//人脸特征点坐标属性,256字节
typedef struct
{
	unsigned char posCount;			//特征点个数
	unsigned char reserved;			//对齐
	unsigned short yawAngle;		//yaw角度 取值范围[-180, +180]。单位1度，0x8000表示未识别
	unsigned short rollAngle;		//roll角度 取值范围[-180, +180]。单位1度，0x8000表示未识别
	unsigned short pitchAngle;		//pitch角度 取值范围[-180, +180]。单位1度，0x8000表示未识别

	SP_IVS_POSITION lEyePos;		//左眼中心坐标
	SP_IVS_POSITION rEyePos;		//右眼中心坐标
	SP_IVS_POSITION nosePos;		//鼻尖位置
	SP_IVS_POSITION lMouthPos;		//左嘴角坐标
	SP_IVS_POSITION rMouthPos;		//右嘴角坐标
	unsigned int feature[57];		//特征点坐标
}SP_IVS_TRAFFIC_ATTRIBUTE_89;

//物体内容属性包
#define SP_IVS_ATTRIBUTE_FLAG_80	(1 << 0)
#define SP_IVS_ATTRIBUTE_FLAG_81	(1 << 1)
#define SP_IVS_ATTRIBUTE_FLAG_82	(1 << 2)
#define SP_IVS_ATTRIBUTE_FLAG_83	(1 << 3)
#define SP_IVS_ATTRIBUTE_FLAG_84	(1 << 4)
#define SP_IVS_ATTRIBUTE_FLAG_85	(1 << 5)
#define SP_IVS_ATTRIBUTE_FLAG_86	(1 << 6)
#define SP_IVS_ATTRIBUTE_FLAG_87	(1 << 7)
#define SP_IVS_ATTRIBUTE_FLAG_88	(1 << 8)
#define SP_IVS_ATTRIBUTE_FLAG_89	(1 << 9)

//属性包集合
typedef struct
{
	unsigned int attrflag; //属性包使能, 见IVS_ATTRIBUTE_FLAG_
	SP_IVS_TRAFFIC_ATTRIBUTE_80 arrtibute80;
	SP_IVS_TRAFFIC_ATTRIBUTE_81 arrtibute81;
	SP_IVS_TRAFFIC_ATTRIBUTE_82 arrtibute82;
	SP_IVS_TRAFFIC_ATTRIBUTE_83 arrtibute83;
	SP_IVS_TRAFFIC_ATTRIBUTE_84 arrtibute84;
	SP_IVS_TRAFFIC_ATTRIBUTE_85 arrtibute85;
	SP_IVS_TRAFFIC_ATTRIBUTE_86 arrtibute86;
	SP_IVS_TRAFFIC_ATTRIBUTE_87 arrtibute87;
	SP_IVS_TRAFFIC_ATTRIBUTE_88 arrtibute88;
	SP_IVS_TRAFFIC_ATTRIBUTE_89 arrtibute89;

}SP_IVS_ATTRIBUTE;

typedef struct
{
	unsigned char funcType;		//大类业务方案
	unsigned char groupCount;	//关联组个数
	unsigned char cameraID[20];	//视频描述数据对应的摄像机编号
	char resv[10];
}SP_IVS_SEGMENT_INFO;

//智能结构化目标信息
typedef struct
{
	SP_IVS_SEGMENT_INFO segInfo;

	unsigned int groupID;				// 关联组ID
	unsigned int objID;					// 目标ID
	SP_IVS_POINT trackPoint;			// 车身车牌轨迹点信息

	unsigned char objType;				// 目标类型，车牌/车身/人etc
	unsigned char pointVailed;			// 坐标是否可信
	unsigned char operatorType;			// 更新操作类型，新增物体(1), 增加物体轨迹点(2)，删除物体(3)，隐藏物体轨迹(4)
	unsigned char reserved[5];			// 对齐字段

	unsigned char version;				// 版本号
	unsigned char* facedata;			// 人脸特征数据
	SP_IVS_ATTRIBUTE attr;
}SP_IVS_COMMON_OBJ;

typedef enum
{
	SP_PARAM_RTPTYPE_PARSER,					// RTP解析
	SP_PARAM_VOBTYPE_PARSER,					// VOB解析
}SP_PARAM_TYPE;

typedef struct
{
	unsigned int struct_size;
	unsigned int encode_type;				// 编码类型
	unsigned int payload_type;				// 负载类型
	unsigned int audio_sample_rate;			// 采样率
	unsigned int audio_channels;			// 声道
	unsigned int channel_count;				// 通道数
	unsigned int channel_id;				// 通道ID
	unsigned int discard_flag;				// 丢弃丢帧flag
	unsigned int audio_payload_type;		// 音频载荷类型
	unsigned int audio_encode_type;			// 音频编码类型
	unsigned int deinter_lace;				// 解交错信息
	unsigned int frame_rate;				// 设置帧率
}SP_RTP_PARSER_PARAM;

#ifndef STREAM_PARSER_FOR_RELEASE
/********************************************************************
 *	Funcname: 	    	IVSCallBack
 *	Purpose:	        解析IVS数据帧的回调函数
 *  InputParam:         IVSType: IVS OBject的类型
 *                      pIVSBuff: IVS Object结构体数组的起始地址
 *                      nIVSBuffLen：pIVSBuff的长度，为IVS Object的个数乘以单个IVS object的长度
 *                                  单个IVS object的长度可有IVSType推断类型获得。
 *                      len: pFrameBody的长度
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码
*********************************************************************/
typedef int (CALLMETHOD *IVSCallBack)(SP_IVS_PARSE_TYPE IVSType,
                                      void* pIVSBuff,
                                      int nIVSBuffLen,
                                      void* pUserData);

/********************************************************************
 *	Funcname: 	    	SP_ParseIVS
 *	Purpose:	        解析IVS数据帧
 *  InputParam:         pBuffer: IVS数据帧的frame或者frameBody数据，如果是IVS_PRESET(暂未定义)，
 *                               需传入包括帧头的帧指针。其他类型，则传入pFrameBody
 *                      len: pBuffer的长度
 *                      parseType: 解析智能帧的类型。
 *                      pCallBack: 回调函数指针
 *                      pUserData: 用户数据
 *  OutputParam:        无
 *  Return:             0:调用成功
 *                      其他值：失败，通过SP_GetLastError获取错误码
*********************************************************************/
STREAMPARSER_API int CALLMETHOD SP_ParseIVS(IN unsigned char* pBuffer,
                                  IN int len,
                                  IN SP_IVS_PARSE_TYPE parseType,
                                  IN IVSCallBack pCallBack,
                                  IN void* pUserData);

 /********************************************************************
 *	Funcname: 	    	SP_CreateStreamParser
 *	Purpose:	        创建流分析器
 *  InputParam:         nType: 码流封装格式,0为由码流分析器内部设定
 *						nBufferSize: 需要开辟的缓冲区大小
 *  OutputParam:        无
 *  Return:             NULL: 创建流分析器失败
 *                      其他值：流解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateStreamParserEx(IN int nType, IN int nBufferSize);


/********************************************************************
 *	Funcname: 	    	SP_CreateFileParserEx
 *	Purpose:	        创建文件分析器
 *  InputParam:			nType:指定解析类型
 *						file: 文件名
 *						fileIndex: 索引信息回调
 *  OutputParam:        无
 *  Return:             NULL: 表示失败
 *                      其他: 文件解析器句柄
*********************************************************************/
STREAMPARSER_API void* CALLMETHOD SP_CreateFileParserEx(IN int nType, IN char* file, IN fFileIndex fileIndex, IN void* userData);


/***********************************************************************
*	Funcname:			SP_SetParam
*	Purpose:			设置码流解析参数
*	InputParam:			handle: 流解析句柄
						nParamType: 参数类型
						pParam:参数地址
						nParamLength:参数大小
*	Return:				0:成功; 其他值:失败
***********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_SetParam(IN void* handle, IN int nParamType, IN const void* pParam, IN int nParamLength);

/***********************************************************************
*	Funcname:			SP_GetParam
*	Purpose:			获取码流解析参数
*	InputParam:			handle:流解析句柄
						nParamType:参数类型
*	OutputParam:		pParam:输出参数地址
*	InoutParam:			nParamLength:输入pParam大小，返回实际输出参数大小
*	Return:				0:成功; 其他值:失败
***********************************************************************/
STREAMPARSER_API SP_RESULT CALLMETHOD SP_GetParam(IN void* handle, IN int nParamType, OUT void* pParam, IN OUT int* nParamLength);

 /********************************************************************
 *	Funcname: 	    	SP_FlushBuffer
 *	Purpose:	        强制没有结束标志的码流输出最后一帧数据
 *  InputParam:         handle: 流解析句柄
 *  OutputParam:        无
 *  Return:             0: 成功
 *                      其他值：失败
*********************************************************************/
extern "C" STREAMPARSER_API int CALLMETHOD SP_FlushBuffer(IN void* handle);

#endif // end #ifndef STREAM_PARSER_FOR_RELEASE

#ifdef __cplusplus
}

#endif

#endif

