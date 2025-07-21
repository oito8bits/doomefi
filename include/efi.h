#ifndef _EFI_INCLUDE_
#define _EFI_INCLUDE_

#include "efidef.h"
#include "eficon.h"
#include "efiapi.h"
#include "efigop.h"
#include "efiprot.h"
#include "efierr.h"

extern EFI_SYSTEM_TABLE *ST;
extern EFI_HANDLE IH;
extern EFI_BOOT_SERVICES *BS;
extern EFI_RUNTIME_SERVICES *RS;

#define ANT_BOOT_VAR_GUID \
  {0xbd539872, 0x0fea, 0x4580, {0x90, 0xad, 0x1a, 0x4a, 0x6e, 0x27, 0x0d, 0xdb}}

#endif
