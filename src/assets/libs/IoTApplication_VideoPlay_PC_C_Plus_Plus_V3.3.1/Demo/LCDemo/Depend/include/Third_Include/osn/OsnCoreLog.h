#ifndef _OSNCORE_API_HPP
#define _OSNCORE_API_HPP


#ifndef WIN32
#include "sys/types.h"
#endif

#if defined(WIN32) && !defined(NABTO_WIN32_API_STATIC)
#define NABTOAPI __stdcall
#ifdef NABTO_CLIENT_API_EXPORTS
#define NABTO_DECL_PREFIX __declspec(dllexport)
#else
#define NABTO_DECL_PREFIX __declspec(dllimport)
#endif
#else
#define NABTOAPI
#define NABTO_DECL_PREFIX extern
#endif



#ifdef __cplusplus
extern "C" {
#endif

/**
 * Definition of the callback function for the nabtoRegisterLogCallback
 * function.
 * @param line     The line to log.
 * @param size     The length of the line.
 */
typedef void (*NabtoLogCallbackFunc)(const char*line , size_t size);

/**
 * Register a log callback function.
 * @param callback     The callback which is called for every log line.
 * @return    NABTO_OK. This is the only value returned.
 */

enum nabto_status {
    NABTO_OK,                     ///< operation successful.
    NABTO_NO_PROFILE,             ///< no user profile found in home directory.
    NABTO_ERROR_READING_CONFIG,   ///< could not read config file.
    NABTO_API_NOT_INITIALIZED,    ///< nabtoStartup() was not invoked as the first function.
    NABTO_INVALID_SESSION,        ///< operation requires a valid session.
    NABTO_OPEN_CERT_OR_PK_FAILED, ///< certificate or private key files could not be opened.
    NABTO_UNLOCK_PK_FAILED,       ///< private key could not be decrypted with specified password.
    NABTO_PORTAL_LOGIN_FAILURE,   ///< could not login to portal to sign cert (invalid email/password for active portal (urlPortalDomain in config)).
    NABTO_CERT_SIGNING_ERROR,     ///< portal failed when signing certificate request.
    NABTO_CERT_SAVING_FAILURE,    ///< could not save signed certificate.
    NABTO_ADDRESS_IN_USE,         ///< could not sign up with specified email address as it is already in use.
    NABTO_INVALID_ADDRESS,        ///< could not sign up with specified email address as it is invalid.
    NABTO_NO_NETWORK,             ///< no network available.
    NABTO_CONNECT_TO_HOST_FAILED, ///< could not connect to specified host.
    NABTO_STREAMING_UNSUPPORTED,  ///< peer does not support streaming.
    NABTO_INVALID_STREAM,         ///< an invalid stream handle was specified.
    NABTO_DATA_PENDING,           ///< unacknowledged stream data pending.
    NABTO_BUFFER_FULL,            ///< all stream data slots are full.
    NABTO_FAILED,                 ///< an unspecified error occurred, necessary to check logfile to find out what actually went wrong.
    NABTO_INVALID_TUNNEL,         ///< an invalid tunnel handle was specified.
    NABTO_ILLEGAL_PARAMETER,      ///< a parameter to a function is not supported.
    NABTO_INVALID_RESOURCE,       ///< an invalid asynchronous resource was specified.
    NABTO_ERROR_CODE_COUNT        ///< number of posible error codes. This number is always larger than all other error codes.
};
typedef enum nabto_status nabto_status_t;
NABTO_DECL_PREFIX nabto_status_t NABTOAPI nabtoRegisterLogCallback(NabtoLogCallbackFunc callback);
    
    
    
#ifdef __cplusplus
} // extern c
#endif

#undef NABTO_DECL_PREFIX
    
#endif // _OSNCORE_API_HPP

