#ifndef _MEM_H_
#define _MEM_H_

#include <efi.h>

VOID *mem_malloc(UINTN);
VOID mem_free(VOID *);

#endif
