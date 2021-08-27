#ifndef DIJISKSTRA2_H
#define DIJISKSTRA2_H

typedef struct adjListNode AdjListNode;

typedef struct adjList AdjList;

typedef struct graph Graph;

typedef struct minHeapNode MinHeapNode;
typedef struct minHeap MinHeap;

MinHeapNode *newMinHeapNode(int v, double dist);
MinHeap *createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);
void minHeapify(MinHeap *minHeap, int idx);
int isEmpty(MinHeap *minHeap);
MinHeapNode *extractMin(MinHeap *minHeap);
void decreaseKey(MinHeap *minHeap, int v, int dist);
int isInMinHeap(MinHeap *minHeap, int v);

AdjListNode *newAdjListNode(int dest, double weight, int tipo);
Graph *createGraph(int V, int E);
void addEdge(Graph *graph, int src, int dest, double weight, int tipoSrc, int tipoDest);
void dijkstra(Graph *graph, int src, double *dist);

#endif
