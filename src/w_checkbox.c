#include <stdlib.h>
#include "w_checkbox.h"
#include "uidl_parser.h"
#include "uidl_scalars.h"
#include "uidlc.h"

uidlc_return_t
uidl_parse_w_checkbox (
    char **token,
    uib_widget_struct_t *widget
)
{
    uidlc_return_t status = UIDLC_ERROR;

    /* optional elements */
    widget->data.checkbox.label_size = 0;
    widget->data.checkbox.label = NULL;
    widget->data.checkbox.checked = 0;
    widget->data.checkbox.callback_id_check_size = 0;
    widget->data.checkbox.callback_id_check = NULL;
    widget->data.checkbox.callback_id_uncheck_size = 0;
    widget->data.checkbox.callback_id_uncheck = NULL;

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
                &widget->data.checkbox.label,
                &widget->data.checkbox.label_size
            );
        }

        if (uidl_cond_adv_col(token, "checked"))
        {
            status = uidl_parse_bool(
                token, 
                &widget->data.checkbox.checked
            );
        }
        
        if (uidl_cond_adv_col(token, "callback_id_check"))
        {
            status = uidl_parse_string(
                token, 
                &widget->data.checkbox.callback_id_check, 
                &widget->data.checkbox.callback_id_check_size
            );
        }
        
        if (uidl_cond_adv_col(token, "callback_id_uncheck"))
        {
            status = uidl_parse_string(
                token, 
                &widget->data.checkbox.callback_id_uncheck, 
                &widget->data.checkbox.callback_id_uncheck_size
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