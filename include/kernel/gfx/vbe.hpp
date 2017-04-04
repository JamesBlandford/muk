#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <std.hpp>
#include <std/vector.hpp>

#include <kernel/tty.hpp>
#include <kernel/multiboot.hpp>

#include <kernel/gfx/vga.hpp>

#define SURF_SCREEN 0


class RGBA {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        (*this).r = r;
        (*this).g = g;
        (*this).b = b;
        (*this).a = a;
    }

    RGBA(uint32_t hex) {
        (*this).r = hex >> 16;
        (*this).g = hex >> 8;
        (*this).b = hex;

        (*this).a = 0xFF; // this constructor only supports 32-bit colour, no transparency
    }

    RGBA() : r(0xFF), g(0xFF), b(0xFF) { } // default to pure white if values aren't specified

    ~RGBA() { }

    string toHex();

};

class Vector2 {
public:
    uint32_t x;
    uint32_t y;

    Vector2() {
        (*this).x = 0;
        (*this).y = 0;
    }    
    Vector2(uint32_t x, uint32_t y ) {
        (*this).x = x;
        (*this).y = y;
    }
};

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} rect;

typedef struct {
    int x;
    int y;
} vec2;

const RGBA color_transparency = RGBA(0x00, 0x00, 0x00, 0x00);
const RGBA color_black = RGBA(0x00, 0x00, 0x00, 0xFF);
const RGBA color_red = RGBA(0xFF, 0x00, 0x00, 0xFF);
const RGBA color_green = RGBA(0x00, 0xFF, 0x00, 0xFF);
const RGBA color_blue = RGBA(0x00, 0x00, 0xFF, 0xFF);
const RGBA color_cyan = RGBA(0x00, 0xFF, 0xFF, 0xFF);
const RGBA color_magenta = RGBA(0xFF, 0x00, 0xFF, 0xFF);
const RGBA color_yellow = RGBA(0xFF, 0xFF, 0x00, 0xFF);
const RGBA color_gray = RGBA(0x77, 0x77, 0x77, 0xFF);
const RGBA color_light_gray = RGBA(0xED, 0xED, 0xED, 0xFF);
const RGBA color_white = RGBA(0xFF, 0xFF, 0xFF, 0xFF);

// front-buffer, grabbed from Multiboot information
void init_fbe(multiboot_info_t * mb_info);
void test_surfaces();

void update_buffer(bool fullRefresh = true);

void putpx(size_t x, size_t y, RGBA color);
void setpx(size_t x, size_t y, RGBA col);

void       draw_circle(const uint32_t x, const uint32_t y,
                                      uint16_t radius, RGBA color);
void       fill_circle(const uint32_t x, const uint32_t y,
                                      uint16_t radius, RGBA color);

extern unsigned int frame_width, frame_height, frame_depth, frame_pitch;
extern uint8_t     *fb_loc;
extern uint8_t     *bb_loc; // back-buffer
extern bool        *dirty_lines;

// Font drawing and display functions
void drawchar_transparent( unsigned char c, int x, int y, RGBA fgcolor);