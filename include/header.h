#ifndef HEADER_H
#define HEADER_H

#include "list.h"
#include "stack.h"
#include "queue.h"

void stack_print_it(stack* s, void (*print_fct)(void*));
void stack_print_rc(stack* s, void (*print_fct)(void*));
void stack_print_aux(stack* s, stack* aux, void (*print_fct)(void*));

void print_int(void* data);

#endif