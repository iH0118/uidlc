#include <stdint.h>
#include <stdlib.h>
#include "w_container.h"
#include "uib_scalars.h"
#include "uib_structs.h"
#include "uib_widget.h"
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

    widget->widget_size += 4 * sizeof(float) + 4 * sizeof(uint16_t) +
        widget->data.container.child->widget_size;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_w_container (
    FILE *stream,
    uib_widget_struct_t *widget
)
{
    if (uib_output_float(
        stream, 
        widget->data.container.padding_relative.l
    ) != UIDLC_SUCCESS ||
    uib_output_float(
        stream, 
        widget->data.container.padding_relative.r
    ) != UIDLC_SUCCESS ||
    uib_output_float(
        stream, 
        widget->data.container.padding_relative.t
    ) != UIDLC_SUCCESS ||
    uib_output_float(
        stream, 
        widget->data.container.padding_relative.b
    ) != UIDLC_SUCCESS ||
    uib_output_uint16(
        stream, 
        widget->data.container.padding_absolute.l
    ) != UIDLC_SUCCESS ||
    uib_output_uint16(
        stream, 
        widget->data.container.padding_absolute.r
    ) != UIDLC_SUCCESS ||
    uib_output_uint16(
        stream, 
        widget->data.container.padding_absolute.t
    ) != UIDLC_SUCCESS ||
    uib_output_uint16(
        stream, 
        widget->data.container.padding_absolute.b
    ) != UIDLC_SUCCESS ||
    uib_output_widget(
        stream, 
        widget->data.container.child
    ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    free(widget->data.container.child);

    return UIDLC_SUCCESS;
}
