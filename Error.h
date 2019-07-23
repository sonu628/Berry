// Error.h
//

#pragma once

#include <array>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>

namespace _Console {
void Write(const char *msg, ...);
} // namespace _Console

namespace Error {
std::string Format(const char *err, ...);
} // namespace Error