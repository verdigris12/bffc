#include <string.h>

#include "bffc.h"

int test_bff_tape1() {
  char* tape = "12313";
  eval(tape, strlen(tape));
  return 1;
}

int main() {

  if (!test_bff_tape1())
    return 1;

  return 0;
}
