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

    GMNodeT*        CreateGMNodeT(const string& name);
    GMNodeNT*       CreateGMNodeNT(const string& name);
    GMProduction*   CreateProduction(GMNodeNT* nameNode, int desirePos = -1);
    void            Dump(const string& title);

    const vector<GMNodeT*>&         GetNodeTs() { return m_NodeTs; }
    const vector<GMNodeNT*>&        GetNodeNTs() { return m_NodeNTs; }
    GMNodeT*                        GetNodeTEpsilon() { return m_NodeTs[0]; };
    GMNodeT*                        GetNodeTEOF() { return m_NodeTs[1]; };
    const vector<GMProduction*>&    GetProductions() { return m_Productions; }

    void                            DestoryProduction(GMProduction* production);

private:
    vector<GMNodeT*>        m_NodeTs;
    vector<GMNodeNT*>       m_NodeNTs;
    vector<GMProduction*>   m_Productions;
};

#endif
