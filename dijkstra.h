#include "item.h"
#include "aresta.h"
#include "PQ.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

void relax(Item** pq, int* N, int* map, Aresta* e, double* distTo, Aresta** edgeTo);
void dijkstra(int nVert, int *map, int N, Item** listaV, double* distTo,int nEdge, Aresta** edgeTo,Aresta** todasArestas, int ID);
int PQ_contains(Item** pq, int* N, int ID);

#endif