#include <stdlib.h>
#include "uidl_application.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidl_canvas.h"

uidlc_return_t
uidl_parse_metadata (
    char **token,
    uib_application_struct_t *application
)
{
    uidlc_return_t status;
    
    if (!uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }
    
    while (1)
    {
        if (uidl_cond_adv_col(token, "name"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_name,
                &application->meta_name_size
            );
        }

        if (uidl_cond_adv_col(token, "version"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_version,
                &application->meta_version_size
            );
        }

        if (uidl_cond_adv_col(token, "id"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_id,
                &application->meta_id_size
            );
        }

        if (uidl_cond_adv_col(token, "creator"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_creator,
                &application->meta_creator_size
            );
        }

        if (uidl_cond_adv_col(token, "copyright"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_copyright,
                &application->meta_copyright_size
            );
        }

        if (uidl_cond_adv_col(token, "url"))
        {
            status = uidl_parse_string(
                token,
                &application->meta_url,
                &application->meta_url_size
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

uidlc_return_t
uidl_parse_application_struct (
    char **token,
    uib_application_struct_t **application
)
{
    uidlc_return_t status = UIDLC_ERROR;

    *application = calloc(1, sizeof(uib_application_struct_t));
    if (!*application) 
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    if (!uidl_cond_adv_col(token, "application") || 
        !uidl_conditional_advance(token, "{"))
    {
        uidlc_syntax_error(*token);
    }

    while (1)
    {
        if (uidl_cond_adv_col(token, "metadata"))
        {
            status = uidl_parse_metadata(token, *application);
        }

        if (uidl_cond_adv_col(token, "canvas"))
        {
            status = uidl_parse_canvas_array(token, *application);
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
