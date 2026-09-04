/********************************************************************
*	Copyright 1992-2008, ZheJiang Dahua Technology Stock Co.Ltd.
* 						All Rights Reserved
*	File Name: 	        StreamParserEx.h
*	Description:	    扩展接口
*********************************************************************/

#ifndef __INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSEREX_H__
#define __INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSEREX_H__

#include "StreamParserAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

/*最大的轨迹点个数*/
#define  MAX_TRACKPOINT_NUM  10

/*车挂件最大数目为4个*/
#define MAX_CAR_HANING_ACCESSORY_NUM  4
/*遮光板最大数目为4个*/
#define MAX_SUN_VISOR_NUM  4
/*纸巾盒最大数目为4个*/
#define MAX_TISSUE_BOX_NUM  4
/*年检标最大数目为8个*/
#define MAX_ANNUAL_INSPECTION_STANDARD_NUM  8

/*信号机流量车道最大数量为5个*/
#define MAX_SIGNAL_FLOW_LANE_NUM  5

/*人员姓名最多为28字节*/
#define MAX_NAME_LEN 28

/*景物点信息标注中，景物点结构个数最大为32个*/
#define  MAX_SCENE_TAGGING_POINTS_NUM  32;

/*智能客流信息标注中，智能客流点结构个数最大为32个*/
const int MAX_SCENE_TRAFFIC_NUM = 32;

const int MAX_SCENE_TRAFFIC_PLAN_NUM = 32;

const int MAX_SCENE_TRAFFIC_PLAN_REGION_NUM = 32;

/*智能帧的分析方式*/
enum SP_IVS_PARSE_TYPE
{
	IVS_TRACK,			/*分析智能帧物体移动轨迹信息（兼容老码流结构）,只包含轨迹点更新信息*/
	IVS_TRACK_EX,		/*分析智能帧物体移动轨迹信息扩展，包含轨迹点更新信息和轨迹点扩展信息*/
	IVS_TRACK_EX2,		/*智能结构化信息帧*/
	IVS_TRACK_EX3,		/*景物点信息标注帧*/

	IVS_TRACK_15 = 0x15,      /*大数据量帧*/  	//大数据量帧，从B1开始增加
	IVS_TRACK_B1 = 0xB1,	  /*大数据量帧：智能客流*/

	IVS_TRACK_40 = 0x40,	/*智能结构化信息帧：大类业务方案*/
	IVS_TRACK_A1 = 0xA1,	/*智能结构化信息帧：NVR浓缩信息轨迹点*/
	IVS_TRACK_A1_EX,		/*智能结构化信息帧：NVR浓缩扩展信息*/
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
	short x;
	short y;
}SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION;

typedef struct
{
    unsigned int obj_id;                        /*物体id*/
    unsigned int enable;						/*0 表示删除物体  1表示物体轨迹信息有效*/
    SP_IVS_POINT track_point[MAX_TRACKPOINT_NUM];
    unsigned int trackpt_num;				    /*轨迹点个数，即track_point有效个数*/
}SP_IVS_OBJ;

typedef struct 
{
	unsigned short RegionId;      	//区域ID
	unsigned short State;           //状态： 离开or进入
	int PeopleNum;                 	//人数
	char reserved[4];              	//预留
}SP_IVS_TRAFFIC_REGION; 

typedef struct 
{
	unsigned short PlanId;        	//规则ID
	unsigned short RuleType;      	//规则类型
	SP_IVS_TRAFFIC_REGION* pRegion; //区域点
	unsigned short RegionNum;       //区域数目
	char reserved[2];              	//预留
}SP_IVS_TRAFFIC_PLAN; 

typedef struct
{
	unsigned short NumberStat;     			//大类业务方案1
	unsigned short nIVSTrafficPlanNum;  	//智能客流规则数量最大不会超过32个；
	SP_IVS_TRAFFIC_PLAN* pIVSTrafficPlan;   //智能客流规则
	char reserved[4];	           			//保留
}SP_IVS_TRACK_TRAFFIC_SCENE_POINTS_INFOR;

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

/* 景物点标注信息 */
typedef struct
{
	int nIndex;			//编号
	SP_IVS_POSITION sceneInfoPoint;
	char fristtile[64];	//一级名称utf-8
	char enable;		//使能
	char titleType;		//标签类型
	char titleAttribute;//标签属性
	char sharpType;		//景物点轮廓类型，0：折线；1：扇形
	unsigned char polygon_num;//景物点轮廓顶点个数
	char reserved[3];	//对齐
	SP_IVS_POSITION polygon[16];//景物点轮廓坐标
}SP_IVS_TRACK_EX3_SCENE_POINTS_INFOR;

/*                         智能结构化信息帧定义                         */

/*属性包定义*/

