#ifndef __INCLUDE_DAHUA_STREAMSVR_VORBIS_H__
#define __INCLUDE_DAHUA_STREAMSVR_VORBIS_H__

namespace Dahua{
namespace StreamSvr{

//RFC 5215 Vorbis RTP Payload Format 3.2 Out of Band Transmission
//packed configuration
struct vorbis_configuration_head
{
	unsigned char * buf;	 //packed configuration
	unsigned short  buf_len; //length of packed configuration
};

}//StreamSvr
}

#endif //__INCLUDE_DAHUA_STREAMSVR_VORBIS_H__
