#include <stdlib.h>
#include "aresta.h"
#include "item.h"

struct aresta{
    Item* from;
    Item* to;
    double weight;
};

Aresta* criaAresta(Item* from, Item* to, double weight){
    Aresta* a = malloc(sizeof(Aresta));
    a->from = from;
    a->to = to;
    a->weight = weight;
    return a;
}

int apontaPara (Aresta* a, Item* to){
    return (returnID(a->to) == returnID(to));
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

void destroiAresta(Aresta* a){
    free(a);
}