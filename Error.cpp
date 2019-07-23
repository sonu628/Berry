// Error.cpp
//

#include "Error.h"

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