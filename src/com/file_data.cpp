#include "file_data.h"

#include <fstream>
#include <iostream>
#include "utils.h"

FileData::FileData() :
    m_Data(NULL),
    m_DataLength(0)
{

}

FileData::~FileData()
{
    CleanData();
}

void FileData::Load(string& filePath)
{
    CleanData();

    ifstream in(filePath, std::ios::in);
    
    if (!in.is_open())
    { 
        cerr << "Error opening file" << filePath << endl;
        return;
    }

    in.seekg(0, ios::end);
    m_DataLength = (int)in.tellg();
    m_Data = new char[m_DataLength + 1];
    m_Data[m_DataLength] = '\0';
    in.seekg(0, ios::beg);

    in.read(m_Data, m_DataLength);
    in.close();
}

void FileData::CleanData()
{
    SAFE_DEL_ARRAY(m_Data);
}
