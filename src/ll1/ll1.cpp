#include "ll1.h"

#include <iostream>
#include "com/set_utils.h"

void LL1::EliminateLeftRecursion()
{
    vector<GMNodeNT*> nodeNTs = m_Grammer->GetNodeNTs();
    vector<GMProduction*> leftRProductions;
    vector<GMProduction*> nonLeftRProductions;
    vector<GMNodeBase*> nodes;
    GMProduction* production;
    int maxPos = -2;

    //E->Ea1|Ea2|Ean|b1|b2|bm

    //1 E->b1E'|b2E'|bmE'
    //2 E'->a1E'|a2E'|anE'|e
    for (int i = 0; i < nodeNTs.size(); ++i)
    {
        GMNodeNT* nameNode = nodeNTs[i];
        GetLeftRecursionProductions(nodeNTs[i], leftRProductions, nonLeftRProductions);
        if (leftRProductions.size() == 0)
        {
            continue;
        }

        maxPos = -1;
        GMNodeNT* newNameNode = m_Grammer->CreateGMNodeNT(nameNode->GetName() + "_");
        
        // 1
        for (int j = 0; j < nonLeftRProductions.size(); ++j)
        {
            production = nonLeftRProductions[j];
            production->AddNode(newNameNode);
        }

        // 2
        for (int j = 0; j < leftRProductions.size(); ++j)
        {
            production = leftRProductions[j];
            nodes = production->GetNodes();
            production->CleanNodes();
            production->SetNameNode(newNameNode);

            for (int k = 1; k < nodes.size(); ++k)
            {
                production->AddNode(nodes[k]);
            }
            production->AddNode(newNameNode);

            if (production->GetNo() > maxPos)
            {
                maxPos = production->GetNo();
            }
        }

        // add epsilon
        GMProduction* nullProduction = m_Grammer->CreateProduction(newNameNode, maxPos + 1);
        nullProduction->AddNode(m_Grammer->GetNodeTEpsilon());
    }
}

void LL1::EliminateIndirectRecursion()
{
    vector<GMNodeNT*> nodeNTs = m_Grammer->GetNodeNTs();

    for (int i = 0; i < nodeNTs.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            ReplaceProductionFirstNode(nodeNTs[i], nodeNTs[j]);
        }
    }
}

void LL1::EliminateCommonPrefix()
{
    const vector<GMNodeNT*> ntNodes = m_Grammer->GetNodeNTs();
    vector<GMProduction*> productions;

    for (int i = 0; i < ntNodes.size(); ++i)
    {
        GetProductionWithNameNode(ntNodes[i], productions);
        for (int j = 0; j < productions.size(); ++j)
        {
            
        }
    }
}

