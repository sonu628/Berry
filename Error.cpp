// Error.cpp
//

#include "Error.h"

/* Built-in errors & warnings */
char Error::errorInLine[] = "Fatal L%d: %s.";
char Error::invalidFormatting[] = "Fatal: Invalid formatting: \"%s\".";
char Error::invalidLiteral[] =
    "Fatal: \"%s\" is invalid literal";
char Error::invalidKeyword[] =
    "Fatal: Invalid keyword \"%s\"";
char Error::noClosingQuote[] =
    "Fatal: No closing quote received.";
char Error::reservedValue[] =
    "Fatal: \"%s\" starts with reserved value";
char Error::symbolExists[] =
    "Fatal: \"%s\" already recorded";
char Error::symbolMissing[] =
    "Fatal: missing symbol \"%s\"";
char Error::tokenAfterQuote[] =
    "Fatal: Parsing token \"%s\" after closing quote";

void _Console::Write(const char *msg, ...) {
  std::array<char, 1024> buf{};

  va_list args;
  va_start(args, msg);
  vsnprintf(buf.data(), 1024, msg, args);
  va_end(args);

  std::cout << buf.data() << std::endl;
}

std::string Error::Format(const char *err, ...) {
  std::array<char, 1024> buf{};

  va_list args;
  va_start(args, err);
  vsnprintf(buf.data(), 1024, err, args);
  va_end(args);

  return std::string(buf.data());
}
