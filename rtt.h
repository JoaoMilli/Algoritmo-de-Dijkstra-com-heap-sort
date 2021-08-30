#ifndef RTT_H
#define RTT_H
#include "item.h"
#include "graph.h"
#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct rtt RTT;

RTT *CriaRTT(int idno1, int idno2, double valor);

void imprimeRTT(RTT *rtt);

void imprimeListaRTT(FILE *file, RTT *lista, int tam);

int retornaIdaRTT(RTT *rtt);

int retornaVoltaRTT(RTT *rtt);

double retornaDistancia(RTT *rtt);

RTT *calculaRTT(Graph *graph, int nVert, int nServ, int nClient, int nMonitor);

double **criaMatriz(Graph *graph, int tam, int *src, int *d1, int *d2, int nd1, int nd2);

void destroiMatriz(double ** matriz, int l);

void destroiListaRTT(RTT *lista);

#endif