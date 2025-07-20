#ifndef _KB_H_
#define _KB_H_

#include <libefi.h>

CHAR16 kb_wait_for_key(VOID);
EFI_STATUS kb_check_event(VOID);
VOID kb_init(VOID);

#endif
