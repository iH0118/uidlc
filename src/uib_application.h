#ifndef _UIDLC_UIB_APPLICATION_H
#define _UIDLC_UIB_APPLICATION_H

#include <stdio.h>
#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uib_output_application_struct (
    FILE *stream,
    uib_application_struct_t *application
);

#endif
