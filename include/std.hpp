#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <std/cstdlib.hpp>

#include <std/ctype.hpp>
#include <std/string.hpp>
#include <std/vector.hpp>

// C++ dynamic memory allocation operators
void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);

// C++ placement operators (for rigid memory allocation)
inline void *operator new(size_t, void *p)     throw() { return p; }
inline void *operator new[](size_t, void *p)   throw() { return p; }
inline void  operator delete  (void *, void *) throw() { };
inline void  operator delete[](void *, void *) throw() { };

// "String" functions

char *strcat(char *dest, const char *source);

int strncmp(const char *s1, const char *s2, size_t n);
char * strstr(char *string, char *substring);
char * strdup(const char *s1);
char * strpbrk(const char *s, const char *accept);
size_t strspn (const char *s, const char *accept);
char * strtok(char *str, const char *delim);
char tolower(char upper);

int putchar(int);

//int printf(const char* __restrict, ...);
int sprintf(char* buffer, const char* fmt, ...);
int vsprintf(char* buffer, const char* format, va_list parameters);

// Long-functions
ldiv_t ldiv (unsigned long numerator, unsigned long denominator );
char* ltoa(unsigned long long value, char* buffer, int radix );

// Integer functions
int itoa(int value, char *sp, int radix);
int atoi(char* str);

long strtol(const char *nptr, char **endptr, int base);

__attribute__((weak))
void abort();