//车身属性包,64字节
typedef struct
{
	unsigned char colorVailed;	//颜色是否有效
	unsigned char carModel;		//车型
	unsigned short brand;		//品牌车标

	unsigned char color_r;		//颜色信息，红
	unsigned char color_g;		//颜色信息，绿
	unsigned char color_b;		//颜色信息，蓝
	unsigned char color_a;		//颜色信息，透明

	unsigned short subbrand;	//子品牌
	unsigned short year;		//年款
	SP_IVS_POINT windowPosition;//车窗位置
	unsigned char nReliabilityOfVehicleBodyDetection;	//车身检测置信度，0表示算法未提供，取值范围为1-100

	unsigned char reserved[43];	//预留
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
	unsigned char fatherCount;		//父ID个数
	unsigned char pointCount;		//待增加轨迹点个数
	unsigned char trackType;		//轨迹类型，0表示IVS物体轨迹，1表示跟踪物体轨迹
	unsigned char reserved;			//对齐

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

	unsigned char hat;			//是否戴帽子：0x00表示未做识别，bit0置1未戴，bit1置1戴帽子
	unsigned char call;			//是否打电话：0x00表示未做识别，bit0置1未打电话，bit1置1打电话
	unsigned char backPack;		//是否背包：0x00表示未做识别，bit0置1未背包，bit1置1背包
	unsigned char umbrella;		//是否打伞：0x00表示未做识别，bit0置1未打伞，bit1置1打伞

	unsigned char height;		//身高：0表示未识别，单位为cm
	unsigned char mask;			//bit0~bit1是否戴口罩，bit2~bit3是否有胡子
	unsigned char coattype;		//上衣类型
	unsigned char pantstype;	//裤子类型

	unsigned char coatcolor[4];	//上衣颜色RGBA
	unsigned char pantscolor[4];//裤子颜色RGBA
	unsigned char reserved[44];	//预留
}SP_IVS_TRAFFIC_ATTRIBUTE_88;

//人脸特征点坐标属性,256字节
typedef struct
{
	unsigned char posCount;			//特征点个数
	unsigned char reserved;			//对齐
	short yawAngle;					//yaw角度 取值范围[-180, +180]。单位1度，0x8000表示未识别
	short rollAngle;				//roll角度 取值范围[-180, +180]。单位1度，0x8000表示未识别
	short pitchAngle;				//pitch角度 取值范围[-180, +180]。单位1度，0x8000表示未识别

	SP_IVS_POSITION lEyePos;		//左眼中心坐标
	SP_IVS_POSITION rEyePos;		//右眼中心坐标
	SP_IVS_POSITION nosePos;		//鼻尖位置
	SP_IVS_POSITION lMouthPos;		//左嘴角坐标
	SP_IVS_POSITION rMouthPos;		//右嘴角坐标
	unsigned int feature[57];		//特征点坐标
}SP_IVS_TRAFFIC_ATTRIBUTE_89;

////车内目标特征点坐标属性包 256字节
typedef struct
{
	unsigned char car_hanging_accessoryCount;		//车挂坠数目
	unsigned char tissue_boxCount;					//纸巾盒数目
	unsigned char sun_visorCount;					//遮阳板数目
	unsigned char annual_inspection_standardCount;	//年检标数目

	SP_IVS_POINT car_hanging_accessoryPos[MAX_CAR_HANING_ACCESSORY_NUM];
	SP_IVS_POINT tissue_boxPos[MAX_TISSUE_BOX_NUM];
	SP_IVS_POINT sun_visorPos[MAX_SUN_VISOR_NUM];
	SP_IVS_POINT annual_inspection_standardPos[MAX_ANNUAL_INSPECTION_STANDARD_NUM];

	unsigned char reserved1[92];
}SP_IVS_TRAFFIC_ATTRIBUTE_8C;

/// 无锡235定制，流量相机信号机对接属性
typedef struct
{
	unsigned char LaneNum;//当前车道的车道号,[1,5]
	unsigned char virtualLoopTotalNum;//车道内的虚拟线圈个数，取值范围[1,2]
	unsigned char firstVirtualLoopStatus;//虚拟线圈1的占用状态，0表示没有线圈，1表示不占用，2表示占用
	unsigned char secondVirtualLoopStatus;//虚拟线圈2的占用状态，0表示没有线圈，1表示不占用，2表示占用
	unsigned int   queneLenth;//排队长度，单位cm

	SP_IVS_POSITION ltailCoordinates;//队尾坐标，左点X,Y
	SP_IVS_POSITION rtailCoordinates;//队尾坐标，右点X,Y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION firstVirtualCoordinates1;//线圈1坐标1，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION firstVirtualCoordinates2;//线圈1坐标2，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION firstVirtualCoordinates3;//线圈1坐标3，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION firstVirtualCoordinates4;//线圈1坐标4，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION secondVirtualCoordinates1;//线圈2坐标1，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION secondVirtualCoordinates2;//线圈2坐标2，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION secondVirtualCoordinates3;//线圈2坐标3，x,y
	SP_IVS_SIGNAL_FLOW_LANE_8D_POSITION secondVirtualCoordinates4;//线圈2坐标4，x,y
}SP_SIGNAL_FLOW_LANE_INFO;


