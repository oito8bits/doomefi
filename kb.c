#include <kb.h>

CHAR16 kb_wait_for_key(VOID)
{
  EFI_INPUT_KEY key;
  ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
 
  return key.UnicodeChar; 
}

EFI_STATUS kb_check_event(VOID)
{
  return BS->CheckEvent(&ST->ConIn->WaitForKey);
}

VOID kb_init(VOID)
{
  UINTN index;
  BS->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
}
