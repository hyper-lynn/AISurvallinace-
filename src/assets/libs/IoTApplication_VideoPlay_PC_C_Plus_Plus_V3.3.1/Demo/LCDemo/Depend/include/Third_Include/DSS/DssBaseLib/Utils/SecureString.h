// SafeString.h: interface for the CSecureString class.
//
// by lin_jianyan 2008-1-24
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAFESTRING_H__C3B4FA32_7166_4489_8660_73EEADAC0E66__INCLUDED_)
#define AFX_SAFESTRING_H__C3B4FA32_7166_4489_8660_73EEADAC0E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>

#ifndef DOAX_DEPRECATED
#ifdef _WIN32
// 放在class关键字后面，以及函数或者变量定义的前面
#define DOAX_DEPRECATED	__declspec(deprecated)
#else
#define DOAX_DEPRECATED	__attribute__ ((deprecated))
#endif // #ifdef WIN32
#endif // #ifndef DOAX_DEPRECATED

class DOAX_DEPRECATED CSecureString
{
public:
	CSecureString();
	CSecureString(const char* src);
	CSecureString(const CSecureString& src);
	virtual ~CSecureString();

	CSecureString& operator=(const char* src);
	CSecureString& operator=(const CSecureString& src);
	CSecureString& operator=(const CSecureString* src);

	CSecureString& operator+=(const char src);
	CSecureString& operator+=(const char* src);
	CSecureString& operator+=(CSecureString& src);
	CSecureString& operator+=(CSecureString* src);

	CSecureString* operator+(const char* src);
	CSecureString* operator+(CSecureString& src);
	CSecureString* operator+(CSecureString* src);
	
	bool operator!=(const char* src) const;
	bool operator!=(const CSecureString& src) const;
	bool operator!=(const CSecureString* src) const;
	
	bool operator==(const char* src) const;
	bool operator==(const CSecureString& src) const;
	bool operator==(const CSecureString* src) const;

	bool operator>(const char* src) const;
	bool operator>(const CSecureString& src) const;
	bool operator>(const CSecureString* src) const;

	bool operator<(const char* src) const;
	bool operator<(const CSecureString& src) const;
	bool operator<(const CSecureString* src) const;
	
	bool operator>=(const char* src) const;
	bool operator>=(const CSecureString& src) const;
	bool operator>=(const CSecureString* src) const;
	
	bool operator<=(const char* src) const;
	bool operator<=(const CSecureString& src) const;
	bool operator<=(const CSecureString* src) const;

	char& operator[](int pos) const;

	const char* c_str() const;

	CSecureString* substr(unsigned int start, unsigned int length) const;
	unsigned int length() const;
	int find_first_of(char target, unsigned int start=0) const;
	int find_first_of(const char*  target, unsigned int start=0) const;
	void insert(unsigned int start, const char* target);
	int erase(unsigned int start, unsigned int length);
	bool empty() const;
	int size() const;
	int compare(const char* src) const;
	int compare(const CSecureString& src) const;
	int compare(const CSecureString* src) const;

	CSecureString& append(const char src);
	CSecureString& append(const char* src);
	CSecureString& append(CSecureString& src);
	CSecureString& append(CSecureString* src);
//	static const int npos = 0;

public:
	static int npos;

private:
	char* m_str;
};

#endif // !defined(AFX_SAFESTRING_H__C3B4FA32_7166_4489_8660_73EEADAC0E66__INCLUDED_)
