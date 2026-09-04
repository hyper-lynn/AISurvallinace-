#ifndef _OSNCLIENT_API_HPP
#define _OSNCLIENT_API_HPP


#ifdef WIN32
#define OSN_API __stdcall
#ifdef OSNCLIENT_EXPORTS
#define OSN_DECLSPEC __declspec(dllexport)
#else
#define OSN_DECLSPEC __declspec(dllimport)
#endif
#else
#define OSN_API
#define OSN_DECLSPEC
#endif
#ifdef __cplusplus
#define OSN_EXTERN extern "C" OSN_DECLSPEC
#else
#define OSN_EXTERN extern OSN_DECLSPEC
#endif


/**
 * Status codes from API functions
 */
enum osn_status {
   OSN_OK,                     ///< operation successful
   OSN_OK_P2P,                 ///< operation successful created tunnel type P2P
   OSN_OK_RELAYED,             ///< operation successful created tunnel type RALAYED and timed out
   OSN_ERROR_API_NOT_INITIALIZED,    /// initialization failed, session wrong, certificates not found ...
   OSN_ERROR_NO_NETWORK,             /// no network available
   OSN_ERROR_CANNOT_CONNECT_TO_AGENT, ///< could not connect to specified host
   OSN_ERROR_LOCAL_PORT_ALREADY_USED, ///< could not connect via specified localport
   OSN_ERROR_AGENT_RESOURCES_LIMIT_REACHED, ///< could not connect due to device max concurrent clients number reached
   OSN_ERROR_INVALID_DEVICE_ID,///< could not connect due to invalid parameter passed
   OSN_ERROR_INVALID_SERVICE_PORT,///< could not connect due to invalid parameter passed
   OSN_ERROR_INVALID_LOCAL_PORT,///< could not connect due to invalid parameter passed
   OSN_ERROR_INVALID_TUNNEL,    /// invalid tunnel data passed for destroy tunnel
   OSN_ERROR,                  ///< an unspecified error occurred, necessary to check logfile to find out what actually went wrong 
   OSN_OK_DIRECT   
};
typedef enum osn_status osn_status_t;



struct osn_tunnel_creds_st {
    const char* user_id;
    const char* domain;
    const char* password;
};
typedef struct osn_tunnel_creds_st  osn_tunnel_creds;

typedef osn_tunnel_creds * osn_tunnelCreds_t;
typedef enum
{
    OSN_CLOSED = -1,
    OSN_CONNECTING = 0,
    OSN_READY_FOR_RECONNECT = 1,
    OSN_UNKNOWN = 2,
    OSN_LOCAL = 3,
    OSN_REMOTE_P2P = 4,
    OSN_REMOTE_RELAY = 5,
    OSN_REMOTE_RELAY_MICRO = 6
}osn_tunnel_state;

typedef enum
{
    OSN_OKAY = 0,
    OSN_NO_PROFILE,
    OSN_ERROR_READING_CONFIG,
    OSN_API_NOT_INITIALIZED,
    OSN_INVALID_SESSION,
    OSN_OPEN_CERT_OR_PK_FAILED,
    OSN_UNLOCK_PK_FAILED,
    OSN_PORTAL_LOGIN_FAILURE,
    OSN_CERT_SIGNING_ERROR,
    OSN_CERT_SAVING_FAILURE,
    OSN_ADDRESS_IN_USE,
    OSN_INVALID_ADDRESS,
    OSN_NO_NETWORK,
    OSN_CONNECT_TO_HOST_FAILED,
    OSN_STREAMING_UNSUPPORTED,
    OSN_INVALID_STREAM,
    OSN_DATA_PENDING,
    OSN_BUFFER_FULL,
    OSN_FAILED,
    OSN_INVALID_TUNNEL,
    OSN_ILLEGAL_PARAMETER,
    OSN_INVALID_RESOURCE,
    OSN_INVALID_STREAM_OPTION,
    OSN_INVALID_STREAM_OPTION_ARGUMENT,
    OSN_ABORTED,
    OSN_STREAM_CLOSED,
    /* adding more error codes*/
    OSN_CANNOT_CONNECT_TO_AGENT = 101,
    OSN_LOCAL_PORT_ALREADY_USED,
    OSN_AGENT_RESOURCES_LIMIT_REACHED,
    OSN_INVALID_DEVICE_ID,
    OSN_INVALID_SERVICE_PORT,
    OSN_INVALID_LOCAL_PORT,
    OSN_ERROR_CODE_LAST
}osn_tunnel_status;

