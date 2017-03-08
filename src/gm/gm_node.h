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
    GMNodeBase(const string& name, eGMNodeType type) : m_Name(name), m_Type(type) {};
    virtual ~GMNodeBase(){}

public:
    const string&   GetName() { return m_Name; }
    eGMNodeType     GetType() { return m_Type; }

protected:
    string          m_Name;
    eGMNodeType     m_Type;
};

class GMNodeT : public GMNodeBase
{
public:
    GMNodeT(int no, const string& name) : GMNodeBase(name, kGMNodeTypeT), m_No(no) {};
    virtual ~GMNodeT(){}

private:
    int     m_No;
};

class GMNodeNT : public GMNodeBase
{
public:
    GMNodeNT(const string& name) : GMNodeBase(name, kGMNodeTypeNT) {};
    virtual ~GMNodeNT(){}
};

#endif
