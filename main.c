#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_TO_READ_FILE -1

typedef unsigned char byte;

int readline(FILE *fptr, byte *out) {
  int n = 0;
  int size = 128;
  // If out has been allocated previously, this will cause a memory leak
  out = malloc(size + 1);
  int ch;

  return ERROR_TO_READ_FILE;
}

int main(int argc, char *argv[]) {
  int i = 0;

  if (argc <= 1) {
    printf("No command line arguments passed\n");
    return EXIT_FAILURE;
  }

  printf("cmdline args count=%d", argc);
  printf("\nexe name=%s", argv[0]);

  char *namefile = malloc(strlen(argv[1]) + 1);
  strcpy(namefile, argv[1]);

  printf("\nfilename=%s\n", namefile);

  FILE *fptr;
  fptr = fopen(namefile, "r");
  if (fptr == NULL) {
    printf("Error! Could not open file %s\n", namefile);
    return EXIT_FAILURE;
  }

  fclose(fptr);
  free(namefile);
  return EXIT_SUCCESS;
}
