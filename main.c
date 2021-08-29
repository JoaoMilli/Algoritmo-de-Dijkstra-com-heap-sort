#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "item.h"
#include "rtt.h"

void leParametros(FILE *file, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
{
	fscanf(file, "%d", nVert);
	fscanf(file, "%d", nEdge);
	fscanf(file, "%d", nServ);
	fscanf(file, "%d", nClient);
	fscanf(file, "%d", nMonitor);
}

Graph *leEntrada(FILE *file, int *servidor, int *cliente, int *monitor, int *v, int dadosVertice[][2], Graph *graph, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
{
	int aux, aux_id1, aux_id2, j;
	double aux_weight;

	//  Inicializar a matriz como -1, melhorar dps
	for (int i = 0; i < *nVert; i++)
	{

		dadosVertice[i][0] = -1;
	}

	//Servidor
	int i = 0;
	for (aux = 0; aux < *nServ; aux++, i++)
	{
		fscanf(file, "%d", &aux_id1);

		servidor[i] = aux_id1;
		//add id
		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 1;
	}

	// Cliente
	for (i = 0; aux < *nClient + *nServ; aux++, i++)
	{
		fscanf(file, "%d", &aux_id1);
		cliente[i] = aux_id1;
		//add id;
		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 2;
	}

	// Monitor
	for (i = 0; aux < *nMonitor + *nClient + *nServ; i++, aux++)
	{
		fscanf(file, "%d", &aux_id1);
		monitor[i] = aux_id1;
		//add id;
		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 3;
	}

	// Inicializar o Grafo
	graph = createGraph(*nVert, *nEdge, servidor, cliente, monitor, v);
	// printGraph(graph);
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

			aux++;
		}
		if (dadosVertice[aux_id2][0] == -1)
		{
			//insere

			dadosVertice[aux_id2][0] = aux_id2;
			dadosVertice[aux_id2][1] = 4;

			aux++;
		}

		//Cria a aresta no grafo
		addEdge(graph, dadosVertice[aux_id1][0], dadosVertice[aux_id2][0], aux_weight, dadosVertice[aux_id1][1], dadosVertice[aux_id2][1]);
	}

	fclose(file);
	return graph;
}

int main(int argc, char **argv)
{
	int nVert, nEdge, nServ, nClient, nMonitor;

	char *path = argv[1];
	char *pathOutput = argv[2];

	FILE *file = fopen(path, "r");

	leParametros(file, &nVert, &nEdge, &nServ, &nClient, &nMonitor);
	Graph *graph;
	int *v = (int *)malloc(sizeof(int) * 10000);
	int *servidor = (int *)malloc(sizeof(int) * nServ);
	int *cliente = (int *)malloc(sizeof(int) * nClient);
	int *monitor = (int *)malloc(sizeof(int) * nMonitor);

	//Matrix com os ids e tipo dos elementos
	int dadosVertice[nVert][2];

	graph = leEntrada(file, servidor, cliente, monitor, v, dadosVertice, graph, &nVert, &nEdge, &nServ, &nClient, &nMonitor);
	//printGraph(graph, nServ, nClient, nMonitor);

	RTT *result = calculaRTT(graph, nVert, nServ, nClient, nMonitor);

	FILE *outputFile = fopen(pathOutput, "w");

	imprimeListaRTT(outputFile, result, nClient * nServ);
}
