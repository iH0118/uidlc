#include <stdlib.h>
#include "uib_canvas.h"
#include "uib_scalars.h"
#include "uib_widget.h"

uidlc_return_t
uib_output_canvas (
    FILE *stream,
    uib_canvas_struct_t *canvas
)
{
    if (uib_output_uint32(
            stream, 
            canvas->canvas_size
        ) != UIDLC_SUCCESS ||
        uib_output_enum8(
            stream, 
            canvas->canvas_type
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            canvas->id_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream, 
            canvas->id, 
            canvas->id_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            canvas->title_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream, 
            canvas->title, 
            canvas->title_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            canvas->size_x
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream, 
            canvas->size_y
        ) != UIDLC_SUCCESS ||
        uib_output_widget(
            stream,
            canvas->w_top
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }



    return UIDLC_SUCCESS;
}

uidlc_return_t
uib_output_canvas_array (
    FILE *stream,
    uib_application_struct_t *application
)
{
    for (int i = 0; i < application->num_canvas; i++)
    {
        if (uib_output_canvas(stream, &application->canvas[i]) != UIDLC_SUCCESS)
        {
            return UIDLC_ERROR_OUTPUT_FAILED;
        }
    }

    free(application->canvas);

    return UIDLC_SUCCESS;
}
