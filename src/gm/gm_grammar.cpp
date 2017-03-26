#include "gm_grammar.h"

#include <iostream>
#include <algorithm>

GMGrammar::GMGrammar()
{
    m_NodeTs.push_back(new GMNodeT(0, ""));
    m_NodeTs.push_back(new GMNodeT(1, "EOF"));
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

GMNodeT* GMGrammar::CreateGMNodeT(const string& name)
{
    for (int i = 0; i < m_NodeTs.size(); ++i)
    {
        if (m_NodeTs[i]->GetName().compare(name) == 0)
        {
            return m_NodeTs[i];
        }
    }

    GMNodeT* node = new GMNodeT(m_NodeTs.size(), name);
    m_NodeTs.push_back(node);
    return node;
}

GMNodeNT* GMGrammar::CreateGMNodeNT(const string& name)
{
    for (int i = 0; i < m_NodeNTs.size(); ++i)
    {
        if (m_NodeNTs[i]->GetName().compare(name) == 0)
        {
            return m_NodeNTs[i];
        }
    }

    GMNodeNT* node = new GMNodeNT(m_NodeNTs.size(), name);
    m_NodeNTs.push_back(node);
    return node;
}

GMProduction* GMGrammar::CreateProduction(GMNodeNT* nameNode, int desirePos)
{
    if (desirePos < 0 || desirePos > m_Productions.size())
    {
        GMProduction* production = new GMProduction(m_Productions.size(), nameNode);
        m_Productions.push_back(production);
        return production;
    }
    else
    {
        GMProduction* production = new GMProduction(desirePos, nameNode);
        m_Productions.push_back(production);
        for (int i = m_Productions.size() - 2; i >= desirePos; --i)
        {
            m_Productions[i]->SetNo(m_Productions[i]->GetNo() + 1);
            m_Productions[i + 1] = m_Productions[i];
        }
        m_Productions[desirePos] = production;
        return production;
    }
}

void GMGrammar::Dump(const string& title)
{
    cout << "***************" << title << "**************" << endl;
    for (int i = 0; i < m_Productions.size(); ++i)
    {
        //const GMNodeNT 
        if (m_Productions[i]->GetNo() < 10)
        {
            cout << " ";
        }
        cout << m_Productions[i]->GetNo() << "    ";
        cout << m_Productions[i]->GetNameNode()->GetName() << " : ";
        for (int j = 0; j < m_Productions[i]->GetNodes().size(); ++j)
        {
            cout << m_Productions[i]->GetNodes()[j]->GetName() << " ";
        }
        cout << endl;
    }
}

void GMGrammar::DestoryProduction(GMProduction* production)
{
    vector<GMProduction*>::iterator itr = find(m_Productions.begin(), m_Productions.end(), production);
    if (itr != m_Productions.end())
    {
        m_Productions.erase(itr);
    }

    SAFE_DEL(production);
}

