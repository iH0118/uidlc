#ifndef _UIDLC_UIB_WIDGET_H
#define _UIDLC_UIB_WIDGET_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uib_output_widget (
    FILE *stream,
    uib_widget_struct_t *widget
);

uidlc_return_t
uib_output_widget_array (
    FILE *stream,
    uib_widget_struct_t *widgets,
    uint16_t num_widgets
);

#endif