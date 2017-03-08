#ifndef __GM_PRODUCTION_H__
#define __GM_PRODUCTION_H__

#include <vector>
#include "gm_node.h"
#include "com/utils.h"
using namespace std;

class GMProduction
{
public:
    GMProduction(int no, GMNodeNT* nameNode) : m_NameNode(nameNode), m_No(no) {}
    ~GMProduction() {}

    GMNodeBase*                 GetNameNode() { return m_NameNode; }
    void                        AddNode(GMNodeBase* node) { m_Nodes.push_back(node); }
    const vector<GMNodeBase*>&  GetNodes() { return m_Nodes; }

private:
    GMNodeNT*           m_NameNode;
    vector<GMNodeBase*> m_Nodes;
    int                 m_No;
};

#endif
