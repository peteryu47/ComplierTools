#include "gm_lexer.h"

#include "com/var.h"
#include <stdio.h>

GMToken GMLexer::GetNextToken()
{
    m_Char = GetNextNonBlankChar();

    if (IsAlpha(m_Char))
    {
        return ReadId();
    }
    else if (m_Char == '%')
    {
        return GMToken(kGMTokenTypePercent, Var());
    }
    else if (m_Char == ':')
    {
        return GMToken(kGMTokenTypeColon, Var());
    }
    else if (m_Char == '|')
    {
        return GMToken(kGMTokenTypeVertical, Var());
    }
    else if (m_Char == '\'' || m_Char == '\"')
    {
        return ReadStr();
    }

    return GMToken(kGMTokenTypeEOF, Var());
}

GMToken GMLexer::ReadNextToken()
{
    return GMToken(kGMTokenTypeEOF, Var());
}

char GMLexer::GetNextChar()
{
    char c;

    if (!m_InputStream.bad())
    {
        m_InputStream >> c;
    }
    else
    {
        c = EOF;
    }

    return c;
}

char GMLexer::GetNextNonBlankChar()
{
    char c = GetNextChar();

    while (IsBlankChar(c))
    {
        c = GetNextChar();
    }

    return c;
}

GMToken GMLexer::ReadId()
{
    string str;
    str.reserve(1000);

    while (IsAlpha(m_Char) || IsUnderline(m_Char))
    {
        str = str + m_Char;
    }
    
    return GMToken(kGMTokenTypeId, Var(str));
}

GMToken GMLexer::ReadStr()
{
    return GMToken(kGMTokenTypeId, Var());
}
