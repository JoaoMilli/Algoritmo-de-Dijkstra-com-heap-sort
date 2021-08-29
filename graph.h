#ifndef GRAPH_H
#define GRAPH_H

typedef struct adjListNode AdjListNode;

typedef struct adjList AdjList;

typedef struct graph Graph;

AdjListNode *newAdjListNode(int dest, double weight, int tipo);
AdjListNode *getHead(Graph *graph, int indice);
int getDest(AdjListNode *head);

double getWeight(AdjListNode *head);

AdjListNode *getNext(AdjListNode *head);

Graph *createGraph(int V, int E, int *servidor, int *cliente, int *monitor, int *v);

void addEdge(Graph *graph, int src, int dest, double weight, int tipoSrc, int tipoDest);

void printGraph(Graph *graph, int nServ, int nCliente, int nMonitor);

int retornaVertice(Graph *graph);

int *retornaServidor(Graph *graph);
int *retornaCliente(Graph *graph);
int *retornaMonitor(Graph *graph);
int *retornaV(Graph *graph);

#endif