#include <env.h>
#include <malloc.h>
#include <str.h>
#include <string.h>
#include <dprintf.h>

char *env_buffer;
int offset;

char *getenv(const char *name)
{
  CHAR16 *name16 = malloc((str_len(name) + 1) * 2);
  str_ascii_to_utf16(name16, name);

  UINT8 *buffer = env_buffer;
  UINTN buffer_size = 4096;
  EFI_GUID var_guid = ANT_BOOT_VAR_GUID; 
  RS->GetVariable(name16,
                  &var_guid,
                  0,
                  &buffer_size,
                  buffer);
  buffer += offset;
  offset += buffer_size;
  free(name16);

  return buffer;
}

int setenv(const char *name, const char *value)
{
  CHAR16 *name16 = malloc((str_len(name) + 1) * 2);
  str_ascii_to_utf16(name16, name);
  
  EFI_GUID var_guid = ANT_BOOT_VAR_GUID; 
  RS->SetVariable(name16,
                  &var_guid,
                  2,
                  str_len(value) + 1,
                  (void *) value);
}

void env_init(void)
{
  env_buffer = malloc(4096);
  setenv("DOOMWADDIR", "/doom1.wad");
  setenv("HOME", ".");
}

void env_end(void)
{
  free(env_buffer);
}
