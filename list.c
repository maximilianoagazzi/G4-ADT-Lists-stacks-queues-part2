#include <stdio.h>
#include <stdlib.h>
#define LIST_H_EXPORT
#include "list.h"

typedef struct _list {
    node* head;
    node* current;
    int size;
} list;

list* list_create()
{
    list* l = (list* )malloc(sizeof(list));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->current = NULL;
    l->size = 0;
    return l;
}

void list_insert_first(list *l, void* elem) //Inserta al principio
{
    if(l != NULL) {
        node* n = new_node_with(elem);
        if (n != NULL) {
            set_next_node(n, l->head);
            l->head = n;
            l->current = n;
            l->size++;
        }
    }
}

void append(list* l, void* elem) //Inseta al final
{
    if(l != NULL) {
        node** h = &(l->head);
        node* n = new_node_with(elem);
        if (n != NULL) {
            while (*h != NULL) {
                h = get_next_node(*h);
            }
            *h = n;
            l->current = n;
            l->size++;
        }
    }
}

void list_free(list** l, int dinamic) //Destruye la lista y hay que indicarle si los datos son dinamicos o no
{
    void* data;
    if(*l != NULL) {
        while ((*l)->head != NULL) {
            node* temp = (*l)->head;
            (*l)->head = *(get_next_node((*l)->head));
            data = get_data(temp);
            destroy_node(temp);
            if(dinamic == 1 && data != NULL) {
                free(data);
            }
        }
        free(*l);
        *l = NULL;
    }
}