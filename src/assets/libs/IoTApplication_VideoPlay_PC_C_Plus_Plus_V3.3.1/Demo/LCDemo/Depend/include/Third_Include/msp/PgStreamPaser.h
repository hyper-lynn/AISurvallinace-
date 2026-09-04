
#ifndef _PGSP_STREAM_PARSER_H_
#define _PGSP_STREAM_PARSER_H_

#include "StreamParser.h"

class PgspPacketManager;
struct SPTYPE_VIDEODATA;
struct SPTYPE_AUDIODATA;
class PgFrame;

class PgStreamParser :public StreamParser
{
public:
	PgStreamParser();
	virtual ~PgStreamParser();
	
	virtual int InputPacket(mediaPacketI *packet);
	virtual int InputData(t_int8 *pData, t_int32 nLen);
	virtual int GetMediaFrame(MediaFrame &frame);
	virtual void Clear();	

	int GetFrameRate() const;

protected:
	int InputVideoData(SPTYPE_VIDEODATA *pVideo);
	int InputAudioData(SPTYPE_AUDIODATA *pAudio);

	static int PacketToMediaFrame(MediaFrame &frame, PgFrame *pgFrame);
	static int GetMedaiFrame(MediaFrame &frame, std::map<unsigned int, PgspPacketManager*> &frameMap);

private:
	int	FramePerSec;

	std::map<unsigned int, PgspPacketManager*> m_videoFrameMap;
	std::map<unsigned int, PgspPacketManager*> m_audioFrameMap;
};

inline int PgStreamParser::GetFrameRate() const
{
	return FramePerSec;
}

#endif
