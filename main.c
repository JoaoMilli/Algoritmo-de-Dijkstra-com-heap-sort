#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "item.h"
#include "dijkstra.h"
#include "rtt.h"

/*
*  Leitura dos parametros do programa :
*  nVert, nEdge, nServ, nClient, nMnitor
*  inputs: O ponteiro para o arquivo e os ponteiros de todos os parametros
*  output: nenhum
*  pre-condicao: O arquivo deve ter sido aberto previamente e os ponteiro dos parametros devem ter sido alocados
*/

void leParametros(FILE *file, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
{
	fscanf(file, "%d", nVert);
	fscanf(file, "%d", nEdge);
	fscanf(file, "%d", nServ);
	fscanf(file, "%d", nClient);
	fscanf(file, "%d", nMonitor);
}

/*
*  Leitura da entrada do programa
*  inputs: O ponteiro para o arquivo e os ponteiros das informações que serão armazenadas
*  output: Um graph que eh incializado dentro da funcao
*  pre-condicao: O arquivo deve ter sido aberto previamente e os ponteiro das informacoes devem ter sido alocados
*/

Graph *leEntrada(FILE *file, int *servidor, int *cliente, int *monitor, int *v, int dadosVertice[][2], Graph *graph, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
{
	int aux, aux_id1, aux_id2, j;
	double aux_weight;
	for (int i = 0; i < *nVert; i++)
	{
		dadosVertice[i][0] = -1;
	}
	/* Leitura dos servidores */
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

	/* Leitura dos clientes */
	for (i = 0; aux < *nClient + *nServ; aux++, i++)
	{
		fscanf(file, "%d", &aux_id1);
		cliente[i] = aux_id1;
		//add id;
		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 2;
	}

	/* Leitura dos monitores */
	for (i = 0; aux < *nMonitor + *nClient + *nServ; i++, aux++)
	{
		fscanf(file, "%d", &aux_id1);
		monitor[i] = aux_id1;
		//add id;
		dadosVertice[aux_id1][0] = aux_id1;
		//add tipo;
		dadosVertice[aux_id1][1] = 3;
	}

	/* Inicializa graph */
	graph = criaGraph(*nVert, *nEdge, servidor, cliente, monitor, v);

	/* Leitura das arestas */
	for (int i = 0; i < *nEdge; i++)
	{
		fscanf(file, "%d %d %lf", &aux_id1, &aux_id2, &aux_weight);

		/* Verificar se já foram inseridos na matrix */

		if (dadosVertice[aux_id1][0] == -1)
		{
			/* insere */
			dadosVertice[aux_id1][0] = aux_id1;
			dadosVertice[aux_id1][1] = 4;

			aux++;
		}
		if (dadosVertice[aux_id2][0] == -1)
		{
			/* insere */

			dadosVertice[aux_id2][0] = aux_id2;
			dadosVertice[aux_id2][1] = 4;

			aux++;
		}

		/* Adiciona a aresta no graph */
		addAresta(graph, dadosVertice[aux_id1][0], dadosVertice[aux_id2][0], aux_weight, dadosVertice[aux_id1][1]);
	}
	return graph;
}

void destroiSCM(int *servidor, int *cliente, int *monitor, int *v)
{
	free(v);
	free(servidor);
	free(cliente);
	free(monitor);
}

int main(int argc, char **argv)
{
	int nVert, nEdge, nServ, nClient, nMonitor;

	char *path = argv[1];
	char *pathOutput = argv[2];

	FILE *file = fopen(path, "r");

	/* Leitura dos parametros */
	leParametros(file, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

	Graph *graph;

	int *v = (int *)malloc(sizeof(int) * nVert);
	int *servidor = (int *)malloc(sizeof(int) * nServ);
	int *cliente = (int *)malloc(sizeof(int) * nClient);
	int *monitor = (int *)malloc(sizeof(int) * nMonitor);

	/* Matriz com os ids e tipo dos elementos */
	int dadosVertice[nVert][2];

	/* Leitura da entrada e criacao do graph*/
	graph = leEntrada(file, servidor, cliente, monitor, v, dadosVertice, graph, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

	/* Calcula o resultado */
	RTT *result = calculaRTT(graph, nVert, nServ, nClient, nMonitor);

	/* Abertura do arquivo de saida */
	FILE *outputFile = fopen(pathOutput, "w");

	/* Imprime o arquivo de saída */
	imprimeListaRTT(outputFile, result, nClient * nServ);

	destroiListaRTT(result);
	destroiGraph(graph);
	destroiSCM(servidor, cliente, monitor, v);
	fclose(file);
	fclose(outputFile);
}
