#ifndef __LIST_H
#define __LIST_H

typedef struct
{
	int item_count;
	int current_max_size;
	char growable;

	void **items;
	char **names;	
} list2;

void list_make(list2 *listo, int size, char growable);
int list_add_item(list2 *listo, void *item, char *name);
char* list_print_items(list2 *listo);
void* list_get_name(list2 *listo, char *name);
void* list_get_index(list2 *listo, int indx);
void* list_get_item(list2 *listo, void *item_to_find);
int list_find(list2 *listo, char *name_to_find);
void list_delete_index(list2 *listo, int indx);
void list_delete_name(list2 *listo, char *name);
void list_delete_item(list2 *listo, void *item);
void list_delete_all(list2 *listo);
void list_print_list(list2 *listo);
void list_free(list2 *listo);

void test_list();
#endif
