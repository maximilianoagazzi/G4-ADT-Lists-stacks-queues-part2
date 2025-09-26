#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/stack.h"
#include "include/queue.h"
#include "include/header.h"

int stack_sum(stack* s);
int queue_sum(queue* q);

int main() 
{
    stack* s = stack_new();
    int nums_s[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        push(s, &nums_s[i]);
    }

    printf("Contenido de la pila de forma iterativa:\n");
    stack_print_it(s, print_int);
    printf("\n\nContenido de la pila de forma recursiva:\n");
    stack_print_rc(s, print_int);
    //Ejercicio 10a

    queue* q = queue_new();
    int nums_q[] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; i++) {
        enqueue(q, &nums_q[i]);
    }
    printf("\n\nContenido de la cola:\n");
    queue_print(q, print_int);
    //Ejercicio 11

    printf("\n\nLa suma de los elementos de la pila es: %d\n", stack_sum(s));
    printf("La suma de los elementos de la cola es: %d\n", queue_sum(q));
    //Ejercicio 12

    stack_free(&s, 0);
    queue_free(&q, 0);
    return 0;
}

void stack_print_it(stack* s, void (*print_fct)(void*)) //Ejercicio 10a
{
    stack* aux = stack_new();
    if(s == NULL || aux == NULL) {
        printf("Pila vacia\n");
        return;
    }
    while(stack_length(s) > 0) {
        void* elem = pop(s);
        print_fct(elem);
        push(aux, elem);
    }
    while(stack_length(aux) > 0) {
        push(s, pop(aux));
    }
    stack_free(&aux, 0);
}

void stack_print_rc(stack* s, void (*print_fct)(void*)) //Ejercicio 10b
{
    stack* aux = stack_new();
    if(s == NULL || aux == NULL) {
        printf("Pila vacia\n");
        return;
    }
    stack_print_aux(s, aux, print_fct);

    stack_free(&aux, 0);
}

void stack_print_aux(stack* s, stack* aux, void (*print_fct)(void*)) //Ejercicio 10b
{
    if(stack_length(s) == 0) {
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
    if(data != NULL) {
        printf("%d  ", *(int*)data);
    } else {
        printf("NULL\n");
    }
}

void queue_print(queue* q, void (*print_fct)(void*)) //Ejercicio 11
{
    if(q == NULL || print_fct == NULL) {
        printf("Cola vacia o funcion nula\n");
        return;
    }

    int len = queue_length(q);
    for(int i=0; i<len; i++) {
        void* elem = dequeue(q);
        print_fct(elem);
        enqueue(q, elem);
    }
}

int stack_sum(stack* s) //Ejercicio 12a
{
    stack* aux = stack_new();
    int sum = 0;
    if(s == NULL || aux == NULL) {
        return -1;  //Indica error
    }

    while(stack_length(s) > 0) {
        int *elem = (int*)pop(s);
        sum += *elem;
        push(aux, elem);
    }
    while(stack_length(aux) > 0) {
        push(s, pop(aux));
    }
    stack_free(&aux, 0);
    return sum;
}

int queue_sum(queue* q) //Ejercicio 12b
{
    int sum = 0;
    if(q == NULL) {
        return -1; //Indica error
    }

    int len = queue_length(q);
    for(int i=0; i<len; i++) {
        int* elem = (int*)dequeue(q);
        sum += *elem;
        enqueue(q, elem);
    }
    return sum;
}