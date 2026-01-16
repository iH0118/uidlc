#ifndef _UIDLC_UIDL_SCALARS_H
#define _UIDLC_UIDL_SCALARS_H

#include "uidlc.h"

uidlc_return_t
uidl_parse_bool (
    char **token,
    _Bool *target
);

uidlc_return_t
uidl_parse_int (
    char **token,
    int *target
);

uidlc_return_t
uidl_parse_uint8 (
    char **token,
    uint8_t *target
);

uidlc_return_t
uidl_parse_uint16 (
    char **token,
    uint16_t *target
);

uidlc_return_t
uidl_parse_float (
    char **token,
    float *target
);

uidlc_return_t
uidl_parse_string (
    char **token,
    char **target,
    uint16_t *len
);

uidlc_return_t
uidl_parse_enum_array_alignment (
    char **token,
    enum8_t *target
);

uidlc_return_t
uidl_parse_enum_reflow_direction (
    char **token,
    enum8_t *target
);

uidlc_return_t
uidl_parse_enum_text_alignment_x (
    char **token,
    enum8_t *target
);

uidlc_return_t
uidl_parse_enum_text_alignment_y (
    char **token,
    enum8_t *target
);

#endif