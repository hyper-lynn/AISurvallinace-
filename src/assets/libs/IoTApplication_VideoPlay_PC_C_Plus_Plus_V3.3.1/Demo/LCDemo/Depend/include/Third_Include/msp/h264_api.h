/*
**  ************************************************************************
**                                  CODEC
**                           H.264 Video Encoder
**
**         (c) Copyright 1992-2008, ZheJiang Dahua Technology Stock Co.Ltd.
**                            All Rights Reserved
**
**	File  Name	: h264_api.h
**	Description	: H.264编码算法
**	Modification: 2008/04/09		zhanghui	Create the file
**  ************************************************************************
*/

#ifndef H264_API_H
#define H264_API_H

//#define CSP_420 0
//#define CSP_422	1//老的DM644X
#ifdef __cplusplus
extern "C" {
#endif

#define CSP_420	0
#define CSP_422	1
#define CCIR422 2//DM648的

//编码参数输入结构体
typedef struct enc_param_t
{
	int enc_stride;		//原始视频存放在内存中亮度Y的相邻两行第一个象素点的跨距
	int csp;			//CSP_420 : uv的enc_stride是y的enc_stride的一半
						//CSP_422 : uv的enc_stride和y的enc_stride的一样
	int width;		//编码原始视频Y的宽度，默认C是Y的一半
	int height;		//编码原始视频Y的高度，默认C是Y的一半
	int i_key_interval; //I帧间隔

	int qp;				//码率控制用  
	int i_bitrate;		//qp==0, i_bitrate==0 : 无效；
						//qp==0, i_bitrate!=0 : 固定码率的CBR模式
						//qp!=0, i_bitrate==0 : 无上限码率的可变码率VBR模式
						//qp!=0, i_bitrate!=0 : 带上限码率的可变码率VBR模式
	int i_framerate;	//帧率
	int interlace;		//原始视频要不要解交错 1: 要做deinterlace； 0：不做deinterlace
	//filter_enc:liujie0017
	int is_filter_enc;		//原始视频是否要滤波处理 1: 要做filter处理；0：不做filter处理
}enc_param_t;

//编码一帧返回信息结构体
typedef struct enc_stat_t
{
	int length;
	int frame_type;

	int i_frame_rate;
	int i_bitrate;
	int i_qp;
	int i_max_qp;
}enc_stat_t;

void Dahua_enc_open();
void *Dahua_get_enc_handle(enc_param_t *p_enc_param);

/*	$Function		:	Dahua_enc_frame
==  ===============================================================
==	Description		:	编码一帧数据

==	Argument		:	p_handle : 编码句柄指针，输入
						p_yuv ： 要编码的原始视频的YUV数据，yuv相连，输入
						p_bits:  编码一帧得到的码流数据，输出
						p_enc_stat：编码一帧后的状态返回信息，输出
==					
== 	Return			:	返回帧类型，0: P帧, 1: I帧, -1:失败
==	Modification	:	2008-04-09     zhanghui    Create
==  ===============================================================
*/
int Dahua_enc_frame(void *p, 
					unsigned char *pDataY,
					unsigned char *pDataU,
					unsigned char *pDataV,
					unsigned char *pBitstream,
					enc_stat_t	*pEnc_stat);

//void Dahua_adjust_enc_param(void *p, int i_frame_rate, int i_key_interval, int i_bitrate, int i_qp, int i_max_qp);
int Dahua_enc_adjust_enc_param(void *p_handle,enc_param_t *p_enc_param);

//void Dahua_adjust_size(void *p, enc_param_t *enc_param);
int Dahua_force_intra_frame( void *p );

void Dahua_free_enc_handle(void *p);
void Dahua_enc_close();


#ifdef __cplusplus
}
#endif


#endif //H264_API_H
