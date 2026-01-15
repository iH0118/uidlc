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
uidl_parse_string (
    char **token,
    char **target,
    uint16_t *len
);


#endif