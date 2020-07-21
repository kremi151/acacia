//
// Created by Michel on 06.06.2020.
//

#ifndef ACACIA_MANUAL_ASSERTIONS_H
#define ACACIA_MANUAL_ASSERTIONS_H

#include <string>

void __acacia_fail(const std::string& message, const char *file, unsigned int line);

#define testFailure(message) \
__acacia_fail(message, __FILE__, __LINE__)

#endif //ACACIA_MANUAL_ASSERTIONS_H
