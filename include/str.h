#ifndef _STR_H_
#define _STR_H_

#include <efi.h>

INTN str_memcmp(const VOID *, const VOID *, INTN);
UINTN str_strlen(const CHAR16 *);
INTN str_strcmp(const CHAR16 *, const CHAR16 *);
INTN str_strncmp(const CHAR16 *, const CHAR16 *, UINTN);
VOID *str_strcpy(CHAR16 *, const CHAR16 *);
VOID *str_strcat(CHAR16 *, const CHAR16 *);
VOID *str_strrev(CHAR16 *str);
VOID *str_memset(VOID *, UINTN, UINTN);
VOID *str_memcpy(VOID *, const VOID *, UINT64);
VOID str_uitoh(CHAR16 *, UINT64);
VOID str_itos(CHAR16 *, INTN);

#endif
