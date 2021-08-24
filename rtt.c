#include "rtt.h"
#include <stdio.h>
#include <stdlib.h>

struct rtt {
    double ida;
    double volta;
    Item *no1;
    Item *no2;
};

RTT* CriaRTT(Item **vetor, int size, double ida, double volta, Item* no1, Item* no2){
    RTT *rtt = (RTT*)malloc(sizeof(RTT));
    rtt->ida = ida;
    rtt->volta = volta;
    rtt->no1 = no1;
    rtt->no2 = no2;
    return rtt;
}

Item* retornaIdaRTT(RTT * rtt){
    return rtt->no1;
}

Item* retornaVoltaRTT(RTT * rtt){
    return rtt->no2;
}


void imprimeRTT(RTT *rtt){
    //printf("RTT(%d, %d)\nIda: %f\nVolta:%f\n", returnID(rtt->no1), returnID(rtt->no2), rtt->ida, rtt->volta);
    printf("(%d, %d) ida: %f volta:%f soma:%f\n", returnID(rtt->no1), returnID(rtt->no2), rtt->ida , rtt->volta,rtt->ida + rtt->volta);
}

double retornaDistancia(RTT *rtt){
    return (rtt->ida + rtt->volta);
}
