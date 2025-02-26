#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define minimo(X, Y) ( (X) < (Y)? (X):(Y) )
#define ReservarMemoria(X,Y,Z,W)( ( ((X) = (typeof(X))malloc(Y)) == NULL) ||   \
                                 ( (Z) = malloc(W)) == NULL ? free(X),0:1)

 typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;
typedef tNodo *tPila;


void CrearPila(tPila *p);
int pilaLlena(const tPila *p, unsigned cantBytes);
int ponerEnPila(tPila *p, const void *d, unsigned cantBytes);
int verTope(const tPila* p,  void *d, unsigned cantBytes);
int pilaVacia(const tPila *p);
int sacarDePila(tPila* p,  void *d, unsigned cantBytes);
void vaciarPila(tPila *p);


void CrearPila(tPila *p)
{
    *p = NULL;
}

int pilaLlena(const tPila *p, unsigned cantBytes)
{
    tNodo *_auxNodo = (tNodo*)malloc(sizeof(tNodo));
    void *_info = malloc(cantBytes);

    free(_info);
    free(_auxNodo);

    return ( _info == NULL || _auxNodo == NULL );
}

int ponerEnPila(tPila *p, const void *d, unsigned cantBytes)
{
    tNodo * node;

    if(!ReservarMemoria(node, sizeof(tNodo), node->info, cantBytes))
        return 0;

    memcpy(node->info, d, cantBytes);
    node->tamInfo = cantBytes;
    node->sig = (*p);
    (*p) = node;
    return 1;
}
int verTope(const tPila* p,  void *d, unsigned cantBytes){
    if(!*p)return 0;

    memcpy(d, (*p)->info, minimo((*p)->tamInfo,cantBytes) );
    return 1;


}
int pilaVacia(const tPila *p){
    return ((*p) == NULL);
}
int sacarDePila(tPila* p,  void *d, unsigned cantBytes){
    tNodo *aux = (*p);

    if(!aux)return 0;

    (*p) = aux->sig;

    memcpy(d, aux->info, minimo(aux->tamInfo,cantBytes) );
    free(aux->info);
    free(aux);
    return 1;
}
void vaciarPila(tPila *p){
    tNodo *aux;

    while(*p){
        aux = (*p);
        (*p) = aux->sig;
        free(aux->info);
        free(aux);
    }
    (*p) = NULL;
    return;
}
