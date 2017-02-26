#include <string>

class FaState
{
public:
    FaState(string name, int no);
    virtual ~FaState();

private:
    string  m_Name;
    int     m_No;
};