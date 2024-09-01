#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bffc.h"

int test_bff_hello_world() {
  // Hello world in brainfuck
  char* tape = ">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.";
  const int nbytes = strlen(tape);
  char * buffer = malloc(nbytes + strlen("Hello world"));
  memcpy(buffer + strlen("Hello world"), tape, nbytes);
  eval(buffer, nbytes + strlen("Hello world"));
  free(buffer);
  return 1;
}

int main() {

  if (!test_bff_hello_world())
    return 1;

  return 0;
}
