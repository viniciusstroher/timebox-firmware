#include "clock.h"

Clock::Clock(int unixtime)
{
    timeval tv;
    tv.tv_sec = unixtime;
    settimeofday(&tv, NULL);
}

String Clock::getTime(){
    struct tm timeinfo;
    
    getLocalTime(&timeinfo, 0);
    
    char * formatedTime = "%Y-%m-%d %H:%M:%S";
    
    char formatedRtcTime[32];
    strftime(formatedRtcTime, sizeof formatedRtcTime, formatedTime, &timeinfo); 

    return formatedRtcTime;
}
