#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "uidl_widget.h"
#include "uidl_parser.h"
#include "w_array_static.h"
#include "w_array_dynamic.h"
#include "w_button.h"
#include "w_checkbox.h"
#include "w_container.h"
#include "w_container_label.h"

uidlc_return_t
uidl_parse_widget (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    widget->widget_type = ULTK_WIDGET_NULL;
    widget->id_size = 0;
    widget->id = NULL;

    if (uidl_conditional_advance(token, "void"))
    {
        widget->widget_type = ULTK_WIDGET_VOID;
    }

    else if (uidl_conditional_advance(token, "array_static"))
    {
        widget->widget_type = ULTK_WIDGET_ARRAY_STATIC;
        status = uidl_parse_w_array_static(token, widget);
    }

    else if (uidl_conditional_advance(token, "array_dynamic"))
    {
        widget->widget_type = ULTK_WIDGET_ARRAY_DYNAMIC;
        status = uidl_parse_w_array_dynamic(token, widget);
    }

    else if (uidl_conditional_advance(token, "button"))
    {
        widget->widget_type = ULTK_WIDGET_BUTTON;
        status = uidl_parse_w_button(token, widget);
    }

    else if (uidl_conditional_advance(token, "checkbox"))
    {
        widget->widget_type = ULTK_WIDGET_CHECKBOX;
        status = uidl_parse_w_checkbox(token, widget);
    }

    else if (uidl_conditional_advance(token, "container"))
    {
        widget->widget_type = ULTK_WIDGET_CONTAINER;
        status = uidl_parse_w_container(token, widget);
    }

    else if (uidl_conditional_advance(token, "container_label"))
    {
        widget->widget_type = ULTK_WIDGET_CONTAINER_LABEL;
        status = uidl_parse_w_container_label(token, widget);
    }

    //add more widget types here

    else
    {
        uidlc_syntax_error(*token);
    }

    if (status != UIDLC_SUCCESS)
    {
        return status;
    }

    if (widget->widget_type == ULTK_WIDGET_NULL &&
        widget->id_size == 0 &&
        widget->id == NULL)
    {
        return UIDLC_ERROR_MISSING_ELEMENT;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_widget_array (
    char **token,
    uib_widget_struct_t **widgets,
    uint16_t *num_widgets
)
{
    uidlc_return_t status = UIDLC_ERROR;

    if (!uidl_conditional_advance(token, "["))
    {
        uidlc_syntax_error(*token);
    }

    if (uidl_conditional_advance(token, "]"))
    {
        uidlc_syntax_error(*token);
    }

    while (1)
    {
        *widgets = realloc(
            *widgets,
            ++*num_widgets * sizeof(uib_widget_struct_t)
        );

        if (!*widgets)
        {
            return UIDLC_ERROR_ALLOCATION_FAILED;
        }

        status = uidl_parse_widget(
            token,
            &(*widgets)[*num_widgets - 1]
        );

        if (status != UIDLC_SUCCESS)
        {
            return status;
        }

        if (uidl_conditional_advance(token, ","))
        {
            continue;
        }

        if (uidl_conditional_advance(token, "]"))
        {
            break;
        }

        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}
