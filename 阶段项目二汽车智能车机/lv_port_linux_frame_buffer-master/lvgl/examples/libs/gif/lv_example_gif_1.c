#include "../../lv_examples.h"
#if LV_USE_GIF && LV_BUILD_EXAMPLES

/**
 * Open a GIF image from a file and a variable
 */
// 定义一个函数，用于展示GIF动画示例
void lv_example_gif_1(void)
{
    // 声明一个GIF图像资源，这里使用的是名为img_bulb_gif的GIF文件
    LV_IMG_DECLARE(img_bulb_gif);
    // 定义一个指向LVGL对象的指针，用于存储创建的GIF对象
    lv_obj_t * img;

    // 在当前活动屏幕上创建一个GIF对象
    img = lv_gif_create(lv_scr_act());
    // 设置GIF对象的源文件为之前声明的img_bulb_gif
    lv_gif_set_src(img, &img_bulb_gif);
    // 将GIF对象对齐到屏幕的中间位置，偏移量为x=0, y=0
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    // 再次在当前活动屏幕上创建一个GIF对象
    img = lv_gif_create(lv_scr_act());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_gif_set_src(img, "A:lvgl/examples/libs/gif/bulb.gif");
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

#endif
