/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font E:/lvgl/assets/DroidSansFallback.ttf -o E:/lvgl/assets\ui_font_Font1small.c --format lvgl -r 0x20-0x7f --symbols 你好我阿是
我地方获取验证码
啊所发生的点击登录 --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT1SMALL
#define UI_FONT_FONT1SMALL 1
#endif

#if UI_FONT_FONT1SMALL

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xf,

    /* U+0022 "\"" */
    0xd9, 0x99,

    /* U+0023 "#" */
    0x9, 0x2, 0x41, 0x90, 0x44, 0x7f, 0xc4, 0x81,
    0x23, 0xfe, 0x22, 0x9, 0x82, 0x40, 0x90,

    /* U+0024 "$" */
    0x10, 0x21, 0xfe, 0x8d, 0x1a, 0x1c, 0xe, 0x16,
    0x2e, 0x5f, 0xe1, 0x2, 0x0,

    /* U+0025 "%" */
    0x70, 0xc9, 0x88, 0x89, 0x88, 0x90, 0x8b, 0xd,
    0xee, 0x75, 0x30, 0xd1, 0x9, 0x11, 0x91, 0x11,
    0x33, 0xe,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0x98, 0x3c, 0xe, 0x7,
    0x83, 0xb3, 0xc6, 0xb0, 0xec, 0x39, 0xf3,

    /* U+0027 "'" */
    0xea,

    /* U+0028 "(" */
    0x32, 0x66, 0xcc, 0xcc, 0xcc, 0xc6, 0x63, 0x10,

    /* U+0029 ")" */
    0xc4, 0x66, 0x33, 0x33, 0x33, 0x36, 0x6c, 0x80,

    /* U+002A "*" */
    0x10, 0x20, 0x4f, 0xf3, 0x85, 0x1b, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0x6d, 0x20,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x20, 0x86, 0x10, 0xc3, 0x8, 0x61, 0x4,
    0x30,

    /* U+0030 "0" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0031 "1" */
    0x1b, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x7d, 0x9c, 0x18, 0x30, 0x61, 0x83, 0xc, 0x30,
    0xc3, 0x7, 0xf0,

    /* U+0033 "3" */
    0x3e, 0x47, 0x3, 0x3, 0x7, 0x3c, 0x6, 0x3,
    0x3, 0x3, 0x86, 0xfc,

    /* U+0034 "4" */
    0x6, 0xe, 0x1e, 0x16, 0x26, 0x26, 0x46, 0xc6,
    0xff, 0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x40, 0x40, 0x40, 0x40, 0x7c, 0x6, 0x3,
    0x3, 0x3, 0x86, 0xfc,

    /* U+0036 "6" */
    0x3c, 0xc1, 0x86, 0xc, 0x1b, 0xb9, 0xe3, 0xc7,
    0x8d, 0xb1, 0xe0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x20, 0xc1, 0x2, 0xc, 0x10,
    0x60, 0x81, 0x0,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1e, 0x36, 0xc7, 0x1f, 0x67, 0xc7,
    0x8f, 0x1b, 0xe0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x79, 0xdd, 0x83, 0x6,
    0x18, 0x33, 0xc0,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x3, 0x4b, 0x0,

    /* U+003C "<" */
    0x2, 0x1c, 0xe3, 0xc, 0x6, 0x3, 0x1,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x81, 0xc0, 0xe0, 0x60, 0x63, 0x18, 0x40,

    /* U+003F "?" */
    0x7c, 0xc, 0x18, 0x30, 0xe3, 0x8c, 0x10, 0x20,
    0x0, 0xc1, 0x80,

    /* U+0040 "@" */
    0xf, 0x83, 0x4, 0x60, 0x24, 0x79, 0x88, 0x99,
    0x9, 0x90, 0x99, 0x9, 0x99, 0xac, 0xee, 0x40,
    0x3, 0x0, 0x1f, 0x80,

    /* U+0041 "A" */
    0xc, 0x3, 0x1, 0xc0, 0x58, 0x12, 0xc, 0x82,
    0x30, 0xfc, 0x61, 0x90, 0x64, 0xb, 0x3,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xc4, 0xf8, 0xc6, 0xc3,
    0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x31, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0x60, 0x70, 0x1f,

    /* U+0044 "D" */
    0xfc, 0x63, 0x30, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xb1, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x18, 0x3f, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0047 "G" */
    0x1f, 0x98, 0x98, 0x18, 0xc, 0x6, 0x3, 0x1f,
    0x83, 0xc1, 0xb0, 0xdc, 0x63, 0xf0,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xf6, 0x66, 0x66, 0x66, 0x66, 0x6f,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8f, 0xc0,

    /* U+004B "K" */
    0xc3, 0xc6, 0xc4, 0xc8, 0xd8, 0xf0, 0xf8, 0xc8,
    0xcc, 0xc6, 0xc2, 0xc3,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+004D "M" */
    0xc0, 0xf8, 0x1f, 0x87, 0xd0, 0xba, 0x17, 0x66,
    0xe4, 0x9c, 0x93, 0x9a, 0x71, 0x8e, 0x31, 0xc6,
    0x30,

    /* U+004E "N" */
    0xc1, 0xe0, 0xf8, 0x74, 0x3b, 0x1c, 0xce, 0x67,
    0x1b, 0x85, 0xc3, 0xe0, 0xf0, 0x70,

    /* U+004F "O" */
    0x1e, 0x18, 0x66, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x66, 0x18, 0x78,

    /* U+0050 "P" */
    0xf9, 0x9f, 0x1e, 0x3c, 0x79, 0xbe, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0051 "Q" */
    0x1e, 0x18, 0x66, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x66, 0x18, 0x78, 0x2,
    0x0, 0xc0, 0x10,

    /* U+0052 "R" */
    0xf8, 0xce, 0xc6, 0xc6, 0xc6, 0xcc, 0xf8, 0xc8,
    0xcc, 0xc4, 0xc6, 0xc3,

    /* U+0053 "S" */
    0x7f, 0x83, 0x6, 0xe, 0xf, 0xf, 0x7, 0x6,
    0xc, 0x37, 0xc0,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xc1, 0xe0, 0xd0, 0x4c, 0x66, 0x31, 0x10, 0xc8,
    0x6c, 0x14, 0xa, 0x7, 0x1, 0x0,

    /* U+0057 "W" */
    0xc3, 0xd, 0xc, 0x34, 0x38, 0x99, 0xe2, 0x66,
    0x98, 0x92, 0x62, 0x4d, 0xb, 0x34, 0x3c, 0x50,
    0x61, 0xc1, 0x86, 0x6, 0x18,

    /* U+0058 "X" */
    0x41, 0x31, 0x88, 0x86, 0x81, 0xc0, 0xc0, 0x70,
    0x28, 0x26, 0x31, 0x10, 0xd8, 0x20,

    /* U+0059 "Y" */
    0x40, 0x98, 0x62, 0x10, 0xcc, 0x12, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xfe, 0xc, 0x10, 0x60, 0x83, 0xc, 0x10, 0x60,
    0x83, 0x7, 0xf0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc1, 0x4, 0x18, 0x20, 0xc3, 0x4, 0x18, 0x20,
    0x83,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x0, 0x18, 0x18, 0x24, 0x24, 0x62, 0x42, 0x41,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc8, 0x80,

    /* U+0061 "a" */
    0x7c, 0x8c, 0x18, 0x37, 0xf8, 0xf1, 0xe7, 0x76,

    /* U+0062 "b" */
    0xc1, 0x83, 0x6, 0xee, 0xd8, 0xf1, 0xe3, 0xc7,
    0x8f, 0xb6, 0xe0,

    /* U+0063 "c" */
    0x3d, 0x8c, 0x30, 0xc3, 0xc, 0x18, 0x3c,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xb6, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8d, 0xbb, 0xb0,

    /* U+0065 "e" */
    0x38, 0xdb, 0x1e, 0x3f, 0xf8, 0x30, 0x31, 0x3e,

    /* U+0066 "f" */
    0x1c, 0xc3, 0x3f, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc,

    /* U+0067 "g" */
    0x7f, 0xc4, 0xc6, 0xc6, 0xc6, 0x7c, 0x40, 0x40,
    0x3e, 0xc3, 0xc3, 0xc7, 0x7c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x3c, 0xdb, 0x34, 0x78, 0xd9,
    0x9b, 0x16, 0x30,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006D "m" */
    0xdd, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xdd, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xf6, 0xdd,
    0x83, 0x6, 0xc, 0x0,

    /* U+0071 "q" */
    0x76, 0xdf, 0x1e, 0x3c, 0x78, 0xf1, 0xb7, 0x76,
    0xc, 0x18, 0x30, 0x60,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7f, 0xc, 0x38, 0x78, 0x70, 0xc3, 0xf8,

    /* U+0074 "t" */
    0x23, 0x3e, 0xc6, 0x31, 0x8c, 0x63, 0xe,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x76,

    /* U+0076 "v" */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x2c, 0x2c, 0x38,
    0x18,

    /* U+0077 "w" */
    0xc6, 0x34, 0x62, 0x46, 0x24, 0xb2, 0x69, 0x62,
    0x94, 0x39, 0x43, 0x1c, 0x30, 0xc0,

    /* U+0078 "x" */
    0x42, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x24, 0x66,
    0x42,

    /* U+0079 "y" */
    0xc2, 0xc2, 0x46, 0x64, 0x64, 0x2c, 0x28, 0x18,
    0x18, 0x10, 0x10, 0x30, 0xe0,

    /* U+007A "z" */
    0xf8, 0xc4, 0x62, 0x31, 0x18, 0xf8,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x1b, 0x6, 0x31, 0x8c, 0x63,
    0xc,

    /* U+007C "|" */
    0xff, 0xff,

    /* U+007D "}" */
    0xe0, 0xc3, 0xc, 0x30, 0xc0, 0xcc, 0x30, 0xc3,
    0xc, 0x33, 0x80,

    /* U+007E "~" */
    0xf3, 0x3c,

    /* U+4F60 "你" */
    0x13, 0x0, 0x48, 0x2, 0x7f, 0xd9, 0x93, 0x6c,
    0x4a, 0x81, 0xa, 0x25, 0x88, 0x92, 0x26, 0x48,
    0x91, 0x32, 0xc4, 0xc8, 0x10, 0x21, 0xc0,

    /* U+51FB "击" */
    0x3, 0x0, 0xc, 0x7, 0xff, 0x80, 0xc0, 0x3,
    0x0, 0xc, 0xf, 0xff, 0xc0, 0xc0, 0x23, 0x18,
    0x8c, 0x62, 0x31, 0x88, 0xc6, 0x3f, 0xf8, 0x0,
    0x60,

    /* U+53D1 "发" */
    0x2, 0x0, 0x89, 0x82, 0x63, 0x11, 0x80, 0x7f,
    0xf8, 0x30, 0x0, 0xc0, 0x3, 0xfe, 0x1c, 0x10,
    0xd8, 0x86, 0x36, 0x30, 0x70, 0x87, 0x70, 0x70,
    0x70,

    /* U+53D6 "取" */
    0xfe, 0xfc, 0x88, 0x89, 0x11, 0x13, 0xe2, 0x64,
    0x44, 0x88, 0x89, 0x11, 0xa, 0x3e, 0x1c, 0x44,
    0x30, 0x8c, 0x63, 0xf1, 0xe0, 0x26, 0x60, 0x48,
    0x40,

    /* U+554A "啊" */
    0xef, 0x7e, 0xa4, 0x2a, 0xa0, 0xaa, 0x9e, 0xae,
    0x5a, 0xa9, 0x6a, 0x95, 0xba, 0x5e, 0xa9, 0x4a,
    0xbc, 0x20, 0x80, 0x82, 0x2,

    /* U+5730 "地" */
    0x0, 0x40, 0x81, 0x2, 0x14, 0x8, 0x52, 0xf9,
    0x78, 0x8f, 0x22, 0x34, 0x88, 0x52, 0x21, 0x48,
    0xa5, 0x4f, 0x14, 0x30, 0x41, 0x1, 0xc, 0x7,
    0xe0,

    /* U+597D "好" */
    0x0, 0x0, 0x43, 0xf8, 0x80, 0x37, 0xe0, 0xc4,
    0xc2, 0x9, 0x84, 0x17, 0xff, 0xcc, 0x10, 0x58,
    0x20, 0x60, 0x40, 0xc0, 0x83, 0xc1, 0xc, 0x82,
    0x10, 0x1c, 0x0,

    /* U+5F55 "录" */
    0x3f, 0xe0, 0x0, 0x83, 0xfe, 0x0, 0x8, 0x0,
    0x23, 0xff, 0xf0, 0x30, 0xc, 0xe6, 0x17, 0xf0,
    0x3d, 0x87, 0x33, 0xb0, 0xc3, 0xe, 0x0,

    /* U+6211 "我" */
    0x0, 0xd1, 0xfb, 0x41, 0x8c, 0x86, 0x30, 0xff,
    0xfc, 0x61, 0x1, 0x84, 0x87, 0x96, 0x7e, 0x53,
    0xe1, 0xc1, 0x86, 0x6, 0x38, 0x19, 0xb5, 0xc8,
    0x60,

    /* U+6240 "所" */
    0x4, 0x9, 0xf7, 0xc4, 0x10, 0x10, 0x40, 0x7d,
    0x1, 0x17, 0xf4, 0x51, 0x11, 0x44, 0x7d, 0x11,
    0x4, 0x44, 0x11, 0x10, 0x84, 0xc2, 0x12, 0x10,
    0x40,

    /* U+65B9 "方" */
    0x2, 0x0, 0x8, 0x0, 0x30, 0x3f, 0xff, 0x8,
    0x0, 0x20, 0x0, 0xff, 0x2, 0x4, 0x8, 0x10,
    0x60, 0x41, 0x1, 0xc, 0x4, 0x60, 0x13, 0x3,
    0x80,

    /* U+662F "是" */
    0x3f, 0xf0, 0x80, 0x43, 0xff, 0x8, 0x4, 0x3f,
    0xf0, 0x0, 0xf, 0xff, 0xc0, 0xc0, 0x33, 0x0,
    0xcf, 0xe7, 0xb0, 0x33, 0xc0, 0x81, 0xfc,

    /* U+70B9 "点" */
    0x1, 0x0, 0x2, 0x0, 0x7, 0xf0, 0x8, 0x0,
    0x10, 0x7, 0xff, 0x8, 0x2, 0x10, 0x4, 0x20,
    0x8, 0x7f, 0xf0, 0x0, 0x1, 0x26, 0x66, 0x64,
    0x58, 0xcc, 0xc0,

    /* U+751F "生" */
    0x1, 0x0, 0x44, 0x3, 0x10, 0x8, 0x40, 0x7f,
    0xf9, 0x4, 0x8, 0x10, 0x0, 0x40, 0x3f, 0xf8,
    0x4, 0x0, 0x10, 0x0, 0x40, 0x1, 0x3, 0xff,
    0xf0,

    /* U+767B "登" */
    0x7f, 0xb0, 0x13, 0x27, 0x87, 0x9f, 0xff, 0x80,
    0x4, 0xff, 0xc2, 0x3, 0x8, 0xc, 0x3f, 0xf0,
    0x0, 0x1, 0x86, 0x2, 0x10, 0xff, 0xfc,

    /* U+7684 "的" */
    0x0, 0x3, 0x4, 0x3e, 0x61, 0xf3, 0xf8, 0xb0,
    0xc7, 0x6, 0x22, 0x3f, 0x11, 0x88, 0xcc, 0x42,
    0x62, 0x3, 0x10, 0x1f, 0x81, 0x40, 0x38,

    /* U+7801 "码" */
    0xfd, 0xf8, 0x80, 0x22, 0x18, 0x98, 0x62, 0x41,
    0x1b, 0xe4, 0x6e, 0x9f, 0xfa, 0x1, 0x68, 0x5,
    0xaf, 0xd7, 0x80, 0x5a, 0x3, 0x60, 0x38,

    /* U+83B7 "获" */
    0x8, 0x43, 0xff, 0xf0, 0x84, 0x0, 0x0, 0x4c,
    0x50, 0xe1, 0x67, 0x4, 0x34, 0xff, 0x18, 0x40,
    0xe3, 0x8e, 0x8a, 0x2, 0x64, 0x1b, 0x19, 0xd8,
    0x30,

    /* U+8BC1 "证" */
    0x20, 0x0, 0x9f, 0xf3, 0x4, 0x0, 0x10, 0x0,
    0x43, 0x89, 0x2, 0x24, 0x8, 0x9e, 0x22, 0x40,
    0x89, 0x2, 0x24, 0xc, 0x90, 0x32, 0x40, 0xbf,
    0xf0,

    /* U+963F "阿" */
    0xf7, 0xfe, 0x40, 0x29, 0x0, 0xa8, 0x2, 0xa3,
    0xca, 0x89, 0x29, 0x24, 0xa4, 0x92, 0x93, 0xcb,
    0xc8, 0x28, 0x0, 0xa0, 0x2, 0x80, 0x38,

    /* U+9A8C "验" */
    0xf8, 0x40, 0x23, 0x84, 0x9b, 0x12, 0xc6, 0xcb,
    0xff, 0x20, 0xf, 0xc9, 0x83, 0xd6, 0xd, 0x51,
    0xb5, 0x4c, 0x91, 0x2, 0x8, 0x3b, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 103, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 141, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 34, .adv_w = 211, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 180, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 68, .adv_w = 77, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 76, .adv_w = 77, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 84, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 91, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 98, .adv_w = 64, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 82, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 101, .adv_w = 69, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 96, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 141, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 69, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 69, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 230, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 237, .adv_w = 141, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 241, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 248, .adv_w = 109, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 222, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 279, .adv_w = 156, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 175, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 177, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 180, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 87, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 69, .box_w = 5, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 396, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 223, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 190, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 148, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 190, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 495, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 133, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 179, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 226, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 140, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 135, .box_w = 10, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 78, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 626, .adv_w = 96, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 78, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 642, .adv_w = 136, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 650, .adv_w = 105, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 651, .adv_w = 148, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 653, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 150, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 150, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 84, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 133, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 720, .adv_w = 151, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 66, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 742, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 229, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 150, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 799, .adv_w = 150, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 811, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 87, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 191, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 125, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 884, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 91, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 899, .adv_w = 141, .box_w = 1, .box_h = 16, .ofs_x = 4, .ofs_y = -4},
    {.bitmap_index = 901, .adv_w = 91, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 912, .adv_w = 141, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 914, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 937, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 962, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 987, .adv_w = 256, .box_w = 15, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1012, .adv_w = 256, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1033, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1058, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1085, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1108, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1133, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1158, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1183, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1206, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1233, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1258, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1281, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1304, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1327, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1352, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1377, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1400, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x29b, 0x471, 0x476, 0x5ea, 0x7d0, 0xa1d, 0xff5,
    0x12b1, 0x12e0, 0x1659, 0x16cf, 0x2159, 0x25bf, 0x271b, 0x2724,
    0x28a1, 0x3457, 0x3c61, 0x46df, 0x4b2c
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 20320, .range_length = 19245, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 21, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 34,
    3, 42,
    3, 53,
    3, 55,
    3, 56,
    3, 57,
    3, 58,
    3, 59,
    3, 68,
    3, 69,
    3, 70,
    3, 72,
    3, 80,
    3, 82,
    3, 85,
    3, 87,
    3, 88,
    3, 90,
    8, 34,
    8, 42,
    8, 53,
    8, 55,
    8, 56,
    8, 57,
    8, 58,
    8, 59,
    8, 68,
    8, 69,
    8, 70,
    8, 72,
    8, 80,
    8, 82,
    8, 85,
    8, 87,
    8, 88,
    8, 90,
    9, 43,
    13, 36,
    13, 40,
    13, 48,
    13, 50,
    13, 53,
    13, 54,
    13, 55,
    13, 56,
    13, 58,
    15, 36,
    15, 40,
    15, 48,
    15, 50,
    15, 53,
    15, 54,
    15, 55,
    15, 56,
    15, 58,
    34, 3,
    34, 8,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    35, 53,
    35, 55,
    35, 57,
    35, 58,
    36, 3,
    36, 8,
    36, 10,
    36, 36,
    36, 40,
    36, 48,
    36, 50,
    36, 62,
    36, 94,
    37, 13,
    37, 15,
    37, 34,
    37, 42,
    37, 53,
    37, 55,
    37, 56,
    37, 57,
    37, 58,
    37, 59,
    39, 3,
    39, 8,
    39, 10,
    39, 13,
    39, 15,
    39, 32,
    39, 34,
    39, 55,
    39, 56,
    39, 58,
    39, 62,
    39, 94,
    42, 3,
    42, 8,
    42, 36,
    42, 40,
    42, 48,
    42, 50,
    44, 3,
    44, 8,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    45, 3,
    45, 8,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    48, 13,
    48, 15,
    48, 34,
    48, 42,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    48, 59,
    49, 13,
    49, 15,
    49, 34,
    49, 36,
    49, 57,
    49, 58,
    49, 59,
    50, 13,
    50, 15,
    50, 34,
    50, 42,
    50, 53,
    50, 55,
    50, 56,
    50, 57,
    50, 58,
    50, 59,
    51, 53,
    53, 3,
    53, 8,
    53, 13,
    53, 15,
    53, 32,
    53, 34,
    53, 36,
    53, 40,
    53, 48,
    53, 50,
    53, 52,
    53, 53,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 13,
    54, 15,
    54, 34,
    55, 3,
    55, 8,
    55, 13,
    55, 15,
    55, 32,
    55, 34,
    55, 36,
    55, 40,
    55, 48,
    55, 50,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 81,
    55, 82,
    55, 83,
    55, 84,
    55, 86,
    56, 3,
    56, 8,
    56, 13,
    56, 15,
    56, 34,
    56, 36,
    56, 40,
    56, 48,
    56, 50,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 78,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 86,
    56, 91,
    57, 3,
    57, 8,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 68,
    57, 69,
    57, 70,
    57, 80,
    57, 82,
    58, 3,
    58, 8,
    58, 13,
    58, 15,
    58, 32,
    58, 34,
    58, 36,
    58, 40,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 86,
    58, 89,
    58, 90,
    58, 91,
    59, 3,
    59, 8,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    60, 43,
    66, 8,
    67, 8,
    68, 3,
    68, 8,
    70, 8,
    71, 3,
    71, 8,
    71, 87,
    71, 88,
    71, 90,
    72, 3,
    72, 8,
    72, 72,
    73, 8,
    76, 3,
    76, 8,
    78, 8,
    79, 8,
    80, 89,
    80, 91,
    83, 3,
    83, 8,
    83, 66,
    83, 72,
    84, 3,
    84, 8,
    85, 3,
    85, 8,
    85, 85,
    87, 3,
    87, 8,
    87, 71,
    88, 3,
    88, 8,
    88, 71,
    89, 3,
    89, 8,
    89, 80,
    90, 3,
    90, 8,
    90, 71,
    91, 80,
    92, 43
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -10, 5, 10, 10, 13, 5, 10, 5,
    -8, -8, -8, -5, -8, -8, 5, 5,
    3, 5, -10, 5, 10, 10, 13, 5,
    10, 5, -8, -8, -8, -5, -8, -8,
    5, 5, 3, 5, 15, -8, -8, -8,
    -8, -13, -5, -13, -10, -13, -8, -8,
    -8, -8, -13, -5, -13, -10, -13, -10,
    -10, -3, -3, -3, -3, -15, -3, -8,
    -5, -13, -3, -3, -3, -3, 5, 5,
    5, -5, -5, -5, -5, 5, 5, -8,
    -8, -3, -3, -8, -3, -3, -3, -5,
    -3, 8, 8, 5, -13, -13, 5, -5,
    3, 3, 3, 5, 5, 5, 5, -3,
    -3, -3, -3, 5, 5, -5, -5, -5,
    -5, -13, -13, -3, -3, -3, -3, -15,
    -3, -10, -8, -13, -8, -8, -3, -3,
    -8, -5, -3, -5, -5, -3, -26, -26,
    -10, -3, -3, -3, -5, -8, -8, -3,
    -3, -8, -5, -3, -5, -5, -3, -3,
    10, 10, -13, -13, 5, -15, -8, -8,
    -8, -8, -3, 3, -15, -15, -15, -15,
    -13, -10, -10, -15, -10, -15, -10, -15,
    -10, -8, -8, -8, -8, -8, -5, -5,
    -3, 10, 10, -13, -13, 5, -8, -5,
    -5, -5, -5, -8, -8, -8, -8, -8,
    -5, -5, -8, -5, -8, -5, -5, -5,
    13, 13, -10, -10, -5, -3, -3, -3,
    -3, -5, -5, -5, -5, -3, -3, -3,
    -5, -3, -5, -3, -5, -3, -3, 5,
    5, -5, -5, -5, -5, -3, -3, -3,
    -3, -3, 10, 10, -13, -13, 5, -13,
    -5, -5, -5, -5, -3, -13, -13, -13,
    -13, -13, -8, -8, -13, -8, -13, -8,
    -10, -8, -5, -3, -8, 5, 5, -3,
    -3, -3, -3, 15, -5, -5, 5, 5,
    -5, 13, 13, 3, 3, 3, 5, 5,
    3, -8, 5, 5, -5, -5, -5, -3,
    13, 13, -3, -3, 8, 8, 10, 10,
    3, 5, 5, 3, 10, 10, 3, 5,
    5, -5, 5, 5, 3, -3, 15
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 319,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
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
const lv_font_t ui_font_Font1small = {
#else
lv_font_t ui_font_Font1small = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT1SMALL*/

