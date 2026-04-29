void thread_init(void);
int thread_create(void (*fn)(void*), void *arg);
void thread_yield(void);
int thread_join(int tid);

// Mutex API
typedef struct {
  uint locked;
} umutex_t;

void mutex_init(umutex_t *m);
void mutex_lock(umutex_t *m);
void mutex_unlock(umutex_t *m);
