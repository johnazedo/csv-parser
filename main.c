#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  free(namefile);
  return EXIT_SUCCESS;
}
