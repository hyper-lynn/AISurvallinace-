#ifndef _DSSC_UTILS_OBJECT_POOL_H_
#define _DSSC_UTILS_OBJECT_POOL_H_

#include <deque>
#include <list>
#include "Utils/Singleton.h"
#include "AX_API/AX_Mutex.h"
#include "AX_API/AX_Thread_Guard.h"


class DOAX_DEPRECATED IPoolBase
{
public:
	virtual ~IPoolBase() {}
	virtual int	Recycle(void *obj) = 0;
};

template <typename OBJ>
class CObjectPool: public Singleton< CObjectPool<OBJ> >, public IPoolBase
{
	friend class Singleton< CObjectPool<OBJ> >;
#define ObjectDeque		typename std::deque<OBJ*>
#define ObjectList		typename std::list<OBJ*>

protected:
	CObjectPool(void)
	{
		m_iMaxQueueSize = 100; //队列大小可能修改调整
		m_iCreateNum = 0;
	}

	~CObjectPool(void)
	{
		AX_Guard<AX_Mutex>  lock(m_mtxDeque);
		m_deque.clear();
		lock.release();

		AX_Guard<AX_Mutex> lock1(m_mtxList);

		ObjectList::iterator itor = m_list.begin();
		while (itor != m_list.end())
		{
			if (NULL != *itor)
			{
				delete *itor;					
			}		
			itor = m_list.erase(itor);
		}

		lock1.release();
	}

public:	
	void SetMaxSize(int size)
	{
		m_iMaxQueueSize = size;
	}

	OBJ *CreateObject()
	{
		OBJ* pObj= NULL;

		AX_Guard<AX_Mutex>  lock(m_mtxDeque);

		if (m_deque.size() == 0)
		{
			pObj = new OBJ;
			pObj->SetPool(this);
			m_iCreateNum++;

			AX_Guard<AX_Mutex> lock1(m_mtxList);
			m_list.push_back(pObj);
			lock1.release();
		}
		else
		{
			pObj = m_deque.front();
			pObj->Reset();
			m_deque.pop_front();
		}

		return pObj;
	}

	virtual int	Recycle(void *obj)
	{
		OBJ *pObj = (OBJ *)obj;

		AX_Guard<AX_Mutex>  lock(m_mtxDeque);

		if((int)m_deque.size() < m_iMaxQueueSize)
		{
			m_deque.push_back(pObj);
		}
		else
		{
			delete pObj;
			m_iCreateNum--;

			AX_Guard<AX_Mutex> lock1(m_mtxList);
			ObjectList::iterator itor = m_list.begin();
			while (itor != m_list.end())
			{
				if (*itor == pObj)
				{
					itor = m_list.erase(itor);
					break;
				}
				itor++;
			}
			lock1.release();
		}

		return 0;
	}

	int GetCreateNum()
	{
		return m_iCreateNum;
	}

	int GetDequeSize()
	{
		m_mtxDeque.acquire();
		int size =  m_deque.size();
		m_mtxDeque.release();
		return size;
	}

protected:
	ObjectDeque			m_deque;
	AX_Mutex			m_mtxDeque;
	int					m_iMaxQueueSize;
	int					m_iCreateNum;

	ObjectList			m_list;
	AX_Mutex            m_mtxList;
};


#endif //_DSSC_UTILS_OBJECT_POOL_H_

