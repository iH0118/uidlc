#ifndef _UIDLC_UIB_CANVAS_H
#define _UIDLC_UIB_CANVAS_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uib_output_canvas (
    FILE *stream,
    uib_canvas_struct_t *canvas
);

uidlc_return_t
uib_output_canvas_array (
    FILE *stream,
    uib_application_struct_t *application
);

#endif