#include "clock.h"

Clock::Clock(int unixtime)
{
    timeval tv;//Cria a estrutura temporaria para funcao abaixo.
    tv.tv_sec = unixtime;//Atribui minha data atual. Voce pode usar o NTP para isso ou o site citado no artigo!
    settimeofday(&tv, NULL);
}

String Clock::getTime(){
  time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
  data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
  
  char data_formatada[64];
  strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
//  printf("\nUnix Time: %d\n", int32_t(tt));//Mostra na Serial o Unix time
  printf("\n[info] Data formatada: %s\n", data_formatada);
  return data_formatada;
}
