

#ifndef encode_algorithm_h__
#define encode_algorithm_h__

#include "../globaldef.h"

#ifdef __cplusplus  
extern "C" {    
#endif

INTERFACE_API int alg_sha1(const char *data, int len, char *outbuf);

#ifdef __cplusplus  
}
#endif

#endif // encode_algorithm_h__