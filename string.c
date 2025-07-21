#include <string.h>

INTN memcmp(const VOID *buf1, const VOID *buf2, INTN count)
{
  const UINT8 *p = buf1;
  const UINT8 *q = buf2;

  while(count--)
  { 
    if(*p++ != *q++)
      return p[-1] < q[-1] ? -1 : 1;  
  } 
    
  return 0;
}

VOID *memcpy(VOID *dest, const VOID *src, UINT64 n)
{
  UINT8 *p = dest;
  const UINT8 *q = src;

  while(n--)
    *p++ = *q++;;

  return dest;
}

UINTN strlen(const CHAR16 *str)
{
  const CHAR16 *p = str - 1;

  while(*++p);

  return p - str;
}

INTN strcmp(const CHAR16 *s1, const CHAR16 *s2)
{
  UINTN s1_len = strlen(s1);
  UINTN s2_len = strlen(s2);
  if(s1_len < s2_len)
    return -1;
  else if (s1_len > s2_len)
    return 1;

  return memcmp(s1, s2, s1_len * sizeof(CHAR16));
}

INTN strncmp(const CHAR16 *s1, const CHAR16 *s2, UINTN n)
{
  return memcmp(s1, s2, n * sizeof(CHAR16));
}

VOID *strcpy(CHAR16 *dest, const CHAR16 *src)
{
  return memcpy(dest, src, (strlen(src) + 1) * sizeof(CHAR16));
}

VOID *strcat(CHAR16 *dest, const CHAR16 *src)
{
  strcpy(dest + strlen(dest), src);

  return dest;
}

VOID *strrev(CHAR16 *str)
{
  CHAR16 *p, *q, c;

  p = str;
  q = str + strlen(str) - 1;
  while(q > p)
  {
    c = *q;
    *q-- = *p;
    *p++ = c;
  }

  return str;
}

VOID *memset(VOID *s, UINTN c, UINTN size)
{
  UINT8 *p = s;
  while(size-- > 0)
    *p++ = c;

  return s;
}

VOID uitoh(CHAR16 *dest, UINT64 number)
{
  INT8 i = 60;
  BOOLEAN left_zero = 1;
  CHAR16 c;

  if(number == 0)
  {
    *dest++ = '0';
    *dest = '\0';
    return;
  }

  while(i != -4)
  {
    c = (number >> i) & 0xf;
    if(!(c) && left_zero)
    {
      i -= 4;
      continue;
    }
    else
      left_zero = 0;

    if(c >= 0 && c <= 9)
      c += L'0';
    else
      c += 0x37;

    *dest++ = c;
    i -= 4;
  }

  *dest = L'\0';
}

VOID itos(CHAR16 *dest, INTN number)
{
  CHAR16 *p = dest;
  UINT8 is_negative = 0;

  if(number < 0)
  {
    number = -number;
    is_negative = 1;
  }

  do
  {
    *p++ = number % 10 + L'0';
    number /= 10;
  } 
  while (number);
  
  if(is_negative)
    *p++ = L'-';

  *p = L'\0';
  strrev(dest);
}
