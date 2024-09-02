#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bffc.h"

int test_bff_eval(const char* data, const char* cmd, const int data_padding, const int cmd_padding) {
  const int tapelen = strlen(data) + strlen(cmd) + data_padding + cmd_padding;
  char* tape = malloc(tapelen);
  memcpy(tape + strlen(data) + data_padding, cmd, strlen(cmd)); // Copy command segment to the tape
  eval(tape, tapelen);

  /* Test the resulting tape
   * Can't use regular strcmp since the tape can contain 0x0 bytes
   */

  // Test data segment
  for (int i = 0; i < (int) strlen(data); i++){
    if (tape[i] != data[i]) {
      printf("Error: data segment mismatch at cell %d. Expected %x, got %x\n", i, data[i], tape[i]);
      return 0;
    }
  }
  // Test data padding
  for (int i = 0; i < data_padding; i++){
    if (tape[(int) strlen(data) + i] != 0) {
      printf("Error: data padding mismatch at cell %d. Expected %x, got %x\n", i, 0, tape[i]);
      return 0;
    }
  }
  // Can't use strcmp since tape can contain 0x0 bytes
  // for (int i = 0; i < tapelen; i++){ 
  //   // Compare data segment
  //   if ((i < (int) strlen(data)) && (tape[i] != data[i])){
  //     return 0;
  //   }
  //   // Compare 
  //   if (( (int) strlen(data) + data_padding <= i < tapelen - cmd_padding) && (tape[i] != cmd[i]))
  //     return 0;
  // }
  free(tape);
  return 1;
}

int main() {

  if (!test_bff_eval("H", "++++++++[>+++++++++<-]>.}},", 2, 1))
    return 1;
  // if (!test_bff_eval("H", "++++++++[>+++[>+++<-]<-]>>.},", 2, 1))
    // return 1;

  return 0;
}
