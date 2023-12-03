#include "kernel/types.h"
#include "user/thread.h"
#include "user/user.h"

const int PGSIZE = 4096;

int thread_create(void *(start_routine)(void*), void *arg) {

  int psize = PGSIZE*sizeof(void);
  void* st_ptr = (void* )malloc(psize);
  int thread_ID = clone(st_ptr);

  if (thread_ID == 0) {
    (*start_routine)(arg);
    exit(0);
  }

  return 0; // for parent process we return ID as 0
}

void lock_init(struct thread_lock* lock) {
  lock->locked = 0;
}

void lock_acquire(struct thread_lock* lock) {
    while(__sync_lock_test_and_set(&lock->locked, 1) != 0);
    __sync_synchronize();
}

void lock_release(struct thread_lock* lock) {
    __sync_synchronize();
    __sync_lock_release(&lock->locked, 0);
}