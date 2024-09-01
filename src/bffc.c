#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "src/bffc.h"

// Evaluate a BFF tape
int eval(char* tape, int bsize) {
  // Reset read and write heads
  int head0 = 0;
  int head1 = 0;
  // Reset instruct pointer
  int instruct = 0;
  int nreads = 0;
  while ((instruct < bsize) && (nreads++ < MAX_EVALS)) {
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
      // Jump backwards to the matching [ command if head0 is at 0
      case ']':
        if (tape[head0] != 0) {
          // Find matching parenthesis
          int npar = 0;
          for (; instruct < bsize; instruct--) {
            if (tape[instruct] == ']')
              npar--;
            if (tape[instruct] == '[')
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
  assert(
    TURING_GAS_SIZE%step_size == 0
    && "TURING_GAS_SIZE must be divisible by sizeof(RAND_MAX) (typically 4)"
  );
  for (int i = 0; i < TURING_GAS_SIZE; i += step_size)
    // Write step_size bytes directly into turing_gas starting with byte i
    *(int*)(turing_gas + i) = rand();
}

void bff_epoch(char* turing_gas, char* buffer){
  int tape1 = rand() % MNUM;
  int tape2 = rand() % MNUM;
  memcpy(buffer, turing_gas + tape1, MLEN);
  memcpy(buffer + MLEN, turing_gas + tape2, MLEN);
  eval(buffer, BUFFER_SIZE);
  memcpy(turing_gas + tape1, buffer, MLEN);
  memcpy(turing_gas + tape2, buffer + MLEN, MLEN);
}

void run() {
  // Memory allocation
  char* turing_gas = malloc(TURING_GAS_SIZE);
  char* buffer = malloc(BUFFER_SIZE);


  //Primary loop
  rand_init_turing_gas(turing_gas, time(NULL));
  for (int epoch = 0; epoch < NMAX; epoch++) {
    bff_epoch(turing_gas, buffer);
  }

  // Memory release
  free(turing_gas);
  free(buffer);
}
