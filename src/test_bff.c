#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bffc.h"

int test_bff_hello_world() {
  // Hello world in brainfuck
  char* cmd_string = "+[+]";
  char* data_string = "Hello world";

  char* tape = malloc(strlen(data_string) + strlen(cmd_string));
  // Copy command segment to the tape
  memcpy(tape + strlen(data_string), cmd_string, strlen(cmd_string));
  eval(tape, strlen(data_string) + strlen(cmd_string));
  free(tape);
  return 1;
}

int main() {

  if (!test_bff_hello_world())
    return 1;

  return 0;
}
