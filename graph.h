#ifndef GRAPH_H
#define GRAPH_H

typedef struct adjListNo AdjListNo;

typedef struct adjList AdjList;

typedef struct graph Graph;

AdjListNo *newAdjListNo(int dest, double weight, int tipo);

AdjListNo *getHead(Graph *graph, int indice);
int getDest(AdjListNo *head);

double getWeight(AdjListNo *head);

AdjListNo *getNext(AdjListNo *head);

Graph *createGraph(int V, int E, int *servidor, int *cliente, int *monitor, int *v);

void addEdge(Graph *graph, int src, int dest, double weight, int tipoSrc, int tipoDest);

void printGraph(Graph *graph, int nServ, int nCliente, int nMonitor);

int retornaVertice(Graph *graph);

int *retornaServidor(Graph *graph);

int *retornaCliente(Graph *graph);

int *retornaMonitor(Graph *graph);

int *retornaV(Graph *graph);

void destroiNode(AdjListNo *node);

void destroiEdges(Graph *graph);

void destroiGraph(Graph * graph);

#endif