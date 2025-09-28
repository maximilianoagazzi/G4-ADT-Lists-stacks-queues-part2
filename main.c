#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/list.h"
#include "include/stack.h"
#include "include/queue.h"
#include "include/header.h"

int main() 
{
    stack* s = stack_new();
    int nums_s[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        push(s, &nums_s[i]);
    }

    printf("Contenido de la pila de forma iterativa:\n");
    stack_print_it(s, print_int);
    printf("\nContenido de la pila de forma recursiva:\n");
    stack_print_rc(s, print_int);
    //Ejercicio 10a

    queue* q = queue_new();
    int nums_q[] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; i++) {
        enqueue(q, &nums_q[i]);
    }
    printf("\nContenido de la cola:\n");
    queue_print(q, print_int);
    //Ejercicio 11

    printf("\nLa suma de los elementos de la pila es: %d\n", stack_sum(s));
    printf("\nLa suma de los elementos de la cola es: %d\n", queue_sum(q));
    //Ejercicio 12

    printf("\nLa cola invertida de forma iterativa es:\n");
    queue_invert_it(q);
    queue_print(q, print_int);
    queue_invert_it(q); //La vuelvo a invertir para dejarla como estaba
    printf("\nLa cola invertida de forma recursiva es:\n");
    queue_invert_rc(q);
    queue_print(q, print_int);
    //Ejercicio 13

    printf("\nCopia de la pila:\n");
    stack* s_copy = stack_copy(s);
    stack_print_it(s_copy, print_int);
    //Ejercicio 14

    printf("\nCopia de la cola:\n");
    queue* q_copy = queue_copy(q);
    queue_print(q_copy, print_int);
    //Ejercicio 15

    char string1[] = "HOLANDA NO ES UN PAIS";
    char string2[] = "LA RUTA NOS APORTO OTRO PASO NATURAL";
    int r = es_palindromo(string1);
    if(r == 1) {
        printf("\nEl string %s es palindromo\n", string1);
    } else {
        printf("\nEl string %s no es palindromo\n", string1);
    }
    r = es_palindromo(string2);
    if(r == 1) {
        printf("\nEl string %s es palindromo\n", string2);
    } else {
        printf("\nEl string %s no es palindromo\n", string2);
    }
    //Ejercicio 18

    stack_free(&s, 0);
    queue_free(&q, 0);
    stack_free(&s_copy, 1);
    queue_free(&q_copy, 1);
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
    printf("\n");
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
    printf("\n");

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
    printf("\n");
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

void queue_invert_it(queue* q) //Ejercicio 13a
{
    if(q != NULL) {
        stack* aux = stack_new();
        if(aux != NULL) {
            while(queue_length(q) > 0) {
                void* elem = dequeue(q);
                push(aux, elem);
            }
            while(stack_length(aux) > 0) {
                enqueue(q, pop(aux));
            }
            stack_free(&aux, 0);
        }
    }
}

void queue_invert_rc(queue* q) //Ejercicio 13b
{
    if(q != NULL) {
        if(queue_length(q) > 0) {
            void* elem = dequeue(q);
            queue_invert_rc(q);
            enqueue(q, elem);
        }
    }
}

stack* stack_copy(stack* s) //Ejercicio 14
{
    if(s == NULL) {
        return NULL;
    }
    stack* copy = stack_new();
    stack* aux = stack_new();
    if(copy != NULL && aux != NULL) {
        while(stack_length(s) > 0) {
            push(aux, pop(s));
        }

        while(stack_length(aux) > 0) {
            void* elem = pop(aux);
            push(s, elem);
            push(copy, elem_copy(elem));  //Los nuevos elementos usan memoria dinamica
        }
        stack_free(&aux, 0);
        return copy;
    }
    return NULL;
}

void* elem_copy(void* elem)  //Ejercicio 14
{
    if(elem == NULL) {
        return NULL;
    }
    void* new_elem = malloc(sizeof(int));
    if(new_elem != NULL) {
        *(int*)new_elem = *(int*)elem;
        return new_elem;
    }
    return NULL;
}

queue* queue_copy(queue* q)  //Ejercicio 15
{
    if(q == NULL) return NULL;
    queue* copy = queue_new();
    queue* aux = queue_new();
    if(copy != NULL && aux != NULL) {
        while(queue_length(q) > 0) {
            enqueue(aux, dequeue(q));
        }

        while(queue_length(aux) > 0) {
            void* elem = dequeue(aux);
            enqueue(q, elem);
            enqueue(copy, elem_copy(elem));  //Los nuevos elementos usan memoria dinamica
        }
        queue_free(&aux, 0);
        return copy;
    }
    return NULL;
}

int es_palindromo(char* string)  //Ejercicio 18
{
    if(string == NULL) return -1;

    int pal = 1;
    stack* s = stack_new();
    if(s != NULL) {
        for (int i=0; i<strlen(string); i++) {
            if(string[i] != ' ') {
                push(s, &string[i]);
            }
        }
        int i=0;
        while(stack_length(s) > 0 && pal == 1) {
            if(string[i] != ' ' && string[i] != *(char*)pop(s)) {
                pal = 0;
            }
            i++;
        }
        stack_free(&s, 0);
    } else {
        pal = -1;
    }
    return pal;
}