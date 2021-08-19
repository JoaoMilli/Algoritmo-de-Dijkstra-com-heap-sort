#ifndef ARESTA_H
#define ARESTA_H

#include "item.h"

typedef struct aresta Aresta;

Aresta* criaAresta(Item* from, Item* to, double weight);
void destroiAresta(Aresta* a);
int apontaPara(Aresta* a, Item* to);
Item* retornaFrom(Aresta* a);
Item* retornaTo(Aresta* a);
double retornaWeight(Aresta* a);
int relaxed(Aresta* a);
void relaxEdge(Aresta* a);
void desrelaxar(Aresta * a);

#endif