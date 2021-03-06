#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include <kernel/proc/mutex.hpp>
#include <kernel/gfx/vga.hpp>
#include <kernel/gfx/buffer.hpp>

#define TAB_WIDTH 12

extern volatile size_t terminal_row;
extern volatile size_t terminal_column;
extern uint16_t* terminal_buffer;

extern const int X_FONTWIDTH;
extern const int Y_FONTWIDTH; 

extern Process::SpinlockMutex print_mutex;

void init_tty();
void tty_update();
void terminal_scrollup();
void terminal_clearline(size_t y);
void terminal_writestring(char* data, Graphics::RGB colour = Graphics::RGB(0xFFFFFF));
void terminal_putentryat(char c, size_t x, size_t y, Graphics::RGB colour = Graphics::RGB(0xFFFFFF));
void terminal_putchar(char c, Graphics::RGB colour = Graphics::RGB(0xFFFFFF));

void terminal_printf(const char* fmt, ...);
void terminal_printf_rgba(const char* fmt, Graphics::RGB color, ...);

void update_cursor(int row, int col);

size_t tty_get_cursor_x();
void tty_set_cursor_x(size_t x);

void parse(char buffer[1024]);