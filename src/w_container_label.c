#include <stdint.h>
#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "w_container_label.h"
#include "uib_scalars.h"
#include "uib_widget.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidl_widget.h"
#include "uidlc.h"

uidlc_return_t
uidl_parse_w_container_label (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    /* optional elements */
    widget->data.container_label.label_size = 0;
    widget->data.container_label.label = NULL;
    widget->data.container_label.label_align = ULTK_TEXT_ALIGN_HCENTER;
    widget->data.container_label.border = 0;
    
    if (!uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }
    
    if (uidl_conditional_advance(token, "}"))
    {
        uidlc_syntax_error(*token);
    }
    
    widget->data.container_label.child = malloc(sizeof(uib_widget_struct_t));

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

        if (uidl_cond_adv_col(token, "label"))
        {
            status = uidl_parse_string(
                token,
                &widget->data.container_label.label,
                &widget->data.container_label.label_size
            );
        }

        if (uidl_cond_adv_col(token, "label_align"))
        {
            status = uidl_parse_enum_text_alignment_x(
                token, 
                &widget->data.container_label.label_align
            );
        }

        if (uidl_cond_adv_col(token, "border"))
        {
            status = uidl_parse_bool(
                token, 
                &widget->data.container_label.border
            );
        }

        if (uidl_cond_adv_col(token, "w_child"))
        {
            status = uidl_parse_widget(
                token, 
                widget->data.container_label.child
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

    widget->widget_size += sizeof(uint16_t) + sizeof(enum8_t) + sizeof(_Bool) +
        widget->data.container_label.label_size +
        widget->data.container_label.child->widget_size;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_w_container_label (
    FILE *stream,
    uib_widget_struct_t *widget
)
{
    if (uib_output_uint16(
            stream,
            widget->data.container_label.label_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            widget->data.container_label.label,
            widget->data.container_label.label_size
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream, 
            widget->data.container_label.label_align
        ) != UIDLC_SUCCESS ||
        uib_output_bool(
            stream,
            widget->data.container_label.border
        ) != UIDLC_SUCCESS ||
        uib_output_widget(
            stream, 
            widget->data.container_label.child    
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}
