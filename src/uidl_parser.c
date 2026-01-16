#include <ctype.h>
#include <string.h>
#include "uidl_parser.h"

char *
uidl_parser_skip (
    char *token
)
{
    size_t wslen = strspn(token, " \f\n\r\t\v");

    if (token[wslen] == '#')
    {
        return uidl_parser_skip(strchr(token + wslen, '\n') + 1);
    }

    return token + wslen;
}

_Bool
uidl_conditional_advance (
    char **token,
    const char *target
)
{
    size_t target_len = strlen(target);

    if (!strncmp(*token, target, target_len))
    {
        *token = uidl_parser_skip(*token + target_len);
        return 1;
    }

    return 0;
}

_Bool
uidl_cond_adv_col (
    char **token,
    const char *target
)
{
    return uidl_conditional_advance(token, target) && 
        uidl_conditional_advance(token, ":");
}
