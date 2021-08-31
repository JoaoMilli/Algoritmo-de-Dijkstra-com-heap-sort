#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "float.h"
#include "PQ.h"

/*Função dijkstra, recebe um grafo do tipo Graph e o inteiro src contendo o ID do nó de origem, retorna um vetor de double contendo a distância para cada nó do grafo*/

double *dijkstra(Graph *graph, int src)
{
	int V = retornaVertice(graph);

	int *map, N;

	//Cria heap para armazenar os valores das distâncias calculadas

	Item **pq = PQ_init(V, &map, &N);

	double *dists = malloc(sizeof(double) * V);

	for (int v = 0; v < V; ++v)
	{
		//Inicia todas as distâncias como MAX_DBL para que a primeira distância calculada seja sempre a menor
		dists[v] = DBL_MAX;

		//Cria e insere um item na heap com id = v e prioridade = DBL_MAX

		Item *item = make_item(v, dists[v]);
		PQ_insert(pq, item, &N, map, dists[v]);
	}

	//Faz com que o nó de ID = src tenha prioridade 0

	PQ_decrease_key(pq, src, map, 0.0);

	//Atualiza o vetor dists

	dists[src] = 0;

	while (!PQ_empty(&N))
	{
		//Tira o item contendo a menor prioridade da heap

		Item *item = PQ_delmin(pq, map, &N);

		int u = returnID(item);

		//Obtém-se a lista com todas as conexões do nó referente à menor prioridade da heap

		AdjListNo *noHead = retornaCabeca(graph, u);

		while (noHead != NULL)
		{
			int v = getDest(noHead);

			//Avança pelas arestas calculando os caminhos pelos pesos

			if (PQ_buscaVertice(pq, map, v, &N) && dists[u] != DBL_MAX && (getWeight(noHead) + dists[u]) < dists[v])
			{

				//Caso seja encontrado um caminho menor para o nó de referência, dists é atualizado contendo o menor valor

				dists[v] = dists[u] + getWeight(noHead);

				PQ_decrease_key(pq, v, map, dists[v]);
			}

			noHead = getNext(noHead);
		}
		destroiItem(item);
	}
	PQ_finish(pq, &N, map);
	return dists;
}