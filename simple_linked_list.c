#include <stdlib.h>
#include <constants.h>
#include <simple_linked_list.h>


int simple_linked_list_create(simple_linked_list_t **list_address)
{
	if(!list_address) return INVALID_ADDRESS;
	*list_address = (simple_linked_list_t *)calloc(1, sizeof(simple_linked_list_t));
	if(!(*list_address)) return INVALID_MEMORY_ALLOCATION;

	return SUCCESS;
}


int simple_linked_list_free(simple_linked_list_t *list)
{
	if(!list) return INVALID_DATA_STRUCTURE;

	simple_linked_list_node_t *aux, *p = list->root;
	
	while(p){
		aux = p; p = p->next;
		if(list->free_element)
			list->free_element(aux->element);
		free(aux);
	}
	free(list);
	list = NULL;

	return SUCCESS;
}


int simple_linked_list_size(int *size, simple_linked_list_t *list)
{
	if(!list) return INVALID_DATA_STRUCTURE;

	*size = list->size;

	return SUCCESS;
}


int simple_linked_list_insert(simple_linked_list_t *list, void *element, int position)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element) return INVALID_USEFULL_DATA;
	if(position < 0 || position > list->size) return INVALID_RANGE_VALUE;

	simple_linked_list_node_t *new, **p = &list->root;

	new = (simple_linked_list_node_t *)calloc(1, sizeof(simple_linked_list_node_t));
	new->element = element;
	while(position-- && (p = &(*p)->next));
	new->next = *p;
	*p = new;
	list->size++;

	return SUCCESS;
}


int simple_linked_list_add(simple_linked_list_t *list, void *element)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element) return INVALID_USEFULL_DATA;

	return simple_linked_list_insert(list, element, list->size);
}


int simple_linked_list_set(void ** prev_elem, simple_linked_list_t *list, void *element, int position)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element) return INVALID_USEFULL_DATA;
	if(position < 0 || position >= list->size) return INVALID_RANGE_VALUE;

	simple_linked_list_node_t *p = list->root;
	
	while(position-- && (p = p->next));
	*prev_elem = p->element;
	p->element = element;
	
	return SUCCESS;
}


int simple_linked_list_get(void **element_address, simple_linked_list_t *list, int position)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element_address) return INVALID_ADDRESS;
	if(position < 0 || position >= list->size) return INVALID_RANGE_VALUE;

	simple_linked_list_node_t *p = list->root;
	
	while(position-- && (p = p->next));
	*element_address = p->element; 
	
	return SUCCESS;
}


int simple_linked_list_remove(void **element_address, simple_linked_list_t *list, int position)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element_address) return INVALID_ADDRESS;
	if(position < 0 || position >= list->size) return INVALID_RANGE_VALUE;

	simple_linked_list_node_t *aux, **p = &list->root;

	while(position-- && (p = &(*p)->next));
	*element_address = (*p)->element;
	aux = *p;
	*p = (*p)->next; 
	free(aux);
	list->size--;

	return SUCCESS;
}


int simple_linked_list_set_free(simple_linked_list_t *list, int (*free_element)(void *))
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!free_element) return INVALID_FUNCTION_ADDRESS;

	list->free_element = free_element;

	return SUCCESS;
}


int simple_linked_list_set_copy(simple_linked_list_t *list, int (*copy_element)(void **, void *))
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!copy_element) return INVALID_FUNCTION_ADDRESS;

	list->copy_element = copy_element;

	return SUCCESS;
}


int simple_linked_list_set_compare(simple_linked_list_t *list, int (*compare)(void *, void *))
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!compare) return INVALID_FUNCTION_ADDRESS;

	list->compare_elements = compare;

	return SUCCESS;
}


int simple_linked_list_set_print(simple_linked_list_t *list, int (*print)(void *))
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!print) return INVALID_FUNCTION_ADDRESS;

	list->print_element = print;

	return SUCCESS;	
}

int simple_linked_list_copy(simple_linked_list_t **copy_list, simple_linked_list_t *list)
{
	if(!copy_list) return INVALID_ADDRESS;
	if(!list) 	return INVALID_DATA_STRUCTURE;

	simple_linked_list_node_t *new_node, **p_new, *p = list->root;

	simple_linked_list_create(copy_list);
	(*copy_list)->free_element = list->free_element;
	(*copy_list)->copy_element = list->copy_element;
	(*copy_list)->compare_elements = list->compare_elements;
	(*copy_list)->print_element = list->print_element;
	p_new = &(*copy_list)->root;
	while((*copy_list)->size < list->size){
		new_node = (simple_linked_list_node_t *)calloc(1, sizeof(simple_linked_list_node_t));
		if(list->copy_element) (*copy_list)->copy_element(&(new_node->element), p->element);		
		else new_node->element = p->element;
		*p_new = new_node;
		p_new = &(*p_new)->next;
		p = p->next;
		((*copy_list)->size)++;
	}	

	return SUCCESS;
}


int simple_linked_list_print_elem(simple_linked_list_t *list, int position)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(position < 0 || position >= list->size) return INVALID_RANGE_VALUE;

	simple_linked_list_node_t *p = list->root;
	
	while(position-- && (p = p->next));
	list->print_element(p->element);

	return SUCCESS;
}


int simple_linked_list_print_list(simple_linked_list_t *list)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!list->print_element) return INVALID_FUNCTION_ADDRESS;

	simple_linked_list_node_t *p = list->root;

	while(p){
		list->print_element(p->element);
		p = p->next;
	}

	return SUCCESS;
}


int simple_linked_list_search(int *position, simple_linked_list_t *list, void *element)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!element) return INVALID_USEFULL_DATA;
	
	simple_linked_list_node_t *p = list->root;
	
	*position = 0;
	while((*position) < list->size){
		if(!list->compare_elements(p->element, element))
			return SUCCESS;
		(*position)++;
		p = p->next;
	}
	*position = -1;

	return SUCCESS;	
}


int simple_linked_list_max_elem(void **max_element, int *max_elem_position, simple_linked_list_t *list)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!max_element) return INVALID_ADDRESS;
	if(!max_elem_position) return INVALID_ADDRESS;

	int current_pos = 0;
	simple_linked_list_node_t *p = list->root;

	while(current_pos < list->size){
		if(list->compare_elements(p->element, *max_element) == 1){
			*max_element = p->element;
			*max_elem_position = current_pos;
		}
		p = p->next;
		current_pos++;
	}

	return SUCCESS;
}

int simple_linked_list_min_elem(void **min_element, int *min_elem_position, simple_linked_list_t *list)
{
	if(!list) return INVALID_DATA_STRUCTURE;
	if(!min_element) return INVALID_ADDRESS;
	if(!min_elem_position) return INVALID_ADDRESS;

	int current_pos = 0;
	simple_linked_list_node_t *p = list->root;

	while(current_pos < list->size){
		if(list->compare_elements(p->element, *min_element) == -1){
			*min_element = p->element;
			*min_elem_position = current_pos;
		}
		p = p->next;
		current_pos++;
	}

	return SUCCESS;	
}
