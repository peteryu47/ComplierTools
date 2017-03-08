#ifndef __GM_GRAMMAR_H__
#define __GM_GRAMMAR_H__

#include <vector>
#include "gm_node.h"
#include "gm_production.h"
using namespace std;

class GMGrammar
{
public:
    GMGrammar();
    ~GMGrammar();

    GMNodeT*        GetGMNodeT(const string& name);
    GMNodeNT*       GetGMNodeNT(const string& name);
    GMProduction*   CreateProduction(GMNodeNT* nameNode);
    void            Dump();

private:
    vector<GMNodeT*>        m_NodeTs;
    vector<GMNodeNT*>       m_NodeNTs;
    vector<GMProduction*>   m_Productions;
};

#endif
