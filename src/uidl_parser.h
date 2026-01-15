#ifndef _UIDLC_UIDL_PARSER_H
#define _UIDLC_UIDL_PARSER_H

char *
uidl_parser_skip (
    char *token
);

_Bool
uidl_conditional_advance (
    char **token,
    const char *target
);

_Bool
uidl_cond_adv_col (
    char **token,
    const char *target
);


#endif