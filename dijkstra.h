#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "heap.h"
#include "graph.h"
#include "item.h"

double *dijkstra(Graph *graph, int src, int *d1, int *d2, int nd1, int nd2);
#endif