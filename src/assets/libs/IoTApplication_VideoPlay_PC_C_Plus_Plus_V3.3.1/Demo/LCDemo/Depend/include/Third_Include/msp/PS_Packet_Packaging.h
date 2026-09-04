#ifndef  _PS_PACKET_PACKAGING_H_
#define  _PS_PACKET_PACKAGING_H_

#ifdef WIN32
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <list>

/************************************************************************
      PS流码流文本结构基本说明   
	  I Frame    PS_Header | PS_Map | PES |.......|PES
	  P Frame    PS_Header | PES | .......|PES
	  Audio Frame   PS_Header | (PS_Map) | PES  (音频为统一格式，封装在一个PES里面即可)

	  广东电网项目中，为了以后更好的扩展PS流，传进来的码流无比保证为一帧一帧单独的数据，支持H.264和mpeg4


	  函数调用必须是单线程调用，函数内部未加锁，如果需要多线程调用，请外部加锁
************************************************************************/

typedef std::list<int> Nal_list;

//此编码函数为最新的广东电网编码的PS流，封装出来为标准的PS流
class CPSPackaging
{
public:
	CPSPackaging();
	virtual ~CPSPackaging();

public:  //方法

	//I帧封装，传进来的pDestBuf务必清零
	int Packet_I_frame(const char* pSrcBuf , int nSrcLen, char* pDestBuf , int& nDestLen , int nFrameRate , int nWidth , int nHeight);
	int Packet_P_frame(const char* pSrcBuf , int nSrcLen, char* pDestBuf , int& nDestLen);
	int Packet_Audio_frame(const char* pSrcBuf , int nSrcLen, char* pDestBuf , int& nDestLen , bool btalk);
private: //方法
	int Packet_PS_header(char* pDestBuf, int& nLen, bool bAudio, bool bAligned = false);                      //封装PS_Header
	int Packet_PS_map(char* pDestBuf, int& nLen);											     //封装PS_MAP
	int Packet_System_header(char* pDestBuf, int& nLen);                                         //封装System_Header  广东电力项目中，此函数没用
	int Packet_Video_frame(const char* pSrcBuf , int nSrcLen , char* pDestBuf, int& nLen , bool bFirst = true);       //封装视频帧
	int Packet_Audio_frame_G711(const char* pSrcBuf , int nSrcLen , char* pDestBuf, int& nLen);  //封装独立的音频格式

	int GeneratePacketsFromFrame(const char* pSrcBuf , int nSrcLen , char* pDestBuf , int& nLen); //拆分NAL包
private: //变量

	int m_IFrameCount;
	uint64_t  m_nScrb;                                              //system_clock_reference_base
	uint64_t  m_nDts;                                               //DTS时标
	uint64_t  m_nAudioPts;                                          //AUDIO PTS时标
	uint64_t  m_nVideoPts;                                          //Video PTS时标

	int m_nFrameRate;                                                       //码流的Rate
	int m_nWidth;                                                           //码流的宽
	int m_nHeight;                                                          //码流的高
	
	unsigned int m_AudioCount;                                              //语音对讲格式的音频数据统计

	Nal_list m_nal_list;                                                     //NAL记载
};

#endif
