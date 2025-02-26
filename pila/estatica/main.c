#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PILA 300
#define minimo(X, Y) ((X)<(Y)?X:Y)

typedef struct{
    char pila[TAM_PILA];
    unsigned tope;
}t_pila;

void crearPila(t_pila * p);
int pilaLlena(t_pila *p, unsigned tam);
int pilaVacia(t_pila *p, unsigned tam);
void eliminarPila(t_pila *p);
int ponerEnPila(t_pila *p,void* d ,unsigned tam);
int sacarDePila(t_pila *p,void* d ,unsigned tam);
int verTope(t_pila *p,void* d ,unsigned tam);


void crearPila(t_pila * p){
    p->tope = TAM_PILA;
}

int pilaLlena(t_pila *p, unsigned tam){
    return (p->tope < sizeof(unsigned) + tam) ;
}

int pilaVacia(t_pila *p, unsigned tam){
    return p->tope == TAM_PILA ;
}
void eliminarPila(t_pila *p){
    p->tope == TAM_PILA;
    return;
}

int ponerEnPila(t_pila *p,void* d ,unsigned tam){
    if(p->tope < sizeof(unsigned) + tam)return 0;

    p->tope -= tam;
    memcpy(p->pila + p->tope, d, tam);

    p->tope -= sizeof(unsigned);

    memcpy(p->pila + p->tope, &tam, sizeof(unsigned));
    return 1;
}

int sacarDePila(t_pila *p,void* d ,unsigned tam){
    unsigned tam_info;

    if(p->tope == TAM_PILA)return 0;

    memcpy(&tam_info ,p->pila + p->tope, sizeof(unsigned));
    p->tope += sizeof(unsigned);

    memcpy(d, p->pila + p->tope, minimo(tam, tam_info));
    p->tope += tam_info;
    return 1;
}

int verTope(t_pila *p,void* d ,unsigned tam){
    int tam_info;

    if(p->tope == TAM_PILA)return 0;

    memcpy(&tam_info ,p->pila + p->tope, sizeof(unsigned));
    memcpy(d, p->pila + p->tope + sizeof(unsigned) ,
           minimo(tam, tam_info));

    return 1;
}


