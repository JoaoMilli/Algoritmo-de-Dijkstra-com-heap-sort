#ifndef GRAPH_H
#define GRAPH_H

typedef struct adjListNo AdjListNo;

typedef struct adjList AdjList;

typedef struct graph Graph;

/*
*  Cria o graph
*  inputs: a quantidade de vertices, quantidade de arestas, lista de servidores,
*  clientes, monitores e de todas os vertices
*  output: a quantidade de vertices
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/
Graph *criaGraph(int V, int E, int *servidor, int *cliente, int *monitor, int *v);

/*
*  Adiciona um novo no na lista adjacente
*  inputs: O dest, o peso e o tipo de noh
*  output: Um noh criado
*  pre-condicao: nenhuma
*/
AdjListNo *novoNoLista(int dest, double weight, int tipo);


/*
*  Retorna a cabeça (inicio) da lista adjacente
*  inputs: O graph e o indice que indica qual a lista
*  output: O noh do inicio da lista adjacente
*  pre-condicao: nenhuma
*/

AdjListNo *retornaCabeca(Graph *graph, int indice);

/*
*  Retorna o dest (id) de um noh
*  inputs: Um ponteiro para um noh da lista adjacente
*  output: O id do noh
*  pre-condicao: nenhuma
*/
int getDest(AdjListNo *head);

/*
*  Retorna o peso de um noh da lista adjacente
*  inputs: Um ponteiro para um noh da lista adjacente
*  output: O peso associado ao noh
*  pre-condicao: A lista e o noh devem ter sido alocados previamente
*/
double getWeight(AdjListNo *head);

/*
*  Retorna um ponteiro para o proximo noh da lista adjacente
*  inputs: Um ponteiro para um noh da lista adjacente
*  output: O pronteiro para o proximo noh da lista
*  pre-condicao: A lista e o noh devem ter sido alocados previamente
*/

AdjListNo *getNext(AdjListNo *head);

/*
*  Adiciona uma aresta no grafo selecionado
*  inputs: O ponteiro para o graph, os IDs dos nós de origem e destino, o peso e o tipo do nó destino
*  output: nada
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/

void addAresta(Graph *graph, int src, int dest, double weight, int tipoDest);

/*
*  Imprime os IDs de todos os nós de um grafo
*  inputs: O ponteiro para o graph, o número de nós servidores, clientes e monitores
*  output: Os IDs dos nós do grafo impressos
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/

void printGraph(Graph *graph, int nServ, int nCliente, int nMonitor);

/*
*  Retorna a quantidade de vertices do graph
*  inputs: O ponteiro para o graph
*  output: a quantidade de vertices
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/

int retornaVertice(Graph *graph);

/*
*  Retorna a lista de servidores que está armazenada no graph
*  inputs: O ponteiro para o graph
*  output: A lista de servidores 
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/

int *retornaServidor(Graph *graph);

/*
*  Retorna a lista de clientes que está armazenada no graph
*  inputs: O ponteiro para o graph
*  output: A lista de clientes 
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/
int *retornaCliente(Graph *graph);

/*
*  Retorna a lista de monitores que está armazenada no graph
*  inputs: O ponteiro para o graph
*  output: A lista de monitores 
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/
int *retornaMonitor(Graph *graph);

/*
*  Retorna a lista de vertices ( servidores + clientes + monitores + normais ) que está armazenada no graph
*  inputs: O ponteiro para o graph
*  output: A lista de vertices (servidores + clientes + monitores + normais ) 
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/
int *retornaV(Graph *graph);

/*
*  Libera memória alocada para o nó
*  inputs: O nó a ser liberado
*  output: nada
*  pre-condicao: nada
*/

void destroiNode(AdjListNo *node);

/*
*  Libera memória alocada para as arestas do grafo
*  inputs: O ponteiro para o graph contendo as arestas a serem liberadas
*  output: nada
*  pre-condicao: O graph deve existir e estar devidamente inicializado
*/

void destroiEdges(Graph *graph);

/*
*  Libera memória alocada para o grafo
*  inputs: O ponteiro para o graph
*  output: nada
*  pre-condicao: nada 
*/

void destroiGraph(Graph * graph);

#endif