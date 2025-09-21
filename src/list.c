#include <stdio.h>
#include <stdlib.h>
#define LIST_H_EXPORT
#include "list.h"

typedef struct _list {
    node* head;
    int size;
} list;

list* list_create(int cant)
{
    node* head = NULL;
    node* prev = NULL;
    for(int i=0; i<cant; i++) {
        node* nuevo = new_node();
        if (head == NULL) {
            head = nuevo;      // el primero se convierte en cabeza
        } else {
            set_next_node(prev, nuevo); // enlazo el anterior con el actual
        }
        prev = nuevo; 
    }

    list* l = (list* )malloc(sizeof(list));
    if (l != NULL) {
        l->head = head;
        l->size = cant;
    }
    return l;
}

int set_node(list* l, void* elem)
{
    if(l != NULL) {
        node* aux = l->head;
        while (aux != NULL && get_data(aux) != NULL) {
            aux = *get_next_node(aux);
        }
        if(aux != NULL) {
            set_data(aux, elem);
            return 0;
        }
    }
    return -1;
}

int list_get_size(list* l)
{
    if(l == NULL) {
        return -1;
    }
    return l->size;
}

node* list_get_head(list* l)
{
    if(l != NULL) {
        return l->head;
    }
    return NULL;
}

node* list_get_next(list* l, int index)
{
    if (l != NULL && l->head != NULL && index >= 0 && index < l->size) {
        node* aux = l->head;
        for (int i = 0; i < index; i++) {
            aux = *get_next_node(aux);
        }
        return aux;
    }
    return NULL; // índice inválido
}

node* list_get_eol(list* l)
{
    if (l != NULL && l->head != NULL) {
        node* aux = l->head;
        while (*get_next_node(aux) != NULL) {
            aux = *get_next_node(aux);
        }
        return aux;
    }
    return NULL;
}

void list_free(list** l, int dinamic)  //Destruye la lista y hay que indicarle si los datos en los nodos son dinamicos o no
{
    void* data;
    if(*l != NULL) {
        node* aux = (*l)->head;
        while((*l)->head != NULL) {
            (*l)->head = *get_next_node((*l)->head);
            data = destroy_node(aux);
            if(dinamic == 1) {
                free(data);
            }
            aux = (*l)->head;
        }
        free(*l);
    }
}

node** find(list* l, void* val, int cmp(void*, void*))  //Encuentra el nodo con val
{
    if(l == NULL) {
        return NULL;
    }
    node** aux = &(l->head);
    while (*aux != NULL && cmp(val, get_data(*aux)) != 0) {
        aux = get_next_node(*aux);
    }
    return aux;
}

node** find_pos(list* l, void* elem, int cmp(void*, void*)) //Encuentra la posicion donde debe ir elem en una lista ordenada
{
    if(l == NULL) {
        return NULL;
    }
    node** aux = &(l->head);
    while (*aux != NULL && cmp(elem, get_data(*aux)) > 0) {
        aux = get_next_node(*aux);
    }
    return aux;
}

list* insert(list* l, void* val) //inserta al principio
{
    if(l == NULL) {
        return NULL;
    }
    node** aux = &(l->head);
    node* n = new_node_with(val);
    if (n != NULL) {
        set_next_node(n, *aux);
        *aux = n;
    }
    l->size++;
    return l;
}

node* insert_sort(list* l, void* elem, int cmp(void*, void*)) //Inserta de forma ordenada
{
    if(l == NULL) {
        return NULL;
    }
    node* n = new_node_with(elem);
    if(n != NULL) {
        node** pos = find_pos(l, elem, cmp);
        set_next_node(n, *pos);
        *pos = n;
        l->size++;
    }
    return n;
}

void append(list* l, void* elem) //Inseta al final
{
    if(l != NULL) {
        node** h = &(l->head);
        node* n = new_node_with(elem);
        while (*h != NULL) {
            h = get_next_node(*h);
        }
        *h = n;
        l->size++;
    }
}

node* remove_node(list* l, void* val, int cmp(void*, void*)) //Remueve el nodo de la lista, pero no lo elimina
{
    if(l == NULL) {
        return NULL;
    }
    node** h = &(l->head);
    node* r = NULL;
    h = find(l, val, cmp);
    if(*h != NULL) {
        r = *h;
        *h = *get_next_node(r);
        set_next_node(r, NULL);
        l->size--;
    }
    return r;
}