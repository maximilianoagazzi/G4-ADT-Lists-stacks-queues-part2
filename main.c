#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/stack.h"
#include "include/queue.h"

// Función para imprimir todos los elementos de la lista
void print_list(list* l) {
    void* data;
    printf("Lista: ");
    for (data = list_first(l); data != NULL; data = list_next(l)) {
        printf("%d ", *(int*)data);
    }
    printf("\n");
}

int main() {
    list* l = list_create();
    if (l == NULL) {
        printf("Error al crear la lista.\n");
        return 1;
    }

    // 1️⃣ Agregar 10 enteros a la lista
    int nums[10] = {5, 12, 3, 7, 9, 1, 6, 8, 4, 2};
    for (int i = 0; i < 10; i++) {
        // Podés usar list_append o list_insert_first
        list_append(l, &nums[i]);
    }

    // 2️⃣ Imprimir la lista
    printf("Lista inicial:\n");
    print_list(l);

    // 3️⃣ Eliminar 5 elementos (los primeros que encuentre)
    for (int i = 0; i < 5; i++) {
        list_first(l);       // apuntamos al primer elemento
        list_remove(l);      // eliminamos el actual
    }

    // 4️⃣ Imprimir la lista después de eliminar 5 elementos
    printf("Lista después de eliminar 5 elementos:\n");
    print_list(l);

    // 5️⃣ Liberar memoria de la lista
    list_free(&l, 0);  // 0 porque los enteros no son dinámicos

    return 0;
}