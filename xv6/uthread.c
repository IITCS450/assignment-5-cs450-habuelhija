#include "types.h"
#include "uthread.h"
#include "stat.h"
#include "user.h"
#define FREE 0x0
#define RUNNING 0x1
#define RUNNABLE 0x2
#define STACK_SIZE 8192
#define MAX_THREAD 4
struct thread {
  int sp;
  char stack[STACK_SIZE];
  int state;
  int id;
};
struct thread all_thread[MAX_THREAD];
struct thread *current_thread;
extern void thread_switch(uint, uint);
void thread_init(void) {
  current_thread = &all_thread[0];
  current_thread->state = RUNNING;
}
void thread_yield(void) {
  struct thread *t;
  struct thread *next_thread = 0;
  for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
    if (t->state == RUNNABLE && t != current_thread) {
      next_thread = t;
      break;
    }
  }
  if (next_thread == 0) return;
  struct thread *prev_thread = current_thread;
  current_thread = next_thread;
  prev_thread->state = RUNNABLE;
  current_thread->state = RUNNING;
  thread_switch((uint)&prev_thread->sp, (uint)&current_thread->sp);
}
int thread_create(void (*fn)(void*), void *arg) {
  struct thread *t;

  for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
    if (t->state == FREE) break;
  }

  if (t == all_thread + MAX_THREAD) return -1;

  t->sp = (int)(t->stack + STACK_SIZE - 48);

  *(int*)(t->sp + 44) = (int)arg;  
  *(int*)(t->sp + 40) = 0;         
  *(int*)(t->sp + 32) = (int)fn;   

  for(int i = 0; i < 8; i++) {
      *(int*)(t->sp + (i * 4)) = 0;
  }

  t->state = RUNNABLE;
  return (int)(t - all_thread);
}
