#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "PQ.h"
#include "rtt.h"
#include "item.h"
#include "aresta.h"
#include "dijkstra.h"

Item **leEntrada(char *path, Aresta ***edgeTo, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor);
void liberaMemoria(Aresta ***endEdgeTo, double *distTo, Aresta **todasArestas, int nVert, int nEdge);

int main(int argc, char **argv)
{

    int *map;
    int N, nVert, nEdge, nServ, nClient, nMonitor, v;
    Aresta ***endEdgeTo;
    double *distTo;
    double *distTo2;
    double *distTo3;

    endEdgeTo = malloc(sizeof(Aresta **));
    Item **listaV = leEntrada(argv[1], endEdgeTo, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

    Aresta **edgeTo = *endEdgeTo;

    distTo = malloc(sizeof(double) * nVert);
    distTo2 = malloc(sizeof(double) * nVert);
    distTo3 = malloc(sizeof(double) * nVert);
    Aresta **todasArestas = malloc(sizeof(Aresta *) * nEdge);

    /*Lista de RTTs com tamanho para todas as combinações servidores/clientes*/
    RTT **listaRTT = malloc(sizeof(RTT *) * (nServ * nClient));
    int k = 0;
    int qtd = 0;
    int n = 0;
    double ida;

    double **servidorCliente = (double **)malloc(sizeof(double *) * nVert);
    double **clienteServidor = (double **)malloc(sizeof(double *) * nVert);
    double **servidorMonitor = (double **)malloc(sizeof(double *) * nVert);
    double **monitorServidor = (double **)malloc(sizeof(double *) * nVert);
    double **monitorCliente = (double **)malloc(sizeof(double *) * nVert);
    double **clienteMonitor = (double **)malloc(sizeof(double *) * nVert);

    for (int i = 0; i < nVert; i++)
    {
        servidorCliente[i] = (double *)malloc(sizeof(double) * nVert);
        clienteServidor[i] = (double *)malloc(sizeof(double) * nVert);
        servidorMonitor[i] = (double *)malloc(sizeof(double) * nVert);
        monitorServidor[i] = (double *)malloc(sizeof(double) * nVert);
        monitorCliente[i] = (double *)malloc(sizeof(double) * nVert);
        clienteMonitor[i] = (double *)malloc(sizeof(double) * nVert);
    }

    for (int i = 0; i < nServ; i++)
    {
        dijkstra(nVert, map, N, listaV, servidorCliente[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }

    for (int i = nClient; i < nClient + nServ; i++)
    {
        dijkstra(nVert, map, N, listaV, clienteServidor[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }
    // printf("entrei joao2\n");

    for (int i = 0; i < nServ; i++)
    {
        dijkstra(nVert, map, N, listaV, servidorMonitor[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }
    // printf("entrei joao3\n");

    for (int i = nServ + nClient; i < nServ + nClient + nMonitor; i++)
    {
        dijkstra(nVert, map, N, listaV, monitorServidor[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }
    // printf("entrei joao4\n");

    for (int i = nServ + nClient; i < nServ + nClient + nMonitor; i++)
    {
        dijkstra(nVert, map, N, listaV, monitorCliente[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }
    // printf("entrei joao5\n");

    for (int i = nClient; i < nClient + nServ; i++)
    {
        dijkstra(nVert, map, N, listaV, clienteMonitor[returnID(listaV[i])], nEdge, edgeTo, todasArestas, returnID(listaV[i]));
    }

    // printf("entrei joao\n");

    int posi = 0;   

    // printf("Servidor -> Cliente\n");
    for (int i = 0; i < nServ; i++){
        for (int j = nServ ; j < nServ + nClient; j++)
        {
            RTT *rtt = CriaRTT(listaV, nVert, servidorCliente[returnID(listaV[i])][returnID(listaV[j])], clienteServidor[returnID(listaV[j])][returnID(listaV[i])], listaV[i], listaV[j]);
            listaRTT[posi] = rtt;
            //imprimeRTT(rtt);
            posi++;
        }
    }


    // printf("\nServidor -> Monitor\n");
    for (int i = 0; i < nServ; i++){
        for (int j = nServ + nClient ; j < nServ + nClient + nMonitor; j++)
        {
            RTT *rtt = CriaRTT(listaV, nVert, servidorMonitor[returnID(listaV[i])][returnID(listaV[j])], monitorServidor[returnID(listaV[j])][returnID(listaV[i])], listaV[i], listaV[j]);
            listaRTT[posi] = rtt;
            //imprimeRTT(rtt);
            posi++;
        }
    }


    // printf("\nMonitor -> Cliente\n");
    for (int i = nServ + nClient; i < nServ + nClient + nMonitor; i++){
        for (int j = nServ; j < nServ + nClient; j++)
        {
            RTT *rtt = CriaRTT(listaV, nVert, monitorCliente[returnID(listaV[i])][returnID(listaV[j])], clienteMonitor[returnID(listaV[j])][returnID(listaV[i])], listaV[i], listaV[j]);
            listaRTT[posi] = rtt;
            //imprimeRTT(rtt);
            posi++;
        }
    }

    int *mapRTT, NRTT, maxRTT = qtd;

    Item **pqRTT = PQ_init(maxRTT, &mapRTT, &NRTT);

    double soma = 0;
    int indice = 0;
    for (int i = 0; i < posi; i++)
    {
        RTT *rttBase, *rtt2, *rtt3;
        Item *destino;
        // encontrando o rtt base que a ida é um servidor e a volta um cliente
        if (retornaTipo(retornaIdaRTT(listaRTT[i])) == 1 && retornaTipo(retornaVoltaRTT(listaRTT[i])) == 2)
        {
            rttBase = listaRTT[i];
            // Procurar um rtt com mesma ida do rttBase e checa se a volta é um monitor
            for (int j = 0; j < posi; j++)
            {
                if (retornaIdaRTT(listaRTT[j]) == retornaIdaRTT(rttBase) && retornaTipo(retornaVoltaRTT(listaRTT[j])) == 3)
                {
                // RTT(0,4)
                // min{RTT(S, M) + RTT(M, C), RTT(S, M) + RTT(M, C)}
                // min{RTT(0, 1) + RTT(1, 4), RTT(0, 2) + RTT(2, 4)}
                    // Salva o destino monitor
                    destino = retornaVoltaRTT(listaRTT[j]);
                    rtt2 = listaRTT[j]; //RTT(0, 1)
                    for (int k = 0; k < posi; k++)
                    {   
                        // Procurar um rtt com o mesmo volta C e checar se  a ida é monitor
                        if (retornaVoltaRTT(rttBase) == retornaVoltaRTT(listaRTT[k]) && retornaTipo(retornaIdaRTT(listaRTT[k])) == 3)
                        {
                            if (retornaIdaRTT(listaRTT[k]) == destino)
                            {   
                                // printf("rttBase ida: %d volta:%d\n", returnID(retornaIdaRTT(rttBase)), returnID(retornaVoltaRTT(rttBase)));
                                // printf("rtt2 ida:%d volta: %d\n", returnID(retornaIdaRTT(rtt2)), returnID(retornaVoltaRTT(rtt2)));
                                // printf("rtt2 ida:%f volta:%f\n\n", returnValue(retornaIdaRTT(rtt2)), returnValue(retornaVoltaRTT(rtt2)));
                                rtt3 = listaRTT[k];
                                // printf("rtt3 ida:%d volta:%d\n", returnID(retornaIdaRTT(rtt3)),returnID(retornaVoltaRTT(rtt3)));
                                // printf("rtt3 ida:%f volta:%f\n\n", returnValue(retornaIdaRTT(rtt3)), returnValue(retornaVoltaRTT(rtt3)));
                                soma = retornaDistancia(rtt2) + retornaDistancia(rtt3);
                                Item *v = make_item(indice, soma, k);
                                indice++;
                                PQ_insert(pqRTT, v, &NRTT, mapRTT, soma);
                            }
                        }
                    }
                }
            }
            if (!PQ_empty(&NRTT))
            {   
                // printf("\nPQ\n");
                Item *menor = PQ_delmin(pqRTT, mapRTT, &NRTT);
                // printf("%f\n", returnValue(menor));

                while(!PQ_empty(&NRTT)){
                    Item *delmin = PQ_delmin(pqRTT, mapRTT, &NRTT);
                    // printf("%f\n", returnValue(delmin));

                }
                // printf("\n\n");
                double value = returnValue(menor) / retornaDistancia(rttBase);
                printf("%d %d ",returnID(retornaIdaRTT(rttBase)) , returnID(retornaVoltaRTT(rttBase)));
                printf("%f\n", value);
                indice = 0;
            }
        }
    }
}

    Item **leEntrada(char *path, Aresta ***edgeTo, int *nVert, int *nEdge, int *nServ, int *nClient, int *nMonitor)
    {

        FILE *file = fopen(path, "r");
        int aux, aux_id1, aux_id2;
        double aux_weight;
        Aresta *aux_aresta;

        fscanf(file, "%d", nVert);
        fscanf(file, "%d", nEdge);
        fscanf(file, "%d", nServ);
        fscanf(file, "%d", nClient);
        fscanf(file, "%d", nMonitor);

        Item **listaV = malloc(sizeof(Item *) * (*nVert));

        for (aux = 0; aux < *nServ; aux++)
        {
            fscanf(file, "%d", &aux_id1);
            listaV[aux] = make_item(aux_id1, 0, 1);
        }

        while (aux < (*nServ) + (*nClient))
        {
            fscanf(file, "%d", &aux_id1);
            listaV[aux] = make_item(aux_id1, 0, 2);
            aux++;
        }

        while (aux < (*nServ) + (*nClient) + (*nMonitor))
        {
            fscanf(file, "%d", &aux_id1);
            listaV[aux] = make_item(aux_id1, 0, 3);
            aux++;
        }

        for (int i = 0; i < (*nVert); i++)
        {
            //printf("%d\n", aux);
            if (retornaGporID(listaV, (*nServ) + (*nClient) + (*nMonitor), i) == NULL)
            {
                listaV[aux] = make_item(i, 0, 4);
                aux++;
            }
        }

        *edgeTo = malloc(sizeof(Aresta *) * (*nEdge));

        for (aux = 0; aux < *nEdge; aux++)
        {
            fscanf(file, "%d", &aux_id1);
            fscanf(file, "%d", &aux_id2);
            fscanf(file, "%lf", &aux_weight);

            Item *aux1 = retornaGporID(listaV, *nVert, aux_id1);
            Item *aux2 = retornaGporID(listaV, *nVert, aux_id2);

            aux_aresta = criaAresta(aux1, aux2, aux_weight);
            (*edgeTo)[aux] = aux_aresta;
        }

        fclose(file);

        return listaV;
    }

    void liberaMemoria(Aresta * **endEdgeTo, double *distTo, Aresta **todasArestas, int nVert, int nEdge)
    {
        free(distTo);
        // for(int i=0; i<nVert; i++){

        // }
        // for(int j=0; j<nEdge; j++){
        //     free(todasArestas[j]);
        // }
        free(todasArestas);
    }