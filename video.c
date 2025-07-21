#include <video.h>

struct pixel *frame_buffer_base;
UINT32 frame_buffer_size;
UINT32 width;
UINT32 height;
UINT32 pixel_format;

static void plot_pixel(struct pixel pixel,
                       UINTN x, UINTN y)
{
  struct pixel *dest_pixel = &frame_buffer_base[y * width + x];
  dest_pixel->red = pixel.blue;
  dest_pixel->green = pixel.green;
  dest_pixel->blue = pixel.red;
}

static void plot_square(struct pixel pixel,
                        UINTN x, UINTN y)
{
  UINTN new_x = x * 2, new_y = y * 2;
  plot_pixel(pixel, new_x, new_y);
  plot_pixel(pixel, new_x, new_y + 1);
  plot_pixel(pixel, new_x + 1, new_y);
  plot_pixel(pixel, new_x + 1, new_y + 1);
}

void video_plot_frame(struct pixel *frame_buffer,
                      UINTN frame_width,
                      UINTN frame_height)
{
  UINTN i, j = 0;
  for(i = 0; i < frame_height; i++)
  {
    for(j = 0; j < frame_width; j++)
      plot_square((struct pixel) frame_buffer[i * frame_width + j],
                  j, i + ((height / 2 - frame_height) / 2));
  }
}

EFI_STATUS video_init(VOID)
{
  EFI_STATUS status;

  EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop_interface;
  status = BS->LocateProtocol(&gop_guid, 0, (VOID **) &gop_interface);

  if(EFI_ERROR(status))
    return status;

  UINTN size_of_info;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
  status = gop_interface->QueryMode(gop_interface, 1, &size_of_info, &info);
  if(EFI_ERROR(status))
    return status;

  status = gop_interface->SetMode(gop_interface, 1);
  if(EFI_ERROR(status))
    return status;

  frame_buffer_base = (void *) gop_interface->Mode->FrameBufferBase;
  frame_buffer_size = gop_interface->Mode->FrameBufferSize;
  width = info->HorizontalResolution;
  height = info->VerticalResolution;
  pixel_format = info->PixelFormat;

  return EFI_SUCCESS; 
}
