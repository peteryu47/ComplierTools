#include "gm_grammar.h"

#include <iostream>

GMGrammar::GMGrammar()
{

}

GMGrammar::~GMGrammar()
{
    for (int i = 0; i < m_NodeTs.size(); ++i)
    {
        delete m_NodeTs[i];
    }

    for (int i = 0; i < m_NodeNTs.size(); ++i)
    {
        delete m_NodeNTs[i];
    }

    for (int i = 0; i < m_Productions.size(); ++i)
    {
        delete m_Productions[i];
    }
}

GMNodeT* GMGrammar::GetGMNodeT(const string& name)
{
    for (int i = 0; i < m_NodeTs.size(); ++i)
    {
        if (m_NodeTs[i]->GetName().compare(name) == 0)
        {
            return m_NodeTs[i];
        }
    }

    GMNodeT* node = new GMNodeT(m_NodeTs.size() + 1, name);
    m_NodeTs.push_back(node);
    return node;
}

GMNodeNT* GMGrammar::GetGMNodeNT(const string& name)
{
    for (int i = 0; i < m_NodeNTs.size(); ++i)
    {
        if (m_NodeNTs[i]->GetName().compare(name) == 0)
        {
            return m_NodeNTs[i];
        }
    }

    GMNodeNT* node = new GMNodeNT(name);
    m_NodeNTs.push_back(node);
    return node;
}

GMProduction* GMGrammar::CreateProduction(GMNodeNT* nameNode)
{
    GMProduction* production = new GMProduction(m_Productions.size() + 1, nameNode);
    m_Productions.push_back(production);
    return production;
}

void GMGrammar::Dump()
{
    for (int i = 0; i < m_Productions.size(); ++i)
    {
        cout << m_Productions[i]->GetNameNode()->GetName() << ":";
        for (int j = 0; j < m_Productions[i]->GetNodes().size(); ++j)
        {
            cout << m_Productions[i]->GetNodes()[j]->GetName();
        }
        cout << endl;
    }
}
