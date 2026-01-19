#ifndef _UIDLC_UIB_SCALARS_H
#define _UIDLC_UIB_SCALARS_H

#include <stdint.h>
#include <stdio.h>
#include "uidlc.h"

uidlc_return_t
uib_output_bool (
    FILE *stream,
    _Bool target
);

uidlc_return_t
uib_output_uint8 (
    FILE *stream,
    uint8_t target
);

uidlc_return_t
uib_output_uint16 (
    FILE *stream,
    uint16_t target
);

uidlc_return_t
uib_output_uint32 (
    FILE *stream,
    uint32_t target
);

uidlc_return_t
uib_output_float (
    FILE *stream,
    float target
);

uidlc_return_t
uib_output_string (
    FILE *stream,
    char *target,
    uint16_t len
);

uidlc_return_t
uib_output_enum8 (
    FILE *stream,
    enum8_t target
);

#endif
