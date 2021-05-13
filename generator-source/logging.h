//
// Created by Michel on 13.05.2021.
//

#ifndef ACACIA_GEN_LOGGING_H
#define ACACIA_GEN_LOGGING_H

#include <cstdio>

// #define DEBUG_LOGGING

#ifdef DEBUG_LOGGING
#define fprintf_debug(p, s, ...) fprintf(p, s, __VA_ARGS__)
#else
#define fprintf_debug(p, s, ...) ((void) 0)
#endif

#define PRINT_BLUE "\033[0;34m"
#define PRINT_GREEN "\033[0;32m"
#define PRINT_RESET "\033[0m"

#endif //ACACIA_GEN_LOGGING_H
