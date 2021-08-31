#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct adjListNo
{
	int dest;
	double weight;
	int tipo;
	AdjListNo *next;
};

struct adjList
{
	AdjListNo *head;
};

struct graph
{
	int V;
	int E;
	int* scm[3];
	int *v;
	AdjList *array;
};

Graph *criaGraph(int V, int E, int * servidor, int *cliente, int *monitor, int* v)
{
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->scm[0] = servidor;
    graph->scm[1] = cliente;
    graph->scm[2] = monitor;
	graph->v = v;

	graph->array = (AdjList *)malloc(V * sizeof(AdjList));

	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

int getDest(AdjListNo *head){
	return head->dest;
}
double getWeight(AdjListNo *head){
	return head->weight;
}
AdjListNo *getNext(AdjListNo *head){
	return head->next;
}

AdjListNo *retornaCabeca(Graph *graph, int indice){
	return graph->array[indice].head;
};

AdjListNo *novoNoLista(int dest, double weight, int tipo)
{
	AdjListNo *newNode = (AdjListNo *)malloc(sizeof(AdjListNo));

	newNode->dest = dest;
	newNode->weight = weight;
	newNode->tipo = tipo;
	newNode->next = NULL;

	return newNode;
}


void addAresta(Graph *graph, int src, int dest, double weight, int tipodest)
{

	AdjListNo *newNode = novoNoLista(dest, weight, tipodest);

	newNode->next = graph->array[src].head;

	graph->array[src].head = newNode;
}

void printGraph(Graph *graph, int nServ, int nCliente, int nMonitor){

	AdjListNo *aux;
	printf("%d\n", graph->V);
	printf("%d\n", graph->E);

	for (int i = 0; i < graph->V; i++)
	{

		for (aux = graph->array[i].head; aux != NULL; aux = aux->next)
		{
			printf("IdSrc: %d, Iddest: %d weight: %lf\n", i, aux->dest, aux->weight);
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
	return graph->scm[0];
}

int * retornaCliente(Graph *graph){
	return graph->scm[1];
}

int * retornaMonitor(Graph *graph){
	return graph->scm[2];
}

int *retornaV(Graph* graph){
	return graph->v;
}

void destroiNode(AdjListNo *node) {
	AdjListNo *aux = NULL;
	while(node != NULL){
		aux = node->next;
		free(node);
		node = aux;
	}
}

void destroiEdges(Graph *graph) {
	for(int i=0; i < graph->V; i++){
		destroiNode(graph->array[i].head);
	}
}

void destroiGraph(Graph * graph){
	destroiEdges(graph);
	free(graph->array);
	free(graph);
}

