#ifndef __GM_PARSER_H__
#define __GM_PARSER_H__

#include <string>
#include "gm_token.h"
using namespace std;

class GMLexer;

class GMParser
{
public:
    GMParser(const string& filePath);
    ~GMParser();

    void        StateG();
    void        StateProductions();
    void        StateProductionName();
    void        StateProductionContext();

private:
    string      m_Text;
    GMLexer*    m_Lexer;
    GMToken     m_CurToken;
};

#endif
