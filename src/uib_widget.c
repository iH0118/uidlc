#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "uib_widget.h"
#include "uib_scalars.h"
#include "w_array_dynamic.h"
#include "w_array_static.h"
#include "w_button.h"
#include "w_checkbox.h"
#include "w_container.h"
#include "w_container_label.h"

uidlc_return_t
uib_output_widget (
    FILE *stream,
    uib_widget_struct_t *widget
)
{
    if (uib_output_uint32(
            stream,
            widget->widget_size
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream, 
            widget->widget_type
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    if (widget->widget_type == ULTK_WIDGET_VOID)
    {
        return UIDLC_SUCCESS;
    }

    if (uib_output_uint16(
            stream, 
            widget->id_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream, 
            widget->id, 
            widget->id_size
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    switch (widget->widget_type)
    {
        case ULTK_WIDGET_ARRAY_STATIC:
        return uib_output_w_array_static(stream, widget);
        break;

        case ULTK_WIDGET_ARRAY_DYNAMIC:
        return uib_output_w_array_dynamic(stream, widget);
        break;

        case ULTK_WIDGET_BUTTON:
        return uib_output_w_button(stream, widget);
        break;

        case ULTK_WIDGET_CHECKBOX:
        return uib_output_w_checkbox(stream, widget);
        break;

        case ULTK_WIDGET_CONTAINER:
        return uib_output_w_container(stream, widget);
        break;

        case ULTK_WIDGET_CONTAINER_LABEL:
        return uib_output_w_container_label(stream, widget);
        break;

        //add more widget types here
    }

    return UIDLC_ERROR_OUTPUT_FAILED;
}

uidlc_return_t
uib_output_widget_array (
    FILE *stream,
    uib_widget_struct_t *widgets,
    uint16_t num_widgets
)
{
    for (int i = 0; i < num_widgets; i++)
    {
        if (uib_output_widget(stream, &widgets[i]) != UIDLC_SUCCESS)
        {
            return UIDLC_ERROR_OUTPUT_FAILED;
        }
    }

    free(widgets);

    return UIDLC_SUCCESS;
}
