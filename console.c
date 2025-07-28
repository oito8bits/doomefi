#include <console.h>
#include <str.h>
#include <stdarg.h>

int console_ascii_printf(const char *format, ...)
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

static VOID put(const CHAR16 *string)
{
  ST->ConOut->OutputString(ST->ConOut, (CHAR16 *) string);
}

static VOID puti(INTN number)
{
  CHAR16 string[21] = {0};
  str_itos(string, number);
  put(string);
}

static VOID print_hex(UINT64 number)
{
  CHAR16 str[17] = {0};
  str_uitoh(str, number);
  put(str);
}

VOID console_puts(const CHAR16 *string)
{
  put(string);
  put(L"\n\r");
}

VOID console_putchar(CHAR16 character)
{
  CHAR16 string[2] = {character, L'\0'};

  ST->ConOut->OutputString(ST->ConOut, string);
}

INTN console_printf(const CHAR16 *format, ...)
{
  va_list vl;

  va_start(vl, format);
  while(*format)
  {
    if(*format == L'%')
    {
      format++;
      switch(*format)
      {
        case L'%':
          console_putchar(L'%');
          break;
        case L'i':
          puti(va_arg(vl, INTN));
          break;
        case L'c':
          console_putchar((CHAR16) va_arg(vl, UINTN));
          break;
        case L's':
          put(va_arg(vl, CHAR16 *));
          break;
        case L'X':
        case L'x':
          print_hex(va_arg(vl, UINT64));
          break;
      }
    }
    else
      console_putchar(*format);

    format++;
  }

  va_end(vl);

  return 0;
}
