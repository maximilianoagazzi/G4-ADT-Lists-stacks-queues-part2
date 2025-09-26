#ifndef HEADER_H
#define HEADER_H

#include "list.h"
#include "stack.h"
#include "queue.h"

void stack_print_it(stack* s, void (*print_fct)(void*));
void stack_print_rc(stack* s, void (*print_fct)(void*));
void stack_print_aux(stack* s, stack* aux, void (*print_fct)(void*));
void queue_print(queue* q, void (*print_fct)(void*));
int stack_sum(stack* s);
int queue_sum(queue* q);
void queue_invert_it(queue* q);
void queue_invert_rc(queue* q);

void print_int(void* data);

#endif