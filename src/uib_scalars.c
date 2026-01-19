#include <stdlib.h>
#include "uib_scalars.h"

uidlc_return_t
uib_output_bool (
    FILE *stream,
    _Bool target
)
{
    if (fputc(target, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_uint8 (
    FILE *stream,
    uint8_t target
)
{
    if (fputc(target & 0x00FF, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_uint16 (
    FILE *stream,
    uint16_t target
)
{
    if (fputc(target & 0x00FF, stream) == EOF ||
        fputc(target >> 8 & 0x00FF, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_uint32 (
    FILE *stream,
    uint32_t target
)
{
    if (fputc(target & 0x00FF, stream) == EOF ||
        fputc(target >> 8 & 0x00FF, stream) == EOF ||
        fputc(target >> 16 & 0x00FF, stream) == EOF ||
        fputc(target >> 24 & 0x00FF, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_float (
    FILE *stream,
    float target
)
{
    union {
        float val_float;
        uint32_t val_uint;
    } target_bytes;

    target_bytes.val_float = target;

    if (fputc(target_bytes.val_uint & 0x00FF, stream) == EOF ||
        fputc(target_bytes.val_uint >> 8 & 0x00FF, stream) == EOF ||
        fputc(target_bytes.val_uint >> 16 & 0x00FF, stream) == EOF ||
        fputc(target_bytes.val_uint >> 24 & 0x00FF, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_string (
    FILE *stream,
    char *target,
    uint16_t len
)
{
    if (fwrite(target, sizeof(char), len, stream) != len)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }
    
    free(target);

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_enum8 (
    FILE *stream,
    enum8_t target
)
{
    if (fputc(target, stream) == EOF)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}
