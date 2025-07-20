#include "env.h"

char *getenv(const char *name)
{
  char *str = malloc(10);
  int i;
  for(i = 0; i < 10; i++)
  {
    str[i] = "doom1.wad"[i];
  }

  return str;
}
