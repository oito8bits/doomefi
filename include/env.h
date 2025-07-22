#ifndef _ENV_H_
#define _ENV_H_

#include <efi.h>

char *getenv(const char *);
int setenv(const char *, const char *);
void env_init(void);
void env_end(void);

#endif
