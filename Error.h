// Error.h
//

#pragma once

#include <array>
#include <iostream>
#include <cstdarg>
#include <cstdio>

namespace _Console {
void Write(const char *msg, ...);
} // namespace _Console

namespace Error {
std::string Format(const char *err, ...);

/* Always use errors from this namespace */
extern char errorInLine[];
extern char fileWrite[];
extern char invalidFormatting[];
extern char invalidLiteral[];
extern char invalidKeyword[];
extern char noClosingQuote[];
extern char reservedValue[];
extern char symbolExists[];
extern char symbolMissing[];
extern char tokenAfterQuote[];
} // namespace Error
