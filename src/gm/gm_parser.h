#ifndef __GM_PARSER_H__
#define __GM_PARSER_H__

#include <string>
#include "gm_token.h"
#include "gm_production.h"
#include "gm_grammar.h"
using namespace std;

class GMLexer;

class GMParser
{
public:
    GMParser();
    ~GMParser();

    GMGrammar*      Parse(const string& filePath);

private:
    void            StateG(GMGrammar* grammar);
    void            StateProductions(GMGrammar* grammar);
    void            StateProduction(GMGrammar* grammar);
    GMNodeNT*       StateProductionName(GMGrammar* grammar);
    void            StateProductionContext(GMGrammar* grammar, GMProduction* production);
    void            GetNextToken();
    void            ThrowParseError();

private:
    string      m_Text;
    GMLexer*    m_Lexer;
    GMToken     m_CurToken;
    bool        m_IsError;
    string      m_ErrorMsg;
};

#endif
