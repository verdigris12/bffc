#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bffc.h"

int test_bff_eval(const char* data, const char* cmd, const int data_padding, const int cmd_padding) {
  const int tapelen = strlen(data) + strlen(cmd) + data_padding + cmd_padding;
  char* tape = malloc(tapelen);
  for (int i = 0; i < tapelen; i++) tape[i] = 0; // Zero out the tape
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
    int j = (int) strlen(data) + i;
    if (tape[j] != 0) {
      printf("Error: data padding mismatch at cell %d. Expected %x, got %x\n", i, 0, tape[j]);
      return 0;
    }
  }
  // Test command segment
  for (int i = 0; i < (int) strlen(cmd); i++){
    int j = (int) strlen(data) + data_padding + i;
    if (tape[j] != cmd[i]) {
      printf("Error: command segment mismatch at cell %d. Expected %x, got %x\n", i, cmd[i], tape[j]);
      return 0;
    }
  }
  // Test command padding
  for (int i = 0; i < cmd_padding; i++){
    int j = (int) strlen(data) + data_padding + (int) strlen(cmd) + i;
    if (tape[j] != 0) {
      printf("Error: command padding mismatch at cell %d. Expected %x, got %x\n", i, 0, tape[j]);
      return 0;
    }
  }
  free(tape);
  return 1;
}

int main() {

  if (!test_bff_eval("H", "++++++++[>+++++++++<-]>.}},", 2, 1))
    return 1;
  if (!test_bff_eval("H", "++++++++[>+++[>+++<-]<-]>>.},", 2, 1))
    return 1;

  return 0;
}
