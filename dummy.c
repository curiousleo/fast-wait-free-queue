#include <stdlib.h>
#include "dummy.h"

extern void queue_init(queue_t * q, int nprocs);
extern void queue_register(queue_t * q, handle_t * th, int id);
extern void enqueue(queue_t * q, handle_t * handle, void * data);
extern void * dequeue(queue_t * q, handle_t * handle);
extern void queue_free(int id, int nprocs);
