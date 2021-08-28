#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct adjListNode
{
	int dest;
	double weight;
	int tipo;
	AdjListNode *next;
};

struct adjList
{
	AdjListNode *head;
};

struct graph
{
	int V;
	int E;
	int* csm[3];
	int *v;
	AdjList *array;
};

int getDest(AdjListNode *head){
	return head->dest;
}
double getWeight(AdjListNode *head){
	return head->weight;
}
AdjListNode *getNext(AdjListNode *head){
	return head->next;
}

AdjListNode *getHead(Graph * graph, int indice){
	return graph->array[indice].head;
};

AdjListNode *newAdjListNode(int dest, double weight, int tipo)
{
	AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));

	newNode->dest = dest;
	newNode->weight = weight;
	newNode->tipo = tipo;
	newNode->next = NULL;

	return newNode;
}

Graph *createGraph(int V, int E, int * servidor, int *cliente, int *monitor, int* v)
{
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->csm[0] = servidor;
    graph->csm[1] = cliente;
    graph->csm[2] = monitor;
	graph->v = v;

	graph->array = (AdjList *)malloc(V * sizeof(AdjList));

	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

void addEdge(Graph *graph, int src, int dest, double weight, int tipoSrc, int tipoDest)
{

	AdjListNode *newNode = newAdjListNode(dest, weight, tipoDest);

	//faz o newnode apontar para o começo da lista array[src]
	newNode->next = graph->array[src].head;

	//o começo da lista array[src] aponta para newNode
	graph->array[src].head = newNode;

	// newNode = newAdjListNode(src, weight, tipoSrc);
	// newNode->next = graph->array[dest].head;
	// graph->array[dest].head = newNode;
}

void printGraph(Graph *graph, int nServ, int nCliente, int nMonitor){

	AdjListNode *aux;
	printf("%d\n", graph->V);
	printf("%d\n", graph->E);

	for (int i = 0; i < graph->V; i++)
	{

		for (aux = graph->array[i].head; aux != NULL; aux = aux->next)
		{
			printf("IdSrc: %d, IdDest: %d weight: %lf\n", i, aux->dest, aux->weight);
		}
	}
	int *monitor = retornaMonitor(graph);
	int *servidor = retornaServidor(graph);
	int *cliente = retornaCliente(graph);
	printf("Servidor\n");
	for(int i=0 ; i < nServ; i++){
		printf("%d ", servidor[i]);
	}

	printf("\nMonitor\n");
	for(int i=0 ; i < nMonitor; i++){
		printf("%d ", monitor[i]);
	}
	printf("\nClientes\n");
	for(int i=0 ; i < nCliente; i++){
		printf("%d ", cliente[i]);
	}
	printf("\n");
}


int retornaVertice(Graph *graph){
	return graph->V;
}



int * retornaServidor(Graph *graph){
	return graph->csm[0];
}

int * retornaCliente(Graph *graph){
	return graph->csm[1];
}

int * retornaMonitor(Graph *graph){
	return graph->csm[2];
}

int *retornaV(Graph* graph){
	return graph->v;
}
