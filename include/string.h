#ifndef _STRING_H_
#define _STRING_H_

#include <efi.h>

INTN memcmp(const VOID *, const VOID *, INTN);
UINTN strlen(const CHAR16 *);
INTN strcmp(const CHAR16 *, const CHAR16 *);
INTN strncmp(const CHAR16 *, const CHAR16 *, UINTN);
VOID *strcpy(CHAR16 *, const CHAR16 *);
VOID *strcat(CHAR16 *, const CHAR16 *);
VOID *strrev(CHAR16 *str);
VOID *memset(VOID *, UINTN, UINTN);
VOID *memcpy(VOID *, const VOID *, UINT64);
VOID uitoh(CHAR16 *, UINT64);
VOID itos(CHAR16 *, INTN);

#endif
