/*
* Copyright (c) 2008, 浙江大华
* All rights reserved.
*
* 文件名称：IDGenerator.h
* 文件标识：
* 摘　　要：ID生成类，平台兼容，线程安全
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2008年07月17日
* 修订记录：创建
*/
#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include "AX_API/AX_Atomic.h"

class IDGenerator
{
public:
	IDGenerator(void)
	{
		atomic_set( &m_id, 0 );
	}

	~IDGenerator(void)
	{

	}

public:
	unsigned int getId(void)
	{
		return (unsigned int)atomic_inc( &m_id );
	}

private:
	atomic_t m_id;
};

#endif  // ID_GENERATOR_H
