#include <stdlib.h>
#include "w_container.h"
#include "uib_structs.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidl_widget.h"
#include "uidlc.h"

uidlc_return_t
uidl_parse_w_container (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    /* optional elements */
    widget->data.container.padding_relative.l = 0.0f;
    widget->data.container.padding_relative.r = 0.0f;
    widget->data.container.padding_relative.t = 0.0f;
    widget->data.container.padding_relative.b = 0.0f;
    widget->data.container.padding_absolute.l = 0;
    widget->data.container.padding_absolute.r = 0;
    widget->data.container.padding_absolute.t = 0;
    widget->data.container.padding_absolute.b = 0;

    if (!uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }

    if (uidl_conditional_advance(token, "}"))
    {
        uidlc_syntax_error(*token);
    }

    widget->data.container.child = malloc(sizeof(uib_widget_struct_t));

    if (!widget->data.container.child)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    while (1)
    {
        if (uidl_cond_adv_col(token, "id"))
        {
            status = uidl_parse_string(
                token,
                &widget->id,
                &widget->id_size
            );
        }

        if (uidl_cond_adv_col(token, "padding_relative_l"))
        {
            status = uidl_parse_float(
                token,
                &widget->data.container.padding_relative.l
            );
        }

        if (uidl_cond_adv_col(token, "padding_relative_r"))
        {
            status = uidl_parse_float(
                token,
                &widget->data.container.padding_relative.r
            );
        }

        if (uidl_cond_adv_col(token, "padding_relative_t"))
        {
            status = uidl_parse_float(
                token,
                &widget->data.container.padding_relative.t
            );
        }

        if (uidl_cond_adv_col(token, "padding_relative_b"))
        {
            status = uidl_parse_float(
                token,
                &widget->data.container.padding_relative.b
            );
        }

        if (uidl_cond_adv_col(token, "padding_absolute_l"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.container.padding_absolute.l
            );
        }

        if (uidl_cond_adv_col(token, "padding_absolute_r"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.container.padding_absolute.r
            );
        }

        if (uidl_cond_adv_col(token, "padding_absolute_t"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.container.padding_absolute.t
            );
        }

        if (uidl_cond_adv_col(token, "padding_absolute_b"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.container.padding_absolute.b
            );
        }

        if (uidl_cond_adv_col(token, "w_child"))
        {
            status = uidl_parse_widget(
                token, 
                widget->data.container.child
            );
        }

        if (status != UIDLC_SUCCESS)
        {
            return status;
        }

        if (uidl_conditional_advance(token, ","))
        {
            continue;
        }

        if (uidl_conditional_advance(token, "}"))
        {
            break;
        }

        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}