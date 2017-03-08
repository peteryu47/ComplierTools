#ifndef __GM_TOKEN_H__
#define __GM_TOKEN_H__

#include <string>
#include "com/var.h"
using namespace std;

enum eGMTokenType
{
    kGMTokenTypeInvalid,
    kGMTokenTypeId,         //id
    kGMTokenTypeStr,        //str
    kGMTokenTypePercent,    //%
    kGMTokenTypeColon,      //:
    kGMTokenTypeVertical,   //|
    kGMTokenTypeSemicolon,  //;
    kGMTokenTypeEOF,
};

class GMToken
{
public:
    GMToken() : m_Type(kGMTokenTypeInvalid) {}
    GMToken(eGMTokenType type, const Var& value) : m_Type(type), m_Var(value) {}
    ~GMToken(){}

    eGMTokenType    GetType() {return m_Type;}
    string          GetTypeName() 
    {
        switch (m_Type)
        {
        case kGMTokenTypeId:
            return "kGMTokenTypeId";
        case kGMTokenTypeStr:
            return "kGMTokenTypeStr";
        case kGMTokenTypePercent:
            return "kGMTokenTypePercent";
        case kGMTokenTypeColon:
            return "kGMTokenTypeColon";
        case kGMTokenTypeVertical:
            return "kGMTokenTypeVertical";
        case kGMTokenTypeSemicolon:
            return "kGMTokenTypeSemicolon";
        case kGMTokenTypeEOF:
            return "kGMTokenTypeEOF";
        default:
            return "";
        }
    }
    Var&            GetValue() {return m_Var;}

private:
    eGMTokenType    m_Type;
    Var             m_Var;
};

#endif