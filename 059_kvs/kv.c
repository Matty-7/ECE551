#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    perror("Could not open file");
    return NULL;
  }

  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->pairs = NULL;
  kvarray->length = 0;

  char * line = NULL;
  size_t len = 0;
  while (getline(&line, &len, file) != -1) {
    char * equals = strchr(line, '=');
    if (equals == NULL) {
      continue;
    }

    *equals = '\0';
    char * key = strdup(line);
    char * value = strdup(equals + 1);

    char * newline = strchr(value, '\n');
    if (newline) {
      *newline = '\0';
    }

    kvarray->pairs =
        realloc(kvarray->pairs, (kvarray->length + 1) * sizeof(*kvarray->pairs));
    kvarray->pairs[kvarray->length].key = key;
    kvarray->pairs[kvarray->length].value = value;
    kvarray->length++;
  }

  free(line);
  fclose(file);
  return kvarray;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pairs[i].key, key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
