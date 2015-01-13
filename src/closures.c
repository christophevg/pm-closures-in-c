// experiment to implement closures in c in a rudimental way
// aka poor-man's closures in c

#include <string.h> // for memcpy
#include <stdlib.h> // for free

#include "closures.h"

// root of the linked list
closure_list_item_t *closures = NULL;
// tail of the linked list
closure_list_item_t *last_closure = NULL;

closure_t create_closure(function_t function, int *env, int size) {
  if(last_closure == NULL) {
    // create first closure
    closures = malloc(sizeof(closure_list_item_t));
    last_closure = closures;
  } else {
    // move to next
    last_closure->next = malloc(sizeof(closure_list_item_t));
    last_closure = last_closure->next;
  }
  // allocate the actual closure structure
  last_closure->closure = malloc(sizeof(struct closure));
  // syntactic sugar
  closure_t closure = last_closure->closure;
  // store function pointer
  closure->function = function;
  // allocate memory to store associated env
  closure->env = malloc(sizeof(int)*size);
  // copy the associated env
  closure->size = size;
  memcpy(closure->env, env, sizeof(int)*size);
  return closure;
}

void free_closure(closure_t closure) {
  if(closures == NULL) { return; }   // NONE
  if(closures->closure == closure) { // first
    closures = closures->next;
    if(closures == NULL) {           // and only
      last_closure = NULL;
    }
    return;
  }
  // find non-first closure
  closure_list_item_t *parent = closures;
  while(parent->next && parent->next->closure != closure) {
    parent = parent->next;
  }
  if(parent->next) {
    // parent->next->closure == closure
    parent->next = parent->next->next;
    if(parent->next == NULL) {
      // it was the last one
      last_closure = parent;
    }
    // free the closure
    free(closure);
  } else {
    // not found
  }
}

void call_closure(closure_t closure, int *args, int size) {
  closure->function(closure->env, closure->size, args, size);
}
