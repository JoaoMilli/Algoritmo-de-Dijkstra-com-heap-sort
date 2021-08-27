// #include "minHeap.h"

// // Structure to represent a min heap node
// struct minHeapNode
// {
// 	int v;
// 	int dist;
// };

// // Structure to represent a min heap
// struct minHeap
// {
// 	int size;	
// 	int capacity;
// 	int *pos;
// 	MinHeapNode **array;
// };

// MinHeapNode* newMinHeapNode(int v,int dist)
// {
// 	MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
// 	minHeapNode->v = v;
// 	minHeapNode->dist = dist;
// 	return minHeapNode;
// }


// MinHeap* createMinHeap(int capacity)
// {
// 	MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
// 	minHeap->pos = (int *)malloc(capacity * sizeof(int));
// 	minHeap->size = 0;
// 	minHeap->capacity = capacity;
// 	minHeap->array =(MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
// 	return minHeap;
// }

// // A utility function to swap two
// // nodes of min heap.
// // Needed for min heapify
// void swapMinHeapNode(MinHeapNode** a,MinHeapNode** b)
// {
// 	MinHeapNode* t = *a;
// 	*a = *b;
// 	*b = t;
// }

// // A standard function to
// // heapify at given idx
// // This function also updates
// // position of nodes when they are swapped.
// // Position is needed for decreaseKey()
// void minHeapify(MinHeap* minHeap,int idx)
// {
// 	int smallest, left, right;
// 	smallest = idx;
// 	left = 2 * idx + 1;
// 	right = 2 * idx + 2;

// 	if (left < minHeap->size &&
// 		minHeap->array[left]->dist <
// 		minHeap->array[smallest]->dist )
// 	smallest = left;

// 	if (right < minHeap->size &&
// 		minHeap->array[right]->dist <
// 		minHeap->array[smallest]->dist )
// 	smallest = right;

// 	if (smallest != idx)
// 	{
// 		// The nodes to be swapped in min heap
// 		MinHeapNode *smallestNode = minHeap->array[smallest];
// 		MinHeapNode *idxNode = minHeap->array[idx];

// 		// Swap positions
// 		minHeap->pos[smallestNode->v] = idx;
// 		minHeap->pos[idxNode->v] = smallest;

// 		// Swap nodes
// 		swapMinHeapNode(&minHeap->array[smallest],
// 						&minHeap->array[idx]);

// 		minHeapify(minHeap, smallest);
// 	}
// }

// // A utility function to check if
// // the given minHeap is ampty or not
// int isEmpty(MinHeap* minHeap)
// {
// 	return minHeap->size == 0;
// }

// // Standard function to extract
// // minimum node from heap
// MinHeapNode* extractMin(MinHeap*minHeap)
// {
// 	if (isEmpty(minHeap))
// 		return NULL;

// 	// Store the root node
// 	MinHeapNode* root = minHeap->array[0];

// 	// Replace root node with last node
// 	MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
// 	minHeap->array[0] = lastNode;

// 	// Update position of last node
// 	minHeap->pos[root->v] = minHeap->size-1;
// 	minHeap->pos[lastNode->v] = 0;

// 	// Reduce heap size and heapify root
// 	--minHeap->size;
// 	minHeapify(minHeap, 0);

// 	return root;
// }

// void decreaseKey(MinHeap* minHeap,int v, int dist)
// {
// 	// Get the index of v in heap array
// 	int i = minHeap->pos[v];

// 	// Get the node and update its dist value
// 	minHeap->array[i]->dist = dist;

// 	// Travel up while the complete
// 	// tree is not hepified.
// 	// This is a O(Logn) loop
// 	while (i && minHeap->array[i]->dist <
// 		minHeap->array[(i - 1) / 2]->dist)
// 	{
// 		// Swap this node with its parent
// 		minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
// 		minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
// 		swapMinHeapNode(&minHeap->array[i],
// 				&minHeap->array[(i - 1) / 2]);

// 		// move to parent index
// 		i = (i - 1) / 2;
// 	}
// }

// // A utility function to check if a given vertex
// // 'v' is in min heap or not
// int isInMinHeap(MinHeap *minHeap, int v)
// {
// if (minHeap->pos[v] < minHeap->size)
// 	return 1;
// return 0;
// }

// // A utility function used to print the solution
// void printArr(int dist[], int n)
// {
// 	printf("Vertex Distance from Source\n");
// 	for (int i = 0; i < n; ++i)
// 		printf("%d \t\t %d\n", i, dist[i]);
// }