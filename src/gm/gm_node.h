#ifndef __GM_NODE_H__
#define __GM_NODE_H__

#include <string>
using namespace std;

enum eGMNodeType
{
    kGMNodeTypeT,
    kGMNodeTypeNT,
};

class GMNodeBase
{
protected:
    GMNodeBase(int no, const string& name, eGMNodeType type) : m_No(no), m_Name(name), m_Type(type) {};
    virtual ~GMNodeBase(){}

public:
    const string&   GetName() const { return m_Name; }
    eGMNodeType     GetType() const { return m_Type; }

    int             GetNo() { return m_No; }

protected:
    string          m_Name;
    eGMNodeType     m_Type;
    int             m_No;
};

class GMNodeT : public GMNodeBase
{
public:
    GMNodeT(int no, const string& name) : GMNodeBase(no, name, kGMNodeTypeT) {};
    virtual ~GMNodeT(){}
};

class GMNodeNT : public GMNodeBase
{
public:
    GMNodeNT(int no, const string& name) : GMNodeBase(no, name, kGMNodeTypeNT) {};
    virtual ~GMNodeNT(){}
};

#endif
