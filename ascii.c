#include <ascii.h>

INTN ascii_strlen(const char *str)
{
  const char *p = str - 1;
  
  while(*++p);
  
  return p - str;
}

VOID ascii_to_utf16(CHAR16 *dest, const char *str)
{
  while(*dest++ = *str++);
}
