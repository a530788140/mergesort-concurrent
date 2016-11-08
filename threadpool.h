#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _task {
    void (*func)(void *);
    void *arg;
    struct _task *next, *last;
} task_t;

int task_free(task_t *the_task);

typedef struct {
    pthread_t *threads;
    uint32_t count;

    task_t *head, *tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    uint32_t size;

} tpool_t;

task_t *tqueue_pop(tpool_t *the_queue);
uint32_t tqueue_size(tpool_t *the_queue);
int tqueue_push(tpool_t *the_queue, task_t *task);

int tpool_init(tpool_t *the_pool, uint32_t count, void *(*func)(void *));
int tpool_free(tpool_t *the_pool);

#endif
