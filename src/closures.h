// experiment to implement closures in c in a rudimental way
// aka poor-man's closures in c

#ifndef __CLOSURES_H
#define __CLOSURES_H

typedef void (*function_t)(int *env, int env_size, int *args, int args_size);

// we store closures with additional env in a closures table
typedef struct closure {
  function_t function;
  int size;
  int *env;
} *closure_t;

// we're storing the closures in a linked list
typedef struct closure_list_item {
  closure_t closure;
  struct closure_list_item *next;
} closure_list_item_t;

closure_t create_closure(function_t function, int *env, int size);
void call_closure(closure_t closure, int *args, int size);
void free_closure(closure_t closure);

#endif
