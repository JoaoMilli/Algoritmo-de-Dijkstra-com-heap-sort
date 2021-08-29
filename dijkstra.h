#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct rtt RTT;

double *dijkstra(Graph *graph, int src, int *d1, int *d2, int nd1, int nd2);

#endif