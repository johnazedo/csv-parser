#ifndef UTILS_C
#define UTILS_C
#include <stdio.h>

#define LOG(fmt, ...)                                                          \
  printf("[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define FREE_AND_NULL(ptr)                                                     \
  do {                                                                         \
    free(ptr);                                                                 \
    ptr = NULL;                                                                \
  } while (0)

#define IF_PTR_NULL(ptr, action)                                               \
  do {                                                                         \
    if ((ptr) == NULL) {                                                       \
      LOG("Pointer %s is NULL", #ptr);                                         \
      action;                                                                  \
    }                                                                          \
  } while (0)

int splitline(char *line, size_t size, const char *delimiter);
int readline(char **str, size_t max_size, FILE *file);

#endif
