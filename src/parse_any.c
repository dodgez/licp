#include "parse_any.h"

Node *parseAny(Stream *stream)
{
  while (TRUE)
  {
    if (isNumber(stream))
    {
      return parseNumber(stream);
    }
    else if (isId(stream))
    {
      return parseId(stream);
    }
    else if (isExpression(stream))
    {
      return parseExpression(stream);
    }
    else if (isQuoted(stream))
    {
      return parseQuoted(stream);
    }
    else if (isWhitespace(getStreamChar(stream)))
    {
      advanceStream(stream);
      continue;
    }
    else
    {
      throwError("any", "number or id or expression or quoted or whitespace", stream);
      return NULL;
    }
  }
}
