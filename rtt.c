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
	for(int i=0; i < n_clients; i++){
        dists_clients[i] = dijkstra(graph, clients[i], servers, monitors, nServ, nMonitor);
	}

    double **dists_servers = criaMatriz(graph, n_servers, servers, clients, monitors, nClient, nMonitor);
	for(int i=0; i < n_servers; i++){
		dists_servers[i] = dijkstra(graph, servers[i], clients, monitors, nClient, nMonitor);
	}

    double **dists_monitors = criaMatriz(graph, n_monitors, monitors, servers, clients, nServ, nClient);
	for(int i=0; i < n_monitors; i++){
		dists_monitors[i] = dijkstra(graph, monitors[i], servers, clients, nServ, nClient);
	}
    printf("FINALIZE DJK\n");

    // ----- Calculando os rtts a partirdo retorn dist
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
		dists[i] = ((double*)malloc(tam * sizeof(double)));
        //dists[i] = dijkstra(graph, src[i], d1, d2, nd1, nd2);
    }

    return dists;
}


