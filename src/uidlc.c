#include <stdio.h>
#include <stdlib.h>
#include "uidlc.h"

void 
uidlc_syntax_error (
    char *token
)
{
    fprintf(stderr, "syntax error:\n---\n%.40s\n---\n", token);
    exit(1);
}

void
uidlc_report_status (
    uidlc_return_t status
)
{
    switch (status)
    {
        case UIDLC_SUCCESS:
        break;

        case UIDLC_ERROR:
        fputs("error: UIDLC_ERROR\n", stderr);
        exit(1);
        break;

        case UIDLC_ERROR_ALLOCATION_FAILED:
        fputs("error: UIDLC_ERROR_ALLOCATION_FAILED\n", stderr);
        exit(1);
        break;

        case UIDLC_ERROR_MISSING_ELEMENT:
        fputs("error: UIDLC_ERROR_MISSING_ELEMENT\n", stderr);
        exit(1);
        break;

        case UIDLC_ERROR_OUTPUT_FAILED:
        fputs("error: UIDLC_ERROR_OUTPUT_FAILED\n", stderr);
        exit(1);
        break;
    }
}