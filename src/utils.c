#include "utils.h"
#include "values.h"
#include <stdlib.h>
#include <string.h>

int splitline(char *line, size_t size, const char *delimiter) {

  char *field = strtok(line, delimiter);

  while (field != NULL) {
    LOG("Field: %s", field);
    field = strtok(NULL, delimiter);
  }

  free(field);
  return SUCCESS;
}

int readline(char **str, size_t max_size, FILE *file) {
  size_t len = 0;
  int c;

  if (str == NULL) {
    LOG("Input string pointer is NULL");
    return INVALID_MEMORY_ERROR;
  }

  char *ptr = NULL;

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

    (*str)[len++] = (char)c;
  }

  if (len == 0 && c == EOF) {
    return END_OF_FILE;
  }

  (*str)[len] = '\0';
  return SUCCESS;
}
