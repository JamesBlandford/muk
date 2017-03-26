#pragma once

#include <stddef.h>

#define KEYBOARD_BUFFER_SIZE 512

unsigned char inb_kbr(uint16_t port);
void outb_kbr(uint16_t port, uint8_t val);

void keyboard_handler(void);
void keyboard_install(void);

char getc(); // Get Char
char * getsn(char * str, size_t max); // get user input and sent it to tty