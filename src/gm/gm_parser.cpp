#include "gm_parser.h"

#include "com/utils.h"
#include "com/file_data.h"
#include "gm_lexer.h"

GMParser::GMParser(const string& filePath)
{
    FileData fileData;
    fileData.Load(filePath);

    m_Text = fileData.GetData();
    m_Lexer = new GMLexer(m_Text);
}

GMParser::~GMParser()
{
    SAFE_DEL(m_Lexer);
}

void GMParser::StateG()
{
    StateProductions();
}

void GMParser::StateProductions()
{

}

void GMParser::StateProductionName()
{

}

void GMParser::StateProductionContext()
{

}
