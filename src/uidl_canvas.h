#ifndef _UIDLC_UIDL_CANVAS_H
#define _UIDLC_UIDL_CANVAS_H

#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_canvas (
    char **token,
    uib_canvas_struct_t *canvas
);

uidlc_return_t
uidl_parse_canvas_array (
    char **token,
    uib_application_struct_t *application
);

#endif