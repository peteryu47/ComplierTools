#ifndef __VAR_H__
#define __VAR_H__

#include <string>
using namespace std;

enum eVarType
{
    kVarTypeChar,
    kVarTypeShort,
    kVarTypeInt32,
    kVarTypeInt64,
    kVarTypeFloat,
    kVarTypeDouble,
    kVarTypeString,
    kVarTypeInvalid,
};

class Var
{
public:
    Var() : m_Char(kVarTypeInvalid) {}
    Var(char v) : m_Char(v), m_VarType(kVarTypeChar) {}
    Var(short v) : m_Short(v), m_VarType(kVarTypeShort) {}
    Var(int v) : m_Int32(v), m_VarType(kVarTypeInt32) {}
    Var(long long v) : m_Int64(v), m_VarType(kVarTypeInt64) {}
    Var(float v) : m_Float(v), m_VarType(kVarTypeFloat) {}
    Var(double v) : m_Double(v), m_VarType(kVarTypeDouble) {}
    Var(string v) : m_String(v), m_VarType(kVarTypeString) {}

    eVarType        GetVarType() {return m_VarType;}
    char            GetCharValue() {return m_Char;}
    short           GetShortValue() {return m_Short;}
    int             GetInt32Value() {return m_Int32;}
    long long       GetInt64Value() {return m_Int64;}
    float           GetFloatValue() {return m_Float;}
    double          GetDoubleValue() {return m_Double;}
    string          GetStringValue() {return m_String;}

    static Var      empty;

private:
    eVarType        m_VarType;
    union
    {
        char        m_Char;
        short       m_Short;
        int         m_Int32;
        long long   m_Int64;
        float       m_Float;
        double      m_Double;
    };
    string          m_String;
};

#endif