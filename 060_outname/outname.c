#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t inputLength = strlen(inputName);

  char * outputName = malloc((inputLength + strlen(".counts") + 1) * sizeof(*outputName));

  if (outputName == NULL) {
    perror("Unable to allocate memory for output file name");
    return NULL;
  }

  strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}
