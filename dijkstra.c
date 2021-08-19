#include "dijkstra.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

void relax(Item** pq, int* N, int* map, Aresta* e, double* distTo, Aresta** edgeTo){
    Item* itv = retornaFrom(e);
    Item* itw = retornaTo(e);
    int v = returnID(itv);
    int w = returnID(itw);

    if(distTo[w] > (distTo[v] + retornaWeight(e))){
        distTo[w] = distTo[v] + retornaWeight(e);
        edgeTo[w] = e;
        if(PQ_contains(pq, N, w)){
            PQ_decrease_key(pq, w, map, distTo[w]);
        }
        else{
            PQ_insert(pq, itw, N, map, distTo[w]);
        }
    }
    relaxEdge(e);
};

void dijkstra(int nVert, int *map, int N, Item** listaV, double* distTo,int nEdge, Aresta** edgeTo,Aresta** todasArestas, int ID){
    Item** pq = PQ_init(nVert, &map, &N);
    for(int i =0; i <nEdge; i++){
        desrelaxar(edgeTo[i]);
    }
    for(int v=0; v<nVert; v++){
        //if(retornaTipo(retornaGporID(listaV, nVert, v)) == ID){
        if (returnID(listaV[v]) == ID){
            distTo[ID] = 0;
            PQ_insert(pq, retornaGporID(listaV, nVert, ID), &N, map, 0.0);
        }
        else distTo[returnID(listaV[v])] = DBL_MAX;
    }

    // RTT(a, b) = δ(a, b) + δ(b, a).

    // removendo o menor elemento e imprimindo
    while (!PQ_empty(&N)) {
        Item* p = PQ_delmin(pq, map, &N);
        
        for(int v=0; v<nEdge; v++){
            if (apontaPara(edgeTo[v], p)){
          
                if(!relaxed(edgeTo[v])){
                   
                    relax(pq, &N, map, edgeTo[v], distTo, todasArestas);
                }
            }
        }
        printf("Identificador %d, distancia %lf\n", id(p), value(p));
    }

    for(int i=0; i < nVert; i++){
        //printf("distTo[%d] - dentro do dijkstra %.2f\n",i, distTo[i]);
    }
}

int PQ_contains(Item** pq, int* N, int ID){
    int i;
    for (i=1; i<=*N; i++){
        if (returnID(pq[i]) == ID) return 1;
    }
    return 0;
}