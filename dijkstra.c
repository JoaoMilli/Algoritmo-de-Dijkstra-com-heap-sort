#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "float.h"
#include "PQ.h"

double *dijkstra(Graph *graph, int src, int *d1, int *d2, int nd1, int nd2)
{
	int V = retornaVertice(graph);

	int *map, N;

	Item **pq = PQ_init(V, &map, &N);
	double *destinies = malloc(sizeof(double) * (nd1 + nd2));
	double *dists = malloc(sizeof(double) * V);
	// double dists[V];

	for (int v = 0; v < V; ++v)
	{
		dists[v] = DBL_MAX;

		Item *item = make_item(v, dists[v]);
		PQ_insert(pq, item, &N, map, dists[v]);
	}

	PQ_decrease_key(pq, src, map, 0.0);
	dists[src] = 0;
	while (!PQ_empty(&N))
	{
		Item *item = PQ_delmin(pq, map, &N);

		int u = returnID(item);

		AdjListNode *pCrawl = getHead(graph, u);

		while (pCrawl != NULL)
		{
			int v = getDest(pCrawl);

			if (PQ_contains(pq, &N, v) && dists[u] != DBL_MAX && getWeight(pCrawl) + dists[u] < dists[v])
			{

				dists[v] = dists[u] + getWeight(pCrawl);

				PQ_decrease_key(pq, v, map, dists[v]);
			}
			pCrawl = getNext(pCrawl);
		}
	}
	PQ_finish(pq, &N, map);

	return dists;
}