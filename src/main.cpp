#include "com/var.h"
#include "gm/gm_lexer.h"

void main()
{
    GMLexer lexer("test.gm");

    GMToken token = lexer.GetNextToken();

    while (token.GetType() != kGMTokenTypeEOF)
    {
        token = lexer.GetNextToken();
    }
}