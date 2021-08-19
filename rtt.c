#include "rtt.h"
#include <stdio.h>
#include <stdlib.h>

struct rtt {
    double ida;
    double volta;
    Item *no1;
    Item *no2;
};

RTT* CriaRTT(Item **vetor, int size, double ida, double volta, int i, int j){
    RTT *rtt = (RTT*)malloc(sizeof(RTT));
    rtt->ida = ida;
    rtt->volta = volta;
    rtt->no1 = retornaGporID(vetor,size,i);
    rtt->no2 = retornaGporID(vetor,size,j);
    return rtt;
}

void imprimeRTT(RTT *rtt){
    //printf("%f\n", rtt->ida);
    //printf("%f\n", rtt->volta);
    printf("%f\n",rtt->ida + rtt->volta);
}

