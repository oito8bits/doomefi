#include <mem.h>
#include <string.h>

VOID *mem_malloc(UINTN size)
{
  VOID *buffer;
  EFI_STATUS status;

  status = BS->AllocatePool(EfiRuntimeServicesData, size, &buffer);

  if(status != EFI_SUCCESS)
    return 0;

  return buffer;
}

VOID mem_free(VOID *buffer)
{
  BS->FreePool(buffer);
}
