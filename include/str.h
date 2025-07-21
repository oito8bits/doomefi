#ifndef _STR_H_
#define _STR_H_

#include <efi.h>

INTN str_len(const char *);
VOID str_ascii_to_utf16(CHAR16 *, const char *);

#endif
