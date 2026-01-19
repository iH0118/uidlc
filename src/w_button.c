#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "w_button.h"
#include "uib_scalars.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidlc.h"

uidlc_return_t
uidl_parse_w_button (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    /* optional elements */
    widget->data.button.label_size = 0;
    widget->data.button.label = NULL;
    widget->data.button.label_align_x = ULTK_TEXT_ALIGN_HCENTER;
    widget->data.button.label_align_y = ULTK_TEXT_ALIGN_VCENTER;
    widget->data.button.size_min_x = 0;
    widget->data.button.size_min_y = 0;
    widget->data.button.size_max_x = 0;
    widget->data.button.size_max_y = 0;
    widget->data.button.callback_id_press_size = 0;
    widget->data.button.callback_id_press = NULL;

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

        if (uidl_cond_adv_col(token, "label"))
        {
            status = uidl_parse_string(
                token,
                &widget->data.button.label,
                &widget->data.button.label_size
            );
        }

        if (uidl_cond_adv_col(token, "label_align_x"))
        {
            status = uidl_parse_enum_text_alignment_x(
                token,
                &widget->data.button.label_align_x
            );
        }

        if (uidl_cond_adv_col(token, "label_align_y"))
        {
            status = uidl_parse_enum_text_alignment_y(
                token,
                &widget->data.button.label_align_y
            );
        }

        if (uidl_cond_adv_col(token, "size_min_x"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.button.size_min_x
            );
        }

        if (uidl_cond_adv_col(token, "size_min_y"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.button.size_min_y
            );
        }

        if (uidl_cond_adv_col(token, "size_max_x"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.button.size_max_x
            );
        }

        if (uidl_cond_adv_col(token, "size_max_y"))
        {
            status = uidl_parse_uint16(
                token,
                &widget->data.button.size_max_y
            );
        }

        if (uidl_cond_adv_col(token, "callback_id_press"))
        {
            status = uidl_parse_string(
                token,
                &widget->data.button.callback_id_press,
                &widget->data.button.callback_id_press_size
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

    widget->widget_size += 6 * sizeof(uint16_t) + 2 * sizeof(enum8_t) +
        widget->data.button.label_size +
        widget->data.button.callback_id_press_size;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_w_button (
    FILE *stream,
    uib_widget_struct_t *widget
)
{
    if (uib_output_uint16(
            stream,
            widget->data.button.label_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            widget->data.button.label,
            widget->data.button.label_size
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream, 
            widget->data.button.label_align_x
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream, 
            widget->data.button.label_align_y
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            widget->data.button.size_min_x
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            widget->data.button.size_min_y
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            widget->data.button.size_max_x
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            widget->data.button.size_max_y
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            widget->data.button.callback_id_press_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            widget->data.button.callback_id_press,
            widget->data.button.callback_id_press_size
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}
