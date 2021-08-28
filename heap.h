#ifndef HEAP_H
#define HEAP_H


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

#endif