#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

Item** PQ_init(int maxN, int** map, int* N);  // cria uma min PQ com capacidade maxN
void PQ_insert(Item **pq, Item* v, int* N, int* map, double value);  // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item* PQ_delmin(Item **pq, int* map, int* N);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(Item **pq, int id, int* map, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item* PQ_min(Item **pq);          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(int* N);      // Retorna True se a PQ não tem elementos
int PQ_size(int* N);         // Número de elementos na PQ
void PQ_finish(Item **pq, int *N, int* map);       // Libera memória
int PQ_contains(Item** pq, int* N, int ID);
#endif
