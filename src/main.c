#include "utils.h"
#include "values.h"
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOL_SIZE 7

struct stock {
  char symbol[MAX_SYMBOL_SIZE + 1];
  float price;
  int volume;
  float net_worth;
};

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
  FREE_AND_NULL(namefile);

  size_t size = MAX_LINE_SIZE * sizeof(char);
  char *line = malloc(size);
  int ret;
  int count = 0;
  const char delimiter = ';';

  LOG("Size of line buffer=%zu", size);
  while (1) {
    ret = readline(&line, size, fptr);
    if (ret != SUCCESS) {
      break;
    }
    count++;
    LOG("line=%s", line);
    splitline(line, size, &delimiter);
  }

  LOG("Total lines read=%d", count);

  FREE_AND_NULL(line);
  fclose(fptr);
  return EXIT_SUCCESS;
}
