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

    const GMNodeBase*           GetNameNode() const { return m_NameNode; }
    void                        SetNameNode(GMNodeNT* nameNode) { m_NameNode = nameNode; }
    void                        AddNode(GMNodeBase* node) { m_Nodes.push_back(node); }
    void                        AddNodes(const vector<GMNodeBase*>& nodes) { for (int i = 0; i < nodes.size(); ++i) m_Nodes.push_back(nodes[i]); }
    const vector<GMNodeBase*>&  GetNodes() { return m_Nodes; }
    int                         GetNo() { return m_No; }
    void                        SetNo(int no) { m_No = no; }
    void                        CleanNodes() { m_Nodes.clear(); }

private:
    GMNodeNT*           m_NameNode;
    vector<GMNodeBase*> m_Nodes;
    int                 m_No;
};

#endif
