#include "threadpool.h"

int task_free(task_t *the_task)
{
    free(the_task->arg);
    free(the_task);
    return 0;
}


task_t *tqueue_pop(tpool_t *the_pool)
{
    task_t *ret;
    pthread_mutex_lock(&(the_pool->mutex));
    ret = the_pool->tail;
    if (ret) {
        the_pool->tail = ret->last;
        if (the_pool->tail) {
            the_pool->tail->next = NULL;
        } else {
            the_pool->head = NULL;
        }
        the_pool->size--;
    }
    pthread_mutex_unlock(&(the_pool->mutex));
    return ret;
}

uint32_t tqueue_size(tpool_t *the_pool)
{
    uint32_t ret;
    pthread_mutex_lock(&(the_pool->mutex));
    ret = the_pool->size;
    pthread_mutex_unlock(&(the_pool->mutex));
    return ret;
}

int tqueue_push(tpool_t *the_pool, task_t *task)
{
    pthread_mutex_lock(&(the_pool->mutex));
    task->last = NULL;
    task->next = the_pool->head;
    if (the_pool->head)
        the_pool->head->last = task;
    the_pool->head = task;
    if (the_pool->size++ == 0)
        the_pool->tail = task;
    pthread_cond_signal(&(the_pool->cond));
    pthread_mutex_unlock(&(the_pool->mutex));
    return 0;
}

int tpool_init(tpool_t *the_pool, uint32_t tcount, void *(*func)(void *))
{
    the_pool->threads = (pthread_t *) malloc(sizeof(pthread_t) * tcount);
    the_pool->count = tcount;

    the_pool->head = NULL;
    the_pool->tail = NULL;
    pthread_mutex_init(&(the_pool->mutex), NULL);
    pthread_cond_init(&(the_pool->cond), NULL);
    the_pool->size = 0;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (uint32_t i = 0; i < tcount; ++i)
        pthread_create(&(the_pool->threads[i]), &attr, func, NULL);
    pthread_attr_destroy(&attr);
    return 0;
}

int tpool_free(tpool_t *the_pool)
{
    for (uint32_t i = 0; i < the_pool->count; ++i)
        pthread_join(the_pool->threads[i], NULL);
    free(the_pool->threads);

    return 0;
}
