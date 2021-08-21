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

    endEdgeTo = malloc(sizeof(Aresta **));
    Item **listaV = leEntrada(argv[1], endEdgeTo, &nVert, &nEdge, &nServ, &nClient, &nMonitor);
    printf("comeco\n");

    Aresta **edgeTo = *endEdgeTo;

    distTo = malloc(sizeof(double) * nVert);
    Aresta **todasArestas = malloc(sizeof(Aresta *) * nEdge);
    //dijkstra(nVert, map, N, listaV, v,  distTo, nEdge, edgeTo, todasArestas,1);

    // free(endEdgeTo);
    // free(distTo);
    // for(int i=0; i < nVert; i++){
    //     free(listaV[i]);
    // }
    // free(todasArestas);
    // free(listaV);

    //liberaMemoria(endEdgeTo, distTo, todasArestas, nVert, nEdge);

    // RTT

    /*Lista de RTTs com tamanho para todas as combinações servidores/clientes*/
    RTT **listaRTT = malloc(sizeof(RTT *) * (nServ * nClient));
    int k = 0;
    int qtd = 0;
    int n = 0;
    double ida;

    for (int i = 0; i < nVert; i++)
    {
        if (retornaTipo(listaV[i]) == 1)
        {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i]));

            //Distancia servidor-cliente
            for (int j = 0; j < nVert; j++)
            {
                if (retornaTipo(listaV[j]) == 2)
                {
                    if (n == 0)
                    {
                        ida = distTo[returnID(listaV[j])];
                        n++;
                    }
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    //printf("ida %f volta %f\n", ida, volta);
                    RTT *rtt = CriaRTT(listaV, nVert, ida, volta, returnID(listaV[i]), returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    qtd++;
                    k++;
                }
            }
            n = 0;
        }
    }

    // RTT (S->M)
    for (int i = 0; i < nVert; i++)
    {
        if (retornaTipo(listaV[i]) == 1)
        {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i]));
            //Distancia servidor-cliente
            //printf("entrei no primeiro dijkstra servidor\n\n");
            for (int j = 0; j < nVert; j++)
            {
                //printf("Estou aqui\n\n");
                if (retornaTipo(listaV[j]) == 3)
                {
                    if (n == 0)
                    {
                        ida = distTo[returnID(listaV[j])];
                        n++;
                    }
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    RTT *rtt = CriaRTT(listaV, nVert, ida, volta, returnID(listaV[i]), returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    qtd++;
                    k++;
                }
            }
            n = 0;
        }
    }

    // RTT (M -> C)

    for (int i = 0; i < nVert; i++)
    {
        if (retornaTipo(listaV[i]) == 3)
        {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i]));

            //Distancia servidor-cliente
            for (int j = 0; j < nVert; j++)
            {
                if (retornaTipo(listaV[j]) == 2)
                {
                    if (n == 0)
                    {
                        ida = distTo[returnID(listaV[j])];
                        n++;
                    }
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    RTT *rtt = CriaRTT(listaV, nVert, ida, volta, returnID(listaV[i]), returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    qtd++;
                    k++;
                }
            }
            n = 0;
        }
    }

    // printf("%d\n", qtd);
    // for (k = 0; k < qtd; k++)
    // {
    //     imprimeRTT(listaRTT[k]);
    //     printf("--\n");
    // }

    /*
    Varre vetor RTT
        procura rtt1 com origem servidor S/cliente C
        Varre vetor RTT
            procura rtt com mesma origem S e checa se destino é monitor
            salvo destino M
            salvo rtt2
        Varre vetor RTT
            procura rtt com mesmo destino C e checa se origem é monitor
            checa se é mesma origem M
                salva rtt3
                soma rtt2 e rtt3
                adiciona na heap              
        menor valor =  pq_delmin
        rtt1/menor valor
        imprime
    */
    int *mapRTT, NRTT, maxRTT = 5;

    Item **pqRTT = PQ_init(maxRTT, &mapRTT, &NRTT);

    int soma = 0;

    for (int i = 0; i < qtd; i++)
    {
        RTT *rttBase, *rtt2, *rtt3;
        Item *destino;
        if (retornaTipo(retornaIdaRTT(listaRTT[i])) == 1 && retornaTipo(retornaVoltaRTT(listaRTT[i])) == 2)
        {
            rttBase = listaRTT[i];
            for (int j = 0; j < qtd; j++)
            {
                if (retornaIdaRTT(listaRTT[j]) == retornaIdaRTT(rttBase) && retornaTipo(retornaVoltaRTT(listaRTT[j])) == 3)
                {
                    destino = retornaVoltaRTT(listaRTT[j]);
                    rtt2 = listaRTT[j];
                    for (int k = 0; k < qtd; k++)
                    {
                        if (retornaVoltaRTT(rttBase) == retornaVoltaRTT(listaRTT[k]) && retornaTipo(retornaIdaRTT(listaRTT[k])) == 3)
                        // printf("estou aqui\n");
                        {
                            if (retornaIdaRTT(listaRTT[k]) == destino)
                            {
                                rtt3 = listaRTT[k];
                                soma = retornaDistancia(rtt2) + retornaDistancia(rtt3);
                                Item *v = make_item(k, soma, k);
                                PQ_insert(pqRTT, v, &NRTT, mapRTT, soma);
                            }
                        }
                    }
                }
            }
            if (!PQ_empty(&NRTT))
            {
                Item *menor = PQ_delmin(pqRTT, mapRTT, &NRTT);
                double value = returnValue(menor) / retornaDistancia(rttBase);
                printf("%f\n", value);
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

void liberaMemoria(Aresta ***endEdgeTo, double *distTo, Aresta **todasArestas, int nVert, int nEdge)
{
    free(distTo);
    // for(int i=0; i<nVert; i++){

    // }
    // for(int j=0; j<nEdge; j++){
    //     free(todasArestas[j]);
    // }
    free(todasArestas);
}