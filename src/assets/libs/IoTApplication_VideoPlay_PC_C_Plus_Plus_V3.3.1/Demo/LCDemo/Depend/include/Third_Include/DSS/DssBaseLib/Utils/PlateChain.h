#ifndef _DSSC_UTILS_PLATE_CHAIN_H_
#define _DSSC_UTILS_PLATE_CHAIN_H_

#include "Utils/ThreadDrive.h"
#include <set>
#include <deque>
#include <map>
#include "Utils/ObjectPool.h"
#include "AX_API/AX_IAddRefAble.h"
#include "AX_API/AX_Mutex.h"
#include "AX_API/AX_Atomic.h"


class IPlateChain;

// 通用包类
class DOAX_DEPRECATED IPdu : public AX_IAddRefAble
{
public:
	IPdu();
	virtual ~IPdu();
	virtual void Reset();
	virtual int release();

public:
	void addCount();
	void delCount();
	int getCount();
	void SetPool(IPoolBase *pool);

public:
	void SetSrcId(int id);
	int GetSrcId();
	void SetDstId(int id);
	int GetDstId();

public:
	//设置获取延迟时间，单位毫秒
	void SetDelayTime(int ms);
	int  GetDelayTime();

	//设置获取生效时间，单位毫秒
	void SetValidTime(uint64 ms);
	uint64 GetValidTime();

private:
	atomic_t _count;
	IPoolBase *m_pool;
	int m_src_id;
	int m_dst_id;
	int m_delay_time;
	uint64 m_valid_time;
};

typedef std::deque<IPdu*>			PduDeque;

struct TimerPri;
typedef std::map<int, TimerPri> TimerMap;

// 输出包回调原型
typedef void (*OutputPduCallback)(IPlateChain *pc, int id, IPdu *pdu);
// 输入包回调原型
typedef void (*InputPduCallback)(IPlateChain *pc, IPdu *pdu);

// 包处理类
class DOAX_DEPRECATED IPlateChain: public IThreadDrive
{
public:
	IPlateChain(void);
	virtual ~IPlateChain(void);

public:
	// 处理PDU，需要外部实现
	virtual int DealPdu(uint64 threadId, IPdu *pdu) = 0;
	// 每次Heartbeat时调用
	virtual int onHeartbeat(uint64 threadId = 0);
	// Timer回调
	virtual int onTimer(int timerId, uint64 threadId = 0);

protected:
	int Heartbeat(uint64 threadId = 0);

public:
	int PushPdu(IPdu *pdu, bool high_pri = false);//暂时public,不然PCSEAS编译不过,6-25
	// 将一个PDU发送给指定ID的Handler
	int SendPdu(int id, IPdu *pdu);

public:
	// 设置名字，只能设置一次
	void SetIdName(int id, const char *name);
	// 获取名字
	int GetId();
	const char *GetName();
	// 用户数据
	void SetContext(void *ctx);
	void *GetContext();

public:
	// 根据ID获取Handler
	static IPlateChain *GetHandler(int id);
	// 打印所有Handler信息
	static void PrintInfo();

public:
	int AddSuccessor(IPlateChain *pSuccessor);
	int DelSuccessor(IPlateChain *pSuccessor);
	int	GetDequeSize();
	int GetHeartbeatCount();

public:
	// 设置定时器，timerId由外部指定，不能重复。interval为定时时间，单位ms
	// （用法类似MFC的Timer）
	int SetTimer(int timerId, int interval);
	int CancelTimer(int timerId);

public:
	// 设置输出包回调函数，当IPlateChain调用SendPdu时，会将Pdu回调出来
	// 可用于测试
	void SetOPCallback(OutputPduCallback cb);
	// 设置输入包回调函数，当IPlateChain调用PushPdu时，会将Pdu回调出来
	// 可用于测试
	void SetIPCallback(InputPduCallback cb);

private:
	void CheckTimer(uint64 threadId = 0);

	int PushPduToAllSuccessor(IPdu *pdu);

	void CheckDelayPdu();
	void PushDelayPdu(IPdu *pdu);

protected:
	typedef std::set<IPlateChain*>		SussessorSet;
	SussessorSet			m_setSussessor;

	PduDeque				m_dequePduDelay;
	PduDeque				m_dequePdu;
	PduDeque				m_dequePduHighPri;
	AX_Mutex				m_mtxDequePdu;

	TimerMap				m_mapTimer;
	AX_Mutex				m_timerMtx;

	int						m_heartbeat_count;

	int						m_id;
	const char			   *m_name;
	void				   *m_ctx;

	OutputPduCallback		m_opcb;
	InputPduCallback		m_ipcb;
};


#endif

