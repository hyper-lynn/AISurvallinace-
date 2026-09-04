// CRtpStreamDec : rtp stream decode

#ifndef INCLUDED_CRTPSTREAMDEC_H
#define INCLUDED_CRTPSTREAMDEC_H

#ifdef WIN32
#pragma warning( disable : 4786 )
#endif

// 负责将RTP包进行解析，处理乱序、丢包等，组装成完成的视频帧提供给外面
// 只处理一路RTP流，不进行demux

// 使用方法，调用InputData()输入一个完整的RTP包，然后循环调用GetFrame()获取视频帧（0到多个）

// 表示一个输出的帧，内存由CRtpStreamDec管理自行管理，有效期到CRtpStreamDec下一个函数被调用



// RTP buffer数量，完整的RTP包会马上组成视频帧，否则会等待乱序的包，超过buffer限制时丢弃不完整的帧
// 这个值小会导致乱序时丢帧概率大，这个值大会导致实际丢包时等待延时大

#define MAX_RTP_BUFFER_FRAME_NUM	( 64 )
#define RTP_DEC_CLOCK_RATE			90000

#define SEQ_OVERTURN_DELTA     10000
#define MAX_SEQ				   0xFFFF

#define TM_OVERTURN_DELTA      1000000
#define MAX_TM				   0xFFFFFFFF

#define RTP_SDEC_SUCCESS   0


// #include "libRtpLog.h"
#include <map>
#include "RTP/RtpDecFrame.h"
#include "RTP/CRTPPacket.h"
#include "AX_API/AX_RefPtr.h"

class CRtpStreamDec
{
protected:
	typedef AX_RefPtr<CRTPPacket> CRTPPacketPtr;
	typedef std::map<uint64,CRTPPacketPtr> CRTPPkgMap;//同一个frame的map
	typedef std::map<uint64,CRTPPkgMap> CFrameMap;//所有frames
public:
	explicit CRtpStreamDec(int maxBufferFrame=MAX_RTP_BUFFER_FRAME_NUM,uint32 clockRate=RTP_DEC_CLOCK_RATE);
	virtual ~CRtpStreamDec();
protected:
	CRtpStreamDec(const CRtpStreamDec&);
	CRtpStreamDec& operator=(const CRtpStreamDec&);
public:
	//返回  RTPSDEC_SUCCESS  表示成功
	int reset();
	//返回  RTPSDEC_SUCCESS  表示成功
	int inputPacket(CRTPPacket* packet);
	//返回  RTPSDEC_SUCCESS  表示成功
	int inputData( const char * buf, int buf_len );
	//返回  RTPSDEC_SUCCESS  表示有Frame
	int getVideoFrame(CRtpDecFrame& frame);

	//主动忽略某个rtp包
	int skipPacket(CRTPPacket* packet);
	//主动忽略某个rtp数据
	int skipData( const char * buf, int buf_len );

protected:
	void checkSeqOverTurn(uint16 seq);
	void checkTmOverTurn(uint32 curTm);
	uint64 convertSeq(uint16 seq);
	uint64 convertTm(uint32 curTm);

	int addRtpPacket(uint64 seq, uint64 curTm,CRTPPacketPtr& pkg);
	int fillFrame(CRTPPkgMap& pkgMap,CRtpDecFrame& frame);
protected:
	uint64 _rtpSeqBase;
	bool    _seqOverTurn;
	uint64 _rtpTmBase;
	bool	_tmOverTurn;	
	uint64	_lastSubmitSeq;
	uint64 _lastSubmitTm;
	uint64 _firstSubmitTm;
	CFrameMap _frames;

	int	_maxBufferFrame;
	uint32  _clockRate;
	
};

// TODO : 内存拷贝优化，增加 packet pool 和 frame pool

#endif // INCLUDED_CRTPSTREAMDEC_H
