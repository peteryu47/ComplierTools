#ifndef __FILE_DATA_H__
#define __FILE_DATA_H__

#include <string>
using namespace std;

class FileData
{
public:
    FileData();
    ~FileData();

    void    Load(string& filePath);
    char*   GetData() { return m_Data; }
    int     GetDataLength() { return m_DataLength; }

private:
    void    CleanData();

private:
    char*   m_Data;
    int     m_DataLength;
};

#endif