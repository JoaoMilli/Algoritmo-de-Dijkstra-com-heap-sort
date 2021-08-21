#ifndef RTT_H
#define RTT_H
#include "item.h"

typedef struct rtt RTT;

RTT* CriaRTT(Item** vetor, int size,double ida, double volta, int i, int j);

void imprimeRTT(RTT *rtt);

Item * retornaIdaRTT(RTT * rtt);

Item * retornaVoltaRTT(RTT * rtt);

double retornaDistancia(RTT *rtt);
#endif