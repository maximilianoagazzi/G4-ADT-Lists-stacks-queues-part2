#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/list.h"

// Función de comparación para enteros
int cmp_int(void* a, void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main() {

    // 1. Crear lista con 10 nodos vacíos
    list* l = list_create(10);
    if(l == NULL) {
        printf("Error al crear la lista\n");
        return 1;
    }

    // 2. Asignar enteros aleatorios a cada nodo usando set_node
    for(int i = 0; i < 10; i++) {
        int* valor = malloc(sizeof(int));
        *valor = rand() % 100;
        if(set_node(l, valor) != 0) {
            printf("Error al setear nodo %d\n", i);
        }
    }

    // 3. Recorrer lista usando get_next_node y get_data
    printf("Lista de enteros:\n");
    node* aux = list_get_head(l);  // necesitarías esta función opaca en list.h
    while(aux != NULL) {
        int* val = (int*)get_data(aux);
        printf("%d ", *val);
        aux = *get_next_node(aux);
    }
    printf("\n");

    // 4. Liberar memoria
    list_free(&l, true);

    return 0;
}