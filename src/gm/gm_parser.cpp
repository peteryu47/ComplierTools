#include "gm_parser.h"

#include "com/utils.h"
#include "com/file_data.h"
#include "gm_lexer.h"
#include <sstream>
#include <iostream>

GMParser::GMParser()
{

}

GMParser::~GMParser()
{
    SAFE_DEL(m_Lexer);
}

GMGrammar* GMParser::Parse(const string& filePath)
{
    SAFE_DEL(m_Lexer);

    FileData fileData;
    fileData.Load(filePath);

    m_Text = fileData.GetData();
    m_Lexer = new GMLexer(m_Text);
    m_IsError = false;

    GMGrammar* grammar = new GMGrammar();
    StateG(grammar);

    if (m_IsError)
    {
        delete grammar;
        return NULL;
    }

    return grammar;
}

void GMParser::StateG(GMGrammar* grammar)
{
    StateProductions(grammar);
}

void GMParser::StateProductions(GMGrammar* grammar)
{
    GetNextToken();
    while (!m_IsError && m_CurToken.GetType() != kGMTokenTypeEOF)
    {
        StateProduction(grammar);
    }
}

void GMParser::StateProduction(GMGrammar* grammar)
{
    if (m_CurToken.GetType() == kGMTokenTypeId)
    {
        GMNodeNT* nameNode = StateProductionName(grammar);
        if (nameNode == NULL)
        {
            return;
        }

        if (m_CurToken.GetType() != kGMTokenTypeColon)
        {
            ThrowParseError();
            return;
        }
        GetNextToken();     //consume :

        do 
        {
            GMProduction* production = grammar->CreateProduction(nameNode);
            StateProductionContext(grammar, production);

            if (m_CurToken.GetType() != kGMTokenTypeVertical && m_CurToken.GetType() != kGMTokenTypeSemicolon)
            {
                ThrowParseError();
                return;
            }

            if (m_CurToken.GetType() == kGMTokenTypeVertical)
            {
                GetNextToken();     //consume |
            }
        } while (m_CurToken.GetType() != kGMTokenTypeSemicolon);

        GetNextToken();     //consume ;
    }
    else
    {
        ThrowParseError();
    }
}

GMNodeNT* GMParser::StateProductionName(GMGrammar* grammar)
{
    if (m_CurToken.GetType() == kGMTokenTypeId)
    {
        GMNodeNT* node = grammar->GetGMNodeNT(m_CurToken.GetValue().GetStringValue());
        GetNextToken();
        return node;
    }
    else
    {
        ThrowParseError();
        return NULL;
    }
}

void GMParser::StateProductionContext(GMGrammar* grammar, GMProduction* production)
{
    GMNodeBase* node;
    while (m_CurToken.GetType() == kGMTokenTypeId || m_CurToken.GetType() == kGMTokenTypeStr)
    {
        if (m_CurToken.GetType() == kGMTokenTypeId)
        {
            node = grammar->GetGMNodeNT(m_CurToken.GetValue().GetStringValue());
        }
        else
        {
            node = grammar->GetGMNodeT(m_CurToken.GetValue().GetStringValue());
        }

        if (node == NULL)
        {
            ThrowParseError();
        }

        GetNextToken();
        production->AddNode(node);
    }
}

void GMParser::GetNextToken()
{
    m_CurToken = m_Lexer->GetNextToken();
}

void GMParser::ThrowParseError()
{
    m_IsError = true;

    stringstream ss;
    ss << "Parse error in: " << m_Text << " token: " << m_CurToken.GetTypeName() << " index: " << m_Lexer->CurIndex();
    m_ErrorMsg = ss.str();

    cerr << m_ErrorMsg;
}
