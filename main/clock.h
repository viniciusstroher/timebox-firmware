#include "Arduino.h"

#include <esp_system.h>
#include <time.h>
#include <sys/time.h>



class Clock
{
  public:
    Clock(int unixtime);
    String getTime();
  private:
    struct tm data;
};
