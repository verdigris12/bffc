#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "bffc.h"

#define MLEN 64
#define MNUM 256
#define MAX_EVALS 2**13
#define BUFFER_SIZE MLEN*2
#define TURING_GAS_SIZE MLEN*MNUM
#define NMAX 1024

// Evaluate a BFF tape
int eval(char* buffer, int bsize) {
  // Reset read and write heads
  // int head0 = 0;
  // int head1 = 0;
  // int instruct = 0;
  for (int i = 0; i < bsize; i++) {
    printf("%x", buffer[i]);
  }
  printf("\n");
  return 0;
}

void rand_init_turing_gas(char* turing_gas, unsigned int rand_seed){
  srand(rand_seed); // Seed the random number generator
  int step_size = sizeof(RAND_MAX);
  for (int i = 0; i < TURING_GAS_SIZE; i += step_size)
    // Write step_size bytes directly into turing_gas starting with byte i
    *(int*)(turing_gas + i) = rand();
}

int main() {
  // Memory allocation
  char* turing_gas = malloc(TURING_GAS_SIZE);
  char* buffer = malloc(BUFFER_SIZE);

  //Primary loop
  rand_init_turing_gas(turing_gas, time(NULL));
  for (int epoch = 0; epoch < NMAX; epoch++){
    memcpy(buffer, turing_gas + (rand() % MNUM), MLEN);
    memcpy(buffer + MLEN, turing_gas + (rand() % MNUM), MLEN);
    eval(buffer, BUFFER_SIZE);

  }
  // eval(turing_gas, BUFFER_SIZE);

  // Memory release
  free(turing_gas);
  free(buffer);
  return 0;
}
