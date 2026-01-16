#include <stdlib.h>
#include <string.h>
#include <ultk/ultk_uidl_uib.h>
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
    }

    else if (uidl_conditional_advance(token, "false"))
    {
        *target = 0;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_int (
    char **token,
    int *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v,#}]");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token = uidl_parser_skip(*token + len);

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint8 (
    char **token,
    uint8_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v,#}]");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token = uidl_parser_skip(*token + len);

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint16 (
    char **token,
    uint16_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v,#}]");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token = uidl_parser_skip(*token + len);

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_float (
    char **token,
    float *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v,#}]");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atof(buf);

    free(buf);

    *token = uidl_parser_skip(*token + len);

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

uidlc_return_t
uidl_parse_enum_array_alignment (
    char **token,
    enum8_t *target
)
{
    if (uidl_conditional_advance(token, "left"))
    {
        *target = (enum8_t) ULTK_ARRAY_ALIGN_LEFT;
    }

    else if (uidl_conditional_advance(token, "center"))
    {
        *target = (enum8_t) ULTK_ARRAY_ALIGN_CENTER;
    }

    else if (uidl_conditional_advance(token, "right"))
    {
        *target = (enum8_t) ULTK_ARRAY_ALIGN_RIGHT;
    }

    else if (uidl_conditional_advance(token, "fill"))
    {
        *target = (enum8_t) ULTK_ARRAY_ALIGN_FILL;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_enum_reflow_direction (
    char **token,
    enum8_t *target
)
{
    if (uidl_conditional_advance(token, "horizontal"))
    {
        *target = (enum8_t) ULTK_REFLOW_HORIZONTAL;
    }

    else if (uidl_conditional_advance(token, "vertical"))
    {
        *target = (enum8_t) ULTK_REFLOW_VERTICAL;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_enum_text_alignment_x (
    char **token,
    enum8_t *target
)
{
    if (uidl_conditional_advance(token, "left"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_LEFT;
    }

    else if (uidl_conditional_advance(token, "center"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_HCENTER;
    }

    else if (uidl_conditional_advance(token, "right"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_RIGHT;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_enum_text_alignment_y (
    char **token,
    enum8_t *target
)
{
    if (uidl_conditional_advance(token, "top"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_TOP;
    }

    else if (uidl_conditional_advance(token, "center"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_VCENTER;
    }

    else if (uidl_conditional_advance(token, "bottom"))
    {
        *target = (enum8_t) ULTK_TEXT_ALIGN_BOTTOM;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}


