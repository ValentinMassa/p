#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COLA 300
#define minimo(X, Y) ((X)<(Y)?X:Y)

typedef struct{
    char cola[TAM_COLA];
    unsigned inicio,fin, tam;
}t_cola;

void crearcola(t_cola *p);
int colaLlena(t_cola *p, unsigned tam);
int colaVacia(t_cola *p, unsigned tam);
void eliminarcola(t_cola *p);
int ponerEncola(t_cola *p,void* d ,unsigned tam);
int sacarDecola(t_cola *p, void* d , unsigned tam);
int verPrimero(t_cola *p,void* d ,unsigned tam);



void crearcola(t_cola *p){
        p->fin = TAM_COLA -50;
        p->inicio = TAM_COLA -50;
        p->tam = TAM_COLA;
    return;
}
int colaLlena(t_cola *p, unsigned tam){

   return  p->tam < (sizeof(unsigned)+tam);
}
int colaVacia(t_cola *p, unsigned tam){
    return p->tam == TAM_COLA;
}
void eliminarcola(t_cola *p){
    p->tam = TAM_COLA;
    p->inicio = p->fin;
    return;
}

int ponerEncola(t_cola *p,void* d ,unsigned tam){
    int ini, fin;

    if(p->tam > sizeof(unsigned) + tam)return 0;

    p->tam -= sizeof(unsigned) + tam;
    if((ini = minimo( sizeof(tam), TAM_COLA - p->fin))!=0)
        memcpy(p->cola + p->fin, &tam, ini);
    if((fin = sizeof(tam) - ini ) != 0)
        memcpy(p->cola, (char*)&tam + ini, fin);
    p->fin = fin? fin: p->fin + ini;

    if((ini = minimo(tam, TAM_COLA - p->fin))  != 0)
        memcpy(p->cola + p->fin, d, ini);

    if((fin = tam - ini) != 0)
        memcpy(p->cola, (char*)d +ini, fin);
    p->fin = fin?fin: p->fin + ini;

    return 1;
}
int sacarDecola(t_cola *p, void* d , unsigned tam){
    int ini, fin, cantBytes;
    if(p->tam == TAM_COLA) return 0;

    if((ini = minimo(sizeof(tam), TAM_COLA - p->inicio))!=0)
        memcpy(&cantBytes, p->cola + p->inicio, ini);
    if((fin = sizeof(tam) - ini)!= 0)
        memcpy((char*)&cantBytes + ini, p->cola, fin);
    p->inicio = fin? fin : p->inicio + ini;

    p->tam += sizeof(tam) + cantBytes;

    cantBytes = minimo(cantBytes, tam);

    if((ini = minimo(cantBytes, TAM_COLA - p->inicio))!=0)
        memcpy(d, p->cola + p->inicio, ini);
    if((fin = cantBytes - ini)!= 0)
        memcpy((char*)d + ini, p->cola, fin);
    p->inicio = fin? fin : p->inicio + ini;
    return 1;
}


int verPrimero(t_cola *p,void* d ,unsigned tam){
    int tambyes, ini, fin, pos = p->inicio;

    if(p->tam == TAM_COLA)return 0;

    if((ini = minimo( sizeof(tam), TAM_COLA - pos))!=0)
        memcpy(&tambyes, p->cola + pos, ini);
    if((fin = sizeof(tam) - ini ) != 0)
        memcpy((char*)&tambyes + ini, p->cola, fin);
    pos = fin? fin: pos + ini;

    tambyes = minimo(tambyes, tam);

    if((ini = minimo(tambyes, TAM_COLA - pos))  != 0)
        memcpy(d, p->cola + pos, ini);
    if((fin = tambyes - ini) != 0)
        memcpy((char*)d + ini, p->cola, fin);

    return 1;
}

