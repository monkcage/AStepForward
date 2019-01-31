
#ifndef HEAP_INTERNAL_H_INCLUDED_
#define HEAP_INTERNAL_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>


typedef int (*func_greater)(void const*, void const*);

typedef struct heap
{
    void **elem;
    unsigned size;
    unsigned cap;
    func_greater cb_greater;
}heap_t;

void	 heap_init(struct heap* s, func_greater greater);
void	 heap_destroy(struct heap* s);
int	     heap_empty(struct heap* s);
unsigned heap_size(struct heap* s);
void*    heap_top(struct heap* s);
int	     heap_reserve_(struct heap* s, unsigned n);
int	     min_heap_push(struct heap* s, void* e);
void*    min_heap_pop(struct heap* s);
int      max_heap_push(struct heap* s, void* e);
void*    max_heap_pop(struct heap* s);


#endif /* MINHEAP_INTERNAL_H_INCLUDED_ */
