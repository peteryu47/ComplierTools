#include "gm_lexer.h"

#include "com/var.h"
#include "com/file_data.h"
#include <stdio.h>

GMLexer::GMLexer(string inputFile)
{
    FileData fileData;
    fileData.Load(inputFile);
    m_Text = fileData.GetData();
    m_CurChar = '\0';
    m_Index = 0;
}

GMToken GMLexer::GetNextToken()
{
    GetNextNonBlankChar();

    if (IsAlpha(m_CurChar))
    {
        return ReadId();
    }
    else if (m_CurChar == '%')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypePercent, Var());
    }
    else if (m_CurChar == ':')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypeColon, Var());
    }
    else if (m_CurChar == '|')
    {
        ConsumeCurChar();
        return GMToken(kGMTokenTypeVertical, Var());
    }
    else if (m_CurChar == '\'' || m_CurChar == '\"')
    {
        return ReadStr();
    }
    else if (m_CurChar == ';')
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

void GMLexer::GetNextChar()
{
    if (m_Index >= m_Text.length())
    {
        m_CurChar = EOF;
    }
    else
    {
        m_CurChar = m_Text[m_Index];
    }
}

void GMLexer::GetNextNonBlankChar()
{
    GetNextChar();

    while (IsBlankChar(m_CurChar))
    {
        ConsumeCurChar();
        GetNextChar();
    }
}

GMToken GMLexer::ReadId()
{
    string str;
    str.reserve(100);

    while (IsAlpha(m_CurChar) || IsUnderline(m_CurChar))
    {
        str += m_CurChar;
        ConsumeCurChar();
        GetNextChar();
    }
    
    return GMToken(kGMTokenTypeId, Var(str));
}

GMToken GMLexer::ReadStr()
{
    string str;
    char startChar = m_CurChar;
    str.reserve(100);

    ConsumeCurChar();
    GetNextChar();

    while (m_CurChar != startChar)
    {
        str += m_CurChar;
        ConsumeCurChar();
        GetNextChar();
    }

    ConsumeCurChar();
    GetNextChar();

    return GMToken(kGMTokenTypeStr, Var(str));
}
