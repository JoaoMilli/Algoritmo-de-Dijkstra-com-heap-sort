#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "float.h"
#include "PQ.h"


void dijkstra(Graph *graph, int src, double *dist)
{
	int V = retornaVertice(graph);

	int *map, N;
	
	Item **pq = PQ_init(V,&map, &N);

	for (int v = 0; v < V; ++v)
	{
		dist[v] = DBL_MAX;

		Item * item = make_item(v, dist[v]);
		PQ_insert(pq, item, &N, map, dist[v]);

	}

	PQ_decrease_key(pq, src, map, 0.0);
	dist[src] = 0;

	while (!PQ_empty(&N))
	{
		Item *item = PQ_delmin(pq, map, &N);

		int u = returnID(item);

		AdjListNode *pCrawl = getHead(graph,u);
		
		while (pCrawl != NULL)
		{
			int v = getDest(pCrawl);

			if (PQ_contains(pq, &N, v) && dist[u] != DBL_MAX && getWeight(pCrawl) + dist[u] < dist[v])
			{
			
				dist[v] = dist[u] + getWeight(pCrawl);
			
				PQ_decrease_key(pq, v, map, dist[v]);
			}
			pCrawl = getNext(pCrawl);
		}
	}
	PQ_finish(pq, &N, map);

}