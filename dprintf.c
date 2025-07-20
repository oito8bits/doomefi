#include "dprintf.h"
#include "str.h"
#include <stdarg.h>

int dprintf(const char *format, ...)
{
/*
  CHAR16 *format16 = malloc(str_len(format) * sizeof(CHAR16));
  str_ascii_to_utf16(format16, format);
  
  va_list arg;
  va_start(arg, format);
  printf(format16, arg);
  va_end(arg);
*/
  return 0;
}
