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
    //printf("RTT(%d, %d)\nIda: %f\nVolta:%f\n", returnID(rtt->no1), returnID(rtt->no2), rtt->ida, rtt->volta);
    printf("%d %d %.16lf\n", rtt->idno1, rtt->idno2, rtt->valor);
}

RTT *somaRTT(RTT *rtt1, RTT *rtt2)
{
}

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
    int n_clients = nClient;
    int n_servers = nServ;
    int n_monitors = nMonitor;
    int count = 0;

    RTT *lista = malloc(sizeof(RTT) * (nServ * nClient));

    double **dists_clients = criaMatriz(graph, n_clients, clients, servers, monitors, nServ, nMonitor);

    // matriz servers * (clients + monitors)
    double **dists_servers = criaMatriz(graph, n_servers, servers, clients, monitors, nClient, nMonitor);

    // matriz monitors * (servers + clients)
    double **dists_monitors = criaMatriz(graph, n_monitors, monitors, servers, clients, nServ, nClient);

    // printf("FINALIZE DJK\n");
    // calculo-- --

    // for (int i = 0; i < nServ; i++)
    // {
    //     for (int j = 0; j < nVert; j++)
    //     {
    //         printf("%1f ", dists_servers[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 0; i < nClient; i++)
    // {
    //     for (int j = 0; j < nVert; j++)
    //     {
    //         printf("%1f ", dists_clients[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // for (int i = 0; i < nMonitor; i++)
    // {
    //     for (int j = 0; j < nVert; j++)
    //     {
    //         printf("%1f ", dists_monitors[i][j]);
    //     }
    //     printf("\n");
    // }

    double rtt_cs, rtt1, rtt2, rtt_m, rtt_min, rtt_ratio;

    for (int i = 0; i < nServ; i++)
    {
        for (int j = 0; j < nClient; j++)
        {
            rtt_cs = dists_servers[i][clients[j]] + dists_clients[j][servers[i]];
            rtt_m = DBL_MAX;
            for (int k = 0; k < n_monitors; k++)
            {
                rtt1 = dists_servers[i][monitors[k]] + dists_monitors[k][servers[i]]; // S->M + M->S
                rtt2 = dists_monitors[k][clients[j]] + dists_clients[j][monitors[k]]; // M->C + C->M
                rtt_min = rtt1 + rtt2;
                // verifica se rtt* eh menor que o anterior
                if (rtt_m > rtt_min)
                {
                    rtt_m = rtt_min;
                }
            }

            rtt_ratio = rtt_m / rtt_cs;
            // printf("%d %d %f\n", servers[i], clients[j], rtt_ratio);

            RTT *rtt = CriaRTT(servers[i], clients[j], rtt_ratio);

            lista[count] = *rtt;
            count++;
        }
    }

    qsort(lista, nServ * nClient, sizeof(RTT), compare);

    return lista;
}

void imprimeListaRTT(FILE *file, RTT *lista, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        fprintf(file, "%d %d %.16lf\n", lista[i].idno1, lista[i].idno2, lista[i].valor);
    }
}

double **criaMatriz(Graph *graph, int tam, int *src, int *d1, int *d2, int nd1, int nd2)
{
    double **dists = malloc(sizeof(double) * tam);

    for (int i = 0; i < tam; i++)
    {
        dists[i] = dijkstra(graph, src[i], d1, d2, nd1, nd2);
    }

    return dists;
}

/*

quicksort(lista, 0, indice - 1);

void quicksort(RTT** lista, int lo, int hi)
{
    int i = lo, j = hi, center = (lo + hi) / 2;
    double v = get_rtt(results[center]);
    Result* aux;

    while (i <= j) {
        if (get_rtt(results[i]) < v){
            i++;
        } 
        else if (get_rtt(results[j]) > v) {
            j--;
        }
        else {
            aux = results[i];
            results[i++] = results[j];
            results[j--] = aux;
        }
    }
    if (lo < j)
        quicksort (results, lo, j);
    if (hi > i)
        quicksort (results, i , hi);
}

*/