void LL1::CalFirstSet()
{
    const vector<GMNodeNT*> ntNodes = m_Grammer->GetNodeNTs();
    const vector<GMNodeT*> tNodes = m_Grammer->GetNodeTs();
    const vector<GMProduction*> productions = m_Grammer->GetProductions();
    vector<GMNodeBase*> nodes;
    int curCount = 0;
    int tempCount = 0;
    GMNodeBase* nameNode;
    bool flag = false;

    // init
    for (int i = 0; i < ntNodes.size(); ++i)
    {
        m_FirstSetMap[ntNodes[i]] = set<GMNodeBase*>();
        ++curCount;
    }

    for (int i = 0; i < tNodes.size(); ++i)
    {
        m_FirstSetMap[tNodes[i]] = set<GMNodeBase*>();
        m_FirstSetMap[tNodes[i]].insert(tNodes[i]);
        ++curCount;
    }

    while (true)
    {
        for (int i = 0; i < productions.size(); ++i)
        {
            nodes = productions[i]->GetNodes();
            nameNode = const_cast<GMNodeBase*>(productions[i]->GetNameNode());

            SetAdd<GMNodeBase*>(m_FirstSetMap[nameNode], m_FirstSetMap[nodes[0]]);
            SetRemove<GMNodeBase*>(m_FirstSetMap[nameNode], m_Grammer->GetNodeTEpsilon());

            flag = true;
            for (int j = 0; j < nodes.size(); ++j)
            {
                if (!SetContains<GMNodeBase*>(m_FirstSetMap[nodes[j]], m_Grammer->GetNodeTEpsilon()))
                {
                    flag = false;
                    break;
                }
            }

            // all node has epsilon
            if (flag == true)
            {
                SetAdd<GMNodeBase*>(m_FirstSetMap[nameNode], m_Grammer->GetNodeTEpsilon());
            }
        }

        tempCount = 0;
        for (map<GMNodeBase*, set<GMNodeBase*>>::iterator itr = m_FirstSetMap.begin(); itr != m_FirstSetMap.end(); ++itr)
        {
            for (set<GMNodeBase*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
            {
                ++tempCount;
            }
        }

        if (curCount == tempCount)
        {
            break;
        }
        else
        {
            curCount = tempCount;
        }
    }
}

void LL1::DumpFirstSet()
{
    cout << "**********DumpFirstSet***********" << endl;
    for (map<GMNodeBase*, set<GMNodeBase*>>::iterator itr = m_FirstSetMap.begin(); itr != m_FirstSetMap.end(); ++itr)
    {
        cout << itr->first->GetName() << " : [";
        int count = 0;
        for (set<GMNodeBase*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
        {
            cout << (*itr1)->GetName();
            if (count != itr->second.size() - 1)
            {
                cout << ", ";
            }
            ++count;
        }
        cout << "]" << endl;
    }
}

void LL1::CalFellowSet()
{
    const vector<GMNodeNT*> ntNodes = m_Grammer->GetNodeNTs();
    const vector<GMNodeT*> tNodes = m_Grammer->GetNodeTs();
    const vector<GMProduction*> productions = m_Grammer->GetProductions();
    vector<GMNodeBase*> nodes;
    int curCount = 0;
    int tempCount = 0;
    GMNodeBase* nameNode;
    bool flag = false;
    GMNodeBase* nodeBeta;

    // init
    for (int i = 0; i < ntNodes.size(); ++i)
    {
        m_FellowSetMap[ntNodes[i]] = set<GMNodeBase*>();
        ++curCount;
    }

    for (int i = 0; i < tNodes.size(); ++i)
    {
        m_FellowSetMap[tNodes[i]] = set<GMNodeBase*>();
        ++curCount;
    }

    while (true)
    {
        for (int i = 0; i < productions.size(); ++i)
        {
            nodes = productions[i]->GetNodes();
            nameNode = const_cast<GMNodeBase*>(productions[i]->GetNameNode());
            set<GMNodeBase*> trailer = m_FellowSetMap[nameNode];

            for (int j = nodes.size() - 1; j >= 0; --j)
            {
                nodeBeta = nodes[j];
                if (nodeBeta->GetType() == kGMNodeTypeNT)
                {
                    SetAdd(m_FellowSetMap[nodeBeta], trailer);
                    if (SetContains<GMNodeBase*>(m_FirstSetMap[nodeBeta], m_Grammer->GetNodeTEpsilon()))
                    {
                        SetAdd(trailer, m_FirstSetMap[nodeBeta]);
                        SetRemove<GMNodeBase*>(trailer, m_Grammer->GetNodeTEpsilon());
                    }
                    else
                    {
                        trailer = m_FirstSetMap[nodeBeta];
                    }
                }
                else
                {
                    trailer = m_FirstSetMap[nodeBeta];
                }
            }
        }

        tempCount = 0;
        for (map<GMNodeBase*, set<GMNodeBase*>>::iterator itr = m_FellowSetMap.begin(); itr != m_FellowSetMap.end(); ++itr)
        {
            for (set<GMNodeBase*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
            {
                ++tempCount;
            }
        }

        if (curCount == tempCount)
        {
            break;
        }
        else
        {
            curCount = tempCount;
        }
    }
}

void LL1::DumpFellowSet()
{
    cout << "**********DumpFellowSet***********" << endl;
    for (map<GMNodeBase*, set<GMNodeBase*>>::iterator itr = m_FellowSetMap.begin(); itr != m_FellowSetMap.end(); ++itr)
    {
        cout << itr->first->GetName() << " : [";
        int count = 0;
        for (set<GMNodeBase*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
        {
            cout << (*itr1)->GetName();
            if (count != itr->second.size() - 1)
            {
                cout << ", ";
            }
            ++count;
        }
        cout << "]" << endl;
    }
}

void LL1::CalFirstPlusSet()
{
    const vector<GMProduction*> productions = m_Grammer->GetProductions();
    set<GMNodeBase*> firstSet;

    for (int i = 0; i < productions.size(); ++i)
    {
        m_FirstlusSetMap[productions[i]] = set<GMNodeBase*>();
    }

    for (int i = 0; i < productions.size(); ++i)
    {
        GetFirstSetOfNodes(productions[i]->GetNodes(), firstSet);
        if (!SetContains<GMNodeBase*>(firstSet, m_Grammer->GetNodeTEpsilon()))
        {
            m_FirstlusSetMap[productions[i]] = firstSet;
        }
        else
        {
            SetAdd(firstSet, m_FellowSetMap[const_cast<GMNodeBase*>(productions[i]->GetNameNode())]);
            m_FirstlusSetMap[productions[i]] = firstSet;
        }
    }
}

void LL1::DumpFirstPlusSet()
{
    const vector<GMProduction*> productions = m_Grammer->GetProductions();
    cout << "**********DumpFirstPlusSet***********" << endl;
    for (int i = 0; i < productions.size(); ++i)
    {
        GMProduction *production = productions[i];
        const vector<GMNodeBase*>& nodes = production->GetNodes();
        cout << production->GetNameNode()->GetName() << " : ";
        for (int j = 0; j < nodes.size(); ++j)
        {
            cout << nodes[j]->GetName() << " ";
        }
        cout << "\t\t: [";
        int count = 0;
        const set<GMNodeBase*>& nodeSet = m_FirstlusSetMap[production];
        for (set<GMNodeBase*>::iterator itr = nodeSet.begin(); itr != nodeSet.end(); ++itr)
        {
            cout << (*itr)->GetName();
            if (count != nodeSet.size() - 1)
            {
                cout << ", ";
            }
            ++count;
        }
        cout << "]" << endl;
    }
}

void LL1::GetLeftRecursionProductions(GMNodeNT *nameNode, vector<GMProduction*>& leftRProductions, vector<GMProduction*>& nonLeftRProductions)
{
    leftRProductions.clear();
    nonLeftRProductions.clear();

    const vector<GMProduction*>& productions = m_Grammer->GetProductions();

    for (int i = 0; i < productions.size(); ++i)
    {
        if (productions[i]->GetNameNode() == nameNode)
        {
            if (productions[i]->GetNodes().size() != 0 && productions[i]->GetNodes()[0] == nameNode)
            {
                leftRProductions.push_back(productions[i]);
            }
            else
            {
                nonLeftRProductions.push_back(productions[i]);
            }
        }
    }
}

void LL1::GetProductionWithNameNodeAndStartNode(GMNodeNT* nameNode, GMNodeNT* startNode, vector<GMProduction*>& result)
{
    result.clear();
    const vector<GMProduction*>& productions = m_Grammer->GetProductions();

    for (int i = 0; i < productions.size(); ++i)
    {
        if (productions[i]->GetNodes().size() == 0)
        {
            continue;
        }

        if (productions[i]->GetNameNode() == nameNode && productions[i]->GetNodes()[0] == startNode)
        {
            result.push_back(productions[i]);
        }
    }
}

void LL1::GetProductionWithNameNode(GMNodeNT* nameNode, vector<GMProduction*>& result)
{
    result.clear();
    const vector<GMProduction*>& productions = m_Grammer->GetProductions();

    for (int i = 0; i < productions.size(); ++i)
    {
        if (productions[i]->GetNameNode() == nameNode)
        {
            result.push_back(productions[i]);
        }
    }
}

void LL1::ReplaceProductionFirstNode(GMNodeNT* nameNode, GMNodeNT* startNode)
{
    vector<GMProduction*> productionsI;
    vector<GMProduction*> productionsJ;
    GMProduction* productionI;
    GMProduction* productionJ;
    vector<GMNodeBase*> nodes;

    GetProductionWithNameNodeAndStartNode(nameNode, startNode, productionsI);

    for (int i = 0; i < productionsI.size(); ++i)
    {
        productionI = productionsI[i];
        GetProductionWithNameNode(startNode, productionsJ);

        for (int j = 0; j < productionsJ.size(); ++j)
        {
            productionJ = productionsJ[j];
            nodes = productionI->GetNodes();
            productionI->CleanNodes();

            for (int k = 0; k < productionJ->GetNodes().size(); ++k)
            {
                productionI->AddNode(productionJ->GetNodes()[k]);
            }

            for (int k = 1; k < nodes.size(); ++k)
            {
                productionI->AddNode(nodes[k]);
            }
        }
    }
}

void LL1::GetFirstSetOfNodes(const vector<GMNodeBase*>& nodes, set<GMNodeBase*>& result)
{
    result.clear();

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->GetType() == kGMNodeTypeT)
        {
            SetAdd(result, m_FirstSetMap[nodes[i]]);
            break;
        }
        else
        {
            SetAdd(result, m_FirstSetMap[nodes[i]]);
        }
    }

    bool isAllHasEpsilon = true;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->GetType() == kGMNodeTypeT)
        {
            isAllHasEpsilon = false;
            break;
        }
        else
        {
            if (!SetContains<GMNodeBase*>(m_FirstSetMap[nodes[i]], m_Grammer->GetNodeTEpsilon()))
            {
                isAllHasEpsilon = false;
                break;
            }
        }
    }

    if (!isAllHasEpsilon)
    {
        SetRemove<GMNodeBase*>(result, m_Grammer->GetNodeTEpsilon());
    }
}
