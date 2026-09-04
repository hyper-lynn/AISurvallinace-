//
//  "$Id: MediaStream.h 16503 2010-11-26 02:23:15Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _STREAM_MEDIA_STREAM_H_
#define _STREAM_MEDIA_STREAM_H_

#include "Infra/IntTypes.h"
#include "Defs.h"

// 本组接口是为兼容原组件接口保留的, 请不要使用

namespace Dahua {
namespace Stream {

enum {MEDIA_STREAM_ERR = -1};
enum {MEDIA_STREAM_OK = 0};

int STREAM_API FindFrameMarker(uint8_t *buf, int nLen, uint32_t *pMP4Code);
int STREAM_API MediaStreamParse(uint8_t * pBuffer, uint32_t *pCount, int bFirst);

} // namespace Stream
} // namespace Dahua

#endif// _UTILS_MEDIA_STREAM_H_


