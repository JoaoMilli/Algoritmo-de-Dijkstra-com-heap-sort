#ifndef RTT_H
#define RTT_H
#include "item.h"
#include "graph.h"
#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct rtt RTT;

/*
*  Cria um estrutura RTT
*  inputs: o id do no1 e no2 e a distancia calculada no dijkstra
*  output: retorna o ponteiro do RTT
*  pre-condicao: nenhuma
*/

RTT *CriaRTT(int idno1, int idno2, double valor);

/*
*  Imprimme a estrutura RTT
*  inputs: O ponteiro para RTT
*  output: nenhum
*  pre-condicao: O RTT deve esta devidamente inicializado
*/
void imprimeRTT(RTT *rtt);

/*
*  Imprime uma lista de RTT no arquivo de saída
*  inputs: O ponteiro para o arquivo, ponteiro para a lista e o tamanho da lista
*  output: nenhum
*  pre-condicao: O arquivo deve ser previamente aberto e a lista deve estar devidamente inicializada
*/

void imprimeListaRTT(FILE *file, RTT *lista, int tam);

/*
*  Cria o id de ida do RTT
*  inputs: O ponteiro para RTT
*  output: retorna o id
*  pre-condicao: O RTT deve esta devidamente inicializado
*/
int retornaIdaRTT(RTT *rtt);

/*
*  Cria o id de volta do RTT
*  inputs: O ponteiro para RTT
*  output: retorna o id
*  pre-condicao: O RTT deve esta devidamente inicializado
*/
int retornaVoltaRTT(RTT *rtt);

/*
*  Calcula os rtts
*  inputs: Ponteiro para o graph, as quantidades de vertices, servidores, clientes, monitores
*  output: Uma lista de RTTS
*  pre-condicao: O graph deve estar devidamdente inicializado
*/

RTT *calculaRTT(Graph *graph, int nVert, int nServ, int nClient, int nMonitor);

/*
*  Cria e aloca matriz para uma matriz
*  inputs: O ponteiro para o arquivo, ponteiro para a lista e o tamanho da lista
*  output: nenhum
*  pre-condicao: O arquivo deve ser previamente aberto e a lista deve estar devidamente inicializada
*/

double **criaMatriz(Graph *graph, int tam);

/*
*  Libera toda a memoria alocada para a matriz
*  inputs: A matriz e o seu tamanho
*  output: nenhum
*  pre-condicao: A matriz deve existir
*/

void destroiMatriz(double ** matriz, int l);

/*
*  Libera toda a memoria alocada para a lista
*  inputs: Um ponteiro para a lista de RTT
*  output: nenhum
*  pre-condicao: A lista deve existir
*/

void destroiListaRTT(RTT *lista);

#endif