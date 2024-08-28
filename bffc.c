#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "bffc.h"

#define MLEN 64
#define MNUM 256
#define MAX_EVALS 2**13
#define BUFFER_SIZE MLEN*2
#define TURING_GAS_SIZE MLEN*MNUM

// Evaluate a BFF tape
int eval(char* buffer, int bsize) {
  // Reset read and write heads
  // int head0 = 0;
  // int head1 = 0;
  // int instruct = 0;
  for (int i = 0; i < bsize; i++) {
    printf("%c", buffer[i]);
  }
  return 0;
}

int main() {
  char* turing_gas = malloc(TURING_GAS_SIZE);
  srand(time(NULL)); // Seed the random number generator
  unsigned long random_value;
  for (int i = 0; i < TURING_GAS_SIZE; i += sizeof(unsigned long)) {
    random_value = rand();
    memcpy(&turing_gas[i], &random_value, sizeof(unsigned long));
  }
  char* buffer = malloc(MLEN * 2 * sizeof(char));
  eval(buffer, BUFFER_SIZE);
  free(turing_gas);
  free(buffer);
  return 0;
}
