#include <gettime.h>

void gettime(int *sec, int *usec)
{
  EFI_TIME time;
  EFI_TIME_CAPABILITIES time_cap;
  RS->GetTime(&time, &time_cap);

  *sec = time.Second;
  *usec += time.Second * 1000000;
}
