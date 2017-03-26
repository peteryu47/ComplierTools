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
    GMGrammar* grammer = parser->Parse("test3.gm");
    LL1* ll1 = new LL1(grammer);
    grammer->Dump("Init");

    ll1->EliminateLeftRecursion();
    grammer->Dump("EliminateLeftRecursion");

    ll1->EliminateIndirectRecursion();
    grammer->Dump("EliminateIndirectRecursion");

    ll1->EliminateLeftRecursion();
    grammer->Dump("EliminateLeftRecursion");

    ll1->CalFirstSet();
    ll1->DumpFirstSet();

    ll1->CalFellowSet();
    ll1->DumpFellowSet();

    ll1->CalFirstPlusSet();
    ll1->DumpFirstPlusSet();

    delete grammer;
    delete parser;
    delete ll1;
    _CrtDumpMemoryLeaks();
}