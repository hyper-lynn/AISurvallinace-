/*
* Copyright (c) 2008, 浙江大华
* All rights reserved.
*
* 文件名称：STLHelper.h
* 文件标识：
* 摘　　要：提供一些公共操作的模版函数, map或list存放的数据必须是new出来的指针才能使用
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2008年10月28日
* 修订记录：创建
*/
#ifndef _STL_HELPER_H_
#define _STL_HELPER_H_

template<class T, class Entry>
inline void clearMapWithDeleteItem(T& var)
{
	Entry it = var.begin();
	for (; it != var.end(); ++it)
	{
		delete (*it).second;
	}
	var.clear();
}

template<class T, class Entry, class ValueType>
inline void clearMapWithReleaseItem(T& var)
{
	Entry it = var.begin();
	for (; it != var.end(); ++it)
	{
		ValueType* value = (*it).second;
		value->release();
	}
	var.clear();
}

template<class MapType, class Entry, class PoolType>
inline void clearMapWithRecycleItem(MapType& collect, PoolType& pool)
{
	Entry it = collect.begin();

	for (; it != collect.end(); ++it)
	{
		pool.push_back((*it).second);
	}
	collect.clear();
}

template<class T>
inline void clearDequeWithDeleteItem(T& var)
{
	while ( !var.empty() )
	{
		delete (var.front());
		var.pop_front();
	}
}

template<class T, class Entry>
inline void clearListWithDeleteItem(T& var)
{
	Entry it = var.begin();
	for (; it != var.end(); ++it)
	{
		delete (*it);
	}
	var.clear();
}

template<class PoolType, class ItemType>
inline ItemType* createItemFromPool(PoolType& pool)
{
	ItemType* item = NULL;
	if ( !pool.empty() )
	{
		item = pool.front();
		pool.pop_front();
	}
	else
	{
		item = new ItemType;
	}

	return item;
}

template<class MapType, class Entry, class ValueType, class KeyType>
inline ValueType* getMapItem(MapType& collect, KeyType key)
{
	ValueType* value = NULL;
	Entry it = collect.find(key);
	if (it != collect.end())
	{
		value = (*it).second;
	}

	return value;
}

template<class MapType, class Entry, class ValueType, class KeyType>
inline ValueType* getMapItemWithErase(MapType& collect, KeyType key)
{
	ValueType* value = NULL;
	Entry it = collect.find(key);
	if (it != collect.end())
	{
		value = (*it).second;
		collect.erase(it);
	}

	return value;
}

template<class MapType, class Entry, class ValueType, class KeyType>
inline int addMapItem(MapType& collect, KeyType key, ValueType* value)
{
	int res = -1;
	Entry it = collect.find(key);

	if ( it == collect.end() )
	{
		res = 0;
		collect[key] = value;
	}

	return res;
}

template<class MapType, class Entry, class KeyType>
inline int delMapItem(MapType& collect, KeyType key)
{
	int res = -1;
	Entry it = collect.find(key);

	if ( it != collect.end() )
	{
		delete (*it).second;
		collect.erase(it);
		res = 0;
	}

	return res;
}

template<class MapType, class Entry, class ValueType, class KeyType>
inline int releaseMapItem(MapType& collect, KeyType key)
{
	int res = -1;
	Entry it = collect.find(key);

	if ( it != collect.end() )
	{
		ValueType* value = (*it).second;
		value->release();
		collect.erase(it);
		res = 0;
	}

	return res;
}

template<class MapType, class Entry, class KeyType, class PoolType>
inline int recycleMapItem(MapType& collect, KeyType key, PoolType& pool)
{
	int res = -1;
	Entry it = collect.find(key);

	if ( it != collect.end() )
	{
		pool.push_back((*it).second);
		collect.erase(it);
		res = 0;
	}

	return res;
}

#endif
