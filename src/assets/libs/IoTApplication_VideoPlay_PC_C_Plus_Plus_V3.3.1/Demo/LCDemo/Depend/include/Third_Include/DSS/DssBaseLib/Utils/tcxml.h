#ifndef DH_DSS_UTILS_TC_XML_H_INCLUDED
#define DH_DSS_UTILS_TC_XML_H_INCLUDED

#include <list>
#include <map>
#include <string>
#include "tinyxml/tinyxml.h"
#include "AX_API/platform.h"

class /*DOAX_DEPRECATED*/ CTCXml	// 去掉DOAX_DEPRECATED修饰,去除warning时,导致协议库编译不过 --20808
{
public:
	const static int max_xml_len=10*1024*1024;
	const static int min_xml_buf_len=5*1024;
public:
	CTCXml();
	~CTCXml();
public:
	void newFile(std::string version="1.0",std::string encode="UTF-8",std::string standalone="");
	void loadFile(const char* fileName);
	void loadString(const std::string& xmlString);

	/*
	保存xml为字符串
	minLen在保存时候，初始尝试分配的字符串buffer大小
	maxLen最大分配的字符串buffer大小,如果分配这个空间之后，仍然不能保存为字符串，则操作失败
	*/
	void saveString(std::string& xmlString,int minLen=min_xml_buf_len,int maxLen=max_xml_len);
	void saveFile();
	void saveFile(const char* fileName);

	void enter(const char* nodeName);
	bool next(const char* nodeName);
	void leave();

	void new_enter(const char* nodeName);
	//bool new_next(const char* nodeName); //这个操作不需要，容易引起概念混乱
	
	bool hasChild(const char* nodeName);
	bool hasAttr(const char* attrName);
	
	std::string get_string_attr(const char* attrName);
	int32 get_int32_attr(const char* attrName);
	uint32 get_uint32_attr(const char* attrName);
	float32 get_float32_attr(const char* attrName);

	void set_string_attr(const char* attrName, const char* attrValue);
	void set_uint32_attr(const char* attrName, uint32 attrValue);
	void set_int32_attr(const char* attrName, int32 attrValue);
	void set_float32_attr(const char* attrName, float32 attrValue);

	std::string get_string(const char* item);
	void get_string(const char* item,char* value,int max_value_len);
	void set_string(const char* item,const char* value);

	int get_int32(const char* item);
	void set_int32(const char* item,int32 value);

	uint32 get_uint32(const char* item);
	void set_uint32(const char* item,uint32 value);

	int64 get_int64(const char* item);
	void set_int64(const char* item,int64 value);

	uint64 get_uint64(const char* item);
	void set_uint64(const char* item,uint64 value);

	float32 get_float32(const char* item);
	void set_float32(const char* item,float32 value);

	int32 get_int32_with_unit(const char* item,const std::map<std::string,int32>& units);
	uint32 get_uint32_with_unit(const char* item,const std::map<std::string,uint32>& units);

	void addComment(const char* comment);

public:
    static const std::map<std::string,uint32>& getDefaultUCapacityUnits();
    static const std::map<std::string,int32>&  getDefaultICapacityUnits();
    static const std::map<std::string,uint32>& getDefaultUTimeUnits();
    static const std::map<std::string,int32>&  getDefaultITimeUnits();
protected:
    static std::map<std::string,uint32> _defaultUCapacityUnits;
    static std::map<std::string,int32>  _defaultICapacityUnits;
    static std::map<std::string,uint32> _defaultUTimeUnits;
    static std::map<std::string,int32>  _defaultITimeUnits;    
protected:
	void checkNodeName(const char* nodeName);
	void checkItemName(const char* item);
	void checkItemValue(const char* value);
    void trim(std::string& value);
    void split_value_with_unit(const std::string str,std::string& value,std::string& unit);
	std::string getAttrValue(const char* attrName);
	void setAttrValue(const char* attrName,const char* attrValue);
	void checkOpenStat(bool opened);
protected:
	TiXmlElement*				_curNode;
	std::list<TiXmlElement*>	_nodeList;
	TiXmlDocument				_doc;
	bool						_opened;
};

#endif//DH_DSS_UTILS_TC_XML_H_INCLUDED
