// osdef.h

#ifndef	__OSDEF_H_
#define	__OSDEF_H_

#if	defined(_WIN32) || defined(WIN32) || defined(__WIN32__)

#	include "win32.h"

#else

#	include	"linux.h"

#endif

#endif	//__OSDEF_H_