//信号量流量属性包256Bytes，仅存在物体类型为信号机流量，无锡所定制
typedef struct
{
	unsigned char laneCount;		//车道数量，取值范围[1，5]
	unsigned char nReserverd[7];	//对齐

	SP_SIGNAL_FLOW_LANE_INFO signal_flow_laneInfo[MAX_SIGNAL_FLOW_LANE_NUM];
	unsigned char reserved1[8];
}SP_IVS_SIGNAL_FLOW_ATTRIBUTE_8D;

//人员姓名属性包 32字节
typedef struct
{
	unsigned char name_codec_format;	//编码方式 0-utf8
	unsigned char name_lenth;			//名字长度
	unsigned char name[MAX_NAME_LEN];	//名字
	unsigned char reserved[2];			//对齐
}SP_IVS_ATTRIBUTE_8E;

//统计类目标属性包
typedef struct
{
	unsigned int m_QueuingTime;        	//排队滞留时间
	unsigned char reserved[12];    		//对齐; 10字节预留字节+2字节对齐
}SP_IVS_ATTRIBUTE_90;

typedef struct
{
	unsigned char vehicles_color[4];	//非机动车颜色RGBA
	unsigned char vehicles_type;		//非机动车类型
	unsigned char cyclingnumber;	//骑车人数
	unsigned char reserved[50];		//保留
}SP_IVS_ATTRIBUTE_92;

typedef struct
{
	unsigned short	ship_length;	//船只长度(米)
	unsigned char	ship_height;	//船只高度(米)
	unsigned char	ship_speed;		//船只速度(米/秒)
	unsigned short	ship_distance;  //船只距离(米)
	unsigned char reserved[50];		//保留
}SP_IVS_ATTRIBUTE_93;

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

#define SP_IVS_ATTRIBUTE_FLAG_8C	(1 << 12)

#define SP_IVS_ATTRIBUTE_FLAG_8E	(1 << 14)
#define SP_IVS_ATTRIBUTE_FLAG_90	(1 << 16)
#define SP_IVE_ATTRIBUTE_FLAG_92	(1 << 18)
#define SP_IVE_ATTRIBUTE_FLAG_93	(1 << 19)

//属性包集合 1956字节
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
	SP_IVS_TRAFFIC_ATTRIBUTE_8C arrtibute8C;
	SP_IVS_ATTRIBUTE_8E         arrtibute8E;
	SP_IVS_ATTRIBUTE_90         arrtibute90;
	SP_IVS_ATTRIBUTE_92			arrtibute92;
	SP_IVS_ATTRIBUTE_93			arrtibute93;
}SP_IVS_ATTRIBUTE;

//结构化信息帧段标识 32字节
typedef struct
{
	unsigned char funcType;		//大类业务方案
	unsigned char groupCount;	//关联组个数
	unsigned char cameraID[20];	//视频描述数据对应的摄像机编号
	char resv[10];
}SP_IVS_SEGMENT_INFO;

//智能结构化目标信息 32位系统 2020字节
typedef struct
{
	SP_IVS_SEGMENT_INFO segInfo;

	unsigned int groupID;				// 关联组ID
	unsigned int objID;					// 目标ID
	SP_IVS_POINT trackPoint;			// 车身车牌轨迹点信息

	unsigned char objType;				// 目标类型，车牌/车身/人etc
	unsigned char pointVailed;			// 坐标是否可信
	unsigned char operatorType;			// 更新操作类型，新增物体(1), 增加物体轨迹点(2)，删除物体(3)，隐藏物体轨迹(4)
	unsigned char reserved;				// 对齐字段

	unsigned int  nStructSize;			//结构体的sizeof大小
	unsigned char version;				// 版本号
	unsigned char resv[3];
	unsigned char* facedata;			// 人脸特征数据

	union
	{
		SP_IVS_ATTRIBUTE comm;			// 通用物体属性
		SP_IVS_SIGNAL_FLOW_ATTRIBUTE_8D signal_flow;	// 无锡235定制属性
	}attr;

}SP_IVS_COMMON_OBJ;

