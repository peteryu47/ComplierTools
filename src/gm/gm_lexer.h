#ifndef __GM_LEXER_H__
#define __GM_LEXER_H__

#include <istream>
#include "gm_token.h"
using namespace std;

class GMLexer
{
public:
    GMLexer(istream& input) : m_InputStream(input) {}
    ~GMLexer(){}

    GMToken     GetNextToken();
    GMToken     ReadNextToken();

private:
    char        GetNextChar();
    char        GetNextNonBlankChar();
    bool        IsAlpha(char c) { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }
    bool        IsDigit(char c) { return (c >= '0' && c <= '9'); }
    bool        IsUnderline(char c) { return (c == '_'); }
    bool        IsBlankChar(char c) { return (c == ' ' || c == '\t' || c == '\r' || c == '\n'); }
    GMToken     ReadId();
    GMToken     ReadStr();

private:
    istream&    m_InputStream;
    char        m_Char;
};

#endif