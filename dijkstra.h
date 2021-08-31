#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/*
*  Algoritmo de Dijkstra implementado com heap
*  inputs: um graph, um inteiro indicando a origem, dois ponteiros de inteiro 
*  indicando os dois grupos (servidores, clientes ou monitores)  e os tamanhos
*  output: retorna um ponteiro de double com as distancias
*  pre-condicao: O Graph e os ponteiros de inteiro devem estar devidamente inicializados
*/

double *dijkstra(Graph *graph, int src);

#endif