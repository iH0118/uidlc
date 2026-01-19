#ifndef _UIDLC_W_ARRAY_DYNAMIC_H
#define _UIDLC_W_ARRAY_DYNAMIC_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_w_array_dynamic (
    char **token,
    uib_widget_struct_t *widget
);

uidlc_return_t
uib_output_w_array_dynamic (
    FILE *stream,
    uib_widget_struct_t *widget
);

#endif