enum
{
    OSNCLIENT_LOG_EMERG, OSNCLIENT_LOG_ALERT, OSNCLIENT_LOG_CRIT, OSNCLIENT_LOG_ERR, OSNCLIENT_LOG_WARNING, 
    OSNCLIENT_LOG_NOTICE, OSNCLIENT_LOG_INFO, OSNCLIENT_LOG_DEBUG
};

typedef unsigned int localPort_t; // available range from 1024 - 65536
typedef unsigned int servicePort_t; // available servicePort (for example 80,9000,1025 or 23) 

/**
 * Struct with all tunnel info with its created connection type
 * that should be returned on   success create tunnel or NULL if create tunnel failed
 */
#define MAX_DNS_NAME    512
struct osn_tunnel_info_st {
   servicePort_t             servicePort;
   localPort_t               localPort;
   osn_status_t              tunnelStatus;
   const char*               deviceId;

};
typedef struct osn_tunnel_info_st  osn_tunnel_info;

typedef osn_tunnel_info * osn_tunnelInfo_t;

typedef struct
{
   servicePort_t        servicePort;
   localPort_t          localPort;
   osn_tunnel_state     tunnelStatus;
   char                 deviceId[MAX_DNS_NAME];
   void                 *context;
}osn_tunnel_data;

//typedef struct osn_tunnel_info_st  osn_tunnel_info;

//typedef osn_tunnel_info * osn_tunnelInfo_t;
#define NUM_OF_RETRIES 50

#define MAX_TUNNEL_ENTRIES 100

typedef void (*print_callback)(char *);
OSN_EXTERN osn_status_t OSN_API fnOsnClient_register_print_callback_V1(print_callback print, int level);

typedef void (*print_callback)(char *);
OSN_EXTERN osn_status_t OSN_API fnOsnClient_register_print_callback(print_callback print, int level);


/**
*  osn_status_t OSN_API fnOsnClient_createTunnel
*  Creates a tunnel to deviceId:servicePort on local port
*  on first call initialize the tunneling environment, opens session on Base Server
*  to re-initialize environment use shutdown call before.
* @param - deviceId - unique device identifier, must match the device id that the agent uses
* @param - servicePort - Agents port number to create a tunnel to
* @param - localPort_t  - local port number of the tunnel. Valid values are 1025 to 65535 or 0.
*   If 0 - OSN will find an available port number for the local tunnel end
*  If 1025-65535 - OSN will assign the local end the specified value or will fail is not available
* @param output osn_tunnelInfo_t
* @return - output param osn_status_t allocatedLocalPort ;
* [RW] - Please write the possible failure codes returned and their meaning
* On success valid return values OSN_OK_RELAYED or OSN_OK_P2P
* on failure the different OSN_ERRORs can be returned
*/
osn_tunnel_status osn_create_tunnel(osn_tunnel_data *tunnelInfoHandle);
/*LEGACY*/OSN_EXTERN    osn_status_t     OSN_API fnOsnClient_createTunnel_V1(
                                                const char*          deviceId,
                                                servicePort_t        servicePort,
                                                localPort_t          localPort,
                                                osn_tunnelInfo_t     tunnelInfoHandle
                                              );



/*LEGACY*/OSN_EXTERN    osn_status_t     OSN_API fnOsnClient_createTunnel(
                                                const char*          deviceId,
                                                servicePort_t        servicePort,
                                                localPort_t          localPort,
                                                const osn_tunnelCreds_t credentials,
                                                osn_tunnelInfo_t     tunnelInfoHandle
                                              );


