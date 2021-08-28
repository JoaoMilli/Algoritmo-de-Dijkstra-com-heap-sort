#include "rtt.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

struct rtt {
    double valor;
    int idno1;
    int idno2;
};

RTT* CriaRTT( int idno1, int  idno2, double valor){
    RTT *rtt = (RTT*)malloc(sizeof(RTT));
    rtt->idno1 = idno1;
    rtt->idno2 = idno2;
    rtt->valor = valor;
    return rtt;
}

int retornaIdaRTT(RTT * rtt){
    return rtt->idno1;
}

int retornaVoltaRTT(RTT * rtt){
    return rtt->idno2;
}


void imprimeRTT(RTT *rtt){
    //printf("RTT(%d, %d)\nIda: %f\nVolta:%f\n", returnID(rtt->no1), returnID(rtt->no2), rtt->ida, rtt->volta);
    printf("%d %d %.16lf\n", rtt->idno1, rtt->idno2, rtt->valor);
}


RTT * somaRTT(RTT *rtt1, RTT* rtt2){

}

static int compare(const void* a, const void* b) {
    RTT a1 = *(RTT*)a;
    RTT a2 = *(RTT*)b;

    if (a1.valor < a2.valor) return -1;
    if (a1.valor > a2.valor) return 1;

    if (a1.idno1 < a2.idno1) return -1;
    if (a1.idno1 > a2.idno1) return 1;

    if (a1.idno2 < a2.idno2) return -1;
    if (a1.idno2 > a2.idno2) return 1;

    return 0;
}


Item * calculaRTT(Graph *graph,int nVert, int nServ, int nClient, int nMonitor){
    
    int* servidor = retornaServidor(graph);
    int* clientes = retornaCliente(graph);
    int* monitor = retornaMonitor(graph);
    
    
    Item * its = alocaItem(nServ, nClient);

    double **dijkstra_servidor = (double**)malloc(sizeof(double*)*nServ);
    double **dijkstra_clientes = (double**)malloc(sizeof(double*)*nClient);
    double **dijkstra_monitor = (double**)malloc(sizeof(double*)*nMonitor);

    
    for(int i=0; i < nServ; i++){
        dijkstra_servidor[i] = (double *)malloc(sizeof(double)*nVert);
    }

    for(int i=0; i < nClient; i++){
        dijkstra_clientes[i] = (double *)malloc(sizeof(double)*nVert);
    }

    for(int i=0; i < nMonitor; i++){
        dijkstra_monitor[i] = (double *)malloc(sizeof(double)*nVert);
    }

     for(int i=0; i < nServ; i++){
        dijkstra(graph, servidor[i], dijkstra_servidor[i]);
    } 

    for(int i=0; i < nClient; i++){
        dijkstra(graph, clientes[i], dijkstra_clientes[i]);
    }

    for(int i=0; i < nMonitor; i++){
        dijkstra(graph, monitor[i], dijkstra_monitor[i]);
    }

    
	// printf("Servidores: \n");
    // for(int i=0; i < nServ; i++){
    //     for(int j=0; j<nVert; j++){
    //         printf("%.2f ", dijkstra_servidor[i][j]);
    //     }
    //     printf("\n");
    // }
	// printf("\nClientes: \n");
    

    // for(int i=0; i < nClient; i++){
    //     for(int j=0; j<nVert; j++){
    //         printf("%.2f ", dijkstra_clientes[i][j]);
    //     }
    //     printf("\n");
    // }
    
    // printf("\nMonitores: \n");
    // for(int i=0; i < nMonitor; i++){
    //     for(int j=0; j<nVert; j++){
    //         printf("%.2f ", dijkstra_monitor[i][j]);
    //     }
    //     printf("\n");
    // }
    


    double rttSC, rtSM, ida1, ida2, volta1, volta2, idaRtt, voltaRtt, rtt1, rtt2, rttMin, rttM;
    RTT ** lista = (RTT **)malloc(sizeof(RTT*) * nServ * nClient);
    int indice = 0;
    for(int i = 0; i < nServ; i++){
        rttMin = DBL_MAX;
        for(int j = 0; j < nClient; j++){

            // RTT
            idaRtt = dijkstra_servidor[i][clientes[j]];
            voltaRtt = dijkstra_clientes[j][servidor[i]];
            rttSC = idaRtt + voltaRtt;
            
            for(int k = 0; k <nMonitor; k++){

                rtt1 = dijkstra_servidor[i][monitor[k]] + dijkstra_monitor[k][servidor[i]]; //ok
                rtt2 = dijkstra_monitor[k][clientes[j]] + dijkstra_clientes[j][monitor[k]]; 
                rttM = rtt1 + rtt2;
                // printf("%f\n", rttM);
                if(rttM < rttMin){  
                    rttMin = rttM;
                }
            }
            // printf("%f", rttMin);

            // printf("%d %d %f\n", servidor[i], clientes[j], rttMin/rttSC);
            RTT * rtt = CriaRTT(servidor[i], clientes[j], rttMin/rttSC);
            lista[indice] = rtt;
            indice++;
        }
    }
    // qsort(graph->edge, graph->E, sizeof(graph->edge[0]), comparacao);

    for(int i=0; i<nServ*nClient; i++){
        imprimeRTT(lista[i]);
    }

    printf("\n---------------------\n");
    
    qsort(lista, nServ * nClient, sizeof(lista[0]), compare);

    for(int i=0; i<nServ*nClient; i++){
        imprimeRTT(lista[i]);
    }
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