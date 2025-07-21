#include <efi.h>
#include <malloc.h>
#include <dprintf.h>
#include <file.h>
#include <env.h>
#include <video.h>
#include <gettime.h>
#include <kb.h>
#define DOOM_IMPLEMENTATION
#include "PureDOOM/PureDOOM.h"

EFI_SYSTEM_TABLE *ST;
EFI_HANDLE IH;
EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RS;

static VOID exit(UINTN status)
{
  BS->Exit(IH, 1, 0, NULL);
}

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;

  ST = system_table;
  IH = image_handle;
  BS = ST->BootServices;
  RS = ST->RuntimeServices;

  video_init();
  kb_init();

  doom_set_print((void *) dprintf);
  doom_set_malloc((void *) malloc, (void *) free);

  file_init_file_protocol();
  doom_set_file_io((void *) fopen,
                   (void *) fclose,
                   (void *) fread,
                   (void *) fwrite,
                   (void *) fseek,
                   (void *) ftell,
                   (void *) feof);
  doom_set_exit((void *) exit);
  doom_set_gettime((void *) gettime);
  doom_set_getenv((void *) getenv);
  
  int argc = 1;
  char *argv[] = {"bootx64.efi"};
  doom_init(argc, argv, DOOM_FLAG_MENU_DARKEN_BG);
  
  ST->ConOut->ClearScreen(ST->ConOut);
  doom_key_t doom_key = 0, last_doom_key = 0;
  while(1)
  {
    CHAR16 key = kb_wait_for_key(); 
    switch(key)
    {
      case L's':
        doom_key = DOOM_KEY_DOWN_ARROW;
        break;
      case L'w':
        doom_key = DOOM_KEY_UP_ARROW;
        break;
      case L'a':
        doom_key = DOOM_KEY_LEFT_ARROW;
        break;
      case L'd':
        doom_key = DOOM_KEY_RIGHT_ARROW;
        break;
      case 0xd:
        doom_key = DOOM_KEY_ENTER;
        break;
      default:
        doom_key = 0;
    }
    
    if(EFI_ERROR(kb_check_event()))
      doom_key_down(doom_key);
    doom_update();
    UINT32 *framebuffer = (UINT32 *) doom_get_framebuffer(4);
    video_plot_frame((struct pixel *) framebuffer, 320, 200);
    if(last_doom_key != doom_key)
    {
      doom_key_up(last_doom_key);
      last_doom_key = doom_key;
    }
  }

  return EFI_SUCCESS;
}