/**
* OSN_API fnOsnClient_destroyTunnel
* Gracefully destroy a tunnel identified by deviceId:servicePort localPort mapping. After the function is called the local port that was associated with this tunnel is available for new tunnel creation.
*
* @param - deviceId - unique device identifier, must match the device id that the agent uses
* @param - servicePort - Agents port number to create a tunnel to
*         If 0 - Destroy all tunnels to all service ports for deviceId (ignores localPort)
*         If 1025-64435 - try to destroy tunnels to the service port (see local port values below)
* @param - localPort  - local port number of the tunnel
*        If 0 - destroy all the tunnels to deviceId:servicePort
*        If 1025-65535 - Destroy the specific tunnel
* @return - osn_status_t  valid return values OSN_OK or OSN_ERROR_INVALID_TUNNEL  tunnel not found
*/
//OSN_EXTERN osn_status_t OSN_API fnOsnClient_destroyTunnel_old(const char*            deviceId, servicePort_t          servicePort,     localPort_t              localPort);
/**
* OSN_API fnOsnClient_destroyTunnel
* Gracefully destroy a tunnel identified by osn_tunnelInfo_t .deviceId, osn_tunnelInfo_t .servicePort osn_tunnelInfo_t .localPort from map of active tunnels. After the function is called the local port that was associated with this tunnel is available for new tunnel creation.
*
* @param - osn_tunnelInfo_t  - struct with tunnel info of created previously tunnel
* @return - osn_status_t valid return values OSN_ERROR_INVALID_TUNNEL or OSN_OK
*/

OSN_EXTERN osn_status_t OSN_API fnOsnClient_destroyTunnel_V1(osn_tunnel_info *tunnelInfoHandle);
osn_tunnel_status osn_destroy_tunnel(osn_tunnel_data *tunnelInfoHandle);

OSN_EXTERN osn_status_t OSN_API fnOsnClient_destroyTunnel(osn_tunnel_info *tunnelInfoHandle);

/**
* OSN_API fnOsnClient_startup
* Set the start directory of the tunneling environment
*
* @param - path - A path to a writable working directory (runtime installed) directory. The following subdirectories and files should exist :
*       roots\ca.crt
*       roots\ozvision-root.crt
*       users\ronny.weiser_at_ozvision.com.crt
*       users\ronny.weiser_at_ozvision.com.key
*       configuration\mimetypes.ini
*
* If path == NULL � or the this API was not called before create tunnel api  then current directory is used (normally in  WIN/MAC/LINUX )
* On Android and IOS platforms, the path is the directory where the apk/ipa package unpacked during application start (in runtime) and the above directories and files copied into it from assets (resources).
* @return - osn_status_t
* Only OSN_OK returned
*
*/
OSN_EXTERN osn_status_t  OSN_API  fnOsnClient_startup_V1 (const char* path);
osn_tunnel_status osn_init(char *dir, char *buff, int buff_len);


OSN_EXTERN osn_status_t  OSN_API  fnOsnClient_startup (const char* path);
/**
* osn_status_t OSN_API fnOsnClient_shutdown
* Gracefully destroys all previously created tunnels and shuts down the tunneling environment.
* @return - osn_status_t
* valid return values OSN_OK on success
* or
*    OSN_ERROR_INVALID_SESSION,            /// could not close session
*    OSN_ERROR_API_NOT_INITIALIZED
*/

osn_tunnel_status osn_cleanup();
/*LEGACY*/OSN_EXTERN osn_status_t OSN_API fnOsnClient_shutdown_V1();

/*LEGACY*/OSN_EXTERN osn_status_t OSN_API fnOsnClient_shutdown();

/**
 * Function definition
 * @return char * version - Full api and Core API version string
 */
OSN_EXTERN const char* OSN_API fnOsnClient_getAPIVersion();
/*DEBUG!!*/
void *main_debug(void *_tunnel_data);
#endif // _OSNCLIENT_API_HPP
