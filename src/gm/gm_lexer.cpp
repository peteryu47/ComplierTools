#include "gm_lexer.h"

#include "com/var.h"
#include "com/file_data.h"
#include <stdio.h>

GMLexer::GMLexer(const string& text)
{
    m_Text = text;
    m_Index = 0;
}

GMToken GMLexer::GetNextToken()
{
    char c = GetNextNonBlankChar();

    if (IsAlpha(c))
    {
        return ReadId();
    }
    else if (c == '%')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypePercent, Var());
    }
    else if (c == ':')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypeColon, Var());
    }
    else if (c == '|')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypeVertical, Var());
    }
    else if (c == '\'' || c == '\"')
    {
        return ReadStr();
    }
    else if (c == ';')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypeSemicolon, Var());
    }

    return GMToken(kGMTokenTypeEOF, Var());
}

GMToken GMLexer::ReadNextToken()
{
    return GMToken(kGMTokenTypeEOF, Var());
}

void GMLexer::ConsumeCurChar()
{
    ++m_Index;
}

char GMLexer::GetNextChar()
{
    if (m_Index >= m_Text.length())
    {
        return EOF;
    }
    else
    {
        return m_Text[m_Index];
    }
}

char GMLexer::GetNextNonBlankChar()
{
    char c = GetNextChar();

    while (IsBlankChar(c))
    {
        ConsumeCurChar();
        c = GetNextChar();
    }
    return c;
}

GMToken GMLexer::ReadId()
{
    string str;
    str.reserve(100);
    char c = GetNextChar();

    while (IsAlpha(c) || IsUnderline(c))
    {
        str += c;
        ConsumeCurChar();
        c = GetNextChar();
    }
    
    return GMToken(kGMTokenTypeId, Var(str));
}

GMToken GMLexer::ReadStr()
{
    string str;
    char startChar = GetNextChar();
    str.reserve(100);

    ConsumeCurChar();
    char c = GetNextChar();

    while (c != startChar)
    {
        str += c;
        ConsumeCurChar();
        c = GetNextChar();
    }

    ConsumeCurChar();
    GetNextChar();

    return GMToken(kGMTokenTypeStr, Var(str));
}
