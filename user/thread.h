struct thread_lock {
  uint locked;
};

int thread_create(void *(start_routine)(void*), void *arg);
void lock_init(struct thread_lock* lock);
void lock_acquire(struct thread_lock* lock);
void lock_release(struct thread_lock* lock);