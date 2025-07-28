#ifndef _ENV_H_
#define _ENV_H_

#include <efi.h>

char *env_get(const char *);
int env_set(const char *, const char *);
void env_init(void);
void env_end(void);

#endif
