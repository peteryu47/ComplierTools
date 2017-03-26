#ifndef __LL1_H__
#define __LL1_H__

#include "gm/gm_grammar.h"
#include "gm/gm_node.h"
#include "gm/gm_production.h"
#include <vector>
#include <map>
#include <set>
using namespace std;

class LL1
{
public:
    LL1(GMGrammar* grammer) : m_Grammer(grammer) {}
    ~LL1() {}

    void            EliminateLeftRecursion();
    void            EliminateIndirectRecursion();
    void            EliminateCommonPrefix();
    void            CalFirstSet();
    void            DumpFirstSet();
    void            CalFellowSet();
    void            DumpFellowSet();
    void            CalFirstPlusSet();
    void            DumpFirstPlusSet();

private:
    void            GetLeftRecursionProductions(GMNodeNT *nameNode, vector<GMProduction*>& leftRProductions, vector<GMProduction*>& nonLeftRProductions);
    void            GetProductionWithNameNodeAndStartNode(GMNodeNT* nameNode, GMNodeNT* startNode, vector<GMProduction*>& result);
    void            GetProductionWithNameNode(GMNodeNT* nameNode, vector<GMProduction*>& result);
    void            ReplaceProductionFirstNode(GMNodeNT* nameNode, GMNodeNT* startNode);
    void            GetFirstSetOfNodes(const vector<GMNodeBase*>& nodes, set<GMNodeBase*>& result);

private:
    GMGrammar*                              m_Grammer;
    map<GMNodeBase*, set<GMNodeBase*>>      m_FirstSetMap;
    map<GMNodeBase*, set<GMNodeBase*>>      m_FellowSetMap;
    map<GMProduction*, set<GMNodeBase*>>    m_FirstlusSetMap;
};

#endif