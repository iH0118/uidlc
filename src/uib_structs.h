#ifndef _UIDLC_UIB_STRUCTS_H
#define _UIDLC_UIB_STRUCTS_H

#include <stdint.h>
#include "uidlc.h"

typedef struct uib_application_struct     uib_application_struct_t;
typedef struct uib_canvas_struct          uib_canvas_struct_t;
typedef struct uib_widget_struct          uib_widget_struct_t;
typedef struct uib_w_data_array_static    uib_w_data_array_static_t;
typedef struct uib_w_data_array_dynamic   uib_w_data_array_dynamic_t;
typedef struct uib_w_data_button          uib_w_data_button_t;
typedef struct uib_w_data_checkbox        uib_w_data_checkbox_t;
typedef struct uib_w_data_container       uib_w_data_container_t;
typedef struct uib_w_data_container_label uib_w_data_container_label_t;


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

#endif