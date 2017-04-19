#include <stddef.h>
#include <std.hpp>

#include <kernel/cpu.hpp>

uint8_t inportb (uint16_t port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outportb (uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

uint16_t inports (uint16_t port) {
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outports (uint16_t port, uint16_t data) {
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

uint32_t inportl (uint16_t port) {
    uint32_t rv;
    __asm__ __volatile__ ("inl %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outportl (uint16_t port, uint32_t data) {
      __asm__ __volatile__ ("outl %1, %0" : : "dN" (port), "a" (data));
}

__attribute__((noreturn)) inline void halt() {
    interrupts_disable();
    while (true) {
        __asm__ __volatile__ ("hlt");
    }
}

void BochsConsolePrint(char *s){
    do {
        outportb(0xe9 ,*s);
        s++;
    } while( *s != 0);
}

void bcprintf(const char* fmt, ...) {
	va_list parameters;
	char temp_buffer[80] = {0};

	va_start(parameters, fmt);
	vsprintf(temp_buffer, fmt, parameters);
	BochsConsolePrint((char*)temp_buffer);
	va_end(parameters);
}