typedef enum
{
	SP_PARAM_RTPTYPE_PARSER,					// RTP解析
	SP_PARAM_VOBTYPE_PARSER,					// VOB解析

	//解密类型
	SP_PARAM_DECRYPT_AES,				    // AES
	SP_PARAM_DECRYPT_AES256,				// AES256
    SP_PARAM_DECRYPT_AES256_GDPR2,			// AES256 GDPR二期
	SP_PARAM_DECRYPT_GM_SM1_ECB,               /*国密加密算法*/       
	SP_PARAM_DECRYPT_GM_SM1_OFB,               /*国密加密算法*/ 
	SP_PARAM_DECRYPT_GM_SM4_ECB,               /*国密加密算法*/ 
	SP_PARAM_DECRYPT_GM_SM4_OFB,               /*国密加密算法*/  
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

// NVR浓缩信息轨迹点集合 (段类型 0xA0)
typedef struct
{
	unsigned char objID;
	unsigned char timeTag;
	unsigned short reserved;
	SP_IVS_POINT trackPoint; 

	unsigned int trackTime;
	unsigned int appearTime;
	unsigned int disappearTime;
}SP_IVS_OBJ_A0;

//扩展的NVR浓缩信息轨迹点集合（段类型 0xA0）
typedef struct
{
	unsigned char	objID;
	unsigned char timeTag;
	unsigned short reserved;
	SP_IVS_POINT trackPoint; 

	unsigned int trackTime;
	unsigned int appearTime;
	unsigned int disappearTime;

	unsigned char	Objtype;
	unsigned char speed;
	unsigned short direct;

	unsigned char globalColor[10];
	unsigned char topColor[10];
	unsigned char bottomColor[10];
	unsigned char reserve[2];
}SP_IVS_OBJ_A0_Ex;

typedef struct
{
	unsigned int type;	//联合体实际存储的结构体，SP_IVS_OBJ_A0为0，SP_IVS_OBJ_A0_Ex为1
	union SP_IVS_OBJ_UNION
	{
		SP_IVS_OBJ_A0	  *IVSObjA0;
		SP_IVS_OBJ_A0_Ex  *IVSObjA0Ex;
	}ObjUnion;
    unsigned int ObjUnionLen;   //表示ObjUnion中实际负载的数据大小，为IVS Object的个数乘以单个IVS object的长度
}SP_IVS_OBJ_ALL;

#ifndef STREAM_PARSER_FOR_RELEASE
/********************************************************************
 *	Funcname: 	    	IVSCallBack
 *	Purpose:	        解析IVS数据帧的回调函数
 *  OutputParam:        IVSType:取值SP_IVS_PARSE_TYPE，取值为IVS_TRACK时，单个IVS object对应 SP_IVS_OBJ；
													   取值为IVS_TRACK_EX时，单个IVS object对应结构体 SP_IVS_OBJ_EX；
													   取值为IVS_TRACK_EX3时，单个IVS object对应结构体 SP_IVS_TRACK_EX3_SCENE_POINTS_INFOR；
													   取值为IVS_TRACK_A1时， 单个IVS object对应结构体 SP_IVS_OBJ_A0;
													   取值为IVS_TRACK_A1_EX时， 单个IVS object对应结构体 SP_IVS_OBJ_ALL;
													   取值为IVS_TRACK_40时，单个IVS object对应结构体 SP_IVS_COMMON_OBJ；
 *                      pIVSBuff: IVS Object结构体数组的起始地址
 *                      nIVSBuffLen：pIVSBuff的长度，为IVS Object的个数乘以单个IVS object的长度
 *                                  单个IVS object的长度可由IVSType备注类型获得。
 *						pUserData: 用户自定义
 *
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
 *                      parseType: 解析智能帧的类型，取值SP_IVS_PARSE_TYPE，当帧子类型值为SP_FRAME_SUB_TYPE_DATA_INTL时，取值IVS_TRACK_EX；
																			当帧子类型值为SP_FRAME_SUB_TYPE_DATA_INTLEX时，取值为SP_IVS_OBJ_EX2；
																			当帧子类型值为SP_FRAME_SUB_TYPE_SCENE_INFORMATION_TAGGING时，取值为SP_IVS_OBJ_EX3；
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
*	Purpose:				设置码流解析参数
*	InputParam:			handle: 流解析句柄
								nParamType: 参数类型  详见SP_PARAM_TYPE 
								pParam:参数地址    当nParamType是解密类型（SP_PARAM_DECRYPT_AES,SP_PARAM_DECRYPT_AES256,SP_PARAM_DECRYPT_AES256_GDPR2）时，pParam传SP_DECRYPT_PARAM*
								nParamLength:参数大小， 当nParamType是解密类型（SP_PARAM_DECRYPT_AES,SP_PARAM_DECRYPT_AES256,SP_PARAM_DECRYPT_AES256_GDPR2）时，pParam传SP_DECRYPT_PARAM结构体大小
*	Return:					0:成功; 其他值:失败
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

#endif // __INCLUDED_DAHUA_MEDIAPARSER_STREAMPARSEREX_H__

