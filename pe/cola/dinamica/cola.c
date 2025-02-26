#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef struct
{
    tNodo *primero, *ultimo;
}tCola;

#define minimo(X, Y) ( (X) < (Y)? (X) : (Y) )

#define reservarMemoria(X,Y,W,Z)( ((X) = (typeof(X))malloc(Y)) == NULL ||   \
                                 ((W) = malloc(Z)) == NULL? free(X),0:1)

void crearCola_din(tCola *p);
int colaLlena_din(const tCola *p, unsigned cantBytes);
int ponerEnCola_din(tCola* p, void* d, unsigned cantBytes);
void vaciarCola_din(tCola *p);
int sacarDeCola_din(tCola *p, void *d, unsigned cantBytes);
int verPrimeroEnCola_din(const tCola* p, void* d, unsigned cantBytes);
int colaVacia_din(const tCola *p);

void crearCola_din(tCola *p){

    p->primero  = p->ultimo = NULL;
}

int colaLlena_din(const tCola *p, unsigned cantBytes){
    tNodo *aux = malloc(sizeof(tNodo));
    void *aux1 = malloc(cantBytes);
    free(aux);
    free(aux1);

    return (aux == NULL || aux1 == NULL);
}
int ponerEnCola_din(tCola* p, void* d, unsigned cantBytes){
    tNodo* aux;
    if(!reservarMemoria(aux, sizeof(tNodo), aux->info, cantBytes))
        return 0;
    aux->sig = NULL;
    memcpy(aux->info, d, cantBytes);
    aux->tamInfo = cantBytes;

    if(p->ultimo)
        p->ultimo->sig = aux;
    else
        p->primero = aux;

    p->ultimo = aux;
    return 1;
}
int verPrimeroEnCola_din(const tCola* p, void* d, unsigned cantBytes){
    if(!p->primero)return 0;

    memcpy(d, p->primero->info, minimo(p->primero->tamInfo, cantBytes));
    return 1;
}
int colaVacia_din(const tCola *p){
    return p->primero == NULL;

}
int sacarDeCola_din(tCola *p, void *d, unsigned cantBytes){
    tNodo *deleted = p->primero;
    if(!deleted)return 0;
    p->primero = deleted->sig;

    memcpy(d, deleted->info, minimo(deleted->tamInfo, cantBytes));
    free(deleted->info);
    free(deleted);
    return 1;
}
void vaciarCola_din(tCola *p){
    tNodo *aux;

    while(p->primero){
        aux = p->primero;
        p->primero = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->primero = p->ultimo = NULL;
    return;
}
