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

/* Always use errors from this namespace */
extern char errorInLine[];
extern char tokenAfterQuote[];
extern char invalidLiteral[];
extern char invalidKeyword[];
extern char reservedValue[];
extern char symbolExists[];
extern char symbolMissing[];
} // namespace Error
