#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <efi.h>

int console_ascii_printf(const char *, ...);
VOID console_puts(const CHAR16 *);
VOID console_putchar(CHAR16);
INTN console_printf(const CHAR16 *, ...);

#endif
