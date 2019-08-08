// Error.cpp
//

#include "Error.h"

/* Built-in errors & warnings */
char Error::errorInLine[64] = "Fatal L%d: %s.";
char Error::tokenAfterQuote[64] =
    "Fatal: Parsing token \"%s\" after closing quote";
char Error::invalidLiteral[64] =
    "Fatal: \"%s\" is invalid literal";
char Error::invalidKeyword[64] =
    "Fatal: Invalid keyword \"%s\"";
char Error::reservedValue[64] =
    "Fatal: \"%s\" starts with reserved value";
char Error::symbolExists[64] =
    "Fatal: \"%s\" already recorded";
char Error::symbolMissing[64] =
    "Fatal: missing symbol \"%s\"";

void _Console::Write(const char *msg, ...) {
  std::array<char, 1024> buf;

  va_list args;
  va_start(args, msg);
  vsnprintf(buf.data(), 1024, msg, args);
  va_end(args);

  std::cout << buf.data() << std::endl;
}

std::string Error::Format(const char *err, ...) {
  std::array<char, 1024> buf;

  va_list args;
  va_start(args, err);
  vsnprintf(buf.data(), 1024, err, args);
  va_end(args);

  return std::string(buf.data());
}
