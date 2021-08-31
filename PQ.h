#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

// cria uma min PQ com capacidade maxN
Item** PQ_init(int maxN, int** map, int* N);  

// Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
void PQ_insert(Item **pq, Item* v, int* N, int* map, double value); 

// Remove Item com menor campo 'value' da PQ
Item* PQ_delmin(Item **pq, int* map, int* N);       

// Muda a prioridade do nó com identificador 'id' para 'value'
void PQ_decrease_key(Item **pq, int id, int* map, double value); 

// Retorna Item com menor campo 'value' da PQ
Item* PQ_min(Item **pq);          

// Retorna True se a PQ não tem elementos
bool PQ_empty(int* N);     

// Número de elementos na PQ
int PQ_size(int* N);         

// Libera memória
void PQ_finish(Item **pq, int *N, int* map);       

// Buscar um vértice na PQ
int PQ_buscaVertice(Item ** pq,int *map, int vertice, int *N);

#endif
