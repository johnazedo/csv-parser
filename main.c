#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_MEMORY_ERROR -2
#define END_OF_FILE -3

#define MIN_LINE_SIZE 4
#define MAX_LINE_SIZE 32
#define SUCCESS 0

// ## is used to handle the case when no variable arguments are passed
#define LOG(fmt, ...)                                                          \
  printf("[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
typedef unsigned char byte;

int readline(byte **str, size_t max_size, FILE *file) {
  size_t len = 0;
  int c;

  if (str == NULL) {
    LOG("Input string pointer is NULL");
    return INVALID_MEMORY_ERROR;
  }

  byte *ptr = NULL;

  while (1) {
    c = fgetc(file);
    if (c == EOF || c == '\n') {
      break;
    }

    if (len == max_size) {
      max_size *= 2;
      ptr = realloc(*str, max_size);
      if (ptr == NULL) {
        LOG("Realloc failed");
        free(*str);
        *str = NULL;
        return INVALID_MEMORY_ERROR;
      }
      *str = ptr;
    }

    (*str)[len++] = (byte)c;
  }

  if (len == 0 && c == EOF) {
    return END_OF_FILE;
  }

  (*str)[len] = '\0';
  return SUCCESS;
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

  size_t size = MAX_LINE_SIZE * sizeof(byte);
  byte *line = malloc(size);
  int ret;
  int count = 0;

  LOG("Size of line buffer=%zu", size);
  while (1) {
    ret = readline(&line, size, fptr);
    if (ret != SUCCESS) {
      break;
    }
    count++;
    LOG("line=%s", line);
  }

  LOG("Total lines read=%d", count);

  free(line);
  fclose(fptr);
  free(namefile);
  return EXIT_SUCCESS;
}
