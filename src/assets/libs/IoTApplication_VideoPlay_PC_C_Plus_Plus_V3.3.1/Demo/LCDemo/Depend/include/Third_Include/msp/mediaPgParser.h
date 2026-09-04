
#ifndef _IBP_MEDIA_PGSP_PARSER_H_
#define _IBP_MEDIA_PGSP_PARSER_H_

#include "media_parser_i.h"

class mediaPgParser : public mediaParserI
{
public:
	mediaPgParser();
	mediaPgParser(mediaRole role);
	virtual ~mediaPgParser();

public:
	virtual t_int32 parse(const t_int8* buff, const t_int32 buffLen, mediaPacketI* &packet, enumMediaSocket peerType);
	virtual t_int32 parse(mediaRawPacketI* rawPacket, mediaPacketI* packet);
};

#endif
