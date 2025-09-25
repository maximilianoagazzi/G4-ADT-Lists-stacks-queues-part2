#ifndef HEADER_H
#define HEADER_H

#include "list.h"
#include "stack.h"
#include "queue.h"

void stack_print(stack* s, void (*print_fct)(void*));
void print_int(void* data);

#endif