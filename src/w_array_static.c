#include "w_array_static.h"
#include "uib_structs.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"

uidlc_return_t
uidl_parse_w_array_static (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

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
            status = uidl_parse_string(token, &widget->id, &widget->id_size);
        }

        if (uidl_cond_adv_col(token, "num_rows"))
        {
            status = uidl_parse_uint8(token, &widget->data.array_static.num_rows);
        }

        if (uidl_cond_adv_col(token, "num_cols"))
        {
            status = uidl_parse_uint8(token, &widget->data.array_static.num_cols);
        }

        //add stuff here

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
