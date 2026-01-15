#ifndef _UIDLC_H
#define _UIDLC_H

#include <stdint.h>

typedef uint8_t                           enum8_t;
typedef enum uidlc_return                 uidlc_return_t;

enum uidlc_return {
    UIDLC_SUCCESS,
    UIDLC_ERROR,
    UIDLC_ERROR_ALLOCATION_FAILED,
    UIDLC_ERROR_MISSING_ELEMENT
};

void 
uidlc_syntax_error (
    char *token
);

#endif