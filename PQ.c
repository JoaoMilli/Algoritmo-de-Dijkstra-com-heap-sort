#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"
#include "item.h"

void swap(Item **pq, int* map, int i, int j) {
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Item **a, int* map, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(a, map, k, k/2);
        k = k/2;
    }
}

void fix_down(Item **a, int* map, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(a, map, k, j);
    k = j;
  }
}

Item** PQ_init(int maxN, int** map, int* N) {
    Item **pq = malloc((maxN+1) * sizeof (Item*));
    *map = malloc((maxN+1) * sizeof (int));
    *N = 0;
    return pq;
}

void PQ_insert(Item **pq, Item* v, int* N, int* map, double value) {

    modificaValue(v, value);
    (*N)++;
    pq[*N] = v;
    
    map[id(v)] = *N;

    fix_up(pq, map, *N);
}

int PQ_buscaVertice(Item ** pq,int *map, int vertice, int *N){
    return map[vertice] <= (*N);
}

Item* PQ_delmin(Item **pq, int* map, int* N) {
    Item* min = pq[1];
    swap(pq, map, 1, *N);
    (*N)--;
    fix_down(pq, map, *N, 1);
    return min;
}

Item* PQ_min(Item **pq) {
    return pq[1];
}

void PQ_decrease_key(Item **pq, int id, int* map, double value) {
    int i = map[id];
    modificaValue(pq[i], value);
    fix_up(pq, map, i);
}

bool PQ_empty(int* N) {
    return (*N) == 0;
}

int PQ_size(int* N) {
    return (*N);
}

void PQ_finish(Item **pq, int *N, int* map) {
    int i;
    for(i=0; i<(*N); i++) destroiItem(pq[i]);
    free(pq);
    free(map);
}


