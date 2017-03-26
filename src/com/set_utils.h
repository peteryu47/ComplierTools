#ifndef __SET_UTILS_H__
#define __SET_UTILS_H__

#include <set>
using namespace std;

template <typename T>
void    SetAdd(set<T>& src, T node)
{
    if (src.find(node) == src.end())
    {
        src.insert(node);
    }
}

template <typename T>
void    SetAdd(set<T>& src, set<T>& nodes)
{
    for (set<T>::iterator itr = nodes.begin(); itr != nodes.end(); ++itr)
    {
        if (src.find(*itr) == src.end())
        {
            src.insert(*itr);
        }
    }
}

template <typename T>
void    SetRemove(set<T>& src, T node)
{
    set<T>::iterator itr = src.find(node);
    if (itr != src.end())
    {
        src.erase(itr);
    }
}

template <typename T>
void    SetRemove(set<T> &src, set<T>& nodes)
{
    for (set<T>::iterator itr = nodes.begin(); itr != nodes.end(); ++itr)
    {
        if (*itr == node)
        {
            src.erase(itr);
            return;
        }
    }
}

template <typename T>
bool    SetContains(set<T>& src, T node)
{
    return (src.find(node) != src.end());
}

#endif