
#ifndef _STREAM_PARSER_H_
#define _STREAM_PARSER_H_

#include "media_rtp_packet_i.h"
#include "MediaFrame.h"

class StreamParser
{
public:
	StreamParser();
	virtual ~StreamParser();

	virtual int InputPacket(mediaPacketI *packet) = 0;
	virtual int InputData(t_int8 *pData, t_int32 nLen) = 0;
	virtual int GetMediaFrame(MediaFrame &frame) = 0;
	virtual void Clear() = 0;
};

#endif
