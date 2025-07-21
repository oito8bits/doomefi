#ifndef _FILE_H_
#define _FILE_H_

#include <stddef.h>
#include <efi.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef EFI_FILE_PROTOCOL FILE;

UINTN get_file_size(FILE *);
EFI_STATUS file_init_file_protocol(void);
FILE *fopen(const char *, const char *);
int fclose(FILE *);
INTN fread(FILE *, void *, int);
INTN fwrite(FILE *, const void *, int);
int fseek(FILE *, long, int);
long ftell(FILE *);
int feof(FILE *);

#endif
