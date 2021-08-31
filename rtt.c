#include "rtt.h"

struct rtt
{
    double valor;
    int idno1;
    int idno2;
};

RTT *CriaRTT(int idno1, int idno2, double valor)
{
    RTT *rtt = (RTT *)malloc(sizeof(RTT));
    rtt->idno1 = idno1;
    rtt->idno2 = idno2;
    rtt->valor = valor;
    return rtt;
}

int retornaIdaRTT(RTT *rtt)
{
    return rtt->idno1;
}

int retornaVoltaRTT(RTT *rtt)
{
    return rtt->idno2;
}

void imprimeRTT(RTT *rtt)
{
    printf("%d %d %.16lf\n", rtt->idno1, rtt->idno2, rtt->valor);
}
/*
*  Função usada pelo qsort para comparar
*  inputs: O ponteiro para RTT
*  output: retorna um inteiro
*  pre-condicao: nenhuma
*/
static int compare(const void *a, const void *b)
{
    RTT a1 = *(RTT *)a;
    RTT a2 = *(RTT *)b;

    if (a1.valor < a2.valor)
        return -1;
    if (a1.valor > a2.valor)
        return 1;

    if (a1.idno1 < a2.idno1)
        return -1;
    if (a1.idno1 > a2.idno1)
        return 1;

    if (a1.idno2 < a2.idno2)
        return -1;
    if (a1.idno2 > a2.idno2)
        return 1;

    return 0;
}

RTT *calculaRTT(Graph *graph, int nVert, int nServ, int nClient, int nMonitor)
{
    int *clients = retornaCliente(graph);
    int *servers = retornaServidor(graph);
    int *monitors = retornaMonitor(graph);
    int count = 0;

    RTT *lista = malloc(sizeof(RTT) * (nServ * nClient));

    /* Executa o algoritmo de Djikstra e calcula as distancia dos servidores, clientes e monitores */

    // /* Servidor */
    double **distsServers = criaMatriz(graph, nServ);
    for (int i = 0; i < nServ; i++)
    {
        distsServers[i] = dijkstra(graph, servers[i]);
    }

    /* Clientes */
    double **distsClients = criaMatriz(graph, nClient);
    for (int i = 0; i < nClient; i++)
    {
        distsClients[i] = dijkstra(graph, clients[i]);
    }

    /* Monitores */
    double **distsMonitors = criaMatriz(graph, nMonitor);
    for (int i = 0; i < nMonitor; i++)
    {
        distsMonitors[i] = dijkstra(graph, monitors[i]);
    }
    // printf("FINALIZE DJK\n");

    /* Calculando os RTTS */

    double rttSc, rtt1, rtt2, rttAst, rttMin, rttFinal;

    for (int i = 0; i < nServ; i++)
    {
        for (int j = 0; j < nClient; j++)
        {
            rttSc = distsServers[i][clients[j]] + distsClients[j][servers[i]];
            // Definindo como o maior possivel para usar na comparação
            rttAst = DBL_MAX;
            for (int k = 0; k < nMonitor; k++)
            {
                rtt1 = distsServers[i][monitors[k]] + distsMonitors[k][servers[i]]; // S->M + M->S
                rtt2 = distsMonitors[k][clients[j]] + distsClients[j][monitors[k]]; // M->C + C->M
                rttMin = rtt1 + rtt2;
                /* verifica se rtt* e menor que oque está armazenado no rttm */
                if (rttAst > rttMin)
                {
                    rttAst = rttMin;
                }
            }

            rttFinal = rttAst / rttSc;
            // printf("%d %d %f\n", servers[i], clients[j], rttFinal);

            RTT *rtt = CriaRTT(servers[i], clients[j], rttFinal);

            lista[count] = *rtt;
            free(rtt);
            count++;
        }
    }

    /* Ordena a lista de RTT */
    qsort(lista, nServ * nClient, sizeof(RTT), compare);

    /* Libera a memória alocada para as matr izes */

    destroiMatriz(distsServers, nServ);
    destroiMatriz(distsClients, nClient);
    destroiMatriz(distsMonitors, nMonitor);
    return lista;
}

void imprimeListaRTT(FILE *file, RTT *lista, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        fprintf(file, "%d %d %.16lf\n", lista[i].idno1, lista[i].idno2, lista[i].valor);
    }
}

double **criaMatriz(Graph *graph, int tam)
{
    double **dists = malloc(sizeof(double) * tam);
    for (int i = 0; i < tam; i++)
    {
        // dists[i] = ((double *)malloc(sizeof(double) * tam));
    }

    return dists;
}

void destroiMatriz(double **matriz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

void destroiListaRTT(RTT *lista)
{
    free(lista);
}