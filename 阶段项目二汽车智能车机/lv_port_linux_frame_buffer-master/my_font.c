/*******************************************************************************
 * Size: 15 px
 * Bpp: 1
 * Opts: --bpp 1 --size 15 --font simkai.ttf --range 32-127 --format lvgl -o my_font.c
 ******************************************************************************/

 #ifdef LV_LVGL_H_INCLUDE_SIMPLE
 #include "lvgl.h"
 #else
 #include "lvgl/lvgl.h"
 #endif
 
 #ifndef MY_FONT
 #define MY_FONT 1
 #endif
 
 #if MY_FONT
 
 /*-----------------
  *    BITMAPS
  *----------------*/
 
 /*Store the image of the glyphs*/
 static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
     /* U+0020 " " */
     0x0,
 
     /* U+0021 "!" */
     0xff, 0x80,
 
     /* U+0022 "\"" */
     0x99, 0x99, 0x90,
 
     /* U+0023 "#" */
     0x22, 0x22, 0x22, 0xff, 0x44, 0x44, 0xff, 0x44,
     0x44, 0x88,
 
     /* U+0024 "$" */
     0x8, 0x50, 0xf3, 0x56, 0x8d, 0xe, 0x16, 0x2b,
     0x55, 0xb1, 0xc2, 0x80,
 
     /* U+0025 "%" */
     0xe1, 0x12, 0x22, 0x48, 0x4a, 0x6, 0x4c, 0x12,
     0x42, 0x48, 0x89, 0x20, 0xc4, 0x0,
 
     /* U+0026 "&" */
     0x18, 0x9, 0x2, 0x40, 0xe0, 0x18, 0xdb, 0x28,
     0x52, 0x8, 0xc7, 0x1e, 0x30,
 
     /* U+0027 "'" */
     0xf8,
 
     /* U+0028 "(" */
     0x12, 0x44, 0x88, 0x88, 0x88, 0x44, 0x20,
 
     /* U+0029 ")" */
     0x84, 0x22, 0x11, 0x11, 0x12, 0x24, 0x40,
 
     /* U+002A "*" */
     0x21, 0x3e, 0xea, 0x90,
 
     /* U+002B "+" */
     0x8, 0x4, 0x2, 0x1, 0xf, 0xf8, 0x40, 0x20,
     0x10,
 
     /* U+002C "," */
     0xd8,
 
     /* U+002D "-" */
     0xe0,
 
     /* U+002E "." */
     0xc0,
 
     /* U+002F "/" */
     0x4, 0x20, 0x84, 0x10, 0x42, 0x8, 0x41, 0x4,
     0x20, 0x80,
 
     /* U+0030 "0" */
     0x72, 0x28, 0x61, 0x86, 0x18, 0x62, 0x70,
 
     /* U+0031 "1" */
     0x2e, 0x22, 0x22, 0x22, 0x20,
 
     /* U+0032 "2" */
     0x39, 0x10, 0x41, 0x8, 0x42, 0x10, 0xfc,
 
     /* U+0033 "3" */
     0x7a, 0x21, 0xe, 0x4, 0x10, 0x42, 0xf0,
 
     /* U+0034 "4" */
     0x8, 0x30, 0xa2, 0x48, 0x9f, 0xc2, 0x4, 0x8,
 
     /* U+0035 "5" */
     0x1, 0xe4, 0x10, 0x78, 0x30, 0x41, 0x5, 0xe0,
 
     /* U+0036 "6" */
     0x8, 0xc4, 0x10, 0x8a, 0x18, 0x61, 0xc5, 0xe0,
 
     /* U+0037 "7" */
     0xfc, 0x20, 0x84, 0x10, 0x42, 0x8, 0x20,
 
     /* U+0038 "8" */
     0x74, 0x63, 0xa7, 0x46, 0x31, 0x70,
 
     /* U+0039 "9" */
     0x7a, 0x28, 0x61, 0x85, 0x90, 0x82, 0x11, 0x80,
 
     /* U+003A ":" */
     0xcc,
 
     /* U+003B ";" */
     0xa0, 0x36,
 
     /* U+003C "<" */
     0x3, 0xc, 0x70, 0x80, 0x70, 0xc, 0x3,
 
     /* U+003D "=" */
     0xff, 0x0, 0x0, 0xff,
 
     /* U+003E ">" */
     0xc0, 0x30, 0xe, 0x1, 0xe, 0x30, 0xc0,
 
     /* U+003F "?" */
     0x60, 0x82, 0x17, 0x21, 0x8, 0x40,
 
     /* U+0040 "@" */
     0xf, 0x80, 0x83, 0x8, 0x8, 0x85, 0x24, 0x49,
     0x44, 0x4a, 0x46, 0x52, 0x24, 0x93, 0x24, 0xee,
     0x10, 0x4, 0x80, 0x42, 0x4, 0xf, 0xc0,
 
     /* U+0041 "A" */
     0x4, 0x3, 0x1, 0x40, 0x48, 0x12, 0x7, 0x82,
     0x10, 0x84, 0x41, 0x18, 0x60,
 
     /* U+0042 "B" */
     0x7e, 0x10, 0x88, 0x47, 0xc2, 0x19, 0x4, 0x82,
     0x43, 0x3e, 0x0,
 
     /* U+0043 "C" */
     0x1f, 0x61, 0x80, 0x80, 0x80, 0x80, 0x80, 0x41,
     0x3f,
 
     /* U+0044 "D" */
     0x3f, 0x4, 0x18, 0x80, 0x90, 0x12, 0x2, 0x40,
     0x48, 0x11, 0x2, 0x7f, 0x80,
 
     /* U+0045 "E" */
     0x3f, 0x88, 0x22, 0x0, 0x84, 0x3f, 0x8, 0x42,
     0x0, 0x81, 0x7f, 0xc0,
 
     /* U+0046 "F" */
     0x7f, 0x41, 0x40, 0x42, 0x7e, 0x42, 0x40, 0x40,
     0x60,
 
     /* U+0047 "G" */
     0x1f, 0x98, 0x28, 0x2, 0x0, 0x83, 0xe0, 0x2c,
     0x9, 0x2, 0x3f, 0x0,
 
     /* U+0048 "H" */
     0x30, 0x42, 0x4, 0x20, 0x42, 0x4, 0x3f, 0xc2,
     0x4, 0x20, 0x42, 0x4, 0x60, 0x60,
 
     /* U+0049 "I" */
     0x71, 0x8, 0x42, 0x10, 0x84, 0x70,
 
     /* U+004A "J" */
     0x10, 0x84, 0x21, 0x8, 0x42, 0x10, 0x84, 0x4c,
     0x0,
 
     /* U+004B "K" */
     0x41, 0x90, 0x84, 0xc1, 0x40, 0x70, 0x12, 0x4,
     0x61, 0xc, 0x41, 0x80,
 
     /* U+004C "L" */
     0x70, 0x10, 0x8, 0x4, 0x2, 0x1, 0x0, 0x80,
     0x42, 0x7f, 0x0,
 
     /* U+004D "M" */
     0x30, 0x31, 0x83, 0xa, 0x28, 0x51, 0x42, 0x4a,
     0x12, 0x90, 0x8c, 0x84, 0x44, 0x72, 0x30,
 
     /* U+004E "N" */
     0x60, 0xc6, 0x8, 0xa1, 0x12, 0x22, 0x44, 0x44,
     0x88, 0x51, 0x6, 0x70, 0x40,
 
     /* U+004F "O" */
     0x1e, 0x18, 0x68, 0x6, 0x1, 0x80, 0x60, 0x18,
     0x5, 0x2, 0x3f, 0x0,
 
     /* U+0050 "P" */
     0x7e, 0x21, 0x21, 0x21, 0x2e, 0x20, 0x20, 0x20,
     0x30,
 
     /* U+0051 "Q" */
     0x1e, 0x18, 0x64, 0xa, 0x1, 0x80, 0x60, 0x18,
     0x5, 0x2, 0x40, 0x8c, 0xc0, 0xe0, 0xc, 0x0,
     0xc0,
 
     /* U+0052 "R" */
     0x7c, 0x11, 0x8, 0x84, 0x43, 0xc1, 0x20, 0x98,
     0x44, 0x63, 0x0,
 
     /* U+0053 "S" */
     0x7a, 0x8, 0x38, 0x38, 0x30, 0x61, 0xf8,
 
     /* U+0054 "T" */
     0x80, 0xff, 0xe2, 0x1, 0x0, 0x80, 0x40, 0x20,
     0x10, 0x8, 0xe, 0x0,
 
     /* U+0055 "U" */
     0x61, 0x90, 0x24, 0x9, 0x2, 0x40, 0x90, 0x24,
     0x9, 0x6, 0x3f, 0x0,
 
     /* U+0056 "V" */
     0x60, 0x88, 0x22, 0x10, 0x44, 0x12, 0x6, 0x80,
     0xc0, 0x30, 0x4, 0x0,
 
     /* U+0057 "W" */
     0x44, 0x8a, 0x24, 0x88, 0xc4, 0x46, 0x43, 0x12,
     0x9, 0x90, 0x73, 0x1, 0x98, 0x8, 0x80,
 
     /* U+0058 "X" */
     0x71, 0x86, 0x20, 0x48, 0x6, 0x0, 0x40, 0x1c,
     0x4, 0xc1, 0x8, 0x71, 0xc0,
 
     /* U+0059 "Y" */
     0x60, 0xcc, 0x21, 0x10, 0x28, 0xc, 0x1, 0x0,
     0x40, 0x10, 0xe, 0x0,
 
     /* U+005A "Z" */
     0x0, 0x3f, 0xa0, 0xc0, 0xc0, 0xc0, 0x40, 0x40,
     0x40, 0x60, 0xff, 0xc0,
 
     /* U+005B "[" */
     0xd2, 0x49, 0x24, 0x92, 0x4e,
 
     /* U+005C "\\" */
     0x82, 0x4, 0x10, 0x40, 0x82, 0x4, 0x10, 0x40,
     0x82, 0x4,
 
     /* U+005D "]" */
     0x64, 0x92, 0x49, 0x24, 0x9e,
 
     /* U+005E "^" */
     0x10, 0x51, 0x12, 0x10,
 
     /* U+005F "_" */
     0xff,
 
     /* U+0060 "`" */
     0x90,
 
     /* U+0061 "a" */
     0x74, 0x84, 0xe9, 0x7c,
 
     /* U+0062 "b" */
     0xc0, 0x81, 0x2, 0x7, 0xc8, 0xd0, 0xa1, 0x42,
     0xf8,
 
     /* U+0063 "c" */
     0x7c, 0x21, 0xc, 0x3c,
 
     /* U+0064 "d" */
     0xc, 0x8, 0x10, 0x27, 0xd0, 0xa1, 0x42, 0x84,
     0xfc,
 
     /* U+0065 "e" */
     0x77, 0xe1, 0xc, 0x3c,
 
     /* U+0066 "f" */
     0x39, 0x4, 0x10, 0xf1, 0x4, 0x10, 0x41, 0x80,
 
     /* U+0067 "g" */
     0x38, 0x8d, 0x12, 0x23, 0x88, 0xf, 0x61, 0x82,
     0xf8,
 
     /* U+0068 "h" */
     0x41, 0x81, 0x2, 0x5, 0x8c, 0x91, 0x22, 0x44,
     0x88,
 
     /* U+0069 "i" */
     0x40, 0x24, 0x92, 0x40,
 
     /* U+006A "j" */
     0x40, 0xd5, 0x55, 0x80,
 
     /* U+006B "k" */
     0x40, 0x81, 0x2, 0x4, 0x8a, 0x1c, 0x28, 0x48,
     0x88,
 
     /* U+006C "l" */
     0xc9, 0x24, 0x92, 0x48,
 
     /* U+006D "m" */
     0x0, 0xb, 0xb1, 0x99, 0x22, 0x24, 0x44, 0x88,
     0x91, 0x10,
 
     /* U+006E "n" */
     0x0, 0xb9, 0x92, 0x24, 0x48, 0x91, 0x0,
 
     /* U+006F "o" */
     0x7a, 0x18, 0x61, 0x85, 0xe0,
 
     /* U+0070 "p" */
     0x1, 0xb9, 0x9a, 0x14, 0x28, 0x59, 0x2c, 0x40,
     0x81, 0x80,
 
     /* U+0071 "q" */
     0x7d, 0xa, 0x14, 0x2c, 0x4f, 0x81, 0x2, 0x4,
     0x8,
 
     /* U+0072 "r" */
     0x2, 0xb8, 0x84, 0x21, 0x80,
 
     /* U+0073 "s" */
     0xe8, 0xc3, 0x1e,
 
     /* U+0074 "t" */
     0x4, 0xf4, 0x44, 0x47,
 
     /* U+0075 "u" */
     0x44, 0x89, 0x12, 0x24, 0x47, 0xc0,
 
     /* U+0076 "v" */
     0x44, 0x90, 0xa1, 0x41, 0x2, 0x0,
 
     /* U+0077 "w" */
     0x4c, 0x91, 0x22, 0x50, 0xac, 0x1a, 0x4, 0x80,
 
     /* U+0078 "x" */
     0x48, 0x50, 0x40, 0x86, 0x88, 0x80,
 
     /* U+0079 "y" */
     0x64, 0x48, 0xa1, 0x41, 0x82, 0x4, 0x10, 0x20,
     0xc0,
 
     /* U+007A "z" */
     0x1, 0xe1, 0x84, 0x21, 0xf, 0x80,
 
     /* U+007B "{" */
     0x29, 0x24, 0xa4, 0x49, 0x24, 0x40,
 
     /* U+007C "|" */
     0xff, 0xf8,
 
     /* U+007D "}" */
     0x89, 0x24, 0x89, 0x49, 0x25, 0x0,
 
     /* U+007E "~" */
     0x60, 0x9e,
 
     /* U+007F "" */
     0x0
 };
 
 
 /*---------------------
  *  GLYPH DESCRIPTION
  *--------------------*/
 
 static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
     {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
     {.bitmap_index = 0, .adv_w = 60, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 1, .adv_w = 53, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 3, .adv_w = 97, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
     {.bitmap_index = 6, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 16, .adv_w = 108, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
     {.bitmap_index = 28, .adv_w = 198, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
     {.bitmap_index = 42, .adv_w = 175, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 55, .adv_w = 42, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
     {.bitmap_index = 56, .adv_w = 70, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
     {.bitmap_index = 63, .adv_w = 70, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
     {.bitmap_index = 70, .adv_w = 102, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
     {.bitmap_index = 74, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
     {.bitmap_index = 83, .adv_w = 53, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
     {.bitmap_index = 84, .adv_w = 75, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
     {.bitmap_index = 85, .adv_w = 53, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 86, .adv_w = 120, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
     {.bitmap_index = 96, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 103, .adv_w = 113, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 108, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 115, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 122, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 130, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 138, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 146, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 153, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 159, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
     {.bitmap_index = 167, .adv_w = 53, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 168, .adv_w = 53, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
     {.bitmap_index = 170, .adv_w = 160, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
     {.bitmap_index = 177, .adv_w = 160, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
     {.bitmap_index = 181, .adv_w = 160, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
     {.bitmap_index = 188, .adv_w = 88, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 194, .adv_w = 220, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
     {.bitmap_index = 217, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 230, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 241, .adv_w = 152, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 250, .adv_w = 185, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 263, .adv_w = 157, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 275, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 284, .adv_w = 185, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 296, .adv_w = 182, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 310, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 316, .adv_w = 80, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -4},
     {.bitmap_index = 325, .adv_w = 178, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 337, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 348, .adv_w = 200, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 363, .adv_w = 185, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 376, .adv_w = 187, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 388, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 397, .adv_w = 185, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
     {.bitmap_index = 414, .adv_w = 150, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 425, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 432, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 444, .adv_w = 170, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 456, .adv_w = 162, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 468, .adv_w = 212, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 483, .adv_w = 168, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 496, .adv_w = 157, .box_w = 10, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
     {.bitmap_index = 508, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 520, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -4},
     {.bitmap_index = 525, .adv_w = 120, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
     {.bitmap_index = 535, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
     {.bitmap_index = 540, .adv_w = 120, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
     {.bitmap_index = 544, .adv_w = 120, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
     {.bitmap_index = 545, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
     {.bitmap_index = 546, .adv_w = 97, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 550, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 559, .adv_w = 100, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 563, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 572, .adv_w = 100, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 576, .adv_w = 78, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 584, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
     {.bitmap_index = 593, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 602, .adv_w = 55, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 606, .adv_w = 55, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = -5},
     {.bitmap_index = 610, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 619, .adv_w = 55, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 623, .adv_w = 185, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 633, .adv_w = 122, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 640, .adv_w = 122, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 645, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
     {.bitmap_index = 655, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
     {.bitmap_index = 664, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 669, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 672, .adv_w = 70, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 676, .adv_w = 118, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 682, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 688, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 696, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
     {.bitmap_index = 702, .adv_w = 100, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -4},
     {.bitmap_index = 711, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
     {.bitmap_index = 717, .adv_w = 115, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
     {.bitmap_index = 723, .adv_w = 120, .box_w = 1, .box_h = 13, .ofs_x = 3, .ofs_y = -4},
     {.bitmap_index = 725, .adv_w = 115, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
     {.bitmap_index = 731, .adv_w = 160, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
     {.bitmap_index = 733, .adv_w = 120, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0}
 };
 
 /*---------------------
  *  CHARACTER MAPPING
  *--------------------*/
 
 
 
 /*Collect the unicode lists and glyph_id offsets*/
 static const lv_font_fmt_txt_cmap_t cmaps[] =
 {
     {
         .range_start = 32, .range_length = 96, .glyph_id_start = 1,
         .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
     }
 };
 
 
 
 /*--------------------
  *  ALL CUSTOM DATA
  *--------------------*/
 
 #if LVGL_VERSION_MAJOR == 8
 /*Store all the custom data of the font*/
 static  lv_font_fmt_txt_glyph_cache_t cache;
 #endif
 
 #if LVGL_VERSION_MAJOR >= 8
 static const lv_font_fmt_txt_dsc_t font_dsc = {
 #else
 static lv_font_fmt_txt_dsc_t font_dsc = {
 #endif
     .glyph_bitmap = glyph_bitmap,
     .glyph_dsc = glyph_dsc,
     .cmaps = cmaps,
     .kern_dsc = NULL,
     .kern_scale = 0,
     .cmap_num = 1,
     .bpp = 1,
     .kern_classes = 0,
     .bitmap_format = 0,
 #if LVGL_VERSION_MAJOR == 8
     .cache = &cache
 #endif
 };
 
 
 
 /*-----------------
  *  PUBLIC FONT
  *----------------*/
 
 /*Initialize a public general font descriptor*/
 #if LVGL_VERSION_MAJOR >= 8
 const lv_font_t my_font = {
 #else
 lv_font_t my_font = {
 #endif
     .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
     .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
     .line_height = 16,          /*The maximum line height required by the font*/
     .base_line = 5,             /*Baseline measured from the bottom of the line*/
 #if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
     .subpx = LV_FONT_SUBPX_NONE,
 #endif
 #if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
     .underline_position = -2,
     .underline_thickness = 0,
 #endif
     .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
 #if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
     .fallback = NULL,
 #endif
     .user_data = NULL,
 };
 
 
 
 #endif /*#if MY_FONT*/
 
 