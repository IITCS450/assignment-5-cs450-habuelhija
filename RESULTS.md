# Assignment 5 Results

## Producer-Consumer Test Output:
Producer: count 1
Producer: count 2
Consumer: count 1
Producer: count 2
Consumer: count 1
Consumer: count 0
... (and so on)

## Implementation Details:
The threading library (uthread.c) handles context switching between 
user-level threads using the thread_switch assembly function.
