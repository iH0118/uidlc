#include <stdio.h>
#include <stdlib.h>
#include "uidlc.h"

void 
uidlc_syntax_error (
    char *token
)
{
    fprintf(stderr, "syntax error:\n---\n%.16s\n---\n", token);
    exit(1);
}
