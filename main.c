#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/stack.h"

void stack_print(stack* s) {
    if(!s) return;

    int len = stack_length(s);
    if(len == 0) {
        printf("Pila vacía.\n");
        return;
    }

    void** temp = malloc(sizeof(void*) * len); // arreglo temporal para guardar los elementos
    if(!temp) return;

    printf("Pila (top a bottom): ");
    int i = 0;
    while(!stack_is_empty(s)) {
        int* val = (int*)pop(s);
        printf("%d ", *val);
        temp[i++] = val; // guardamos el puntero temporalmente
    }
    printf("\n");

    // Volvemos a llenar la pila en el mismo orden
    for(i = len - 1; i >= 0; i--) {
        push(s, temp[i]);
    }

    free(temp);
}

int main() {
    stack* s = stack_new();
    if(!s) {
        printf("Error al crear la pila.\n");
        return 1;
    }

    // Agregar 15 enteros
    for(int i = 1; i <= 15; i++) {
        int* num = malloc(sizeof(int));
        if(!num) {
            printf("Error de memoria.\n");
            stack_free(&s, 1);
            return 1;
        }
        *num = i * 10;
        push(s, num);
    }

    // Imprimir la pila
    stack_print(s);

    // Sacar 5 elementos
    printf("Sacando 5 elementos...\n");
    for(int i = 0; i < 5; i++) {
        int* val = (int*)pop(s);
        if(val) {
            printf("Sacado: %d\n", *val);
            free(val);
        }
    }

    // Imprimir la pila restante
    stack_print(s);

    // Destruir la pila
    stack_free(&s, 1);

    return 0;
}