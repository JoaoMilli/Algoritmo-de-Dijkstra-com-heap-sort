#include "item.h"
#include <stdlib.h>

struct item{
  int id;           // identificador do nó
  double value;     // valor associado ao nó
  int tipo;
};

Item* make_item(int id, double value) {
    Item* t = malloc(sizeof(Item));
    modificaID(t, id);
    modificaValue(t, value);
    return t;
}

Item * alocaItem(int nServ, int nClient){
    Item * t = (Item*)malloc(sizeof(Item) * nServ * nClient);
    return t;
}

int returnID(Item* item){
    return item->id;
}

double returnValue(Item* item){
    return item->value;
}

void modificaID(Item* item, int ID){
    item->id = ID;
}

void modificaValue(Item* item, double value){
    item->value = value;
}

void destroiItem(Item* item){
    free(item);
}

int retornaTipo(Item* item){
    return item->tipo;
}

Item* retornaGporID(Item** vetor, int size, int ID){
    int i;
    for(i=0; i<size; i++){
        if(returnID(vetor[i]) == ID) return vetor[i];
    }
    return NULL;
};

