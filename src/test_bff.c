#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bffc.h"

int test_bff_hello_world() {
  // Hello world in brainfuck
  // char* cmd_string = "++++++++[>+++++++++<-]>";
  char* cmd_string = "++++++++[>+++[>+++<-]<-]>>.},<";
  char* data_string = "H  ";

  // +2 since both data a code segments should have terminating bytes
  char* tape = malloc(strlen(data_string) + strlen(cmd_string) + 2);
  // Copy command segment to the tape
  memcpy(tape + strlen(data_string) + 1, cmd_string, strlen(cmd_string));
  eval(tape, strlen(data_string) + strlen(cmd_string) + 2);
  free(tape);
  return 1;
}

int main() {

  if (!test_bff_hello_world())
    return 1;

  return 0;
}
