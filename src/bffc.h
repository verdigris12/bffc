#define MLEN 64
#define MNUM 256
// #define MAX_EVALS 1024*1024
#define MAX_EVALS 1024*1024
#define BUFFER_SIZE MLEN*2
#define TURING_GAS_SIZE MLEN*MNUM
#define MAX_EPOCH 1024
#define DEBUG 1

int eval(char* tape, int bsize);

void rand_init_turing_gas(char* turing_gas, unsigned int rand_seed);

void bff_epoch(char* turing_gas, char* buffer);

void run();
