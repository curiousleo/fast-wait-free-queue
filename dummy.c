#include <stdlib.h>
#include "delay.h"
#include "dummy.h"

void queue_init(queue_t * q, int nprocs)
{
}

void queue_register(queue_t * q, handle_t * th, int id)
{
}

void enqueue(queue_t * q, handle_t * handle, void * data)
{
}

void * dequeue(queue_t * q, handle_t * handle)
{
  return (void *) (long) *handle;
}

void queue_free(int id, int nprocs) {}
