#include "uib_application.h"
#include "uib_scalars.h"
#include "uib_canvas.h"

uidlc_return_t
uib_output_application_struct (
    FILE *stream,
    uib_application_struct_t *application
)
{
    if (uib_output_uint32(
            stream,
            application->application_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_name_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_name,
            application->meta_name_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_version_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_version,
            application->meta_version_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_id_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_id,
            application->meta_id_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_creator_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_creator,
            application->meta_creator_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_copyright_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_copyright,
            application->meta_copyright_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->meta_url_size
        ) != UIDLC_SUCCESS ||
        uib_output_string(
            stream,
            application->meta_url,
            application->meta_url_size
        ) != UIDLC_SUCCESS ||
        uib_output_uint16(
            stream,
            application->num_canvas
        ) != UIDLC_SUCCESS ||
        uib_output_canvas_array(
            stream,
            application
        ) != UIDLC_SUCCESS)
    {
        return UIDLC_ERROR_OUTPUT_FAILED;
    }

    return UIDLC_SUCCESS;
}
