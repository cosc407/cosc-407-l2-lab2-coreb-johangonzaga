/* Lab 2, core B -- THE ALTERNATIVE named in BRIEF.md.
 *
 * The two-turnstile barrier, out of counting semaphores: arrive, count, and
 * when the last one arrives open the first turnstile for everybody; then
 * leave, count down, and when the last one leaves open the second.
 * (Downey, "The Little Book of Semaphores", 3.6-3.7, and class 6.)
 *
 * TWO turnstiles, not one. Work out for yourself what a fast thread does to a
 * single-turnstile version before you decide the second one is decoration --
 * and say so in S2.3, because it is the same lesson as your fix.
 *
 * my_sem_init / my_sem_wait / my_sem_post / my_sem_destroy are declared in
 * include/mysem.h and implemented, correctly, in src/mysem_ref.c. A
 * pthread_mutex_t is fine for the counter.
 *
 * It is correct, and it is not expected to be fast. Do not tune it: it is
 * evidence, not a submission.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "barrier.h"
#include "mysem.h"

/* TODO: the barrier's state. What has to be shared between the threads, and
 *       what does each thread have to remember for itself? */
typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t  cv;
    int             n;        /* how many threads have to arrive */
    int             count;    /* how many have arrived this round */
    unsigned long   gen;      /* which round this barrier is on   */
    void*           turnstile1;
    void*           turnstile2;
}bar_t;


static void *create(int nthreads)
{
    /* TODO: allocate it, initialise everything, and return it. Anything a
     *       thread might lock or wait on has to be ready BEFORE the first
     *       thread can reach it. */
 bar_t *b = malloc(sizeof *b);
    if (b == NULL) {
        return NULL;
    }

    if (pthread_mutex_init(&b->lock, NULL) != 0) {
        free(b);
        return NULL;
    }
    
    b->n     = nthreads;
    b->count = 0;

    return b;
}


   static void wait_(void *p)
   {
/* TODO: the barrier. Write the invariant you are keeping in a comment
     *       above it, in one line, before you write the code -- your report
     *       and your oral both ask you to state it. */
    /* Invariant: Turnstile 1 locks until all threads arrive; Turnstile 2 locks until all threads exit Phase 1. */
    bar_t *b = (bar_t *)p;

    /* --- PHASE 1: Arrive and pass through Turnstile 1 --- */
    pthread_mutex_lock(&b->lock);
    b->count++;
    if (b->count == b->n) {
        /* The last thread unlocks the first gate */
        my_sem_post(b->turnstile1);
    }
    pthread_mutex_unlock(&b->lock);

    /* Turnstile 1 Cascading Wakeup: Pass the token to the next thread */
    my_sem_wait(b->turnstile1);
    my_sem_post(b->turnstile1); 

    /* --- PHASE 2: Depart and pass through Turnstile 2 --- */
    pthread_mutex_lock(&b->lock);
    b->count--;
    if (b->count == 0) {
        /* The last thread unlocks the second gate */
        my_sem_post(b->turnstile2);
    }
    pthread_mutex_unlock(&b->lock);

    /* Turnstile 2 Cascading Wakeup: Pass the token to the next thread */
    my_sem_wait(b->turnstile2);
    my_sem_post(b->turnstile2);

}
static void destroy(void *p)
{
    /* TODO: release what create() took. Every thread has been joined by the
     *       time this is called. */
  bar_t *b = (bar_t *)p;
    pthread_mutex_destroy(&b->lock);
    pthread_cond_destroy(&b->cv);
    free(b);
}

const bar_ops_t bar_alt = { "alt", create, wait_, destroy };
