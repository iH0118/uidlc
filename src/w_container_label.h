#ifndef _UIDLC_W_CONTAINER_LABEL_H
#define _UIDLC_W_CONTAINER_LABEL_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_w_container_label (
    char **token,
    uib_widget_struct_t *widget
);

uidlc_return_t
uib_output_w_container_label (
    FILE *stream,
    uib_widget_struct_t *widget
);

#endif
