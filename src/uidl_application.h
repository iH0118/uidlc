#ifndef _UIDLC_UIDL_APPLICATION_H
#define _UIDLC_UIDL_APPLICATION_H

#include "uidlc.h"
#include "uib_structs.h"

uidlc_return_t
uidl_parse_metadata (
    char **token,
    uib_application_struct_t *application
);

uidlc_return_t
uidl_parse_application_struct (
    char **token,
    uib_application_struct_t **application
);

#endif