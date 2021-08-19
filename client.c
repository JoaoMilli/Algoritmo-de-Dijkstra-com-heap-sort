#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "PQ.h"
#include "rtt.h"
#include "item.h" 
#include "aresta.h"
#include "dijkstra.h"

Item** leEntrada(char* path, Aresta*** edgeTo, int* nVert, int* nEdge, int* nServ, int* nClient, int* nMonitor);
void liberaMemoria(Aresta*** endEdgeTo, double* distTo, Aresta** todasArestas, int nVert, int nEdge);

int main(int argc, char** argv) {

    int* map;
    int N, nVert, nEdge, nServ, nClient, nMonitor, v;
    Aresta*** endEdgeTo;
    double* distTo;

    endEdgeTo = malloc(sizeof(Aresta**));
    Item** listaV = leEntrada(argv[1], endEdgeTo, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

    Aresta** edgeTo = *endEdgeTo;


    distTo = malloc(sizeof(double)*nVert);
    Aresta** todasArestas = malloc(sizeof(Aresta*) * nEdge);

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
    RTT **listaRTT = malloc(sizeof(RTT*) * (nServ * nClient));
    int k =0; 

    for(int i=0; i<nVert; i++){
        if(retornaTipo(listaV[i]) == 1) {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i])); 

            //Distancia servidor-cliente
            for(int j=0; j<nVert; j++){
                if(retornaTipo(listaV[j]) == 2){
                    double ida = distTo[returnID(listaV[j])];
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    printf("ida %f volta %f\n", ida, volta);
                    RTT *rtt = CriaRTT(listaV, nVert ,ida, volta,returnID(listaV[i]),returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    k++;
                } 
            }
        }
    }

    // RTT*
    /*                     S -> M      M -> C  S -> M      M -> C
    RTT∗ (0, 4) = min{RTT(0, 1) + RTT(1, 4), RTT(0, 2) + RTT(2, 4)}
                = min{20 + 20, 19 + 10}
                = min{40, 29}
                = 29
*/

    // RTT (S->M)

    for(int i=0; i<nVert; i++){
        if(retornaTipo(listaV[i]) == 1) {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i])); 

            //Distancia servidor-cliente
            for(int j=0; j<nVert; j++){
                if(retornaTipo(listaV[j]) == 3){
                    double ida = distTo[returnID(listaV[j])];
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    printf("ida %f volta %f\n", ida, volta);
                    RTT *rtt = CriaRTT(listaV, nVert ,ida, volta,returnID(listaV[i]),returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    k++;
                } 
            }
        }
    }

     for(k=0; k < 3; k++){
        imprimeRTT(listaRTT[k]); 
        printf("--\n");    
    }
    printf("\n");


    // RTT (M -> C)

    for(int i=0; i<nVert; i++){
        if(retornaTipo(listaV[i]) == 3) {
            dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[i])); 

            //Distancia servidor-cliente
            for(int j=0; j<nVert; j++){
                if(retornaTipo(listaV[j]) == 2){
                    double ida = distTo[returnID(listaV[j])];
                    dijkstra(nVert, map, N, listaV, distTo, nEdge, edgeTo, todasArestas, returnID(listaV[j]));
                    double volta = distTo[returnID(listaV[i])];
                    //printf("ida %f volta %f\n", ida, volta);
                    RTT *rtt = CriaRTT(listaV, nVert ,ida, volta,returnID(listaV[i]),returnID(listaV[j]));
                    listaRTT[k] = rtt;
                    k++;
                } 
            }
        }
    }    

    for(k=0; k < 5; k++){
        imprimeRTT(listaRTT[k]); 
        printf("--\n");    
    }

}

Item** leEntrada(char* path, Aresta*** edgeTo, int* nVert, int* nEdge, int* nServ, int* nClient, int* nMonitor){

    FILE* file = fopen(path, "r");

    int aux, aux_id1, aux_id2;
    double aux_weight;
    Aresta* aux_aresta;

    fscanf(file, "%d", nVert);
    fscanf(file, "%d", nEdge);
    fscanf(file, "%d", nServ);
    fscanf(file, "%d", nClient);
    fscanf(file, "%d", nMonitor);

    Item** listaV = malloc(sizeof(Item*) * (*nVert));

    for(aux = 0; aux< *nServ; aux++){
        fscanf(file, "%d", &aux_id1);
        listaV[aux] = make_item(aux_id1, 0, 1);
    }

    while(aux < (*nServ) + (*nClient)){
        fscanf(file, "%d", &aux_id1);
        listaV[aux] = make_item(aux_id1, 0, 2);
        aux++;
    }

    while(aux < (*nServ) + (*nClient) + (*nMonitor)){
        fscanf(file, "%d", &aux_id1);
        listaV[aux] = make_item(aux_id1, 0, 3);
        aux++;
    }

    for(int i=0; i< (*nVert); i++){
        if(retornaGporID(listaV, (*nServ) + (*nClient) + (*nMonitor), i) == NULL){
            listaV[aux] = make_item(i, 0, 4);
        }
    }

    *edgeTo= malloc(sizeof(Aresta*) * (*nEdge));

    for(aux = 0; aux < *nEdge; aux++){
        fscanf(file, "%d", &aux_id1);
        fscanf(file, "%d", &aux_id2);
        fscanf(file, "%lf", &aux_weight);

        Item* aux1 =retornaGporID(listaV, *nVert, aux_id1);
        Item* aux2 =retornaGporID(listaV, *nVert, aux_id2);

        aux_aresta = criaAresta(aux1, aux2, aux_weight);
        (*edgeTo)[aux] = aux_aresta;
    }

    fclose(file);

    return listaV;

}

void liberaMemoria(Aresta*** endEdgeTo, double* distTo, Aresta** todasArestas, int nVert, int nEdge){
    free(distTo);
    // for(int i=0; i<nVert; i++){
        
    // }
    // for(int j=0; j<nEdge; j++){
    //     free(todasArestas[j]);
    // }
    free(todasArestas);
}