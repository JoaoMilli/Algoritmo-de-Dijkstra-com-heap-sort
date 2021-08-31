#ifndef ITEM_H
#define ITEM_H

/*Struct que define um item na heap*/

typedef struct item Item;

#define id(A)          (returnID(A))                           
#define value(A)        (returnValue(A))                       
#define more(A, B)      (value(A) > value(B))           
#define exch(A, B)      { Item* t = A; A = B; B = t; } 


/*
*  Cria um item
*  inputs: O ID referente ao item e seu valor em double
*  output: O ponteiro para o Item alocado
*  pre-condicao: nada
*/

Item* make_item(int id, double value);


/*
*  Retorna o ID de um item
*  inputs: Um ponteiro para item
*  output: O ID do item
*  pre-condicao: O item deve existir e estar devidamente inicializado
*/

int returnID(Item* item);

/*
*  Modifica o ID de um determinado item
*  inputs: O ponteiro para o item, o novo ID do item
*  output: nada
*  pre-condicao: O item deve existir e estar devidamente inicializado
*/

void modificaID(Item* item, int ID);

/*
*  Retorna o valor de um item
*  inputs: O ponteiro para o item
*  output: O valor do item
*  pre-condicao: O item deve existir e estar devidamente inicializado
*/

double returnValue(Item* item);

/*
*  Modifica o valor de um determinado item
*  inputs: O ponteiro para o item, o novo valor do item
*  output: nada
*  pre-condicao: O item deve existir e estar devidamente inicializado
*/

void modificaValue(Item* item, double value);

/*
*  Libera memória alocada para o item
*  inputs: O ponteiro para o item
*  output: nada
*  pre-condicao: nada 
*/

void destroiItem(Item* item);

/*
*  Retorna um inteiro sinalizando o tipo do item
*  inputs: O ponteiro para o item
*  output: O inteiro representando o tipo do item
*  pre-condicao: nada 
*/

int retornaTipo(Item* item);

/*
*  Aloca a estrutura de um Item
*  inputs: a quantidade de servidores e clientes
*  output: O Item
*  pre-condicao: nenhum 
*/
Item * alocaItem(int nServ, int nClient);

#endif
