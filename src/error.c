#include "error.h"

void throwError(char* type, char* expected, Stream* stream) {
  error_message = (char*)malloc(sizeof(char) * 255);
  if (getStreamChar(stream) == -1) {
    sprintf(error_message, "Error while parsing type '%s': expected to find '%s' but found EOF.\n", type, expected);
  } else {
    sprintf(error_message, "Error while parsing type '%s': expected to find '%s' but found '%c'.\n", type, expected, getStreamChar(stream));
  }
}
