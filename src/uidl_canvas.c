#include <stdlib.h>
#include <ultk/ultk_uidl_uib.h>
#include "uidl_canvas.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidl_widget.h"


uidlc_return_t
uidl_parse_canvas (
    char **token,
    uib_canvas_struct_t *canvas
)
{
    uidlc_return_t status = UIDLC_ERROR;

    canvas->canvas_type = ULTK_CANVAS_NULL;
    canvas->id_size = 0;
    canvas->id = NULL;
    canvas->title_size = 0;
    canvas->title = NULL;
    canvas->size_x = 0;
    canvas->size_y = 0;
    canvas->w_top = NULL;

    if (uidl_conditional_advance(token, "application"))
    {
        canvas->canvas_type = ULTK_CANVAS_APPLICATION;
    }

    else if (uidl_conditional_advance(token, "utility"))
    {
        canvas->canvas_type = ULTK_CANVAS_UTILITY;
    }

    else if (uidl_conditional_advance(token, "popup"))
    {
        canvas->canvas_type = ULTK_CANVAS_POPUP_MENU;
    }

    else if (uidl_conditional_advance(token, "tooltip"))
    {
        canvas->canvas_type = ULTK_CANVAS_TOOLTIP;
    }

    else
    {
        uidlc_syntax_error(*token);
    }

    if (!uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }

    while (1)
    {
        if (uidl_cond_adv_col(token, "id"))
        {
            status = uidl_parse_string(
                token,
                &canvas->id,
                &canvas->id_size
            );
        }

        if (uidl_cond_adv_col(token, "title"))
        {
            status = uidl_parse_string(
                token,
                &canvas->title,
                &canvas->title_size
            );
        }

        if (uidl_cond_adv_col(token, "size_x"))
        {
            status = uidl_parse_uint16(token, &canvas->size_x);
        }

        if (uidl_cond_adv_col(token, "size_y"))
        {
            status = uidl_parse_uint16(token, &canvas->size_y);
        }

        if (uidl_cond_adv_col(token, "w_top"))
        {
            canvas->w_top = malloc(sizeof(uib_widget_struct_t));

            if (!canvas->w_top)
            {
                return UIDLC_ERROR_ALLOCATION_FAILED;
            }

            status = uidl_parse_widget(token, canvas->w_top);
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

    if (canvas->canvas_type == ULTK_CANVAS_NULL ||
        canvas->id_size == 0 ||
        canvas->id == NULL ||
        canvas->w_top == NULL)
    {
        return UIDLC_ERROR_MISSING_ELEMENT;
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_canvas_array (
    char **token,
    uib_application_struct_t *application
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
        application->canvas = realloc(
            application->canvas,
            ++application->num_canvas * sizeof(uib_canvas_struct_t)
        );

        if (!application->canvas)
        {
            return UIDLC_ERROR_ALLOCATION_FAILED;
        }

        status = uidl_parse_canvas(
            token,
            &application->canvas[application->num_canvas - 1]
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