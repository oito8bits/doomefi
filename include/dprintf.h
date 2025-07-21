#ifndef _DPRINTF_H_
#define _DPRINTF_H_

#include <efi.h>

int dprintf(const char *, ...);
VOID puts(const CHAR16 *);
VOID putchar(CHAR16);
INTN printf(const CHAR16 *, ...);

#endif
