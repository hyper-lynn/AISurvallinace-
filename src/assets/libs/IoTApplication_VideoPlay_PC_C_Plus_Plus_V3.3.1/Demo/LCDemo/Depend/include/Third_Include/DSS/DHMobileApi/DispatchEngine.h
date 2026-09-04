
#ifndef DispatchEngine_h__
#define DispatchEngine_h__

/*
    分发线程
*/
#include "DHMobileApi.h"
#include <list>
#include "DHEventHandler.h"

typedef int (*msgCall)(int param1, int param2, int param3);

typedef struct Tag_FuncMsg 
{
    msgCall         msgFunction;
    int             param1;
    int             param2;
    int             param3;
}FuncMsg;

typedef struct Tag_EventMsg
{
    DHEventHandler* handle;
    int             param1;
    int             param2;
    void*           reserved;
}EventMsg;

typedef struct Tag_CommandMsg
{
    int             nMsgCommand;
    int             param1;
    int             param2;
    void*           reserved;
}CommandMsg;

enum MSG_TYPE{
    MSG_FUNCTION,
    MSG_EVENT,
    MSG_COMMAND,
};

struct DispathMsg
{
    MSG_TYPE  nType;
    union {
        FuncMsg     funcMsg;
        EventMsg    eventMsg;
        CommandMsg  commandMsg;
    };
};

typedef struct TagCommandMsgItem
{
    int             nMsgCmd;
    DHEventHandler* handle;
}CommandMsgItem;

class INTERFACE_API_CLASS CMsgManager
{
    typedef std::vector<DHEventHandler*> HandleList;
    typedef std::vector<CommandMsgItem> CmdHandleList;

public:
    static CMsgManager& GetInstance();

    void onEvent(const DispathMsg& msg );
    // 注册一个消息响应
    void RegisterEventMsg(int nMsgCMD, DHEventHandler* pHandle);
    // 移除一个消息响应
    void UnRegisterEventMsg(int nMsgCMD, DHEventHandler* pHandle);
    // 移除一个句柄的一系列的消息响应
    void RemoveEventHandle();

    void RemoveHandle();
protected:
    virtual void DealFunctionMsg(const DispathMsg&);
    virtual void DealEventMsg(const DispathMsg&);
    virtual void DealCommandMsg(const DispathMsg&);

private:
    CMsgManager(){};
    virtual ~CMsgManager(){};
    bool IsRemove(int nCMD, DHEventHandler* pHandle);
    // 消息号与响应列表的对应
    std::map<int, HandleList> m_MsgMap;

    CReadWriteMutex m_removeLock;
    CmdHandleList   m_removeList;

    CReadWriteMutex m_msglock;
};

class INTERFACE_API_CLASS CDispatchEngine
{
public:
    ~CDispatchEngine(void);

    static CDispatchEngine& GetInstance();

    void InitEngine();
    void ExitEngine();

    void PostMsg(DHEventHandler* pHandle, int param1, int param2);
    void PostMsg(int nMsgCommand, int param1, int param2);

    void doEvent(const DispathMsg& msg);

protected:
    void StartEngine();
    void StopEngine();
    void ClearEngine();
    // 暂时没有使用
    void PostMsg(msgCall nID, int param1, int param2, int param3);

    static DWORD WINAPI MSG_RoutineThread(LPVOID lpParam);
private:
    CDispatchEngine();

    std::list<DispathMsg>   m_MsgQueue;

    CReadWriteMutex m_datalock;
    MobileApi::OS_THREAD        m_hThread;
    MobileApi::OS_EVENT     m_hExitEvent;
    bool            m_bExitFlag;

    bool            m_stopFlag;
};

#endif // DispatchEngine_h__

