#include "ll1.h"

#include <iostream>

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

            SetAdd(m_FirstSetMap[nameNode], m_FirstSetMap[nodes[0]]);
            SetRemove(m_FirstSetMap[nameNode], m_Grammer->GetNodeTEpsilon());

            flag = true;
            for (int j = 0; j < nodes.size(); ++j)
            {
                if (!SetContains(m_FirstSetMap[nodes[j]], m_Grammer->GetNodeTEpsilon()))
                {
                    flag = false;
                    break;
                }
            }

            if (flag == true)
            {
                SetAdd(m_FirstSetMap[nameNode], m_Grammer->GetNodeTEpsilon());
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

void LL1::CalFellowSet()
{

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
    const vector<GMProduction*>& productions = m_Grammer->GetProductions();
    result.clear();

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
    const vector<GMProduction*>& productions = m_Grammer->GetProductions();
    result.clear();

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

void LL1::SetAdd(set<GMNodeBase*>& src, set<GMNodeBase*>& add)
{
    for (set<GMNodeBase*>::iterator itr = add.begin(); itr != add.end(); ++itr)
    {
        if (src.find(*itr) == src.end())
        {
            src.insert(*itr);
        }
    }
}

void LL1::SetAdd(set<GMNodeBase*>& src, GMNodeBase* add)
{
    if (src.find(add) == src.end())
    {
        src.insert(add);
    }
}

void LL1::SetRemove(set<GMNodeBase*>& src, GMNodeBase* node)
{
    for (set<GMNodeBase*>::iterator itr = src.begin(); itr != src.end(); ++itr)
    {
        if (*itr == node)
        {
            src.erase(itr);
            return;
        }
    }
}

bool LL1::SetContains(set<GMNodeBase*>& src, GMNodeBase* node)
{
    return (src.find(node) != src.end());
}

void LL1::DumpFirstSet()
{
    for (map<GMNodeBase*, set<GMNodeBase*>>::iterator itr = m_FirstSetMap.begin(); itr != m_FirstSetMap.end(); ++itr)
    {
        cout << itr->first->GetName() << " : [";
        for (set<GMNodeBase*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
        {
            cout << (*itr1)->GetName() << ", ";
        }
        cout << "]" << endl;
    }
}

void LL1::DumpFellowSet()
{

}
