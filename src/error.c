#include "error.h"

void throwError(char* type, char* expected, Stream* stream) {
  error_message = (char*)malloc(sizeof(char) * MAX_ERROR_MESSAGE_LENGTH);
  if (getStreamChar(stream) == -1) {
    snprintf(error_message, MAX_ERROR_MESSAGE_LENGTH + 1, "Error while parsing type '%s': expected to find '%s' but found EOF.\n", type, expected);
  } else {
    snprintf(error_message, MAX_ERROR_MESSAGE_LENGTH + 1, "Error while parsing type '%s': expected to find '%s' but found '%c'.\n", type, expected, getStreamChar(stream));
  }
}
