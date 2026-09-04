/**
 *  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
 *  All Rights Reserved.
 *
 *  "$Id$"
 *
 * @brief  此文件用于封装接口繁杂的tinyxml,提供出简洁常用到的接口
 *
 * Revisions:    2011-10-13  liu_ding@dahuatech.com  Created
 *
 *   2012-02-14 liu_ding@dahuatech.com modified
 *    增加设置及读取值增加不同类型接口的重载；
 *    增加对<<及>>运算符的重载；
 *    增加对读写文件的支持；
 *    增加CTiXmlHandle类：节点辅助类 以更方便地访问多级节点；
 *   2012-10-22 liu_ding@dahuatech.com modified
 *    增加CTiXmlTable类中getRoot()非const接口；
 *    增加CTiXmlNode类中next()及child()非const接口；
 *    增加CTiXmlNode类中parent()const及非const接口；
 *    解决xxxAsUInt()返回值范围不够的BUG；
 *  2013-01-06 liu_ding@dahuatech.com modified
 *    增加toString()接口的重载,实现标签前后可设置自定义分隔符；
 */

#ifndef __DAHUA_TINYXML_TIXMLTABLE_H__
#define __DAHUA_TINYXML_TIXMLTABLE_H__

#include <iostream>
#include <string>
#include "TinyXmlDefs.h"

class TiXmlElement;

namespace Dahua{

namespace TiXml{

class CTiXmlNode;
class CTiXmlTableImplement;

/// tinyxml列表类
class TINYXML_API CTiXmlTable
{
public:
    CTiXmlTable();
    ~CTiXmlTable();

public: /// 解析操作
    /// 解析 成功返回0,失败-1
    int parse(const char* pXmlData);

    /// 返回根节点
    const CTiXmlNode* getRoot() const;

public: /// 组建操作
    /// 组建并返回根节点
    CTiXmlNode* setRoot(const char* pVersion = "1.0", const char* pEncoding = "UTF-8", const char* pStandalone = "");

    /// 返回根节点
    CTiXmlNode* getRoot();

public: /// 字符串化操作
    /// 形成字符串
    const char* toString();
    /// 形成字符串
    /// \param [in] indent, 标签前的分隔符,如4个或8个空格 ("    ")
    /// \param [in] lineBreak, 标签后的分隔符,如回车换行符 ("\n","\r")
    const char* toString(const char *indent, const char *lineBreak);

    ///重载>>
    friend std::istream& operator >> (std::istream& in, CTiXmlTable& tTable);
    ///重载<<
    friend std::ostream& operator << (std::ostream& out, const CTiXmlTable& tTable);
    ///重载<<
    friend std::string& operator << (std::string& out, const CTiXmlTable& tTable);

public: /// 文件操作
    /// 编码
    enum
    {
        E_ENCODING_UNKNOWN,//默认方式 对应tixml开源库中的TIXML_ENCODING_UNKNOWN
        E_ENCODING_UTF8,   //UTF8方式 对应tixml开源库中的TIXML_ENCODING_UTF8
        E_ENCODING_LEGACY, //Legacy方式 一种在支持UTF8之前使用的方式,可理解为扩展的ascii
                           // 对应tixml开源库中的TIXML_ENCODING_LEGACY,具体说明可参考tinyxml说明文档
    };
    ///读写文件
    bool loadFile(const char * pFilename, unsigned int uEncoding=E_ENCODING_UNKNOWN);
    bool saveFile(const char * pFilename) const;

private:
    CTiXmlTable(const CTiXmlTable &);
    void operator=(const CTiXmlTable &);

    CTiXmlTableImplement *m_ptImplement;
};

/// 节点类
class TINYXML_API CTiXmlNode
{
    friend class CTiXmlTableImplement;

public:

    /// 构造函数
    /// \param [in] pTag, TinyXml节点名称
    /// \param [in] pText, TinyXml节点值
    /// \param [in] bCDATA, 是否设置TinyXml的CDATA属性值
    /// \return 1 添加成功, 0 添加队列失败
    CTiXmlNode(const char *pTag = NULL, const char *pText = NULL, bool bCDATA = false);

    /// 重载赋值操作符
    /// \param [in] tOther, 赋值的CTiXmlNode对象引用
    /// \return 被赋值后的对象引用
    CTiXmlNode& operator=(const CTiXmlNode& tOther);

    /// 析构函数
    ~CTiXmlNode();

    /// 返回本节点的父节点指针
    /// 返回查找到的节点指针，失败为NULL
    const CTiXmlNode* parent() const;
    CTiXmlNode* parent();

    /// 子节点的指针
    /// \param [in] pTag, 若pTag=NULL, 返回第一个子节点
    ///                   若PTag!=NULL, 返回指点名称的子节点
    /// \param [in] uIndex, 默认为0，则返回pTag名称的第一个子节点
    ///                     否则返回uIndex索引的pTag名称的子结点
    /// \return 返回查找到的子节点的指针， 失败返回NULL
    const CTiXmlNode* child(const char* pTag = NULL, unsigned int uIndex = 0) const;
    CTiXmlNode* child(const char* pTag = NULL, unsigned int uIndex = 0);

    /// 下一节点的指针
    /// \param [in] pTag, 若pTag=NULL, 直接返回下一个节点
    ///                   若PTag!=NULL, 返回Tag值相同的下一个节点
    /// 返回查找到的节点指针，失败为NULL
    const CTiXmlNode* next(const char* pTag = NULL) const;
    CTiXmlNode* next(const char* pTag = NULL);

    /// 返回节点的tag
    const char* tag() const;

    /// 返回节点的text
    const char* text() const;

    /// 以string类型返回节点的text值
    std::string textAsString() const;

