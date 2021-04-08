#include "clock.h"

Clock::Clock(int unixtime)
{
    timeval tv;//Cria a estrutura temporaria para funcao abaixo.
    tv.tv_sec = unixtime;//Atribui minha data atual. Voce pode usar o NTP para isso ou o site citado no artigo!
    settimeofday(&tv, NULL);
}

String Clock::getTime(){
    struct tm timeinfo;
    
    getLocalTime(&timeinfo, 0);

    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
return "";
}
