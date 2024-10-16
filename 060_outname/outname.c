#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  size_t len = strlen(inputName) + 8;
  char * outName = malloc(len);
  snprintf(outName, len, "%s.counts", inputName);
  return outName;
}
