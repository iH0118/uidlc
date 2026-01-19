#include <stdint.h>
#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "w_array_static.h"
#include "uib_scalars.h"
#include "uib_structs.h"
#include "uib_widget.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidl_widget.h"
#include "uidlc.h"

uidlc_return_t
uidl_parse_w_array_static (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    /* required elements */
    widget->data.array_static.num_rows = 0;
    widget->data.array_static.num_cols = 0;
    widget->data.array_static.num_children = 0;
    widget->data.array_static.children = NULL;

    /* optional elements */
    widget->data.array_static.alignment = ULTK_ARRAY_ALIGN_FILL;
    widget->data.array_static.scrollable_x = 1;
    widget->data.array_static.scrollable_y = 1;

    if (!uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }

    if (uidl_conditional_advance(token, "}"))
    {
        uidlc_syntax_error(*token);
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

        if (uidl_cond_adv_col(token, "num_rows"))
        {
            status = uidl_parse_uint8(
                token,
                &widget->data.array_static.num_rows
            );
        }

        if (uidl_cond_adv_col(token, "num_cols"))
        {
            status = uidl_parse_uint8(
                token,
                &widget->data.array_static.num_cols
            );
        }

        if (uidl_cond_adv_col(token, "alignment"))
        {
            status = uidl_parse_enum_array_alignment(
                token,
                &widget->data.array_static.alignment
            );
        }

        if (uidl_cond_adv_col(token, "scrollable_x"))
        {
            status = uidl_parse_bool(
                token,
                &widget->data.array_static.scrollable_x
            );
        }

        if (uidl_cond_adv_col(token, "scrollable_y"))
        {
            status = uidl_parse_bool(
                token,
                &widget->data.array_static.scrollable_y
            );
        }

        if (uidl_cond_adv_col(token, "w_children"))
        {
            status = uidl_parse_widget_array(
                token,
                &widget->data.array_static.children,
                &widget->data.array_static.num_children
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

    if (widget->data.array_static.num_rows == 0 ||
        widget->data.array_static.num_cols == 0 ||
        widget->data.array_static.num_children == 0 ||
        widget->data.array_static.children == NULL)
    {
        return UIDLC_ERROR_MISSING_ELEMENT;
    }

    widget->widget_size += 2 * sizeof(uint8_t) + sizeof(enum8_t) +
        2 * sizeof(_Bool) + sizeof(uint16_t);

    for (int i = 0; i < widget->data.array_static.num_children; i++)
    {
        widget->widget_size +=
            widget->data.array_static.children[i].widget_size;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_w_array_static (
    FILE *stream,
    uib_widget_struct_t *widget
)
{
    if (uib_output_uint8(
            stream,
            widget->data.array_static.num_rows
        ) != UIDLC_SUCCESS ||
        uib_output_uint8(
            stream,
            widget->data.array_static.num_cols
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream,
            widget->data.array_static.alignment
        ) != UIDLC_SUCCESS ||
        uib_output_bool(
            stream,
            widget->data.array_static.scrollable_x
        ) != UIDLC_SUCCESS ||
        uib_output_bool(
            stream,
            widget->data.array_static.scrollable_y
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            widget->data.array_static.num_children
        ) != UIDLC_SUCCESS ||
        uib_output_widget_array(
            stream,
            widget->data.array_static.children,
            widget->data.array_static.num_children
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}
