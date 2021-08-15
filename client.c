#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "PQ.h"
#include "item.h"
#include "aresta.h"

Item* retornaGporID(Item** vetor, int size, int ID);
void relax(Item** pq, int* N, int* map, Aresta* e, double* distTo, Aresta** edgeTo);
Item** leEntrada(char* path, Aresta*** edgeTo, int* nVert, int* nEdge, int* nServ, int* nClient, int* nMonitor);

int main(int argc, char** argv) {

    int* map;
    int N, nVert, nEdge, nServ, nClient, nMonitor, v;
    Aresta*** endEdgeTo;
    double* distTo;

    endEdgeTo = malloc(sizeof(Aresta**));
    Item** listaV = leEntrada(argv[1], endEdgeTo, &nVert, &nEdge, &nServ, &nClient, &nMonitor);

    Aresta** edgeTo = *endEdgeTo;

    free(endEdgeTo);

    distTo = malloc(sizeof(double)*nVert);
    Aresta** todasArestas = malloc(sizeof(Aresta*) * nEdge);

    Item** pq = PQ_init(nVert, &map, &N);

    for(v=0; v<nVert; v++){
        if(retornaTipo(retornaGporID(listaV, nVert, v)) == 1){
            distTo[v] = 0;
            PQ_insert(pq, retornaGporID(listaV, nVert, v), &N, map, 0.0);
        }
        else distTo[v] = DBL_MAX;
    }


    // removendo o menor elemento e imprimindo
    while (!PQ_empty(&N)) {
        Item* p = PQ_delmin(pq, map, &N);
        for(v=0; v<nEdge; v++){
            if (apontaPara(edgeTo[v], p)){
                if(!relaxed(edgeTo[v])){
                    relax(pq, &N, map, edgeTo[v], distTo, todasArestas);
                }
            }
        }
        printf("Identificador %d, distancia %lf\n", id(p), value(p));
    }
}

int PQ_contains(Item** pq, int* N, int ID){
    int i;
    for (i=1; i<=*N; i++){
        if (returnID(pq[i]) == ID) return 1;
    }
    return 0;
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
}

Item* retornaGporID(Item** vetor, int size, int ID){
    int i;
    for(i=0; i<size; i++){
        if(returnID(vetor[i]) == ID) return vetor[i];
    }
    return NULL;
}