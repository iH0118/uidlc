#include <stdlib.h>
#include <string.h>
#include "uidl_scalars.h"
#include "uidl_parser.h"


uidlc_return_t
uidl_parse_bool (
    char **token,
    _Bool *target
)
{
    if (uidl_conditional_advance(token, "true"))
    {
        *target = 1;
        return UIDLC_SUCCESS;
    }

    if (uidl_conditional_advance(token, "false"))
    {
        *target = 0;
        return UIDLC_SUCCESS;
    }

    uidlc_syntax_error(*token);
    return UIDLC_ERROR;
}

uidlc_return_t
uidl_parse_int (
    char **token,
    int *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint8 (
    char **token,
    uint8_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint16 (
    char **token,
    uint16_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_string (
    char **token,
    char **target,
    uint16_t *len
)
{
    if (!uidl_conditional_advance(token, "\""))
    {
        uidlc_syntax_error(*token);
    }

    *len = strcspn(*token, "\"");

    *target = malloc(*len + 1);
    if (!*target)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(*target, *token, *len);

    *token += *len;

    if (!uidl_conditional_advance(token, "\""))
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}
