

#ifndef global_h__
#define global_h__

#include <stdio.h>

#ifdef WIN32
	#ifdef DLL_INTERFACE_EXPORTS
		#define INTERFACE_API __declspec(dllexport)
		#define INTERFACE_API_CLASS __declspec(dllexport)
	#else
		#define INTERFACE_API __declspec(dllimport)
		#define INTERFACE_API_CLASS __declspec(dllexport)
	#endif

    #define Log_Write(tag, msg) printf("[");printf(tag);printf("] ");printf(msg);printf("\n")
	#define Log_Print(tag, msg, ...) printf("[");printf(tag);printf("] ");printf(msg, __VA_ARGS__);printf("\n")
#else 
	#define INTERFACE_API			extern
	#define INTERFACE_API_CLASS	

    #ifdef ANDROID
		#include <android/log.h>
		#define  Log_Print(tag, msg, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, msg, __VA_ARGS__)
        #define  Log_Write(tag, msg) __android_log_write(ANDROID_LOG_DEBUG, tag, msg)

    #elif IOS
        #include <stdlib.h>
        #define Log_Print(tag, msg, ...) printf("[");printf(tag);printf("] ");printf(msg, __VA_ARGS__);printf("\n")
        #define Log_Write(tag, msg) printf("[");printf(tag);printf("] ");printf(msg);printf("\n")
        #define library

    #else
        #define Log_Print(tag, msg, ...) printf("[");printf(tag);printf("] ");printf(msg, __VA_ARGS__);printf("\n")
        #define Log_Write(tag, msg) printf("[");printf(tag);printf("] ");printf(msg);printf("\n")
    #endif


#endif





#endif // global_h__
