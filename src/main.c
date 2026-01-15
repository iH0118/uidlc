#include "ultk/ultk_canvas.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ultk/ultk_uidl_uib.h>

typedef uint8_t                           enum8_t;
typedef enum uidlc_return                 uidlc_return_t;
typedef struct uib_application_struct     uib_application_struct_t;
typedef struct uib_canvas_struct          uib_canvas_struct_t;
typedef struct uib_widget_struct          uib_widget_struct_t;
typedef struct uib_w_data_array_static    uib_w_data_array_static_t;
typedef struct uib_w_data_array_dynamic   uib_w_data_array_dynamic_t;
typedef struct uib_w_data_button          uib_w_data_button_t;
typedef struct uib_w_data_checkbox        uib_w_data_checkbox_t;
typedef struct uib_w_data_container       uib_w_data_container_t;
typedef struct uib_w_data_container_label uib_w_data_container_label_t;

enum uidlc_return {
    UIDLC_SUCCESS,
    UIDLC_ERROR,
    UIDLC_ERROR_ALLOCATION_FAILED,
    UIDLC_ERROR_MISSING_ELEMENT
};

struct uib_w_data_array_static {
    uint8_t num_rows;
    uint8_t num_cols;
    enum8_t alignment;
    _Bool scrollable_x;
    _Bool scrollable_y;
    uint16_t num_children;
    uib_widget_struct_t *children;
};

struct uib_w_data_array_dynamic {
    enum8_t alignment;
    _Bool keep_grid;
    enum8_t reflow_direction;
    uint8_t max_reflow_sections;
    uint16_t num_children;
    uib_widget_struct_t *children;
};

struct uib_w_data_button {
    uint16_t label_size;
    char *label;
    enum8_t label_align_x;
    enum8_t label_align_y;
    uint16_t size_min_x;
    uint16_t size_min_y;
    uint16_t size_max_x;
    uint16_t size_max_y;
    uint16_t callback_id_press_size;
    char *callback_id_press;
};

struct uib_w_data_checkbox {
    uint16_t label_size;
    char *label;
    _Bool checked;
    uint16_t callback_id_check_size;
    char *callback_id_check;
    uint16_t callback_id_uncheck_size;
    char *callback_id_uncheck;
};

struct uib_w_data_container {
    struct {
        float l;
        float r;
        float t;
        float b;
    } padding_relative;
    struct {
        uint16_t l;
        uint16_t r;
        uint16_t t;
        uint16_t b;
    } padding_absolute;
    uib_widget_struct_t *child;
};

struct uib_w_data_container_label {
    uint16_t label_size;
    char *label;
    enum8_t label_align;
    _Bool border;
    uib_widget_struct_t *child;
};

struct uib_widget_struct {
    uint32_t widget_size;
    enum8_t widget_type;
    uint16_t id_size;
    char *id;
    union {
        uib_w_data_array_static_t array_static;
        uib_w_data_array_dynamic_t array_dynamic;
        uib_w_data_button_t button;
        uib_w_data_checkbox_t checkbox;
        uib_w_data_container_t container;
        uib_w_data_container_label_t container_label;
    } data;
};

struct uib_canvas_struct {
    uint32_t canvas_size;
    enum8_t canvas_type;
    uint16_t id_size;
    char *id;
    uint16_t title_size;
    char *title;
    uint16_t size_x;
    uint16_t size_y;
    uib_widget_struct_t *w_top;
};

struct uib_application_struct {
    uint32_t application_size;
    uint16_t meta_name_size;
    char *meta_name;
    uint16_t meta_version_size;
    char *meta_version;
    uint16_t meta_id_size;
    char *meta_id;
    uint16_t meta_creator_size;
    char *meta_creator;
    uint16_t meta_copyright_size;
    char *meta_copyright;
    uint16_t meta_url_size;
    char *meta_url;
    uint16_t num_canvas;
    uib_canvas_struct_t *canvas;
};

const char *helpmsg = "uidlc - the uidl bytecode compiler\n"
    "usage:\nuidlc [-h] [-o <outfile>] <infile>\n";

void 
uidlc_syntax_error (
    char *token
)
{
    fprintf(stderr, "syntax error:\n---\n%.16s\n---\n", token);
    exit(1);
}


char *
uidl_parser_skip (
    char *token
)
{
    int wslen = strspn(token, " \f\n\r\t\v");

    if (token[wslen] == '#')
    {
        return uidl_parser_skip(strchr(token + wslen, '\n') + 1);
    }

    return token + wslen;
}

_Bool
uidl_conditional_advance (
    char **token,
    const char *target
)
{
    int target_len = strlen(target);

    if (!strncmp(*token, target, target_len))
    {
        *token = uidl_parser_skip(*token + target_len);
        return 1;
    }

    return 0;
}

inline _Bool
uidl_cond_adv_col (
    char **token,
    const char *target
)
{
    return uidl_conditional_advance(token, target) && 
        uidl_conditional_advance(token, ":");
}

uidlc_return_t
uidl_parse_bool (
    char **token,
    _Bool *target
)
{
    if (uidl_conditional_advance(token, "true"))
    {
        *target = 1;
        return UIDLC_SUCCESS;
    }

    if (uidl_conditional_advance(token, "false"))
    {
        *target = 0;
        return UIDLC_SUCCESS;
    }

    uidlc_syntax_error(*token);
    return UIDLC_ERROR;
}

uidlc_return_t
uidl_parse_int (
    char **token,
    int *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint8 (
    char **token,
    uint8_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_uint16 (
    char **token,
    uint16_t *target
)
{
    int len = strcspn(*token, " \f\n\r\t\v");
    char *buf = malloc(len + 1);

    if (!buf)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(buf, *token, len);
    buf[len] = '\0';

    *target = atoi(buf);

    free(buf);

    *token += len;

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_string (
    char **token,
    char **target,
    uint16_t *len
)
{
    if (!uidl_conditional_advance(token, "\""))
    {
        uidlc_syntax_error(*token);
    }

    *len = strcspn(*token, "\"");

    *target = malloc(*len + 1);
    if (!*target)
    {
        return UIDLC_ERROR_ALLOCATION_FAILED;
    }

    strncpy(*target, *token, *len);

    *token += *len;

    if (!uidl_conditional_advance(token, "\""))
    {
        uidlc_syntax_error(*token);
    }

    return UIDLC_SUCCESS;
}

uidlc_return_t
uidl_parse_w_array_static (
    char **token,
    uib_w_data_array_static_t *array_static
)
{
    //add stuff here
}

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
        status = uidl_parse_w_array_static(token, &widget->data.array_static);
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

int 
main (
    int argc,
    char **argv
)
{
    char *input_filename;
    char *output_filename = "out.uib";

    int c;

    while ((c = getopt (argc, argv, "ho:")) != -1) switch (c) 
    {
        case 'h':
        fputs(helpmsg, stderr);
        exit(0);
        break;

        case 'o':
        output_filename = optarg;
        break;

        case '?':
        fputs(helpmsg, stderr);
        exit(1);
        
        default:
        abort();
    }

    if (optind >= argc)
    {
        fputs("eror: missing input file\n", stderr);
        return 1;
    }

    input_filename = argv[optind++];

    if (optind < argc)
    {
        fputs("error: too many arguments\n", stderr);
        return 1;
    }

    FILE *infile = fopen(input_filename, "w");
    
    if (!infile)
    {
        fputs("error: input file not found", stderr);
        return 1;
    }







}