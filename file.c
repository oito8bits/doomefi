#include "file.h"
#include "str.h"

EFI_FILE_PROTOCOL *root;

static VOID convert_path(CHAR16 *path)
{
  UINTN i;
  for(i = 0; i < strlen(path); i++)
  {
    if(path[i] == '/')
      path[i] = '\\';
  }
}

UINTN get_file_size(FILE *stream)
{
  EFI_GUID file_info_id = EFI_FILE_INFO_ID;
  EFI_FILE_INFO file_info;
  UINTN buffer_size = sizeof(EFI_FILE_INFO);
  stream->GetInfo(stream,
                  &file_info_id,
                  &buffer_size,
                  &file_info);

  return file_info.FileSize;
}

EFI_STATUS file_init_file_protocol(void)
{
  EFI_STATUS status;

  EFI_GUID fs_protocol_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *device;
  status = BS->LocateProtocol(&fs_protocol_guid,
                              0,
                              (VOID **) &device);

  if(EFI_ERROR(status))
    return status;

  EFI_FILE_PROTOCOL *rootp;
  status = device->OpenVolume(device, &rootp);
  if(EFI_ERROR(status))
    return status;

  root = rootp;

  return EFI_SUCCESS;
}

FILE *fopen(const char *pathname, const char *mode)
{
  EFI_STATUS status;

  CHAR16 *pathname16 = malloc((str_len(pathname) + 1) * sizeof(CHAR16));
  str_ascii_to_utf16(pathname16, pathname);
  convert_path(pathname16);
  EFI_FILE_PROTOCOL *stream;
  status = root->Open(root,
                      &stream,
                      (CHAR16 *) pathname16,
                      EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
                      EFI_FILE_ARCHIVE);
  if(EFI_ERROR(status))
    stream = 0;
  
  free(pathname16);

  return stream;
}

int fclose(FILE *stream)
{
  stream->Close(stream);
}

INTN fread(FILE *stream, void *ptr, int size)
{
  EFI_STATUS status;
  UINTN file_size = size;
  status = stream->Read(stream, &file_size, (void *) ptr);
  if(EFI_ERROR(status))
    return 0;
  
  return size;
}

INTN fwrite(FILE *stream, const void *ptr, int size)
{
  EFI_STATUS status;
  UINTN file_size = size;
  status = stream->Write(stream, &file_size, (void *) ptr);
  if(EFI_ERROR(status))
    return 0;

  return size;
}

int fseek(FILE *stream, long offset, int whence)
{
  EFI_STATUS status;
  INTN position = ftell(stream); 
  switch(whence)
  {
    case SEEK_SET:
      position = offset;
      break;
    case SEEK_CUR:
      position += offset;
      break;
    case SEEK_END:
      position = 4196020 + offset;
      break;
  }
  
  stream->SetPosition(stream, position);
}

long ftell(FILE *stream)
{
  INTN position;
  stream->GetPosition(stream, &position);
  return position;
}

int feof(FILE *stream)
{
  INTN position = ftell(stream);
  printf(L"File size: %i\n", get_file_size(stream));
  if(position >= get_file_size(stream))
    return 1;
  return 0;
}
