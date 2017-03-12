#include "com/var.h"
#include "com/file_data.h"
#include "gm/gm_lexer.h"
#include "gm/gm_parser.h"
#include "gm/gm_grammar.h"
#include "ll1/ll1.h"

#define CRTDBG_MAP_ALLOC    
#include <crtdbg.h> 

void main()
{
    //FileData fileData;
    //fileData.Load("test.gm");
    //string text = fileData.GetData();

    //GMLexer lexer(text);
    //GMToken token = lexer.GetNextToken();
    //while (token.GetType() != kGMTokenTypeEOF)
    //{
    //    token = lexer.GetNextToken();
    //}

    GMParser* parser = new GMParser();
    GMGrammar* grammer = parser->Parse("test.gm");
    LL1* ll1 = new LL1(grammer);
    grammer->Dump();

    ll1->EliminateLeftRecursion();
    grammer->Dump();

    ll1->EliminateIndirectRecursion();
    grammer->Dump();

    ll1->EliminateLeftRecursion();
    grammer->Dump();

    ll1->CalFirstSet();
    ll1->DumpFirstSet();

    delete grammer;
    delete parser;
    delete ll1;
    _CrtDumpMemoryLeaks();
}