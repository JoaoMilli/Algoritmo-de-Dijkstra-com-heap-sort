#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dijikstra2.h"
#include "PQ.h"
#include "limits.h"
#include <float.h>

// #include "minHeap.h"

//Aresta
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
	AdjList *array;
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

Graph *createGraph(int V, int E)
{
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;

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

// MinHeap
// Structure to represent a min heap node
struct minHeapNode
{
	int v;
	double dist;
};

// Structure to represent a min heap
struct minHeap
{
	int size;
	int capacity;
	int *pos;
	MinHeapNode **array;
};

MinHeapNode *newMinHeapNode(int v, double dist)
{
	MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

MinHeap *createMinHeap(int capacity)
{
	MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
	return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b)
{
	MinHeapNode *t = *a;
	*a = *b;
	*b = t;
}

// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(MinHeap *minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist <
			minHeap->array[smallest]->dist)
		smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist <
			minHeap->array[smallest]->dist)
		smallest = right;

	if (smallest != idx)
	{
		// The nodes to be swapped in min heap
		MinHeapNode *smallestNode = minHeap->array[smallest];
		MinHeapNode *idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if
// the given minHeap is ampty or not
int isEmpty(MinHeap *minHeap)
{
	return minHeap->size == 0;
}

// Standard function to extract
// minimum node from heap
MinHeapNode *extractMin(MinHeap *minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	MinHeapNode *root = minHeap->array[0];

	// Replace root node with last node
	MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

void decreaseKey(MinHeap *minHeap, int v, int dist)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	// Travel up while the complete
	// tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
	{
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;

		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(MinHeap *minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return 1;
	return 0;
}

// A utility function used to print the solution
void printArr(double dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %f\n", i, dist[i]);
}

void dijkstra(Graph *graph, int src, double *dist)
{
	int V = graph->V;

	// minHeap represents set E

	MinHeap *minHeap = createMinHeap(V);

	// Initialize min heap with all
	// vertices. dist value of all vertices
	for (int v = 0; v < V; ++v)
	{
		dist[v] = DBL_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	// Make dist value of src vertex
	// as 0 so that it is extracted first
	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;

	decreaseKey(minHeap, src, dist[src]);

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the followin loop,
	// min heap contains all nodes
	// whose shortest distance
	// is not yet finalized.
	while (!isEmpty(minHeap))
	{
		// Extract the vertex with
		// minimum distance value
		MinHeapNode *minHeapNode = extractMin(minHeap);

		// Store the extracted vertex number
		int u = minHeapNode->v;

		// Traverse through all adjacent
		// vertices of u (the extracted
		// vertex) and update
		// their distance values
		AdjListNode *pCrawl = graph->array[u].head;
		while (pCrawl != NULL)
		{

			int v = pCrawl->dest;

			// If shortest distance to v is
			// not finalized yet, and distance to v
			// through u is less than its
			// previously calculated distance
			if (isInMinHeap(minHeap, v) && dist[u] != DBL_MAX && pCrawl->weight + dist[u] < dist[v])
			{
				//printf("dist u %f\n", dist[u]);
				//printf("pCrawl  %f\n", pCrawl->weight);
				dist[v] = dist[u] + pCrawl->weight;
				//printf("dist v %f\n", dist[v]);
				// update distance
				// value in min heap also
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	// print the calculated shortest distances
	// printArr(dist, V);
}

Graph *leEntrada(char *path, Graph *graph, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor);
void printGraph(Graph *graph);

// Driver program to test above functions
int main(int argc, char **argv)
{
	// create the graph given in above fugure
	int nVert, nEdge, nServ, nClient, nMonitor;
	char *path = argv[1];

	Graph *graph;
	graph = leEntrada(path, graph, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

	double **servidorCliente = (double **)malloc(sizeof(double *) * nVert);
	double **clienteServidor = (double **)malloc(sizeof(double *) * nVert);
	double **servidorMonitor = (double **)malloc(sizeof(double *) * nVert);
	double **monitorServidor = (double **)malloc(sizeof(double *) * nVert);
	double **monitorCliente = (double **)malloc(sizeof(double *) * nVert);
	double **clienteMonitor = (double **)malloc(sizeof(double *) * nVert);

	for (int i = 0; i < nVert; i++)
	{
		servidorCliente[i] = (double *)malloc(sizeof(double) * nVert);
		clienteServidor[i] = (double *)malloc(sizeof(double) * nVert);
		servidorMonitor[i] = (double *)malloc(sizeof(double) * nVert);
		monitorServidor[i] = (double *)malloc(sizeof(double) * nVert);
		monitorCliente[i] = (double *)malloc(sizeof(double) * nVert);
		clienteMonitor[i] = (double *)malloc(sizeof(double) * nVert);
	}

	for (int i = 0; i < nVert; i++)
	{
		for (int j = 0; j < nVert; j++)
		{
			servidorCliente[i][j] = -1;
			clienteServidor[i][j] = -1;
			servidorMonitor[i][j] = -1;
			monitorServidor[i][j] = -1;
			monitorCliente[i][j] = -1;
			clienteMonitor[i][j] = -1;
		}
	}

	for (int i = 0; i < nServ; i++)
	{
		dijkstra(graph, i, servidorCliente[i]);
	}
	for (int i = 0; i < nServ; i++)
	{
		dijkstra(graph, i, clienteServidor[i]);
	}
	// for (int i = 0; i < nServ; i++)
	// {
	// 	dijkstra(graph, i, servidorCliente[i]);
	// }

	for (int i = 0; i < nVert; i++)
	{
		for (int j = 0; j < nVert; j++)
		{
			printf("%f ", clienteServidor[i][j]);
		}
		printf("\n");
	}

	return 0;
}

Graph *leEntrada(char *path, Graph *graph, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
{

	FILE *file = fopen(path, "r");
	int aux, aux_id1, aux_id2, j;
	double aux_weight;

	fscanf(file, "%d", nVert);
	fscanf(file, "%d", nEdge);
	fscanf(file, "%d", nServ);
	fscanf(file, "%d", nClient);
	fscanf(file, "%d", nMonitor);

	//Matrix com os ids e tipo dos elementos
	int dadosVertice[*nVert][2];

	//  Inicializar a matriz como -1, melhorar dps
	for (int i = 0; i < *nVert; i++)
	{
		dadosVertice[i][0] = -1;
	}

	//Servidor
	for (aux = 0; aux < *nServ; aux++)
	{
		fscanf(file, "%d", &aux_id1);

		//add id;

		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 1;
	}

	// Cliente
	for (; aux < *nClient + *nServ; aux++)
	{
		fscanf(file, "%d", &aux_id1);

		//add id;

		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 2;
	}

	// Monitor
	for (; aux < *nMonitor + *nClient + *nServ; aux++)
	{
		fscanf(file, "%d", &aux_id1);

		//add id;

		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 3;
	}

	// Inicializar o Grafo
	graph = createGraph(*nVert, *nEdge);

	// Ler as arestas
	for (int i = 0; i < *nEdge; i++)
	{
		fscanf(file, "%d %d %lf", &aux_id1, &aux_id2, &aux_weight);

		// Verificar se já foram inseridos na matrix

		if (dadosVertice[aux_id1][0] == -1)
		{
			//insere

			dadosVertice[aux_id1][0] = aux_id1;
			dadosVertice[aux_id1][1] = 4;
		}
		if (dadosVertice[aux_id2][0] == -1)
		{
			//insere

			dadosVertice[aux_id2][0] = aux_id2;
			dadosVertice[aux_id2][1] = 4;
		}

		//Cria a aresta no grafo
		addEdge(graph, dadosVertice[aux_id1][0], dadosVertice[aux_id2][0], aux_weight, dadosVertice[aux_id1][1], dadosVertice[aux_id2][1]);
	}

	// for (int i = 0; i < *nVert; i++)
	// {
	// 	printf("id: %d  tipo: %d\n", dadosVertice[i][0], dadosVertice[i][1]);
	// }

	// printf("Arestas do Grafo\n");
	// printGraph(graph);

	fclose(file);
	return graph;
}

void printGraph(Graph *graph)
{

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
}