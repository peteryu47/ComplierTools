#include "com/var.h"
#include "gm/gm_lexer.h"
#include "gm/gm_parser.h"
#include "gm/gm_grammar.h"
#include "com/file_data.h"

void main()
{
    FileData fileData;
    fileData.Load("test.gm");
    string text = fileData.GetData();

    //GMLexer lexer(text);
    //GMToken token = lexer.GetNextToken();
    //while (token.GetType() != kGMTokenTypeEOF)
    //{
    //    token = lexer.GetNextToken();
    //}

    GMParser parser;

    GMGrammar* grammer = parser.Parse("test.gm");

    grammer->Dump();
}