#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include "com/var.h"
using namespace std;

enum eGMTokenType
{
    kGMTokenTypeId,
    kGMTokenTypeStr,
    kGMTokenTypePercent,
    kGMTokenTypeColon,
    kGMTokenTypeVertical,
    kGMTokenTypeEOF,
};

class GMToken
{
public:
    GMToken(eGMTokenType type, const Var& value) : m_Type(type), m_Var(value) {}
    ~GMToken(){}

    eGMTokenType    GetType() {return m_Type;}
    Var&            GetValue() {return m_Var;}

private:
    eGMTokenType    m_Type;
    Var             m_Var;
};

#endif