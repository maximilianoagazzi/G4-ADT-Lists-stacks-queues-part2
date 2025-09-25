#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/stack.h"
#include "include/queue.h"
#include "include/header.h"

int main() 
{
    stack* s = stack_new();
    int nums[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        push(s, &nums[i]);
    }

    printf("Contenido de la pila de forma iterativa:\n");
    stack_print_it(s, print_int);
    printf("Contenido de la pila de forma recursiva:\n");
    stack_print_rc(s, print_int);
    //Ejercicio 10a

    stack_free(&s, 0);
    return 0;
}

void stack_print_it(stack* s, void (*print_fct)(void*)) //Ejercicio 10a
{
    stack* aux = stack_new();
    if (s == NULL || aux == NULL) {
        printf("Pila vacia\n");
        return;
    }
    while (stack_length(s) > 0) {
        void* elem = pop(s);
        print_fct(elem);
        push(aux, elem);
    }
    while (stack_length(aux) > 0) {
        push(s, pop(aux));
    }
    stack_free(&aux, 0);
}

void stack_print_rc(stack* s, void (*print_fct)(void*)) //Ejercicio 10b
{
    stack* aux = stack_new();
    if (s == NULL || aux == NULL) {
        printf("Pila vacia\n");
        return;
    }
    stack_print_aux(s, aux, print_fct);

    stack_free(&aux, 0);
}

void stack_print_aux(stack* s, stack* aux, void (*print_fct)(void*)) //Ejercicio 10b
{
    if (stack_length(s) == 0) {
        return;
    }
    void* elem = pop(s);
    print_fct(elem);
    push(aux, elem);
    stack_print_aux(s, aux, print_fct);
    push(s, pop(aux));
}

void print_int(void* data) //Ejercicio 10
{
    if (data != NULL) {
        printf("%d\n", *(int*)data);
    } else {
        printf("NULL\n");
    }
}

