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
FILE *file_open(const char *, const char *);
int file_close(FILE *);
int file_read(FILE *, void *, int);
int file_write(FILE *, const void *, int);
int file_seek(FILE *, long, int);
long file_tell(FILE *);
int file_eof(FILE *);

#endif
