#ifndef RTT_H
#define RTT_H
#include "item.h"
#include "graph.h"

typedef struct rtt RTT;

RTT* CriaRTT( int idno1, int  idno2, double valor);

void imprimeRTT(RTT *rtt);

int retornaIdaRTT(RTT * rtt);

int retornaVoltaRTT(RTT * rtt);

double retornaDistancia(RTT *rtt);

Item * calculaRTT(Graph *graph,int nVert, int nServ, int nClient, int nMonitor);

#endif