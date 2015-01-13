// experiment to implement closures in c in a rudimental way
// aka poor-man's closures in c

#include <stdlib.h>
#include <stdio.h>

#include "closures.h"

void my_function(int *env, int env_size, int *args, int args_size) {
  printf("my_function with env = ");
  for(int i=0;i<env_size;i++) {
    printf("%d ", env[i]);
  }
  printf(" / args = ");
  for(int i=0;i<args_size;i++) {
    printf("%d ", args[i]);
  }
  printf("\n");
}

int main(void) {
  int env[3];

  env[0] = 22; env[1] = 33; env[2] = 44;
  closure_t closure1 = create_closure(my_function, env, 3);

  env[0] = 11; env[1] = 55; env[2] = 66;
  closure_t closure2 = create_closure(my_function, env, 3);

  int args[3];

  args[0] = 2; args[1] = 3; args[2] = 4;
  call_closure(closure1, args, 3);

  args[0] = 1; args[1] = 5; args[2] = 6;
  call_closure(closure2, args, 3);

  exit(EXIT_SUCCESS);
}