    /// 以int类型返回节点的text值,失败将返回默认值0,是否失败可用NULL==text()判断
    int textAsInt() const;

    /// 以unsigned int类型返回节点的text值,失败将返回默认值0,是否失败可用NULL==text()判断
    unsigned int textAsUInt() const;

    /// 以double类型返回节点的text值,失败将返回默认值0,是否失败可用NULL==text()判断
    double textAsDouble() const;

    /// 以bool类型返回节点的text值,失败将返回默认值false,是否失败可用NULL==text()判断
    bool textAsBool() const;

    /// 设置节点的tag,text
    int setData(const char* pTag, const char* pText = NULL, bool bCDATA = false);

    /// 设置节点的tag,text(string类型)
    int setData(const char* pTag, const std::string& strText, bool bCDATA = false);

    /// 设置节点的tag,text(int类型)
    int setData(const char* pTag, int iText, bool bCDATA = false);

    /// 设置节点的tag,text(unsigned int类型)
    int setData(const char* pTag, unsigned int uText, bool bCDATA = false);

    /// 设置节点的tag,text(double类型)
    int setData(const char* pTag, double dText, bool bCDATA = false);

    /// 设置节点的tag,text(bool类型)
    int setData(const char* pTag, bool bText, bool bCDATA = false);

    /// 返回节点的属性
    const char* attribute(const char* pName) const;

    /// 以int类型返回节点的属性值
    std::string attributeAsString(const char* pName) const;

    /// 以int类型返回节点的属性值,失败将返回默认值0,是否失败可用NULL==attribute(pName)判断
    int attributeAsInt(const char* pName) const;

    /// 以unsigned int类型返回节点的属性值,失败将返回默认值0,是否失败可用NULL==attribute(pName)判断
    unsigned int attributeAsUInt(const char* pName) const;

    /// 以double类型返回节点的属性值,失败将返回默认值0,是否失败可用NULL==attribute(pName)判断
    double attributeAsDouble(const char* pName) const;

    /// 以bool类型返回节点的属性值,失败将返回默认值false,是否失败可用NULL==attribute(pName)判断
    bool attributeAsBool(const char* pName) const;

    /// 设置节点的属性
    int setAttribute(const char *pName, const char *pValue);

    /// 设置节点的属性(string类型)
    int setAttribute(const char *pName, const std::string& strValue);

    /// 设置节点的属性(int类型)
    int setAttribute(const char *pName, int iValue);

    /// 设置节点的属性(unsigned int类型)
    int setAttribute(const char *pName, unsigned int uValue);

    /// 设置节点的属性(double类型)
    int setAttribute(const char *pName, double dValue);

    /// 设置节点的属性(bool类型)
    int setAttribute(const char *pName, bool bValue);

    /// 注意以下添加子节点,都是深拷贝操作

    /// 添加子节点
    int setChild(const CTiXmlNode *pChild);
    int setChild(const CTiXmlNode &tChild);

    /// 以给定的tag,text值直接添加子节点
    int setChild(const char *pChildTag, const char *pChildText, bool bCDATA = false);

    /// 以给定的tag,text(string类型)值直接添加子节点
    int setChild(const char *pChildTag, const std::string strChildText, bool bCDATA = false);

    /// 以给定的tag,text(int类型)值直接添加子节点
    int setChild(const char *pChildTag, int iChildText, bool bCDATA = false);

    /// 以给定的tag,text(unsigned int类型)值直接添加子节点
    int setChild(const char *pChildTag, unsigned int uChildText, bool bCDATA = false);

    /// 以给定的tag,text(double类型)值直接添加子节点
    int setChild(const char *pChildTag, double dChildText, bool bCDATA = false);

    /// 以给定的tag,text(bool类型)值直接添加子节点
    int setChild(const char *pChildTag, bool bChildText, bool bCDATA = false);

    static int setChild(CTiXmlNode &tParent, const char *pChildTag, const char *pChildText, bool bCDATA = false);

private:
    CTiXmlNode(const CTiXmlNode &tOther);
    CTiXmlNode(TiXmlElement *ptHandle);
    void elementBindNode(TiXmlElement *ptHandle);
    void elementUnBindNode(TiXmlElement *ptHandle);
    CTiXmlNode* parentImpl() const;
    CTiXmlNode* childImpl(const char* pTag, unsigned int uIndex) const;
    CTiXmlNode* nextImpl(const char* pTag) const;

    TiXmlElement *m_ptNewHandle; /// 保存内部申请缓冲的指针
    TiXmlElement *m_ptHandle;    /// 保存内部操作指针
};


/// 节点辅助类 以更方便地访问多级节点
class TINYXML_API CTiXmlHandle
{
public:
    CTiXmlHandle(const CTiXmlNode *pNode);
    CTiXmlHandle(const CTiXmlHandle &tHandle);
    CTiXmlHandle operator=(const CTiXmlHandle &tHandle);

    /// 以CTiXmlHandle的child方式可方便访问多级子节点
    /// 无需对每级节点进行安全性检查
    /// 如：
    /// <root>
    ///     <node1>
    ///         <node2>
    ///             <node3>node3_text</node3>
    ///         </node2>
    ///     </node1>
    /// </root>
    /// 则访问node3节点时：
    /// CTiXmlHandle handle(pRoot)
    /// const CTiXmlNode *pNode3=handle.child("node1").child("node2").child("node3").node();
    /// if(NULL != pNode3)
    /// {do something}
    CTiXmlHandle child(const char *pTag = NULL, unsigned int uIndex = 0) const;

    const CTiXmlNode* node() const;

private:
    const CTiXmlNode* m_pNode;
};

}//namespace TiXml
}//namespace Dahua

#endif //__DAHUA_TINYXML_TIXMLTABLE_H__

