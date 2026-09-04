/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：TPTypedef.h
* 文件标识：参见配置管理计划书
* 摘　　要：传输层预定义
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年4月28日

*
* 取代版本：1.0
* 原作者　：
* 完成日期：
* 修订记录：
*/
#ifndef _DATAROW_H_
#define _DATAROW_H_

#include <deque>
#include "AX_API/AX_IAddRefAble.h"
#include "TPLayer/ThreadMutex.h"

class DataRow;

typedef std::deque<DataRow*> DataRow_Queue;

class CDataRowPool;

class DataRow : public AX_IAddRefAble
{
public:
	int len;
	unsigned int id;
	int socket;
	int sequence;
	int partDataSent;

	char* data;

public:
	virtual int release();

protected:
	int SetPool(CDataRowPool* pool);

protected:
	friend class CDataRowPool;
	DataRow(CDataRowPool* pool);
	CDataRowPool* _pool;
};

class CDataRowPool
{
public:
	CDataRowPool();
	~CDataRowPool();

	DataRow*			CreateDataRow();

	void				SetPoolSize(int size);

protected:
	//user should not call this function
	int					Recycle(DataRow* dataRow);

protected:
	friend class DataRow;
	DataRow_Queue _pool;
	CThreadMutex  _mutex;

	int			  _maxSize;
};


#endif // _DATAROW_H_
