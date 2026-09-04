#ifndef HEAD_FILE_CAMERA
#define HEAD_FILE_CAMERA

#include "baselib/common/CommonTypeDefine.h"
#include "NameSolution/INameSolution.h"
#include <string>
#include <sstream>
#include <list>

using namespace std;

class CCamera
{
public:
    CCamera(){};
    virtual ~CCamera(){};
    virtual string getIdentify() = 0;
    virtual int    getType() = 0;
public:
	bool 	useMiniMemory;
    string  dataSavePath;
public:
    static const int TYPE_FILE          = 0;
    static const int TYPE_RTSP_RT       = 1;
    static const int TYPE_RTSP_PB       = 2;
    static const int TYPE_DIRECT_RT     = 3;
    static const int TYPE_DIRECT_PB     = 4;
    static const int TYPE_DSS_RT        = 5;
    static const int TYPE_DSS_PB        = 6;
    static const int TYPE_DH_CLOUD_PB   = 7;
    static const int TYPE_DH_MEETING    = 8;
    
};

//================================================================
class CRTSPCamera : public CCamera
{
public:
    virtual string getIdentify(){return url;}
    virtual int getType(){return CCamera::TYPE_RTSP_RT;}
public:
    string  url;			// URL of rtsp
	bool	isPlayback;		// whether is playback palyer
	bool	isEncrypt;		// whether encrypt the data
	string	psk;			// psk for the encrypt
};

//================================================================
class CFileCamera : public CCamera
{
public:
    virtual string getIdentify(){return filePath;}
    virtual int getType(){return CCamera::TYPE_FILE;}
public:
    string  filePath;			// path of file
};

//================================================================
///\brief Cloud camera define
class CCloudCamera : public CCamera
{
public:
    virtual string getIdentify() {return  m_m3u8Url;}
    virtual int getType() {return CCamera::TYPE_DH_CLOUD_PB;}   /// DH Cloud
    
public:
    string m_m3u8Url;       ///< M3U8列表
    string m_slicePrefix;   ///< 切片URL前缀
	string m_decryptKey;	///< 解密秘钥
	bool   m_needDecrypt;	///< 是否需要解密
#ifdef Save_File
    string m_path;
#endif
};


class CDirectBaseCamera : public CCamera
{
public:
    INT32               channel;		//channel to play
    int                 streamType;     //stream type to play
    LoginDeviceInfo     mLoginInfo;     //info to get login handle
};

class CMeetingCamera : public CCamera
{
public:
    virtual string getIdentify() {return  m_clientID;}
    virtual int     getType() {return CCamera::TYPE_DH_MEETING;}
public:
    INT32               m_channel;		//channel to play
    string              m_clientID;      //clientID to play
    string              m_clientKey;
    string              m_sipServerIP;
    int                 m_sipServerPort;
    string              m_p2pServerIP;
    int                 m_p2pServerPort;
};

/**
 *  camera that direct connect to device for realtime play
 */
class CDirectRTCamera : public CDirectBaseCamera
{
public:
    virtual string  getIdentify()
    {
        ostringstream oss;
        oss << "deviceId"   << mLoginInfo.strDeviceID
            << "channel:"   << channel;
        return oss.str();
    }
    virtual int     getType() {return CCamera::TYPE_DIRECT_RT;}
};

///\brief 直连点播Camera
class CDirectPBCamera : public CDirectBaseCamera
{
public:
    virtual string getIdentify()
    {
        ostringstream oss;
        oss << "deviceId"   << mLoginInfo.strDeviceID
            << "channel:"   << channel
            << "beginTime:" << m_startTime
            << "endTime"    << m_endTime;
        return oss.str();
    }
    virtual int getType() {return CCamera::TYPE_DIRECT_PB;}
    
public:
    long                m_startTime;            ///< 起始时间
    long                m_endTime;              ///< 结束时间
};


/**
 * DSS base camera
 */
class CDSSBaseCamera : public CCamera
{
public:
    /**
     * handle of DPSDK
     */
    int         dpHandle;
    /**
     * ID of camera. get this value from platform
     */
    string      cameraID;
    
    /**
     * stream type
     */
    int         streamType;
    
    /**
     * whether check permission
     */
    bool        isCheckPermission;
    
};

/**
 * DSS real time camera
 */
class CDSSRTCamera : public CDSSBaseCamera
{
public:
    virtual string  getIdentify()
    {
        ostringstream oss;
        oss << "cameraID : "  << cameraID
            << " streamType:" << streamType;
        return oss.str();
    }
    virtual int     getType() {return CCamera::TYPE_DSS_RT;}
    
    /**
     * media type of stream. 1.video 2.audio 3.video and audio
     */
    int     mediaType;
};

struct CDSSRecordFile{
    /**
     * begin time of record file
     */
    long    beginTime;
    /**
     * end time of record file
     */
    long    endTime;
    /**
     * index of file
     */
    int     index;
};
class CDSSPBCamera : public CDSSBaseCamera
{
public:
    virtual string  getIdentify()
    {
        ostringstream oss;
        oss << "cameraID : "    << cameraID
            << " streamType:"   << streamType
            << " beginTime:"    << beginTime
            << " endTime: "     << endTime;
        return oss.str();
    }
    virtual int     getType() {return CCamera::TYPE_DSS_PB;}
    /**
     * request mode. 1:play back as 1 time speed. 2.download as full speed
     */
    int     requestMode;
    
    /**
     * record source. 1.ALL 2.Device 3.Platform
     */
    int     reocrdSource;
    
    /**
     * begin time of playback
     */
    long    beginTime;
    
    /**
     * end time of playback
     */
    long    endTime;
    
    /**
     * record file between beginTime and endTime
     */
    list<CDSSRecordFile> recordFiles;
};

#endif