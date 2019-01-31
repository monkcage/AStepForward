#include "heap.h"

static inline void min_heap_shift_down(heap_t* s, unsigned hole_index, void* e);
static inline void min_heap_shift_up(heap_t* s, unsigned hole_index, void* e);
static inline void max_heap_shift_down(heap_t* s, unsigned hole_index, void* e);
static inline void max_heap_shift_up(heap_t* s, unsigned hole_index, void* e);

int default_greater(void const* el1, void const* el2)
{
    return *(int*)el1 > *(int*)el2;
}

int heap_empty(heap_t* s) { return 0u == s->size; }
unsigned heap_size(heap_t* s) { return s->size; }
void* heap_top(heap_t* s) { return s->size ? *s->elem : 0; }

void heap_init(heap_t* s, func_greater greater)
{
    s->elem = 0;
    s->size = 0;
    s->cap = 0;
    s->cb_greater = greater == NULL ? default_greater : greater;
}

void heap_destroy(heap_t* s)
{
    s->cap = 0;
    s->size = 0;
    if (s->elem) free(s->elem);
}

int heap_reserve(heap_t* s, unsigned n)
{
    if (s->cap < n)
    {
        void **elem;
        unsigned a = s->cap ? s->cap * 2 : 8;
        if (a < n)
            a = n;
        if (!(elem = (void**)realloc(s->elem, a * sizeof *elem)))
            return -1;
        s->elem = elem;
        s->cap = a;
    }
    return 0;
}

int min_heap_push(heap_t* s, void* e)
{
    if (heap_reserve(s, s->size + 1))
        return -1;
    min_heap_shift_up(s, s->size++, e);
    return 0;
}

void* min_heap_pop(heap_t* s)
{
    if (s->size)
    {
        void* e = *s->elem;
        min_heap_shift_down(s, 0u, s->elem[--s->size]);
        return e;
    }
    return 0;
}

void min_heap_shift_down(heap_t* s, unsigned hole_index, void* e)
{
    unsigned min_child = 2 * (hole_index + 1);
    while (min_child <= s->size){
        min_child -= min_child == s->size || s->cb_greater(s->elem[min_child], s->elem[min_child - 1]);
        if (!(s->cb_greater(e, s->elem[min_child])))
            break;
        s->elem[hole_index] = s->elem[min_child];
        hole_index = min_child;
        min_child = 2 * (hole_index + 1);
    }
    s->elem[hole_index] = e;
}

void min_heap_shift_up(heap_t* s, unsigned hole_index, void* e)
{
    unsigned parent = (hole_index - 1) / 2;
    while (hole_index && s->cb_greater(s->elem[parent], e))
    {
        s->elem[hole_index] = s->elem[parent];
        hole_index = parent;
        parent = (hole_index - 1) / 2;
    }
    s->elem[hole_index] = e;
}


int max_heap_push(heap_t* s, void* e)
{
    if (heap_reserve(s, s->size + 1))
        return -1;
    max_heap_shift_up(s, s->size++, e);
    return 0;
}

void* max_heap_pop(heap_t* s)
{
    if (s->size)
    {
        void* e = *s->elem;
        max_heap_shift_down(s, 0u, s->elem[--s->size]);
        return e;
    }
    return 0;
}


void max_heap_shift_down(heap_t* s, unsigned hole_index, void* e)
{
    unsigned min_child = 2 * (hole_index + 1);
    while (min_child <= s->size){
        min_child -= min_child == s->size || !s->cb_greater(s->elem[min_child], s->elem[min_child - 1]);
        if ((s->cb_greater(e, s->elem[min_child])))
            break;
        s->elem[hole_index] = s->elem[min_child];
        hole_index = min_child;
        min_child = 2 * (hole_index + 1);
    }
    s->elem[hole_index] = e;
}

void max_heap_shift_up(heap_t* s, unsigned hole_index, void* e)
{
    unsigned parent = (hole_index - 1) / 2;
    while (hole_index && !s->cb_greater(s->elem[parent], e))
    {
        s->elem[hole_index] = s->elem[parent];
        hole_index = parent;
        parent = (hole_index - 1) / 2;
    }
    s->elem[hole_index] = e;
}
