#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void errorExit(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "%s: ", filename);
    errorExit("cannot open file");
  }

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    char * newline_pos = strchr(line, '\n');
    if (newline_pos != NULL) {
      *newline_pos = '\0';
    }

    size_t i;
    for (i = 0; i < kvPairs->length; i++) {
      if (strcmp(line, kvPairs->pairs[i].key) == 0) {
        addCount(counts, kvPairs->pairs[i].value);
        break;
      }
    }

    if (i == kvPairs->length) {
      addCount(counts, NULL);
    }
  }

  free(line);
  if (fclose(f) != 0) {
    errorExit("cannot close file");
  }

  return counts;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    errorExit("Usage: <key_value_file> <input1> <input2> ...");
  }

  kvarray_t * kvPairs = readKVs(argv[1]);
  if (kvPairs == NULL) {
    errorExit("Failed to read key/value pairs");
  }

  for (int i = 2; i < argc; i++) {
    counts_t * counts = countFile(argv[i], kvPairs);

    char * outName = computeOutputFileName(argv[i]);

    FILE * outFile = fopen(outName, "w");
    if (outFile == NULL) {
      free(outName);
      freeCounts(counts);
      errorExit("Cannot open output file");
    }

    printCounts(counts, outFile);

    if (fclose(outFile) != 0) {
      free(outName);
      freeCounts(counts);
      errorExit("Failed to close output file");
    }

    freeCounts(counts);
    free(outName);
  }

  freeKVs(kvPairs);

  return EXIT_SUCCESS;
}
