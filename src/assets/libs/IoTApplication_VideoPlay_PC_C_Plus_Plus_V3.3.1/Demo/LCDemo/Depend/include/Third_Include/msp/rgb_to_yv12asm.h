#ifndef _RGB24_TO_YV12_ASM_LIB_H
#define _RGB24_TO_YV12_ASM_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

	/*
	width, height: rgb src图像的宽度和高度
	stride: y的跨距
	*/
	void RGB24_To_YV12_Convert(	unsigned char *  y_out,
							unsigned char *  u_out,
							unsigned char *  v_out,
							unsigned char *  src,
							unsigned int width,
							unsigned int height,
							unsigned int stride);


#ifdef __cplusplus
}
#endif
#endif
