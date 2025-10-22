#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE -1
#define MIN_LINE_SIZE 128
#define MAX_LINE_SIZE 128
#define SUCCESS 0

// ## is used to handle the case when no variable arguments are passed
#define LOG(fmt, ...)                                                          \
  printf("[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
typedef unsigned char byte;

char *readline(char *src, size_t max_size, FILE *file) {
  size_t len = 0;
  int c;

  while (1) {
    c = fgetc(file);
    if (c == EOF || c == '\n') {
      break;
    }

    src[len++] = (byte)c;
  }

  if (len == 0 && c == EOF) {
    return NULL;
  }

  return src;
}

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

  char line[MAX_LINE_SIZE];
  char *ret;
  while (1) {
    ret = readline(line, MAX_LINE_SIZE, fptr);
    if (ret == NULL) {
      break;
    }
    LOG("line=%s", line);
    memset(line, 0, sizeof(line));
  }
  fclose(fptr);
  free(namefile);
  return EXIT_SUCCESS;
}
