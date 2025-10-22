#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_TO_READ_FILE -1
// ## is used to handle the case when no variable arguments are passed
#define LOG(fmt, ...)                                                          \
  printf("%s:%d" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
typedef unsigned char byte;

int main(int argc, char *argv[]) {
  int i = 0;

  if (argc <= 1) {
    LOG("No command line arguments passed");
    return EXIT_FAILURE;
  }

  LOG("cmdline args count=%d", argc);
  LOG("exe name=%s", argv[0]);

  char *namefile = malloc(strlen(argv[1]) + 1);
  strcpy(namefile, argv[1]);

  LOG("filename=%s", namefile);

  FILE *fptr;
  fptr = fopen(namefile, "r");
  if (fptr == NULL) {
    LOG("Error! Could not open file %s", namefile);
    return EXIT_FAILURE;
  }

  fclose(fptr);
  free(namefile);
  return EXIT_SUCCESS;
}
