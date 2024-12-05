#include "options.h"
#include "output.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "rand48.h"

#include <unistd.h>

/* Main program, which outputs N bytes of random data.  */
int main(int argc, char **argv) {
  /* Check arguments.  */
  long long nbytes = 0;
  long long chunksize = 0;
  int inputChoice = 0; // 0 = rdrand, 1 = mrand48_r, 2 = /F
  int outputChoice = 0; // 0 = stdio, 1 = N

  // Process the options
  if (process_options(argc, argv, &nbytes, &inputChoice, &outputChoice, &chunksize)) {
    fprintf(stderr, "Error processing options!\n");
    return 1;
  }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0) return 0;

  /* Initialize function pointers for RNG */
  void (*initialize)(void) = NULL;
  unsigned long long (*rand64)(void) = NULL;
  void (*finalize)(void) = NULL;

  /* Check input choice and initialize RNG accordingly */
  if (inputChoice == 0) {  // rdrand
    if (rdrand_supported()) {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    } else {
      fprintf(stderr, "rdrand hardware random number generator currently not available!\n");
      return 1;
    }
  }
  else if (inputChoice == 1) {  // lrand_48
    initialize = software_rand48_init;
    rand64 = software_rand48;
    finalize = software_rand48_fini;
  }
  else if (inputChoice == 2) {  // file
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }

  /* Ensure that function pointers are properly initialized */
  if (initialize == NULL || rand64 == NULL || finalize == NULL) {
    fprintf(stderr, "Invalid input choice or missing random number generation method.\n");
    return 1;
  }

  /* Initialize RNG */
  initialize();

  int wordsize = sizeof(rand64());
  
  if (outputChoice == 0) {  // Default output to stdout
    do {
      unsigned long long x = rand64();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes(x, outbytes)) {
        fprintf(stderr, "Output error!\n");
        return 1;
      }
      nbytes -= outbytes;
    } while (nbytes > 0);

    if (fclose(stdout) != 0) {
      fprintf(stderr, "Output error!\n");
      return 1;
    }
  } else if (outputChoice == 1) {  // Output to file with chunksize
    int offset = 0;
    unsigned long long x;

    while (nbytes > 0) {
      size_t outbytes = (nbytes >= chunksize) ? chunksize : nbytes;
      x = rand64();
      
      // Write chunk of data
      memcpy(stdout, (const char*)&x + offset, outbytes);
      
      if (write(1, stdout, outbytes) < 0) {
        fprintf(stderr, "Output error!\n");
        return 1;
      }

      offset += outbytes;
      nbytes -= outbytes;
    }
  }

  /* Finalize RNG */
  finalize();
  
  return 0;
}