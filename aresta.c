#include <stdlib.h>
#include "aresta.h"
#include "item.h"

struct aresta{
    Item* from;
    Item* to;
    double weight;
    int relaxed;
};

Aresta* criaAresta(Item* from, Item* to, double weight){
    Aresta* a = malloc(sizeof(Aresta));
    a->from = from;
    a->to = to;
    a->weight = weight;
    a->relaxed = 0;
    return a;
}

int apontaPara (Aresta* a, Item* to){
    return (returnID(a->from) == returnID(to));
}

Item* retornaFrom(Aresta* a){
    return a->from;
}

Item* retornaTo(Aresta* a){
    return a->to;
}

double retornaWeight(Aresta* a){
    return a->weight;
}

int relaxed(Aresta* a){
    return a->relaxed;
}

void relaxEdge(Aresta* a){
    a->relaxed = 1;
}

void destroiAresta(Aresta* a){
    free(a);
}