#ifndef _ASCII_H_
#define _ASCII_H_

#include <efi.h>

INTN ascii_strlen(const char *);
VOID ascii_to_utf16(CHAR16 *, const char *);

#endif
