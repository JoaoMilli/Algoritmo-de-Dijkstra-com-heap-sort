#ifndef ITEM_H
#define ITEM_H

typedef struct item Item;

#define id(A)          (returnID(A))                           // retorna identificador do nó
#define value(A)        (returnValue(A))                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item* t = A; A = B; B = t; }   // troca dois nós

Item* make_item(int id, double value, int tipo);
Item* retornaGporID(Item** vetor, int size, int ID);
int returnID(Item* item);
void modificaID(Item* item, int ID);
double returnValue(Item* item);
void modificaValue(Item* item, double value);
void destroiItem(Item* item);
int retornaTipo(Item* item);

#endif
