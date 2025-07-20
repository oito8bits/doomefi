#ifndef _VIDEO_INCLUDE_
#define _VIDEO_INCLUDE_

#include <libefi.h>

struct pixel
{
  unsigned red: 8;
  unsigned green: 8;
  unsigned blue: 8;
  unsigned reserved: 8;
} __attribute__((packed));

VOID video_plot_frame(struct pixel *,
                    UINTN, UINTN);
EFI_STATUS video_init(VOID);

#endif
