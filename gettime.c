#include <gettime.h>

UINT64 _usec;

void gettime(int *sec, int *usec)
{
  EFI_TIME time;
  EFI_TIME_CAPABILITIES time_cap;
  RS->GetTime(&time, &time_cap);

  *sec = time.Hour * 3600 + time.Minute * 60 + time.Second;
  _usec += 5000;
  if(_usec >= 1000000)
    _usec = 0;
  *usec = _usec;
}
