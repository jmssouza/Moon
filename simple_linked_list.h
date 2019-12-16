/********************************************************************************
 * 	Moon Project																*
 *																				*
 *																				*
 *  Data Structure Package - Simple Linked List Features						*
 *	Author: João Matheus Siqueira Souza (jmssouza)								*
 *																				*
 *  December 15th, 2019															*
 ********************************************************************************/

#ifndef JM_SIMPLE_LINKED_LIST_H_
#define JM_SIMPLE_LINKED_LIST_H_

struct SIMPLE_LINKED_LIST_NODE
{
	void *element;
	struct SIMPLE_LINKED_LIST_NODE *next;
};

struct SIMPLE_LINKED_LIST
{
	int size;	
	struct SIMPLE_LINKED_LIST_NODE *root;
	int (*free_element)(void *);
	int (*copy_element)(void **, void *);
	int (*compare_elements)(void *, void *);
	int (*print_element)(void *);
};

typedef struct SIMPLE_LINKED_LIST_NODE simple_linked_list_node_t;
typedef struct SIMPLE_LINKED_LIST      simple_linked_list_t;



// Constructor and Destructor functions ============================================= 
int simple_linked_list_create(simple_linked_list_t **);
int simple_linked_list_free(simple_linked_list_t *);


// Basic list manipulation functions ================================================ 
int simple_linked_list_size(int *, simple_linked_list_t *);
int simple_linked_list_insert(simple_linked_list_t *, void *, int);
int simple_linked_list_add(simple_linked_list_t *, void *);
int simple_linked_list_set(void **, simple_linked_list_t *, void *, int);
int simple_linked_list_get(void **, simple_linked_list_t *, int);
int simple_linked_list_remove(void **, simple_linked_list_t *, int);


//Function pointers setter ==========================================================
int simple_linked_list_set_free(simple_linked_list_t *, int (*)(void *));
int simple_linked_list_set_copy(simple_linked_list_t *, int (*)(void **, void *));
int simple_linked_list_set_compare(simple_linked_list_t *, int (*)(void *, void *));
int simple_linked_list_set_print(simple_linked_list_t *, int (*)(void *));


// Usefull list manipulation functions ============================================== 
int simple_linked_list_copy(simple_linked_list_t **, simple_linked_list_t *);
int simple_linked_list_print_elem(simple_linked_list_t *, int);
int simple_linked_list_print_list(simple_linked_list_t *);
int simple_linked_list_search(int *, simple_linked_list_t *, void *);
int simple_linked_list_max_elem(void **, int *, simple_linked_list_t *);
int simple_linked_list_min_elem(void **, int *, simple_linked_list_t *);


#endif