#include <env.h>
#include <mem.h>
#include <str.h>
#include <ascii.h>

char *env_buffer;
int offset;

char *env_get(const char *name)
{
  CHAR16 *name16 = mem_malloc((ascii_strlen(name) + 1) * 2);
  ascii_to_utf16(name16, name);

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
  mem_free(name16);

  return buffer;
}

int env_set(const char *name, const char *value)
{
  CHAR16 *name16 = mem_malloc((ascii_strlen(name) + 1) * 2);
  ascii_to_utf16(name16, name);
  
  EFI_GUID var_guid = ANT_BOOT_VAR_GUID; 
  RS->SetVariable(name16,
                  &var_guid,
                  2,
                  ascii_strlen(value) + 1,
                  (void *) value);
}

void env_init(void)
{
  env_buffer = mem_malloc(4096);
  env_set("DOOMWADDIR", "/doom1.wad");
  env_set("HOME", ".");
}

void env_end(void)
{
  mem_free(env_buffer);
}
