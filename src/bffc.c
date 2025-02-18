#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "bffc.h"

void pretty_print_tape(char* tape, int bsize, int nreads, int instruct, int head0, int head1) {
  printf("WRITE   %03d \u250C", tape[head0]);
  for (int i = 0; i < bsize; i++) {
    if (i == head0)
      printf("\u253c");
    else
      printf("\u2500");
  }
  printf("\u2510\n");
  printf("%05d %05d \u2502", nreads, instruct);
  for (int i = 0; i < bsize; i++) {
    char to_print = tape[i];
    if (tape[i] == 0)
      to_print = '_';
    else if (!strchr("<>{}+-.,[]", to_print) && (!isalnum(to_print)))
      to_print = '_';
    if (i == instruct) {
      printf("\033[37;41;1m%c\033[0m", to_print);
    } else {
      if (strchr("<>{}+-.,[]", to_print)) {
        printf("\033[0;32m%c\033[0m", to_print); // Green for Brainfuck characters
      } else {
        printf("\033[0;36m%c\033[0m", to_print); // Grey for alphanumeric characters
      }
    }
  }
  printf("\u2502\n"); // Right border
  printf("READ    %03d \u2514", tape[head1]);
  for (int i = 0; i < bsize; i++) {
    if (i == head1)
      printf("\u253c");
    else
      printf("\u2500");
  }
  printf("\u2518\n"); // Bottom-right corner

}

// Evaluate a BFF tape
int eval(char* tape, int bsize) {
  // Reset read and write heads
  int head0 = 0;
  int head1 = 0;
  // Reset instruct pointer
  int instruct = 0;
  int nreads = 0;
  while ((instruct < bsize) && (nreads++ < MAX_EVALS)) {
    if (DEBUG) {
      pretty_print_tape(tape, bsize, nreads, instruct, head0, head1);
      // getchar();
    }

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
            if (npar == 0){
              instruct--;
              break;
            }
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
            if (npar == 0){
              instruct--;
              break;
            }
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
  for (int epoch = 0; epoch < MAX_EPOCH; epoch++) {
    bff_epoch(turing_gas, buffer);
  }

  // Memory release
  free(turing_gas);
  free(buffer);
}
