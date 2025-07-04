// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"


// COMPONENT Button1

lv_obj_t * ui_Button1_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Button1;
    cui_Button1 = lv_btn_create(comp_parent);
    lv_obj_set_width(cui_Button1, 208);
    lv_obj_set_height(cui_Button1, 123);
    lv_obj_set_x(cui_Button1, 286);
    lv_obj_set_y(cui_Button1, 5);
    lv_obj_set_align(cui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(cui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Button1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(cui_Button1, lv_color_hex(0x039DC9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(cui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(cui_Button1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(cui_Button1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_BUTTON1_NUM);
    children[UI_COMP_BUTTON1_BUTTON1] = cui_Button1;
    lv_obj_add_event_cb(cui_Button1, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Button1, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Button1_create_hook(cui_Button1);
    return cui_Button1;
}

