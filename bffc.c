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
int eval(char* tape, int bsize) {
  // Reset read and write heads
  int head0 = 0;
  int head1 = 0;
  // Reset instruct pointer
  int instruct = 0;
  while (instruct < bsize) {
    switch (tape[instruct]) {
      case '<':
        if (head0 > 0)
          head0--;
        break;
      case '>':
        if (head0 < bsize)
          head0++;
        break;
      case '{':
        if (head1 > 0)
          head1--;
        break;
      case '}':
        if (head1 < bsize)
          head1++;
        break;
      case '-':
        tape[head0] = (char)((int)tape[head0] - 1);
        break;
      case '+':
        tape[head0] = (char)((int)tape[head0] + 1);
        break;
      case '.':
        tape[head1] = tape[head0];
        break;
      case ',':
        tape[head0] = tape[head1];
        break;
      // Jump forward to the matching ] command if head0 is at 0
      case '[':
        if (tape[head0] == 0) {
          // Find matching parenthesis
          int npar = 0;
          for (; instruct < bsize; instruct++) {
            if (tape[instruct] == '[')
              npar--;
            if (tape[instruct] == ']')
              npar++;
            if (npar == 0)
              break;
          }
          // If no match found, terminate
          if (npar != 0)
            break;
        }
        break;
      default:
        break;
    }
    instruct++;
  }
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
