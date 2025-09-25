#ifdef LIST_H_EXPORT
#define LIST_API __declspec(dllexport)
#else
#define LIST_API __declspec(dllimport)
#endif

#include "node.h"

typedef struct _list list;

LIST_API list* list_create(int cant);
LIST_API int set_node(list* l, void* elem);
LIST_API int list_get_size(list* l);
LIST_API node* list_get_head(list* l);
LIST_API void list_free(list** l, int dinamic);
LIST_API node** find(list* l, void* val, int cmp(void*, void*));
LIST_API node** find_pos(list* l, void* elem, int cmp(void*, void*));
LIST_API list* insert(list* l, void* val);
LIST_API node* insert_sort(list* l, void* elem, int cmp(void*, void*));
LIST_API void append(list* l, void* elem);
LIST_API node* remove_node(list* l, void* val, int cmp(void*, void*));