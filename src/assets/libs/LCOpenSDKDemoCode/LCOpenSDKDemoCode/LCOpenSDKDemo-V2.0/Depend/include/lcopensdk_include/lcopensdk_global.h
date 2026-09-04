#ifndef _LCOPENSDK_GLOBAL_H_
#define _LCOPENSDK_GLOBAL_H_

#ifdef LCOPENSDK_EXPORTS
# define LCOPENSDK_EXPORT _declspec(dllexport)
#else
# define LCOPENSDK_EXPORT
#endif

#endif /* _LCOPENSDK_GLOBAL_H_ */
