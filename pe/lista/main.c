#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN(X,Y) ((X)<(Y)?(X):(Y))
#define reserveMemory(X,Y,Z,W)( ( ((X) = (typeof(X))malloc(Y)) == NULL) || \
                               (((Z) = malloc(W)) == NULL)? free(X),0:1)

typedef struct sNode
{
    void* data;
    unsigned sized;
    struct sNode *next;
}tNode;

typedef tNode * tlist;

void createList(tlist * l);
int insertIntoList(tlist * l, const void*data, unsigned sized);
void deleteList(tlist * l);
void sortList(tlist * l, int(*cmp)(const void*, const void*));
int showFirst(const tlist * l, void*data, unsigned sized);
int showLast(const tlist * l, void*data, unsigned sized);
void walkList(tlist *l, void* param, unsigned sized,void(*action)(void*, void*, unsigned, unsigned));
void invertList(tlist *l);
void walkListReverse(tlist *l, void* param, unsigned sized,void(*action)(void*, void*, unsigned, unsigned));
int insertNelementsInOrder(tlist * l, void* data, unsigned sized, unsigned* n,
                           int(*cmp)(const void*, const void*));


tNode * getMinor(tlist * l, int(*cmp)(const void*, const void*));

void createList(tlist * l)
{
    (*l) = NULL;
    return;
}

int insertIntoList(tlist * l, const void*data, unsigned sized)
{
    tNode * aux;

    while(*l)
        l = &(*l)->next;

    aux = (tNode*)malloc(sizeof(tNode));
    if(aux == NULL || (aux->data = malloc(sized)) == NULL)
    {
        free(aux);
        return 0;
    }


    memcpy(aux->data, data, sized);
    aux->next = NULL;
    aux->sized = sized;
    *l = aux;
    return 1;
}
void deleteList(tlist * l)
{
    tNode * aux;
    while(*l)
    {
        aux = *l;
        l = &aux->next;
        free(aux->data);
        free(aux);
    }
    *l = NULL;
    return;
}
void sortList(tlist * l, int(*cmp)(const void*, const void*))
{
    tNode * minor = NULL;
    unsigned sizeaux;
    void* dataaux;

    if(!*l)return;

    while((*l)->next)
    {
        minor = getMinor(&(*l)->next, cmp);
        if(cmp( (*l)->data, minor->data ) > 0)
        {
            dataaux = (*l)->data;
            sizeaux = (*l)->sized;
            (*l)->data = minor->data;
            (*l)->sized = minor->sized;
            minor->data = dataaux;
            minor->sized = sizeaux;
        }
        l = &(*l)->next;
    }
    return;
}

tNode * getMinor(tlist * l, int(*cmp)(const void*, const void*))
{
    tNode *minor = (*l);
    while(*l)
    {
        if(cmp((*l)->data, minor->data) < 0)
            minor = *l;
        l = &(*l)->next;
    }
    return minor;

}

int showFirst(const tlist * l, void*data, unsigned sized)
{
    if(!*l)return 0;

    memcpy(data, (*l)->data, MIN((*l)->sized, sized));
    return 1;
}
int showLast(const tlist * l, void*data, unsigned sized)
{
    if(!*l)return 0;

    while((*l)->next)
        l = &(*l)->next;

    memcpy(data, (*l)->data, MIN((*l)->sized, sized));
    return 1;
}
void walkList(tlist *l, void* param, unsigned sized,void(*action)(void*, void*, unsigned, unsigned))
{
    if(!*l)return;

    action((*l)->data, param, (*l)->sized, sized);
    walkList(&(*l)->next,param,sized,action);
    return;
}

void invertList(tlist *l)
{
    tNode * rest;
    if( (*l) == NULL || (*l)->next == NULL )return;


    rest = (*l)->next;

    invertList(&rest);

    (*l)->next->next = *l;
    (*l)->next = NULL;
    (*l) = rest;
    return;

}

void walkListReverse(tlist *l, void* param, unsigned sized,void(*action)(void*, void*, unsigned, unsigned))
{
    if(!*l)return;

    walkListReverse(&(*l)->next,param,sized,action);
    action((*l)->data, param, (*l)->sized, sized);
    return;
}


int insertNelementsInOrder(tlist * l, void* data, unsigned sized, unsigned* n,
                           int(*cmp)(const void*, const void*)){
    tNode *aux, **end;
    int result;

    while((*l) != NULL){
        result = cmp((*l)->data, data);
        if(result<0)break;
        l = &(*l)->next;
    }

    if((*n)>0){
        if(!reserveMemory(aux, sizeof(tNode), aux->data, sized)) return 0;
        memcpy(aux->data, data, sized);
        aux->sized = sized;

        if((*l) == NULL)//hay q insertar al final
        {
            aux->next = NULL;
            (*l) = aux;
        }
        else{
            aux->next = (*l);
            (*l) = aux;
        }
        (*n) -= 1;
        return 1;
    }
    else{
        if((*l) == NULL)return 1;
        end = l;
        while((*end)->next){
            end = &(*end)->next;
            }
        free((*end)->data);
        free(*end);
        (*end) = NULL;
        if(!reserveMemory(aux, sizeof(tNode), aux->data, sized)) return 0;
        memcpy(aux->data, data, sized);
        aux->sized = sized;
        aux->next = (*l);
        (*l) = aux;
        return 1;
    }

}
