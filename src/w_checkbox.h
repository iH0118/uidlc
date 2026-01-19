#ifndef _UIDLC_W_CHECKBOX_H
#define _UIDLC_W_CHECKBOX_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_w_checkbox (
    char **token,
    uib_widget_struct_t *widget
);

uidlc_return_t
uib_output_w_checkbox (
    FILE *stream,
    uib_widget_struct_t *widget
);

#endif
