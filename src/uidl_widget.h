#ifndef _UIDLC_UIDL_WIDGET_H
#define _UIDLC_UIDL_WIDGET_H

#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_widget (
    char **token,
    uib_widget_struct_t *widget
);

uidlc_return_t
uidl_parse_widget_array (
    char **token,
    uib_widget_struct_t **widgets,
    uint16_t *num_widgets
);

#endif